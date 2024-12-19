#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include "FollowCable.h"
//几种控制模式定义
#define GOTO_SETPOINT_STEP 0
#define GOTO_SETPOINT_CLOSED_LOOP 1
#define GOTO_SETPOINT_SMOOTH 2
#define GOTO_SETPOINT_RELATIVE 3
FollowCable::FollowCable(const ros::NodeHandle& nh) : nh_(nh), isGetOnlinePoint_(false), isSendOnlinePoint_(false)
{
    // 设置目标点客户端
    setPointClient_ = nh_.serviceClient<offboard_control::SetTargetPoint>("/offboard_control/set_target_point");
    // 设置目标点原始值客户端
    setRawPointClient_ = nh_.serviceClient<offboard_control::SetTargetPoint>("/offboard_control/set_raw_target_point");
    // 设置控制模式客户端
    setOffboardCtlTypeClient_ = nh_.serviceClient<offboard_control::SetOffboardCtlType>("/offboard_control/set_offboard_ctl_type");
    // 设置pid参数客户端
    setPidGainsClient_ = nh_.serviceClient<offboard_control::SetPidGains>("/offboard_control/set_pid_gains");
    // 判断是否到达目标点客户端
    isUavArrivedClient_ = nh_.serviceClient<offboard_control::isUavArrived>("/offboard_control/is_arrived");
    // 设置offboard和解锁客户端
    setUavTakeoffReadyClient_ = nh_.serviceClient<offboard_control::SetUavTakeoffReady>("/offboard_control/set_uav_takeoff_ready");
    // 键盘输入订阅
    keyboardSub_ = nh_.subscribe("/keyboard_input", 10, &FollowCable::keyboardCallback, this);
    // 无人机本地位置订阅
    uavPoseSub1_ = nh_.subscribe("uav1/mavros/local_position/pose", 10, &FollowCable::uavPoseLocalCallback1, this);
    uavPoseSub2_ = nh_.subscribe("uav2/mavros/local_position/pose", 10, &FollowCable::uavPoseLocalCallback2, this);
    // 无人机home位置订阅
    uavHomeSub1_ = nh_.subscribe("uav1/mavros/home_position/home", 10, &FollowCable::uavHomePoseCallback1, this);
    uavHomeSub2_ = nh_.subscribe("uav2/mavros/home_position/home", 10, &FollowCable::uavHomePoseCallback2, this);
    // 控制状态机
    controlLoop_ = nh_.createTimer(ros::Duration(controlPeriod), &FollowCable::controlLoop, this);
    // 初始化状态
    stateControl_.state_ctrl_type = offboard_control::StateControl::TAKEOFF;
    // 读取参数
    loadConfigParam("/home/chen/offboard_control/src/offboard_control/config/config.yaml");
    // 读取索道点
    wayPoints_ = loadWaypoints("/home/chen/offboard_control/src/offboard_control/config/waypoints.yaml");
    // 设置模式
    setOffboardCtlType(GOTO_SETPOINT_SMOOTH);
    // 大小无人机起飞
    setUavTakeoffReady(2);
    takeOffPoint2_= uavPoseGlobal2Local2(takeOffPoint2_);
    setTargetPoint(takeOffPoint2_,2);
    setUavTakeoffReady(1);
    takeOffPoint1_= uavPoseGlobal2Local1(takeOffPoint1_);
    setTargetPoint(takeOffPoint1_,1);

    testPoseTrans(); // 测试坐标转换
    
    // 假设cablePose数值
    cablePose_.pose.position.x = 0.0;
    cablePose_.pose.position.y = 0.0;
    cablePose_.pose.position.z = 0.0;
    cablePose_.pose.orientation.x = 0.0;
    cablePose_.pose.orientation.y = 0.0;
    cablePose_.pose.orientation.z = 0.0;
    cablePose_.pose.orientation.w = 1.0;
}

