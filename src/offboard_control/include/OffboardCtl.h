#ifndef OFFBOARD_CTL_H
#define OFFBOARD_CTL_H

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/AccelWithCovarianceStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/PositionTarget.h>
#include <mavros_msgs/AttitudeTarget.h>
#include <control_toolbox/pid.h>

//自定义的服务类型
#include <offboard_control/SetTargetPoint.h>
#include <offboard_control/OffboardCtlType.h>
#include <offboard_control/SetOffboardCtlType.h>
#include <offboard_control/SetPidGains.h>
#include <ros/ros.h>
class OffboardCtl {
public:
    OffboardCtl(const ros::NodeHandle& nh);
    ~OffboardCtl();
    void positionCtl(geometry_msgs::PoseStamped targetPoint, geometry_msgs::PoseStamped uavPoseLocal);
private:
    ros::NodeHandle nh_; //在主函数中使用nh_(nh)，
    ros::Subscriber uavPoseLocalSub_; //订阅无人机本地位置
    ros::Subscriber uavTwistLocalSub_; //订阅无人机本地速度
    ros::Subscriber uavAccLocalSub_; //订阅无人机本地加速度

    ros::Publisher setpointLocalPub_; //发布无人机本地位置
    ros::Publisher setpointRawLocalPub_; //发布无人机本地原始位置
    ros::Publisher setpointRawAttPub_; //发布无人机原始姿态

    ros::ServiceServer setTargetPointSrv_; //设置目标位置服务
    ros::ServiceServer setOffboardCtlTypeSrv_; //设置控制模式服务
    ros::ServiceServer setPidGainsSrv_; //动态调整pid参数服务

    //状态切换定时器
    ros::Timer stateSwitchTimer_;
    void stateSwitchTimerCallback(const ros::TimerEvent& event);

    // 回调函数
    void uavPoseLocalCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
    void uavTwistLocalCallback(const geometry_msgs::TwistStamped::ConstPtr& msg);
    void uavAccLocalCallback(const geometry_msgs::AccelWithCovarianceStamped::ConstPtr& msg);

    //定义的消息类型
    geometry_msgs::PoseStamped uavPoseLocal_; //订阅得到的无人机本地位置
    geometry_msgs::TwistStamped uavTwistLocal_; //订阅得到的无人机本地速度
    geometry_msgs::AccelWithCovarianceStamped uavAccLocal_; //订阅得到的无人机本地加速度

    //定义是否获得无人机目标位置
    bool isGetTargetPoint_;
    
    geometry_msgs::PoseStamped targetPoint_; //位置服务函数中设置的目标位置
    int offbCtlType_; //控制模式服务函数中设置的控制模式
    
    //位置设置服务函数
    bool setTargetPoint(offboard_control::SetTargetPoint::Request& req, offboard_control::SetTargetPoint::Response& res);
    //控制模式设置服务函数
    bool setOffboardCtlType(offboard_control::SetOffboardCtlType::Request& req, offboard_control::SetOffboardCtlType::Response& res);
    // pid参数设置服务函数
    bool setPidGains(offboard_control::SetPidGains::Request& req, offboard_control::SetPidGains::Response& res);

    // pid控制参数
    control_toolbox::Pid pidX_, pidY_, pidZ_, pidYaw_;
    // 位置环pid控制
    
};

#endif // OFFBOARD_CTL_H