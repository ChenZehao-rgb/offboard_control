#ifndef FOLLOWCABLE_H
#define FOLLOWCABLE_H

#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/PositionTarget.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/tf.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf/transform_listener.h>
#include <vector>
#include <yaml-cpp/yaml.h>

#include "offboard_control/SetTargetPoint.h"
#include "offboard_control/SetOffboardCtlType.h"
#include "offboard_control/SetPidGains.h"
#include "offboard_control/isUavArrived.h"
#include "offboard_control/StateControl.h"

class FollowCable{
public:
    FollowCable(const ros::NodeHandle& nh);
    ~FollowCable();
    void controlLoop(const ros::TimerEvent&);
    void setTargetPoint(const geometry_msgs::PoseStamped& targetPoint, uint8_t uavID);
    void setTargetPointRaw(const mavros_msgs::PositionTarget& targetPointRaw, uint8_t uavID);
    void setOffboardMode();
    void setArm();
    void setOffboardCtlType(int type);
    void setPidGains(int axis, double kp, double ki, double kd);
    void keyboardCallback(const std_msgs::String::ConstPtr& msg);

private:
    ros::NodeHandle nh_;
    ros::ServiceClient armingClient_; //解锁客户端
    ros::ServiceClient setModeClient_; //设置模式客户端

    ros::ServiceClient setPointClient_; //设置目标点客户端
    ros::ServiceClient setRawPointClient_; //设置目标点原始值客户端
    ros::ServiceClient setOffboardCtlTypeClient_; //设置控制模式客户端
    ros::ServiceClient setPidGainsClient_; //设置pid参数客户端
    ros::ServiceClient isUavArrivedClient_; //判断是否到达目标点客户端

    // 键盘输入
    ros::Subscriber keyboardSub_;
    // 订阅无人机本地位置
    ros::Subscriber uavPoseLocalSub_;

    // 控制状态机
    ros::Timer controlLoop_;
    // 控制状态
    offboard_control::StateControl stateControl_;

    // 无人机本地位置
    geometry_msgs::PoseStamped uavPoseLocal_;
    // 本地位置回调函数
    void uavPoseLocalCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
    // 判断是否到达目标点服务函数
    bool isUavArrived(const geometry_msgs::PoseStamped& targetPoint, uint8_t uavID, double precision);
    // 根据线结构传感器的测量结果，判断姿态调整是否到位
    bool isAjusted(const geometry_msgs::PoseStamped& cablePose);

    // 获取线传感器数据
    void getCablePose(const geometry_msgs::PoseStamped::ConstPtr& msg);
    // 上线操作中索道坐标->大小飞机坐标
    void onLineTarg2UavTarg(const geometry_msgs::PoseStamped& onLineTarg, geometry_msgs::PoseStamped& uavTarg1, geometry_msgs::PoseStamped& uavTarg2);
    // 根据线结构传感器的测量结果，得到大小飞机需要运动的相对位置/角度
    void cablePose2UavRalPose(const geometry_msgs::PoseStamped& cablePose, geometry_msgs::PoseStamped& uavRalPose1, geometry_msgs::PoseStamped& uavRalPose2);
    // 获取上线点标志位
    bool isGetOnlineTarg_;
    // 是否发送过上线点标志位
    bool isSendOnlineTarg_;
    // 是否到达上线点标志位
    bool isArrivedOnlineTarg_;
    // 获取大小飞机调整姿态点标志位
    bool isGetAjustPose_;
    // 爪子控制
    bool graspCable();
    bool releaseCable();
    // 采集信息
    bool storeCableInfo();
    // 坐标变换成员变量
    tf::TransformListener tfListener_;
    // 从yaml文件中读取参数
    std::vector<geometry_msgs::PoseStamped> loadWaypoints(const YAML::Node& node);
    // 示例采集点列表
    std::vector<geometry_msgs::PoseStamped> wayPoints_;
    // 跟踪索道点
    void followCablePoints(const std::vector<geometry_msgs::PoseStamped>& waypoints, uint8_t uavID);

};

#endif // FOLLOWCABLE_H