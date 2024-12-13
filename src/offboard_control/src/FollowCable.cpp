#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include "FollowCable.h"

// 状态机控制频率
#define controlRate 20.0
#define controlPeriod (1.0 / controlRate)
// 定义一些重要的点
geometry_msgs::PoseStamped takeOffTarg_; // 起飞点
geometry_msgs::PoseStamped onLineTarg_, onLineTarg1_, onLineTarg2_; // 索道上的上线点，小飞机的目标点，大飞机的目标点
// 线结构传感器的测量结果
geometry_msgs::PoseStamped cablePose_;
// 大小飞机运动的相对位姿点
geometry_msgs::PoseStamped uavRalPose1_, uavRalPose2_;

FollowCable::FollowCable(const ros::NodeHandle& nh) : nh_(nh), isGetOnlineTarg_(false), isSendOnlineTarg_(false), tfListener_(ros::Duration(10))
{
    // 解锁服务
    armingClient_ = nh_.serviceClient<mavros_msgs::CommandBool>("/mavros/cmd/arming");
    // 设置模式客户端
    setModeClient_ = nh_.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");
    // 设置目标点客户端
    setPointClient_ = nh_.serviceClient<offboard_control::SetTargetPoint>("/offboard_control/set_target_point");
    // 设置控制模式客户端
    setOffboardCtlTypeClient_ = nh_.serviceClient<offboard_control::SetOffboardCtlType>("/offboard_control/set_offboard_ctl_type");
    // 设置pid参数客户端
    setPidGainsClient_ = nh_.serviceClient<offboard_control::SetPidGains>("/offboard_control/set_pid_gains");
    // 键盘输入订阅
    keyboardSub_ = nh_.subscribe("/keyboard_input", 10, &FollowCable::keyboardCallback, this);
    // 无人机本地位置订阅
    uavPoseLocalSub_ = nh_.subscribe("/mavros/local_position/pose", 10, &FollowCable::uavPoseLocalCallback, this);
    // 控制状态机
    controlLoop_ = nh_.createTimer(ros::Duration(controlPeriod), &FollowCable::controlLoop, this);
    // 初始化状态
    stateControl_.state_ctrl_type = offboard_control::StateControl::TAKEOFF;
}

