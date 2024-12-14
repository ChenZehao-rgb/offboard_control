#include <ros/ros.h>
#include <std_msgs/String.h>
#include "OffboardCtl.h"

#define controlRate 20.0
#define controlPeriod (1.0 / controlRate)
//几种控制模式定义
#define GOTO_SETPOINT_STEP 0
#define GOTO_SETPOINT_CLOSED_LOOP 1

// 构造函数
OffboardCtl::OffboardCtl(const std::string& nh1, const std::string& nh2) : nh1_(nh1), nh2_(nh2),isGetTargetPoint_(false)
{
    // 订阅无人机本地位置
    uavPoseLocalSub1_ = nh1_.subscribe("/mavros/local_position/pose", 10, &OffboardCtl::uavPoseLocalCallback1, this);
    uavPoseLocalSub2_ = nh2_.subscribe("/mavros/local_position/pose", 10, &OffboardCtl::uavPoseLocalCallback2, this);
    // 订阅无人机本地速度
    uavTwistLocalSub1_ = nh1_.subscribe("/mavros/local_position/velocity", 10, &OffboardCtl::uavTwistLocalCallback1, this);
    uavTwistLocalSub2_ = nh2_.subscribe("/mavros/local_position/velocity", 10, &OffboardCtl::uavTwistLocalCallback2, this);
    // 订阅无人机本地加速度
    uavAccLocalSub1_ = nh1_.subscribe("/mavros/Local_position/accel", 10, &OffboardCtl::uavAccLocalCallback1, this);
    uavAccLocalSub2_ = nh2_.subscribe("/mavros/Local_position/accel", 10, &OffboardCtl::uavAccLocalCallback2, this);

    // 发布无人机本地位置
    setpointLocalPub1_ = nh1_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local", 10);
    setpointLocalPub2_ = nh2_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local", 10);
    // 发布无人机本地原始位置
    setpointRawLocalPub1_ = nh1_.advertise<mavros_msgs::PositionTarget>("/mavros/setpoint_raw/local", 10);
    setpointRawLocalPub2_ = nh2_.advertise<mavros_msgs::PositionTarget>("/mavros/setpoint_raw/local", 10);
    // 发布无人机原始姿态
    setpointRawAttPub1_ = nh1_.advertise<mavros_msgs::AttitudeTarget>("/mavros/setpoint_raw/attitude", 10);
    setpointRawAttPub2_ = nh2_.advertise<mavros_msgs::AttitudeTarget>("/mavros/setpoint_raw/attitude", 10);

    /* 服务函数两无人机共用，使用大无人机uav2的句柄 */
    // 设置目标位置服务
    setTargetPointSrv_ = nh2_.advertiseService("offboard_control/set_target_point", &OffboardCtl::setTargetPoint, this);
    // 设置控制模式服务
    setOffboardCtlTypeSrv_ = nh2_.advertiseService("offboard_control/set_offboard_ctl_type", &OffboardCtl::setOffboardCtlType, this);
    // 动态调整pid参数服务
    setPidGainsSrv_ = nh2_.advertiseService("offboard_control/set_pid_gains", &OffboardCtl::setPidGains, this);
    // 判断无人机是否到点服务
    isUavArrivedSrv_ = nh2_.advertiseService("offboard_control/is_arrived", &OffboardCtl::isUavArrived, this);

    // 状态切换定时器
    stateSwitchTimer_ = nh2_.createTimer(ros::Duration(controlPeriod), &OffboardCtl::stateSwitchTimerCallback, this);

    // 初始化控制模式
    // offbCtlType_= GOTO_SETPOINT_STEP;
    offbCtlType_= GOTO_SETPOINT_CLOSED_LOOP;

    // 初始化pid控制器
    pidX_.initPid(1.0, 0.0, 0.1, 0.0, 0.0, 0);
    pidY_.initPid(1.0, 0.0, 0.1, 0.0, 0.0, 0);
    pidZ_.initPid(5.0, 0.0, 0.1, 0.0, 0.0, 0);
}
OffboardCtl::~OffboardCtl()
{
    // 在这里添加任何需要的清理代码
}

