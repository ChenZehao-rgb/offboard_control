#ifndef FOLLOWCABLE_H
#define FOLLOWCABLE_H

#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/PositionTarget.h>
#include <geometry_msgs/PoseStamped.h>
#include <geographic_msgs/GeoPoint.h>
#include <geographic_msgs/GeoPoseStamped.h>
#include <mavros_msgs/HomePosition.h>
#include <tf/tf.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>
#include <std_msgs/String.h> // 确保包含了正确的头文件
#include <vector>
#include <yaml-cpp/yaml.h>
#include <map>

#include "offboard_control/SetTargetPoint.h"
#include "offboard_control/SetOffboardCtlType.h"
#include "offboard_control/SetPidGains.h"
#include "offboard_control/isUavArrived.h"
#include "offboard_control/StateControl.h"
#include "offboard_control/SetUavTakeoffReady.h"
#include <offboard_control/Status.h>
#include <offboard_control/Measure.h>
#include <offboard_control/cameraControl.h>

class FollowCable{
public:
    FollowCable(const ros::NodeHandle& nh);
    ~FollowCable();
private:
    /******************** ROS头定义 **********************/
    ros::NodeHandle nh_;

    ros::ServiceClient setPointClient_; //设置目标点客户端
    ros::ServiceClient setRawPointClient_; //设置目标点原始值客户端
    ros::ServiceClient setOffboardCtlTypeClient_; //设置控制模式客户端
    ros::ServiceClient setPidGainsClient_; //设置pid参数客户端
    ros::ServiceClient isUavArrivedClient_; //判断是否到达目标点客户端
    ros::ServiceClient setUavTakeoffReadyClient_; //设置offboard和解锁客户端
    ros::ServiceClient setUavReturnClient1_;
    ros::ServiceClient setUavReturnClient2_;
    ros::ServiceClient setCameraControlClient_;
    // 键盘输入
    ros::Subscriber keyboardSub_;
    // 订阅无人机本地位置
    ros::Subscriber uavPoseSub1_;
    ros::Subscriber uavPoseSub2_;
    // 订阅小无人机本地速度
    ros::Subscriber uavVelSub1_;
    // 订阅无人机home位置
    ros::Subscriber uavHomeSub1_;
    ros::Subscriber uavHomeSub2_;
    // 订阅小无人机在大无人机坐标系下的local坐标
    ros::Subscriber smallUavPoseInBigUavFrameSub_;
    // 订阅由小无人机相对坐标转换得到的大无人机目标位置
    ros::Subscriber bigUavTargetPoseSub_;
    // 订阅传感器数据
    ros::Subscriber sensorDateSub_;
    // 发布无人机转换坐标后的本地位置
    ros::Publisher uavPoseGlobalPub1_;
    ros::Publisher uavPoseGlobalPub2_;
    // publish the topic of control sensor switch
    ros::Publisher controlSensorSwitchPub_;
    // 发布状态机控制状态
    ros::Publisher status_pub_;
    // 控制状态机
    ros::Timer controlLoop_, statusPubTimer_;
    /******************** 使用变量定义 **********************/
    // 状态机控制频率
    #define controlRate 5.0
    #define controlPeriod (1.0 / controlRate)
    // 状态机控制状态
    offboard_control::StateControl stateControl_, previousStateControl_, nextStateControl_;
    std::string preStateControlStr_;
    // mavros订阅本地位置
    geometry_msgs::PoseStamped uavPoseLocalSub1_;
    geometry_msgs::PoseStamped uavPoseLocalSub2_;
    // mavros订阅本地速度
    geometry_msgs::TwistStamped uavVelLocalSub1_;
    // mavros订阅home位置
    mavros_msgs::HomePosition uavHomePoseSub1_;
    mavros_msgs::HomePosition uavHomePoseSub2_;
    // 转换后的无人机本地位置
    geometry_msgs::PoseStamped uavPoseGlobal1_, uavPoseGlobal2_;
    // 无人机相关参数
    geometry_msgs::PoseStamped takeOffPoint1_, takeOffPoint2_; // 起飞点
    geometry_msgs::PoseStamped uavHomePoint1_, uavHomePoint2_; // 无人机home点
    geometry_msgs::PoseStamped onLinePoint1_, onLinePoint2_; // 小飞机的上线目标点，大飞机的上线目标点
    geometry_msgs::PoseStamped crossPoint_; // 越过节点的目标点，主要是大无人机高度
    std::vector<geometry_msgs::PoseStamped> cablePoints_; // 索道上的上线点
    double claw_diameter, rope_length; // 爪子直径，大小无人机连接绳长度
    double onLinePoint_Z; // 小飞机相对索道上线点的高度
    int onLineFailCnt = 0; // 上线失败计数
    geometry_msgs::PoseStamped smallUavPoseInBigUavFrame_, bigUavTargetPose_; // 小无人机在大无人机坐标系下的local坐标，大无人机目标位置
    double targetPointError1, targetPointError2, stableVelError1; // 目标点误差,设置两种精度的，只有达到这个精度，才认为到达目标点
    offboard_control::Measure sensorDate_; // 传感器测量的索道位置
    // 沿索道运动目标点
    std::vector<std::vector<geometry_msgs::PoseStamped>> all_waypoints_;
    // 上线状态机中的目标点
    geometry_msgs::PoseStamped targetPointInOnLineState_;
    /******************** 状态机运行中的标志位 **********************/
    // 上线操作中的标志位
    bool isGetOnlinePoint_; // 获取上线点标志位
    bool isSendOnlinePoint_; // 是否发送过上线点标志位
    bool isArrivedOnlinePoint_; // 是否到达上线点标志位
    bool isGetAjustPose_; // 获取大小飞机调整姿态点标志位
    bool isGetCrossPoint_; // 获取越过节点点标志位
    // 接收到外部指令标志位
    bool isGetCommand_;
    // 是否发送状态切换
    bool isSendStateChange_;
    /******************** 函数定义 **********************/
    // 本地位置回调函数
    void uavPoseLocalCallback1(const geometry_msgs::PoseStamped::ConstPtr& msg);
    void uavPoseLocalCallback2(const geometry_msgs::PoseStamped::ConstPtr& msg);
    // 本地速度回调函数
    void uavVelLocalCallback1(const geometry_msgs::TwistStamped::ConstPtr& msg);
    // home位置回调函数
    void uavHomePoseCallback1(const mavros_msgs::HomePosition::ConstPtr& msg);
    void uavHomePoseCallback2(const mavros_msgs::HomePosition::ConstPtr& msg);
    // 小无人机在大无人机坐标系下的local坐标回调函数
    void smallUavPoseInBigUavFrameCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
    // 由小无人机相对坐标转换得到的大无人机目标位置回调函数
    void bigUavTargetPoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
    // 客户端服务函数
    bool isUavArrived(const geometry_msgs::PoseStamped& targetPoint, uint8_t uavID, double precision); // 判断是否到达目标点服务函数
    void setTargetPoint(const geometry_msgs::PoseStamped& targetPoint, uint8_t uavID); // 设置目标点服务函数
    bool setUavTakeoffReady(uint8_t uavID); // 设置offboard和解锁函数
    void setOffboardCtlType(uint8_t ctlType); // 设置控制模式服务函数
    // 根据线结构传感器的测量结果，判断姿态调整是否到位
    bool isAjusted(const geometry_msgs::PoseStamped& cablePose);
    // 获取线传感器数据
    void getCablePose(const offboard_control::Measure::ConstPtr& msg);
    // 上线操作中索道坐标->大小飞机坐标
    void onLineCablePoint2UavPoint(const geometry_msgs::PoseStamped& onLineCablePoint, geometry_msgs::PoseStamped& uavPoint1, geometry_msgs::PoseStamped& uavPoint2, double ral_high);
    void onLineCableHight2UavHight(const geometry_msgs::PoseStamped& onLineCablePoint, geometry_msgs::PoseStamped& uavPoint1, geometry_msgs::PoseStamped& uavPoint2, double ral_high);
    // 根据线结构传感器的测量结果，得到大小飞机需要运动的相对位置/角度
    void cablePose2UavRalPose(const geometry_msgs::PoseStamped& cablePose, geometry_msgs::PoseStamped& uavRalPose1, geometry_msgs::PoseStamped& uavRalPose2);
    // 爪子控制
    bool graspCable();
    bool releaseCable();
    // 采集信息
    bool storeCableInfo();
    // 从yaml文件中读取参数
    // 读取无人机初始化参数
    void loadConfigParam(const std::string& filename);
    std::vector<std::vector<geometry_msgs::PoseStamped>> loadWaypoints(const std::string& filename);
    void readParameters(ros::NodeHandle& nh);
    // 跟踪索道点
    void followCablePoints(std::vector<geometry_msgs::PoseStamped> &waypoints);

    void controlLoop(const ros::TimerEvent&);

    void setPidGains(double vz_max);
    void keyboardCallback(const std_msgs::String::ConstPtr& msg);
    // 接收外部节点指令
    void waitForCommand();
    // 发布状态信息
    void publishStatus(const ros::TimerEvent&);
    // 测试坐标转换以及运动模式
    void testPoseTrans();
    // 上线过程状态机定义
    enum State
    {
        DESCEND,
        CHECK_SENSOR,
        ADJUST_Y_POSITION
    };
    State onLinestate = DESCEND;
    bool adjustTargetPoint();
    double judgeSensorZ(double sensor_z, double local_z);
    // 根据当前小飞机线速度判断是否稳定
    bool isUav1Stable(double VelError);
    void sendStartMeasureCommand();
    void sendEndMeasureCommand();
    double smallUav_y, smallUav_z;
    std::vector<float> descendHeight;
    void loadDescendHeight(ros::NodeHandle& nh);
    void sendCameraControlCommand(int command);
};

#endif // FOLLOWCABLE_H