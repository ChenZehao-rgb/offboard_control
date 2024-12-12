#include <ros/ros.h>
#include <std_msgs/String.h>
#include "OffboardCtl.h"

#define controlRate 20.0
#define controlPeriod (1.0 / controlRate)
//几种控制模式定义
#define GOTO_SETPOINT_STEP 0
#define GOTO_SETPOINT_CLOSED_LOOP 1

// 构造函数
OffboardCtl::OffboardCtl(const ros::NodeHandle& nh)
    :nh_(nh),isGetTargetPoint_(false)
{
    // 订阅无人机本地位置
    uavPoseLocalSub_ = nh_.subscribe("/mavros/local_position/pose", 10, &OffboardCtl::uavPoseLocalCallback, this);
    // 订阅无人机本地速度
    uavTwistLocalSub_ = nh_.subscribe("/mavros/local_position/velocity", 10, &OffboardCtl::uavTwistLocalCallback, this);
    // 订阅无人机本地加速度
    uavAccLocalSub_ = nh_.subscribe("/mavros/Local_position/accel", 10, &OffboardCtl::uavAccLocalCallback, this);

    // 发布无人机本地位置
    setpointLocalPub_ = nh_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local", 10);
    // 发布无人机本地原始位置
    setpointRawLocalPub_ = nh_.advertise<mavros_msgs::PositionTarget>("/mavros/setpoint_raw/local", 10);
    // 发布无人机原始姿态
    setpointRawAttPub_ = nh_.advertise<mavros_msgs::AttitudeTarget>("/mavros/setpoint_raw/attitude", 10);

    // 设置目标位置服务
    setTargetPointSrv_ = nh_.advertiseService("offboard_control/set_target_point", &OffboardCtl::setTargetPoint, this);
    // 设置控制模式服务
    setOffboardCtlTypeSrv_ = nh_.advertiseService("offboard_control/set_offboard_ctl_type", &OffboardCtl::setOffboardCtlType, this);
    // 动态调整pid参数服务
    setPidGainsSrv_ = nh_.advertiseService("offboard_control/set_pid_gains", &OffboardCtl::setPidGains, this);
    // 状态切换定时器
    stateSwitchTimer_ = nh_.createTimer(ros::Duration(controlPeriod), &OffboardCtl::stateSwitchTimerCallback, this);

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

// 位置环pid控制
void OffboardCtl::positionCtl(geometry_msgs::PoseStamped targetPoint, geometry_msgs::PoseStamped uavPoseLocal)
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
    setpointRawLocalPub_.publish(positionTarget);

}
// 目标点平滑过渡控制

// 设置目标位置服务函数
bool OffboardCtl::setTargetPoint(offboard_control::SetTargetPoint::Request& req, offboard_control::SetTargetPoint::Response& res)
{
    targetPoint_ = req.targetPoint;
    res.success = true;
    // 设置目标位置成功
    isGetTargetPoint_ = true;
    // 打印目标位置
    ROS_INFO_STREAM("setTargetPoint: " << targetPoint_);
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
    //判断是否ok,通过isGetTargetPoint_，其为真，退出循环，可以进行下一步
    while(ros::ok()&&!isGetTargetPoint_)
    {   
        //打印信息
        ROS_INFO_STREAM("Waiting for target point...");
        //运行频率5hz
        ros::Rate(5).sleep();
        // 原理是因为offborad模式，需要无人机持续接收位置信息，如果没有接收到位置信息，无人机会自动降落
        setpointLocalPub_.publish(uavPoseLocal_); // 持续发布无人机当前位置，即静止状态的位置，防止arm失败
        
    }
    // 状态机开始运行
    switch (offbCtlType_)
    {
        case GOTO_SETPOINT_STEP:
        {
            targetPoint_.header.stamp = ros::Time::now(); //设置时间戳
            setpointLocalPub_.publish(targetPoint_); //发布目标位置
            //打印信息
            // ROS_INFO_STREAM("offboard_control::OffboardCtlType::GOTO_SETPOINT_STEP: " << targetPoint_);
            ROS_INFO_STREAM("offboard_control::OffboardCtlType::GOTO_SETPOINT_STEP: " << uavPoseLocal_);
            break;
        }
        // 在原定点控制外环加位置闭环
        case GOTO_SETPOINT_CLOSED_LOOP:
        {
            positionCtl(targetPoint_, uavPoseLocal_); //位置环pid控制
            //打印信息
            // ROS_INFO_STREAM("offboard_control::OffboardCtlType::GOTO_SETPOINT_CLOSED_LOOP: " << targetPoint_);
            ROS_INFO_STREAM("offboard_control::OffboardCtlType::GOTO_SETPOINT_CLOSED_LOOP: " << uavPoseLocal_);
            break;
        }
    
        default:
            break;
    }
    
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
    // 创建 OffboardCtl 对象,创建了使用nh句柄的各种订阅、发布、服务等
    OffboardCtl offboardctl(nh);

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