// 位置环pid控制 ,返回位置环控制量
mavros_msgs::PositionTarget OffboardCtl::positionCtl(geometry_msgs::PoseStamped targetPoint, geometry_msgs::PoseStamped uavPoseLocal)
{
    // 获取目标位置和当前位置
    double target_x = targetPoint.pose.position.x;
    double target_y = targetPoint.pose.position.y;
    double target_z = targetPoint.pose.position.z;
    double current_x = uavPoseLocal.pose.position.x;
    double current_y = uavPoseLocal.pose.position.y;
    double current_z = uavPoseLocal.pose.position.z;
    // 计算位置误差
    double error_x = target_x - current_x;
    double error_y = target_y - current_y;
    double error_z = target_z - current_z;
    // 计算位置环控制量
    double control_vx = pidX_.computeCommand(error_x, ros::Duration(controlPeriod));
    double control_vy = pidY_.computeCommand(error_y, ros::Duration(controlPeriod));
    double control_vz = pidZ_.computeCommand(error_z, ros::Duration(controlPeriod));
    // 发布位置环控制量
    mavros_msgs::PositionTarget positionTarget;
    positionTarget.header.stamp = ros::Time::now();
    positionTarget.coordinate_frame = mavros_msgs::PositionTarget::FRAME_LOCAL_NED;
    positionTarget.type_mask = mavros_msgs::PositionTarget::IGNORE_PX |
                                mavros_msgs::PositionTarget::IGNORE_PY |
                                mavros_msgs::PositionTarget::IGNORE_PZ |
                                mavros_msgs::PositionTarget::IGNORE_AFX |
                                mavros_msgs::PositionTarget::IGNORE_AFY |
                                mavros_msgs::PositionTarget::IGNORE_AFZ |
                                mavros_msgs::PositionTarget::IGNORE_YAW |
                                mavros_msgs::PositionTarget::IGNORE_YAW_RATE;
    positionTarget.velocity.x = control_vx;
    positionTarget.velocity.y = control_vy;
    positionTarget.velocity.z = control_vz;
    return positionTarget;
}
// 目标点平滑过渡控制

// 设置目标位置服务函数
bool OffboardCtl::setTargetPoint(offboard_control::SetTargetPoint::Request& req, offboard_control::SetTargetPoint::Response& res)
{
    // 判断uavID,赋值给两个无人机对应的目标位置
    switch (req.uavID)
    {
        case 1:
            uavTargetPoint1_ = req.targetPoint;
            ROS_INFO_STREAM("targetPointUav1_: " << uavTargetPoint1_);
            break;
        case 2:
            uavTargetPoint2_ = req.targetPoint;
            ROS_INFO_STREAM("targetPointUav2_: " << uavTargetPoint2_);
            break;
        default:
            ROS_ERROR_STREAM("uavID is not correct.");
            res.success = false;
            return false;
    }
    res.success = true;
    // 设置目标位置成功
    isGetTargetPoint_ = true;
    return true;
}

// 设置控制模式服务函数
bool OffboardCtl::setOffboardCtlType(offboard_control::SetOffboardCtlType::Request& req, offboard_control::SetOffboardCtlType::Response& res)
{
    offbCtlType_ = req.offbCtlType;
    res.success = true;
    // 打印控制模式
    ROS_INFO_STREAM("setOffboardCtlType: " << offbCtlType_);
    return true;
}

// pid参数设置服务函数
bool OffboardCtl::setPidGains(offboard_control::SetPidGains::Request& req, offboard_control::SetPidGains::Response& res)
{
    switch (req.pid_axis)
    {
        case 0:
            pidX_.setGains(req.kp, req.ki, req.kd, req.i_max, req.i_min);
            break;
        
        case 1:
            pidY_.setGains(req.kp, req.ki, req.kd, req.i_max, req.i_min);
            break;
        case 2:
            pidZ_.setGains(req.kp, req.ki, req.kd, req.i_max, req.i_min);
            break;
        default:
            break;
    }
    res.success = true;
    // 打印pid参数
    ROS_INFO_STREAM("setPidGains: " << req);
    return true;
}
// 判断无人机是否到点服务函数
bool OffboardCtl::isUavArrived(offboard_control::isUavArrived::Request& req, offboard_control::isUavArrived::Response& res)
{
    // 判断uavID,赋值给两个无人机对应的本地
    switch (req.uavID)
    {
        case 1:
            // req.targetPoint由客户端传入，判断是否到达目标点，是则将isArrived赋值为true，否则为false
            res.isArrived = isArrived(req.targetPoint, uavPoseLocal1_);
            break;
        case 2:
            res.isArrived = isArrived(req.targetPoint, uavPoseLocal2_);
            break;
        default:
            ROS_ERROR_STREAM("uavID is not correct.");
            res.isArrived = false;
            return false;
    }
    return true;
}
// 判断是否到达目标点
bool OffboardCtl::isArrived(const geometry_msgs::PoseStamped& targetPoint, const geometry_msgs::PoseStamped& uavPoseLocal)
{
    // 计算距离
    double distance = sqrt(pow(targetPoint.pose.position.x - uavPoseLocal.pose.position.x, 2) + 
                           pow(targetPoint.pose.position.y - uavPoseLocal.pose.position.y, 2) + 
                           pow(targetPoint.pose.position.z - uavPoseLocal.pose.position.z, 2));
    // 判断精度需要根据实际设置
    if (distance < 0.5)
    {
        return true;
    }
    return false;
}
// 回调函数
void OffboardCtl::uavPoseLocalCallback1(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    uavPoseLocal1_ = *msg;
    // 打印无人机本地位置
    // ROS_INFO_STREAM("uavPoseLocalCallback: " << uavPoseLocal_);
}
void OffboardCtl::uavPoseLocalCallback2(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    uavPoseLocal2_ = *msg;
    // 打印无人机本地位置
    // ROS_INFO_STREAM("uavPoseLocalCallback: " << uavPoseLocal_);
}
void OffboardCtl::uavTwistLocalCallback1(const geometry_msgs::TwistStamped::ConstPtr& msg)
{
    uavTwistLocal1_ = *msg;
    // 打印无人机本地速度
    // ROS_INFO_STREAM("uavTwistLocalCallback: " << uavTwistLocal_);
}
void OffboardCtl::uavTwistLocalCallback2(const geometry_msgs::TwistStamped::ConstPtr& msg)
{
    uavTwistLocal2_ = *msg;
    // 打印无人机本地速度
    // ROS_INFO_STREAM("uavTwistLocalCallback: " << uavTwistLocal_);
}
void OffboardCtl::uavAccLocalCallback1(const geometry_msgs::AccelWithCovarianceStamped::ConstPtr& msg)
{
    uavAccLocal1_ = *msg;
    // 打印无人机本地加速度
    // ROS_INFO_STREAM("uavAccLocalCallback: " << uavAccLocal_);
}
void OffboardCtl::uavAccLocalCallback2(const geometry_msgs::AccelWithCovarianceStamped::ConstPtr& msg)
{
    uavAccLocal2_ = *msg;
    // 打印无人机本地加速度
    // ROS_INFO_STREAM("uavAccLocalCallback: " << uavAccLocal_);
}