FollowCable::~FollowCable()
{
    // 在这里添加任何需要的清理代码
}
// 测试函数
void FollowCable::testPoseTrans()
{
    setOffboardCtlType(GOTO_SETPOINT_RELATIVE); // 设置相对位置控制模式
    // 延时10s,等待无人机起飞
    ros::Duration(10).sleep();
    // 测试全局坐标转换为本地坐标
    geometry_msgs::PoseStamped testPose;
    testPose.pose.position.x = 1.0;
    testPose.pose.position.y = 1.0;
    testPose.pose.position.z = 1.0;
    testPose.pose.orientation.x = 0.0;
    testPose.pose.orientation.y = 0.0;
    testPose.pose.orientation.z = 0.0;
    testPose.pose.orientation.w = 1.0;
    setTargetPoint(testPose,1);
    ROS_INFO_STREAM("testPoseTrans: " << testPose);
    while(1)
    {
        ros::spinOnce();
        ros::Rate(1).sleep();
        ROS_INFO_STREAM("uavPoseLocalSub1_: " << uavPoseLocalSub1_);
    }
}
// 线传感器数据处理,现假设是通过另一个节点发布的
void FollowCable::getCablePose(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    cablePose_ = *msg;
}
// 这里的全局坐标是在map中的坐标,因为无人机以起飞点为原点，需要将目标点转换到无人机坐标系下
geometry_msgs::PoseStamped FollowCable::uavPoseGlobal2Local1(const geometry_msgs::PoseStamped globalPose)
{
    // 将全局坐标转换为本地坐标
    geometry_msgs::PoseStamped localPose;
    localPose.pose.position.x = globalPose.pose.position.x - uavHomePoint1_.pose.position.x;
    localPose.pose.position.y = globalPose.pose.position.y - uavHomePoint1_.pose.position.y;
    localPose.pose.position.z = globalPose.pose.position.z;
    localPose.pose.orientation = globalPose.pose.orientation;
    return localPose;

}
geometry_msgs::PoseStamped FollowCable::uavPoseGlobal2Local2(const geometry_msgs::PoseStamped globalPose)
{
    // 将全局坐标转换为本地坐标
    geometry_msgs::PoseStamped localPose;
    localPose.pose.position.x = globalPose.pose.position.x - uavHomePoint2_.pose.position.x;
    localPose.pose.position.y = globalPose.pose.position.y - uavHomePoint2_.pose.position.y;
    localPose.pose.position.z = globalPose.pose.position.z;
    localPose.pose.orientation = globalPose.pose.orientation;
    return localPose;

}
// 跟随索道点无人机本地坐标处理
void FollowCable::wayPointsGlobal2Local(std::vector<geometry_msgs::PoseStamped> waypoints)
{
    for(auto& point : waypoints)
    {
        geometry_msgs::PoseStamped wayPointUav1, wayPointUav2;
        wayPointUav1 = uavPoseGlobal2Local1(point);
        wayPointsUav1_.push_back(wayPointUav1);
        wayPointUav2 = uavPoseGlobal2Local2(point);
        wayPointUav2.pose.position.z += rope_length;
        wayPointsUav2_.push_back(wayPointUav2);
    }
}
// 上线操作中索道坐标->大小飞机坐标，onlineTarg只得是通过雷达离线采点得到的全局坐标，包含x,y,z以及orientation
void FollowCable::onLineCablePoint2UavPoint(const geometry_msgs::PoseStamped& onLineCablePoint, geometry_msgs::PoseStamped& uavPoint1, geometry_msgs::PoseStamped& uavPoint2, double ral_high)
{
    // 小飞机坐标为索道坐标的上方，距离由携带爪子大小而定
    uavPoint1 = onLineCablePoint;
    uavPoint1.pose.position.z += ral_high; // 假设小飞机在索道上方0.5米处
    // 大飞机坐标为小飞机坐标的上方，距离由两者间连接绳的长度而定
    uavPoint2 = uavPoint1;
    uavPoint2.pose.position.z += rope_length;
}
// 根据线结构传感器的测量结果，得到大小飞机需要运动的相对位置/角度，cablePose为相机坐标系下的坐标，需要先转换到小无人机坐标系下，然后再转换到大无人机坐标系下，最后再计算大小无人机运动的相对位置/角度
void FollowCable::cablePose2UavRalPose(const geometry_msgs::PoseStamped& cablePose, geometry_msgs::PoseStamped& uavRalPose1, geometry_msgs::PoseStamped& uavRalPose2)
{
    // 假设cablePose数值
    uavRalPose1 = cablePose;
    uavRalPose2 = cablePose;
}

