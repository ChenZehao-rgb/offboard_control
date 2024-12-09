#include <ros/ros.h>
#include <std_msgs/String.h>
#include "OffboardCtl.h"

#define controlRate 20.0
#define controlPeriod (1.0 / controlRate)
// 构造函数
OffboardCtl::OffboardCtl(const ros::NodeHandle& nh) : nh_(nh)
{
    // 订阅无人机本地位置
    uavPoseLocalSub_ = nh_.subscribe("/mavros/local_position/pose", 1, &OffboardCtl::uavPoseLocalCallback, this);
    // 订阅无人机本地速度
    uavTwistLocalSub_ = nh_.subscribe("/mavros/local_position/velocity", 1, &OffboardCtl::uavTwistLocalCallback, this);
    // 订阅无人机本地加速度
    uavAccLocalSub_ = nh_.subscribe("/mavros/Local_position/accel", 1, &OffboardCtl::uavAccLocalCallback, this);

    // 发布无人机本地位置
    setpointLocalPub_ = nh_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local", 1);
    // 发布无人机本地原始位置
    setpointRawLocalPub_ = nh_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_raw/local", 1);
    // 发布无人机原始姿态
    setpointRawAttPub_ = nh_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_raw/attitude", 1);

    // 解锁服务
    armingClient_ = nh_.serviceClient<mavros_msgs::CommandBool>("/mavros/cmd/arming");
    // 设置模式服务
    setModeClient_ = nh_.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");

    // 设置目标位置服务
    setTargetPointSrv_ = nh_.advertiseService("offboard_control/set_target_point", &OffboardCtl::setTargetPoint, this);

    // 状态切换定时器
    stateSwitchTimer_ = nh_.createTimer(ros::Duration(controlPeriod), &OffboardCtl::stateSwitchTimerCallback, this);
}
OffboardCtl::~OffboardCtl()
{
    // 在这里添加任何需要的清理代码
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "offboard_control_node");
    ros::NodeHandle nh;

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
    // 创建 FollowCable 对象,创建了使用nh句柄的各种订阅、发布、服务等
    OffboardCtl followCable(nh);

    // 开启异步线程处理回调函数
    ros::AsyncSpinner spinner(6);
    spinner.start();

    ROS_INFO("OffboardCtl node has started.");
    // 循环等待回调函数，需要解决，回调函数的频率，为啥回调位置觉得这么慢
    ros::spin();

    return 0;
}

// 设置目标位置服务函数
bool OffboardCtl::setTargetPoint(offboard_control::SetTargetPoint::Request& req, offboard_control::SetTargetPoint::Response& res)
{
    targetPoint_ = req.targetPoint;
    res.success = true;
    // 打印目标位置
    ROS_INFO_STREAM("setTargetPoint: " << targetPoint_);
    return true;
}

// 回调函数
void OffboardCtl::uavPoseLocalCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    uavPoseLocal_ = *msg;
    // 打印无人机本地位置
    // ROS_INFO_STREAM("uavPoseLocalCallback: " << uavPoseLocal_);
}
void OffboardCtl::uavTwistLocalCallback(const geometry_msgs::TwistStamped::ConstPtr& msg)
{
    uavTwistLocal_ = *msg;
    // 打印无人机本地速度
    // ROS_INFO_STREAM("uavTwistLocalCallback: " << uavTwistLocal_);
}
void OffboardCtl::uavAccLocalCallback(const geometry_msgs::AccelWithCovarianceStamped::ConstPtr& msg)
{
    uavAccLocal_ = *msg;
    // 打印无人机本地加速度
    // ROS_INFO_STREAM("uavAccLocalCallback: " << uavAccLocal_);
}

//状态机
void OffboardCtl::stateSwitchTimerCallback(const ros::TimerEvent& event)
{
    
}