//状态机
void OffboardCtl::stateSwitchTimerCallback(const ros::TimerEvent& event)
{
    //判断是否ok,通过isGetTargetPoint_，其为真，退出循环，可以进行下一步
    while(ros::ok()&&!isGetTargetPoint_)
    {   
        //打印信息
        ROS_INFO_STREAM("Waiting for target point...");
        //运行频率20hz
        ros::Rate(20).sleep();
        // 原理是因为offborad模式，需要无人机持续接收位置信息，如果没有接收到位置信息，无人机会自动降落
        setpointLocalPub1_.publish(uavPoseLocal1_); // 持续发布无人机当前位置，即静止状态的位置，防止arm失败
        
    }
    // 状态机开始运行
    switch (offbCtlType_)
    {
        case GOTO_SETPOINT_STEP:
        {
            uavTargetPoint1_.header.stamp = ros::Time::now(); //设置时间戳
            setpointLocalPub1_.publish(uavTargetPoint1_); //发布目标位置
            //打印信息
            // ROS_INFO_STREAM("offboard_control::OffboardCtlType::GOTO_SETPOINT_STEP: " << targetPoint_);
            ROS_INFO_STREAM("offboard_control::OffboardCtlType::GOTO_SETPOINT_STEP: " << uavPoseLocal1_);
            break;
        }
        // 在原定点控制外环加位置闭环
        case GOTO_SETPOINT_CLOSED_LOOP:
        {
            positionCtl(uavTargetPoint1_, uavPoseLocal1_); //位置环pid控制
            //打印信息
            // ROS_INFO_STREAM("offboard_control::OffboardCtlType::GOTO_SETPOINT_CLOSED_LOOP: " << targetPoint_);
            ROS_INFO_STREAM("offboard_control::OffboardCtlType::GOTO_SETPOINT_CLOSED_LOOP: " << uavPoseLocal1_);
            break;
        }
    
        default:
            break;
    }
    
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "offboard_control_node");
    // 等待mavros
    ROS_INFO_STREAM("Waiting for mavros...");
    // 等待offboard模式  ？offboard模式应该如何设置，周期发送？不使用程序设置？
    if(!ros::service::waitForService("/mavros/set_mode", ros::Duration(10)))
    {
        ROS_ERROR_STREAM("Failed to start offboard mode.");
        return -1;
    }
    else
    {
        ROS_INFO_STREAM("Start offboard mode.");
    }
    // 等待解锁
    if(!ros::service::waitForService("/mavros/cmd/arming", ros::Duration(10)))
    {
        ROS_ERROR_STREAM("Failed to arm.");
        return -1;
    }
    else
    {
        ROS_INFO_STREAM("Arm success!");
    }
    // 创建 OffboardCtl 对象,创建了使用nh句柄的各种订阅、发布、服务等
    OffboardCtl offboardctl("uav1", "uav2");

    // 开启异步线程处理回调函数
    ros::MultiThreadedSpinner spinner(6);
    spinner.spin();

    ROS_INFO("OffboardCtl node has started.");

    //延时等待5s
    ros::Duration(5).sleep();
    // 循环等待回调函数，需要解决，回调函数的频率，为啥回调位置觉得这么慢
    ros::spin();

    return 0;
}