// 根据线结构传感器的测量结果，判断姿态调整是否到位
bool FollowCable::isAjusted(const geometry_msgs::PoseStamped& cablePose)
{
    // 计算角度差
    double yaw_diff = tf::getYaw(cablePose.pose.orientation) - tf::getYaw(uavPoseLocalSub1_.pose.orientation);
    if (fabs(yaw_diff) < 0.1)
    {
        return true;
    }
    return false;
}
// 判断是否到达目标点
bool FollowCable::isUavArrived(const geometry_msgs::PoseStamped& targetPoint, uint8_t uavID, double precision)
{
    offboard_control::isUavArrived isUavArrived;
    isUavArrived.request.targetPoint = targetPoint;
    isUavArrived.request.uavID = uavID;
    isUavArrived.request.precision = precision;
    if(isUavArrivedClient_.call(isUavArrived))
    {
        return isUavArrived.response.isArrived;
    }
    else
    {
        ROS_ERROR_STREAM("Failed to call isUavArrived service.");
        return false;
    }
}
// 控制爪子抓住索道
bool FollowCable::graspCable()
{
    // 控制指令

    //等待20s
    ROS_INFO_STREAM("Grasp cable...");
    ros::Duration(20).sleep();
    // 判断是否抓住索道
    return (1>0); // 某个值大于阈值
}
// 松开爪子
bool FollowCable::releaseCable()
{
    // 控制指令

    //等待20s
    ROS_INFO_STREAM("Release cable...");
    ros::Duration(20).sleep();
    // 判断是否松开索道
    return (1<0); // 某个值小于阈值
}
// 判断是否获取索道采集信息
bool FollowCable::storeCableInfo()
{
    // 控制指令

    //等待3s
    ROS_INFO_STREAM("Store cable info...");
    ros::Duration(3).sleep();
    // 判断是否获取索道采集信息
    return (1>0); // 某个值大于阈值
}
// 设置目标点
void FollowCable::setTargetPoint(const geometry_msgs::PoseStamped& targetPoint,uint8_t uavID)
{
    offboard_control::SetTargetPoint setTargetPoint;
    setTargetPoint.request.targetPoint = targetPoint;
    setTargetPoint.request.uavID = uavID;
    if(setPointClient_.call(setTargetPoint) && setTargetPoint.response.success)
    {
        ROS_INFO_STREAM("Set uav "<<uavID<<" target point success, x: "<<targetPoint.pose.position.x<<", y: "<<targetPoint.pose.position.y<<", z: "<<targetPoint.pose.position.z);
    }
    else
    {
        ROS_ERROR_STREAM("Set uav "<<uavID<<" target point failed");
    }
}
// 设置目标点原始值
void FollowCable::setTargetPointRaw(const mavros_msgs::PositionTarget& targetPointRaw, uint8_t uavID)
{
    offboard_control::SetTargetPoint setTargetPoint;
    setTargetPoint.request.targetPointRaw = targetPointRaw;
    setTargetPoint.request.uavID = uavID;
    if(setRawPointClient_.call(setTargetPoint) && setTargetPoint.response.success)
    {
        ROS_INFO_STREAM("Set uav "<<uavID<<" target point success");
    }
    else
    {
        ROS_ERROR_STREAM("Set uav "<<uavID<<" target point failed");
    }
}
// 设置无人机offboard和解锁
bool FollowCable::setUavTakeoffReady(uint8_t uavID)
{
    offboard_control::SetUavTakeoffReady setUavTakeoffReady;
    setUavTakeoffReady.request.uavID = uavID;
    if(setUavTakeoffReadyClient_.call(setUavTakeoffReady) && setUavTakeoffReady.response.armed && setUavTakeoffReady.response.offboard_enabled)
    {
        ROS_INFO_STREAM("Uav "<<uavID<<" takeoff ready");
    }
    else
    {
        ROS_ERROR_STREAM("Uav "<<uavID<<" takeoff failed");
    }
    return(setUavTakeoffReady.response.armed && setUavTakeoffReady.response.offboard_enabled);
}
// 设置控制模式
void FollowCable::setOffboardCtlType(uint8_t ctlType)
{
    offboard_control::SetOffboardCtlType setOffboardCtlType;
    setOffboardCtlType.request.offbCtlType = ctlType;
    if(setOffboardCtlTypeClient_.call(setOffboardCtlType) && setOffboardCtlType.response.success)
    {
        ROS_INFO_STREAM("Set control type success");
    }
    else
    {
        ROS_ERROR_STREAM("Set control type failed");
    }
}
// 指定无人机到达一系列目标点
void FollowCable::followCablePoints(const std::vector<geometry_msgs::PoseStamped>& waypoints)
{
    for (const auto& waypoint : waypoints)
    {
        geometry_msgs::PoseStamped wayPointUav1, wayPointUav2; // 定义无人机本地坐标系下的目标点
        // 大无人机坐标
        wayPointUav2 = uavPoseGlobal2Local2(waypoint);
        wayPointUav2.pose.position.z += rope_length;
        setTargetPoint(wayPointUav2, 2);
        // 小无人机坐标
        wayPointUav1 = uavPoseGlobal2Local1(waypoint);
        setTargetPoint(wayPointUav1, 1);
        // 等待到达每个目标点
        while (ros::ok())
        {
            ros::spinOnce();
            ros::Rate(1).sleep();
            // 检查是否到达目标点
            if (isUavArrived(wayPointUav2, 2, targetPointError1))
            {
                // 存储采集到的索道信息
                if(storeCableInfo()) 
                {
                    ROS_INFO_STREAM("Arrived waypoint: " << wayPointUav2 << ", get cable info ...");
                    break; // 跳出 while 循环，继续 for 循环的下一次迭代
                }
            }
        }
    }
}
// 状态机
void FollowCable::controlLoop(const ros::TimerEvent&)
{
    // 等待无人机起飞
    while(ros::ok() && stateControl_.state_ctrl_type == offboard_control::StateControl::TAKEOFF)
    { 
        // 如果大飞机到达起飞点，起飞成功
        if(isUavArrived(takeOffPoint2_,2,targetPointError2))
        {
            stateControl_.state_ctrl_type = offboard_control::StateControl::ARRIVE_ONLINE_POINT;
            ROS_INFO_STREAM("Takeoff success, and arrive online point...");
            break;
        }
        ROS_INFO_STREAM("Waiting for takeoff..., uavpose2: "<<uavPoseLocalSub2_);
        ros::Rate(1).sleep();
    }
    // 运动控制状态机逻辑
    switch (stateControl_.state_ctrl_type)
    {
        // 控制大小无人机均到达上线点
        case offboard_control::StateControl::ARRIVE_ONLINE_POINT:
        {
            // 获取上线坐标
            if(!isGetOnlinePoint_)
            {
                onLineCablePoint2UavPoint(onLinePoint_, onLinePoint1_, onLinePoint2_, onLinePoint_Z);
                // 从全局坐标转换到无人机本地坐标
                onLinePoint1_ = uavPoseGlobal2Local1(onLinePoint1_);
                onLinePoint2_ = uavPoseGlobal2Local2(onLinePoint2_);
                isGetOnlinePoint_ = true;

            }
            // 发送大飞机上线点
            if(!isSendOnlinePoint_)
            {
                setTargetPoint(onLinePoint2_,2);
                setTargetPoint(onLinePoint1_,1);
                isSendOnlinePoint_ = true;
            }
            // 判断小飞机是否到达onLineTarg1_
            if(isUavArrived(onLinePoint1_,1,targetPointError1))
            {
                stateControl_.state_ctrl_type = offboard_control::StateControl::AJUST_ATTITUDE;
                ROS_INFO_STREAM("Arrived on line point, and adjust attitude...");
                // 重置标志位
                isGetOnlinePoint_ = false;
                isSendOnlinePoint_ = false;
                isArrivedOnlinePoint_ = false;
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
                // 设置控制模式
                setOffboardCtlType(GOTO_SETPOINT_RELATIVE);
                // 发送大小飞机的相对pose
                setTargetPoint(uavRalPose1_,1);
                setTargetPoint(uavRalPose2_,2);
                isGetAjustPose_ = true;
            }
            // 通过获取线结构传感器的测量结果，判断大小飞机是否到达相对位置/角度
            if(isAjusted(cablePose_))
            {
                // 已经调整好位置，准备降落上线
                stateControl_.state_ctrl_type = offboard_control::StateControl::ON_LINE;
                ROS_INFO_STREAM("Ajust attitude success, and prepare to land on line...");
                setOffboardCtlType(GOTO_SETPOINT_SMOOTH);
                // setOffboardCtlType(GOTO_SETPOINT_STEP);
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
            // 获取上线坐标
            if(!isGetOnlinePoint_)
            {
                onLineCablePoint2UavPoint(onLinePoint_, onLinePoint1_, onLinePoint2_, 0);
                // 从全局坐标转换到无人机本地坐标
                onLinePoint1_ = uavPoseGlobal2Local1(onLinePoint1_);
                onLinePoint2_ = uavPoseGlobal2Local2(onLinePoint2_);
                isGetOnlinePoint_ = true;
                // 控制大飞机下降
                setTargetPoint(onLinePoint2_,2); // 降落过程可能需要根据线结构传感器的测量结果实时调整
                setTargetPoint(onLinePoint1_,1); // 小飞机目标位置是正好能抓住索道的位置
            }
            // 判断小飞机是否到达，判断范围根据线结构传感器的测量范围来定
            if(isUavArrived(onLinePoint1_,1,0.1))
            {
                // 控制爪子抓住索道
                if(graspCable())
                {
                    stateControl_.state_ctrl_type = offboard_control::StateControl::FOLLOW_CABLE;
                    ROS_INFO_STREAM("Grasp cable success, and follow cable...");
                }
                else
                {
                    ROS_ERROR_STREAM("Grasp cable failed.");
                    releaseCable(); // 释放索道
                    // 返回上线点上方，重新调整姿态后再次尝试上线
                    if(onLineFailCnt++ < 2) //上线失败次数小于2，即至多2次上线失败
                    {
                        stateControl_.state_ctrl_type = offboard_control::StateControl::ARRIVE_ONLINE_POINT;
                        // 修改上线点距索道的距离，比第一次低一些
                        onLinePoint_Z -= 0.5;
                        ROS_INFO_STREAM("Release cable success, and back to on line point...");
                    }
                    else
                    {
                        // 任务失败，返航
                        stateControl_.state_ctrl_type = offboard_control::StateControl::LAND;
                        ROS_ERROR_STREAM("Task failed, and return to home...");
                    }
                }
            }
            break;
        }
        case offboard_control::StateControl::FOLLOW_CABLE:
        {
            ROS_INFO("Following cable...");
            // 跟随索道，沿离线采集的点运动
            followCablePoints(wayPoints_);
            // 任务完成，返航
            stateControl_.state_ctrl_type = offboard_control::StateControl::LAND;
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
    // 开启回调
    // 使用多线程spinner
    ros::MultiThreadedSpinner spinner(2); // 2表示使用两个线程
    spinner.spin();
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
void FollowCable::uavPoseLocalCallback1(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    // 更新无人机本地位置
    uavPoseLocalSub1_ = *msg;
}
void FollowCable::uavPoseLocalCallback2(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    // 更新无人机本地位置
    uavPoseLocalSub2_ = *msg;
}
// 无人机home位置回调函数
void FollowCable::uavHomePoseCallback1(const mavros_msgs::HomePosition::ConstPtr& msg)
{
    // 更新无人机home位置
    uavHomePoseSub1_ = *msg;
}
void FollowCable::uavHomePoseCallback2(const mavros_msgs::HomePosition::ConstPtr& msg)
{
    // 更新无人机home位置
    uavHomePoseSub2_ = *msg;
}
// 从yaml文件中读取参数
std::vector<geometry_msgs::PoseStamped> FollowCable::loadWaypoints(const std::string& filename) {
    YAML::Node config = YAML::LoadFile(filename);
    std::vector<geometry_msgs::PoseStamped> waypoints;
    for (const auto& item : config["waypoints_set_1"]) {
        geometry_msgs::PoseStamped waypoint;
        waypoint.pose.position.x = item["position"]["x"].as<double>();
        waypoint.pose.position.y = item["position"]["y"].as<double>();
        waypoint.pose.position.z = item["position"]["z"].as<double>();
        waypoint.pose.orientation.x = item["orientation"]["x"].as<double>();
        waypoint.pose.orientation.y = item["orientation"]["y"].as<double>();
        waypoint.pose.orientation.z = item["orientation"]["z"].as<double>();
        waypoint.pose.orientation.w = item["orientation"]["w"].as<double>();
        waypoints.push_back(waypoint);
    }
    return waypoints;
}
// 从config.yaml文件中读取参数
void FollowCable::loadConfigParam(const std::string& filename)
{
    YAML::Node config = YAML::LoadFile(filename);
    // 读取uav1起飞点
    auto uav1 = config["takeoff_points"]["uav1"];
    takeOffPoint1_.pose.position.x = uav1["position_x"].as<double>();
    takeOffPoint1_.pose.position.y = uav1["position_y"].as<double>();
    takeOffPoint1_.pose.position.z = uav1["position_z"].as<double>();
    takeOffPoint1_.pose.orientation.x = uav1["orientation_x"].as<double>();
    takeOffPoint1_.pose.orientation.y = uav1["orientation_y"].as<double>();
    takeOffPoint1_.pose.orientation.z = uav1["orientation_z"].as<double>();
    takeOffPoint1_.pose.orientation.w = uav1["orientation_w"].as<double>();
    // 读取uav2起飞点
    auto uav2 = config["takeoff_points"]["uav2"];
    takeOffPoint2_.pose.position.x = uav2["position_x"].as<double>();
    takeOffPoint2_.pose.position.y = uav2["position_y"].as<double>();
    takeOffPoint2_.pose.position.z = uav2["position_z"].as<double>();
    takeOffPoint2_.pose.orientation.x = uav2["orientation_x"].as<double>();
    takeOffPoint2_.pose.orientation.y = uav2["orientation_y"].as<double>();
    takeOffPoint2_.pose.orientation.z = uav2["orientation_z"].as<double>();
    takeOffPoint2_.pose.orientation.w = uav2["orientation_w"].as<double>();
    // 读取索道上的上线点
    auto onLine = config["online_points"]["cable_point"];
    onLinePoint_.pose.position.x = onLine["position_x"].as<double>();
    onLinePoint_.pose.position.y = onLine["position_y"].as<double>();
    onLinePoint_.pose.position.z = onLine["position_z"].as<double>();
    onLinePoint_.pose.orientation.x = onLine["orientation_x"].as<double>();
    onLinePoint_.pose.orientation.y = onLine["orientation_y"].as<double>();
    onLinePoint_.pose.orientation.z = onLine["orientation_z"].as<double>();
    onLinePoint_.pose.orientation.w = onLine["orientation_w"].as<double>();
    // 读取小飞机携带爪子尺寸
    auto claw = config["size"]["claw"];
    claw_diameter = claw["diameter"].as<double>();
    // 读取连接绳长度
    auto rope = config["size"]["rope"];
    rope_length = rope["length"].as<double>();
    // 读取home_points
    auto home1 = config["home_points"]["uav1"];
    uavHomePoint1_.pose.position.x = home1["position_x"].as<double>();
    uavHomePoint1_.pose.position.y = home1["position_y"].as<double>();
    uavHomePoint1_.pose.position.z = home1["position_z"].as<double>();
    uavHomePoint1_.pose.orientation.x = home1["orientation_x"].as<double>();
    uavHomePoint1_.pose.orientation.y = home1["orientation_y"].as<double>();
    uavHomePoint1_.pose.orientation.z = home1["orientation_z"].as<double>();
    uavHomePoint1_.pose.orientation.w = home1["orientation_w"].as<double>();

    auto home2 = config["home_points"]["uav2"];
    uavHomePoint2_.pose.position.x = home2["position_x"].as<double>();
    uavHomePoint2_.pose.position.y = home2["position_y"].as<double>();
    uavHomePoint2_.pose.position.z = home2["position_z"].as<double>();
    uavHomePoint2_.pose.orientation.x = home2["orientation_x"].as<double>();
    uavHomePoint2_.pose.orientation.y = home2["orientation_y"].as<double>();
    uavHomePoint2_.pose.orientation.z = home2["orientation_z"].as<double>();
    uavHomePoint2_.pose.orientation.w = home2["orientation_w"].as<double>();

    // 打印读取到的参数
    ROS_INFO_STREAM("Takeoff point of uav1: " << takeOffPoint1_ << ", uav2: " << takeOffPoint2_);
    ROS_INFO_STREAM("Online point of cable: " << onLinePoint_);
    ROS_INFO_STREAM("Claw diameter: " << claw_diameter << ", rope length: " << rope_length);
    ROS_INFO_STREAM("Home point of uav1: " << uavHomePoint1_ << ", uav2: " << uavHomePoint2_);
}