FollowCable::~FollowCable()
{
    // 在这里添加任何需要的清理代码
}
// 线传感器数据处理,现假设是通过另一个节点发布的
void FollowCable::getCablePose(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    cablePose_ = *msg;
}
// 上线操作中索道坐标->大小飞机坐标，onlineTarg只得是通过雷达离线采点得到的全局坐标，包含x,y,z以及orientation
void FollowCable::onLineTarg2UavTarg(const geometry_msgs::PoseStamped& onLineTarg, geometry_msgs::PoseStamped& uavTarg1, geometry_msgs::PoseStamped& uavTarg2)
{
    // 小飞机坐标为索道坐标的上方，距离由携带爪子大小而定
    uavTarg1 = onLineTarg;
    uavTarg1.pose.position.z += 1.0;
    // 大飞机坐标为小飞机坐标的上方，距离由两者间连接绳的长度而定
    uavTarg2 = uavTarg1;
    uavTarg2.pose.position.z += 1.0;
    
}
// 根据线结构传感器的测量结果，得到大小飞机需要运动的相对位置/角度，cablePose为相机坐标系下的坐标，需要先转换到小无人机坐标系下，然后再转换到大无人机坐标系下，最后再计算大小无人机运动的相对位置/角度
void FollowCable::cablePose2UavRalPose(const geometry_msgs::PoseStamped& cablePose, geometry_msgs::PoseStamped& uavRalPose1, geometry_msgs::PoseStamped& uavRalPose2)
{
    // 将cablePose转换到小飞机坐标系下
    geometry_msgs::PoseStamped cablePoseInUav1Frame;
    try
    {
        tfListener_.transformPose("uav1_frame", cablePose, cablePoseInUav1Frame);
    }
    catch (tf::TransformException& ex)
    {
        ROS_ERROR("Transform error: %s", ex.what());
        return;
    }

    // 计算小无人机的目标位置和姿态
    uavRalPose1 = cablePoseInUav1Frame;
    uavRalPose1.pose.position.z += 1.0; // 假设小飞机在索道上方1米处

    // 3. 将小无人机的目标位置转换到大无人机坐标系下
    geometry_msgs::PoseStamped uavRalPose1InUav2Frame;
    try
    {
        tfListener_.transformPose("uav2_frame", uavRalPose1, uavRalPose1InUav2Frame);
    }
    catch (tf::TransformException& ex)
    {
        ROS_ERROR("Transform error: %s", ex.what());
        return;
    }

    // 计算大无人机的目标位置和姿态
    uavRalPose2 = uavRalPose1InUav2Frame;
    uavRalPose2.pose.position.z += 1.0; // 假设大飞机在小飞机上方1米处

    // 考虑大小飞机的 yaw 角度偏差
    double yaw_offset = tf::getYaw(uavRalPose1.pose.orientation) - tf::getYaw(uavPoseLocal_.pose.orientation);
    tf::Quaternion q;
    q.setRPY(0, 0, yaw_offset);
    tf::quaternionTFToMsg(q, uavRalPose2.pose.orientation);
}
// 判断是否到达目标点
bool FollowCable::isArrived(const geometry_msgs::PoseStamped& targetPoint)
{
    // 计算距离
    double distance = sqrt(pow(targetPoint.pose.position.x - uavPoseLocal_.pose.position.x, 2) + 
                           pow(targetPoint.pose.position.y - uavPoseLocal_.pose.position.y, 2) + 
                           pow(targetPoint.pose.position.z - uavPoseLocal_.pose.position.z, 2));
    if (distance < 0.5)
    {
        return true;
    }
    return false;
}
// 根据线结构传感器的测量结果，判断姿态调整是否到位
bool FollowCable::isAjusted(const geometry_msgs::PoseStamped& cablePose)
{
    // 计算角度差
    double yaw_diff = tf::getYaw(cablePose.pose.orientation) - tf::getYaw(uavPoseLocal_.pose.orientation);
    if (fabs(yaw_diff) < 0.1)
    {
        return true;
    }
    return false;
}
void FollowCable::controlLoop(const ros::TimerEvent&)
{
    // 等待无人机起飞
    while(ros::ok() && stateControl_.state_ctrl_type == offboard_control::StateControl::TAKEOFF)
    {
        // 通过当前位置信息以及offboard模式，判断无人机是否起飞
        if(isArrived(takeOffTarg_))
        {
            stateControl_.state_ctrl_type = offboard_control::StateControl::ON_LINE;
        }
        ROS_INFO_STREAM("Waiting for takeoff...");
        ros::Rate(5).sleep();
    }
    // 运动控制状态机逻辑
    ROS_INFO("Running control loop...");
    switch (stateControl_.state_ctrl_type)
    {
        // 控制大小无人机均到达上线点
        case offboard_control::StateControl::ARRIVE_ONLINE_POINT:
        {
            // 获取上线坐标
            if(!isGetOnlineTarg_)
            {
                // 已知onLineTarg_是索道上的上线点，全局位置，包含x,y,z
                // 根据onLineTarg_的位置，获取小飞机和大飞机的目标点，onLineTarg1_和onLineTarg2_，均是全局位置，包含x,y,z
                onLineTarg2UavTarg(onLineTarg_, onLineTarg1_, onLineTarg2_);
                isGetOnlineTarg_ = true;
            }
            // 发送大飞机上线点
            if(!isSendOnlineTarg_)
            {
                setTargetPoint(onLineTarg2_);
                isSendOnlineTarg_ = true;
            }
            // 判断大飞机是否到达上线点,当大飞机到达上线点时且是否到达上线点标志位为false时，控制小飞机到达onLineTarg1_
            if(isArrived(onLineTarg2_)&&!isArrivedOnlineTarg_)
            {
                setTargetPoint(onLineTarg1_);
                isArrivedOnlineTarg_ = true;
            }
            // 判断小飞机是否到达onLineTarg1_
            if(isArrived(onLineTarg1_))
            {
                stateControl_.state_ctrl_type = offboard_control::StateControl::AJUST_ATTITUDE;
                ROS_INFO_STREAM("Arrived on line point, and adjust attitude...");
            }
            break;
        }
        // 当大小飞机都到点后，执行调整姿态
        case offboard_control::StateControl::AJUST_ATTITUDE:
        {
            // 根据传感器获取大小飞机需要运动的相对位置/角度
            if(!isGetAjustPose_)
            {
                // 已知cablePose_是线结构传感器的测量结果，包含相对于小飞机的x,y,z,orientation
                // 根据cablePose_的位置和角度，得到大小飞机需要运动的相对位置/角度，uavRalPose1_和uavRalPose2_，均是相对位置，包含x,y,z,orientation
                cablePose2UavRalPose(cablePose_, uavRalPose1_, uavRalPose2_);
                // 发送大小飞机的相对pose
                setTargetPoint(uavRalPose1_);
                setTargetPoint(uavRalPose2_);
                isGetAjustPose_ = true;
            }
            // 通过获取线结构传感器的测量结果，判断大小飞机是否到达相对位置/角度
            if(isAjusted(cablePose_))
            {
                // 已经调整好位置，准备降落上线
                stateControl_.state_ctrl_type = offboard_control::StateControl::ON_LINE;
                ROS_INFO_STREAM("Ajust attitude success, and prepare to land on line...");
            }
            else
            {
                // 未调整好位置，继续调整
                isGetAjustPose_ = false; // 重新获取大小飞机需要运动的相对位置/角度
            }
            break;
        }
        // 大小无人机上线操作
        case offboard_control::StateControl::ON_LINE:
        {
            
            // 控制大飞机到达onLineTarg2_
            setTargetPoint(onLineTarg2_); // 需要在offboardCtl中新建一个模式，即到点前需要减速，尽量让大飞机到点后，小飞机也能很快稳定在onLineTarg1_上,或者可以同时发送大小飞机的目标点
            // 判断大飞机是否到达onLineTarg2_，判断范围根据线结构传感器的测量范围来定
            if(isArrived(onLineTarg2_))
            {
                

                // 大飞机降落，到达小飞机能抓住的位置

                // 小飞机抓

                stateControl_.state_ctrl_type = offboard_control::StateControl::FOLLOW_CABLE;
            }
            ROS_INFO("Following line...");
            break;
        }
        case offboard_control::StateControl::FOLLOW_CABLE:
        {
            // 跟随电缆
            ROS_INFO("Following cable...");
            break;
        }
        case offboard_control::StateControl::APPROACH_NODE:
        {
            // 靠近节点
            ROS_INFO("Approaching node...");
            break;
        }
        case offboard_control::StateControl::CROSS_NODE:
        {
            // 跨越节点
            ROS_INFO("Crossing node...");
            break;
        }
        case offboard_control::StateControl::LAND:
        {
            // 降落
            ROS_INFO("Landing...");
            break;
        }
        default:
            break;
    }
    
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "follow_cable");
    ros::NodeHandle nh;
    FollowCable followCable(nh);
    followCable.setArm(); // 解锁
    followCable.setOffboardMode(); // 设置模式
    // 目标点位置信息
    geometry_msgs::PoseStamped targetPoint;
    targetPoint.pose.position.x = 0;
    targetPoint.pose.position.y = 0;
    targetPoint.pose.position.z = 5;
    followCable.setTargetPoint(targetPoint); // 设置目标点
    
    
    // 开启回调
    ros::spin();
    return 0;
}
// 键盘输入回调函数，键盘输入的数据应该是mode 0/1或者pid 0/1/2 kp ki kd
void FollowCable::keyboardCallback(const std_msgs::String::ConstPtr& msg)
{
    std::istringstream iss(msg->data);
    std::string command;
    iss >> command;

    if (command == "mode")
    {
        int mode;
        iss >> mode;
        offboard_control::SetOffboardCtlType setOffboardCtlType;
        setOffboardCtlType.request.offbCtlType = mode;
        if (setOffboardCtlTypeClient_.call(setOffboardCtlType) && setOffboardCtlType.response.success)
        {
            ROS_INFO_STREAM("Set control mode to " << mode << " success");
        }
        else
        {
            ROS_ERROR_STREAM("Failed to set control mode to " << mode);
        }
    }
    else if (command == "pid")
    {
        int axis;
        double kp, ki, kd;
        iss >> axis >> kp >> ki >> kd;
        offboard_control::SetPidGains setPidGains;
        setPidGains.request.pid_axis = axis;
        setPidGains.request.kp = kp;
        setPidGains.request.ki = ki;
        setPidGains.request.kd = kd;
        setPidGains.request.i_max = 0;
        setPidGains.request.i_min = 0;
        if (setPidGainsClient_.call(setPidGains) && setPidGains.response.success)
        {
            ROS_INFO_STREAM("Set PID gains for axis " << axis << " success");
        }
        else
        {
            ROS_ERROR_STREAM("Failed to set PID gains for axis " << axis);
        }
    }
}
// 无人机本地位置回调函数
void FollowCable::uavPoseLocalCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    // 更新无人机本地位置
    uavPoseLocal_ = *msg;
}
// 设置目标点
void FollowCable::setTargetPoint(const geometry_msgs::PoseStamped& targetPoint)
{
    offboard_control::SetTargetPoint setTargetPoint;
    setTargetPoint.request.targetPoint = targetPoint;
    if(setPointClient_.call(setTargetPoint) && setTargetPoint.response.success)
    {
        ROS_INFO_STREAM("Set target point success");
    }
    else
    {
        ROS_ERROR_STREAM("Set target point failed");
    }
}

void FollowCable::setOffboardMode()
{
    // 设置模式
    mavros_msgs::SetMode offb_set_mode;
    offb_set_mode.request.custom_mode = "OFFBOARD";
    if(setModeClient_.call(offb_set_mode) && offb_set_mode.response.mode_sent)
    {
        ROS_INFO_STREAM("Offboard enabled");
    }
    else
    {
        ROS_ERROR_STREAM("Offboard enable failed");
    }
}

void FollowCable::setArm()
{
    // 解锁
    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;
    if(armingClient_.call(arm_cmd) && arm_cmd.response.success)
    {
        ROS_INFO_STREAM("Vehicle armed");
    }
    else
    {
        ROS_ERROR_STREAM("Arming failed");
    }
}