#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include "FollowCable.h"

FollowCable::FollowCable(const ros::NodeHandle& nh) : nh_(nh)
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
}

FollowCable::~FollowCable()
{
    // 在这里添加任何需要的清理代码
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