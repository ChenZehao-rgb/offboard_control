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
#include <tf/tf.h>

//自定义的服务类型
#include <offboard_control/SetTargetPoint.h>
#include <offboard_control/OffboardCtlType.h>
#include <offboard_control/SetOffboardCtlType.h>
#include <offboard_control/isUavArrived.h>
#include <offboard_control/SetPidGains.h>
#include <offboard_control/SetUavTakeoffReady.h>
#include <offboard_control/GenTrajOnline.h>
#include <ros/ros.h>
class OffboardCtl {
public:
    OffboardCtl(const ros::NodeHandle& nh);
    ~OffboardCtl();
private:
    ros::NodeHandle nh_; //在主函数中使用nh_(nh)，
    ros::Subscriber uavPoseLocalSub1_; //订阅无人机本地位置
    ros::Subscriber uavTwistLocalSub1_; //订阅无人机本地速度
    ros::Subscriber uavAccLocalSub1_; //订阅无人机本地加速度

    ros::Publisher setpointLocalPub1_; //发布无人机本地位置
    ros::Publisher setpointRawLocalPub1_; //发布无人机本地原始位置
    ros::Publisher setpointRawAttPub1_; //发布无人机原始姿态
    ros::Publisher setpointVelLocalPub1_; //发布无人机本地速度
    ros::ServiceClient armingClient1_; //解锁客户端
    ros::ServiceClient setModeClient1_; //设置模式客户端

    ros::Subscriber uavPoseLocalSub2_; //订阅无人机本地位置
    ros::Subscriber uavTwistLocalSub2_; //订阅无人机本地速度
    ros::Subscriber uavAccLocalSub2_; //订阅无人机本地加速度
    ros::Publisher setpointLocalPub2_; //发布无人机本地位置
    ros::Publisher setpointRawLocalPub2_; //发布无人机本地原始位置
    ros::Publisher setpointRawAttPub2_; //发布无人机原始姿态
    ros::Publisher setpointVelLocalPub2_; //发布无人机本地速度
    
    // 订阅小无人机在大无人机坐标系下的local坐标
    ros::Subscriber smallUavPoseInBigUavFrameSub_;

    ros::ServiceClient armingClient2_; //解锁客户端
    ros::ServiceClient setModeClient2_; //设置模式客户端

    ros::ServiceServer setTargetPointSrv_; //设置目标位置服务
    ros::ServiceServer setOffboardCtlTypeSrv_; //设置控制模式服务
    ros::ServiceServer setPidGainsSrv_; //动态调整pid参数服务
    ros::ServiceServer isUavArrivedSrv_; //判断无人机是否到点服务
    ros::ServiceServer setUavTakeoffReadySrv_; //设置offboard和解锁服务

    ros::ServiceClient trajGeneratorClient1_; //轨迹生成器客户端
    ros::ServiceClient trajGeneratorClient2_; //轨迹生成器客户端
    //状态切换定时器
    ros::Timer stateSwitchTimer_;
    void stateSwitchTimerCallback(const ros::TimerEvent& event);

    // 回调函数
    void uavPoseLocalCallback1(const geometry_msgs::PoseStamped::ConstPtr& msg);
    void uavTwistLocalCallback1(const geometry_msgs::TwistStamped::ConstPtr& msg);
    void uavAccLocalCallback1(const geometry_msgs::AccelWithCovarianceStamped::ConstPtr& msg);
    void uavPoseLocalCallback2(const geometry_msgs::PoseStamped::ConstPtr& msg);
    void uavTwistLocalCallback2(const geometry_msgs::TwistStamped::ConstPtr& msg);
    void uavAccLocalCallback2(const geometry_msgs::AccelWithCovarianceStamped::ConstPtr& msg);
    // 小无人机在大无人机坐标系下的local坐标回调函数
    void smallUavPoseInBigUavFrameCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
    // 小无人机在大无人机坐标系下的目标位置->小无人机在自己local坐标系下的目标位置
    geometry_msgs::PoseStamped uav1PoseInUav2FrameToUav1Frame(const geometry_msgs::PoseStamped& smallUavPoseInBigUavFrame);
    // 一开始读到的小无人机在大无人机坐标系下的local坐标
    geometry_msgs::PoseStamped smallUavPoseInBigUavFrameInit_;
    //定义的消息类型
    geometry_msgs::PoseStamped uavPoseLocal1_,uavPoseLocal2_; //订阅得到的无人机本地位置
    geometry_msgs::TwistStamped uavTwistLocal1_,uavTwistLocal2_; //订阅得到的无人机本地速度
    geometry_msgs::AccelWithCovarianceStamped uavAccLocal1_,uavAccLocal2_; //订阅得到的无人机本地加速度
    mavros_msgs::PositionTarget uavTargetPointRaw1_, uavTargetPointRaw2_; //平滑过渡设置的目标位置
    mavros_msgs::AttitudeTarget uavTargetAttRaw1_; // 小无人机单独控制
    //定义是否获得无人机目标位置
    bool isGetTargetPoint_;
    bool isUpdateTargetPoint_;
    // 是否获取初始化的小无人机在大无人机坐标系下的local坐标
    bool isGetSmallUavPoseInBigUavFrameInit_;
    geometry_msgs::PoseStamped uavTargetPoint1_,uavTargetPoint2_; //位置服务函数中设置的目标位置
    int offbCtlType_, preOffbCtlType; //控制模式服务函数中设置的控制模式
    
    //位置设置服务函数
    bool setTargetPoint(offboard_control::SetTargetPoint::Request& req, offboard_control::SetTargetPoint::Response& res);
    //控制模式设置服务函数
    bool setOffboardCtlType(offboard_control::SetOffboardCtlType::Request& req, offboard_control::SetOffboardCtlType::Response& res);
    // pid参数设置服务函数
    bool setPidGains(offboard_control::SetPidGains::Request& req, offboard_control::SetPidGains::Response& res);
    // 判断无人机是否到点服务函数
    bool isUavArrived(offboard_control::isUavArrived::Request& req, offboard_control::isUavArrived::Response& res);
    // 判断是否到达目标点
    bool isArrived(const geometry_msgs::PoseStamped& targetPoint, const geometry_msgs::PoseStamped& uavPoseLocal, double precision);
    // 设置offboard和解锁服务函数
    bool setUavTakeoffReady(offboard_control::SetUavTakeoffReady::Request& req, offboard_control::SetUavTakeoffReady::Response& res);
    // 获取平滑到点
    bool getTargetPointRawLocal1();
    bool getTargetPointRawLocal2();
    // 小无人机原始姿态控制
    mavros_msgs::AttitudeTarget smallUavTargetAttRaw(geometry_msgs::Quaternion orientation);
    // pid控制参数
    control_toolbox::Pid pidX_, pidY_, pidZ_, pidYaw_;
    // pid限幅
    double vz_max_;

    // 位置环pid控制
    mavros_msgs::PositionTarget positionCtl(geometry_msgs::PoseStamped targetPoint, geometry_msgs::PoseStamped uavPoseLocal, double vz_min, double vz_max);
    geometry_msgs::TwistStamped uavPoseToTwist(const geometry_msgs::PoseStamped& uavTargetPoint, geometry_msgs::PoseStamped& uavPoseLocal, double vz_min, double vz_max);
};

#endif // OFFBOARD_CTL_H