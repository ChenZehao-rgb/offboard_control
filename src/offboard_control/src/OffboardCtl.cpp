#include <ros/ros.h>
#include <std_msgs/String.h>
#include "OffboardCtl.h"

#define controlRate 20.0
#define controlPeriod (1.0 / controlRate)
//几种控制模式定义
#define GOTO_SETPOINT_STEP 0
#define GOTO_SETPOINT_CLOSED_LOOP 1
#define GOTO_SETPOINT_SMOOTH 2
#define GOTO_SETPOINT_ACTUAL 3

void quat2RPY(const geometry_msgs::Quaternion &quat, double &roll,
              double &pitch, double &yaw) {
  tf::Quaternion q(quat.x, quat.y, quat.z, quat.w);
  tf::Matrix3x3 m(q);
  m.getRPY(roll, pitch, yaw);
  return;
}

// 构造函数
OffboardCtl::OffboardCtl(const ros::NodeHandle& nh) : nh_(nh), isGetTargetPoint_(false), isUpdateTargetPoint_(false), isGetSmallUavPoseInBigUavFrameInit_(false)
{
    // 订阅无人机本地位置
    uavPoseLocalSub1_ = nh_.subscribe("uav1/mavros/local_position/pose", 10, &OffboardCtl::uavPoseLocalCallback1, this);
    uavPoseLocalSub2_ = nh_.subscribe("uav2/mavros/local_position/pose", 10, &OffboardCtl::uavPoseLocalCallback2, this);

    // 小无人机在大无人机坐标系下的local坐标订阅
    smallUavPoseInBigUavFrameSub_ = nh_.subscribe("/transform/small_uav_pose_in_big_uav_frame", 10, &OffboardCtl::smallUavPoseInBigUavFrameCallback, this);
    // 订阅无人机本地速度
    uavTwistLocalSub1_ = nh_.subscribe("uav1/mavros/local_position/velocity", 10, &OffboardCtl::uavTwistLocalCallback1, this);
    uavTwistLocalSub2_ = nh_.subscribe("uav2/mavros/local_position/velocity_local", 10, &OffboardCtl::uavTwistLocalCallback2, this);
    // sub uav2 imu data
    imuSub_ = nh_.subscribe("uav2/mavros/imu/data", 10, &OffboardCtl::imuDataCallback, this);
    // 发布无人机本地位置
    setpointLocalPub1_ = nh_.advertise<geometry_msgs::PoseStamped>("uav1/mavros/setpoint_position/local", 10);
    setpointLocalPub2_ = nh_.advertise<geometry_msgs::PoseStamped>("uav2/mavros/setpoint_position/local", 10);
    // 发布无人机本地原始位置
    setpointRawLocalPub1_ = nh_.advertise<mavros_msgs::PositionTarget>("uav1/mavros/setpoint_raw/local", 10);
    setpointRawLocalPub2_ = nh_.advertise<mavros_msgs::PositionTarget>("uav2/mavros/setpoint_raw/local", 10);
    // 发布无人机原始姿态
    setpointRawAttPub1_ = nh_.advertise<mavros_msgs::AttitudeTarget>("uav1/mavros/setpoint_raw/attitude", 10);
    setpointRawAttPub2_ = nh_.advertise<mavros_msgs::AttitudeTarget>("uav2/mavros/setpoint_raw/attitude", 10);
    // 发布无人机本地速度
    setpointVelLocalPub1_ = nh_.advertise<geometry_msgs::TwistStamped>("uav1/mavros/setpoint_velocity/cmd_vel", 10);
    setpointVelLocalPub2_ = nh_.advertise<geometry_msgs::TwistStamped>("uav2/mavros/setpoint_velocity/cmd_vel", 10);

    /* 服务函数两无人机共用，使用大无人机uav2的句柄 */
    // 设置目标位置服务
    setTargetPointSrv_ = nh_.advertiseService("offboard_control/set_target_point", &OffboardCtl::setTargetPoint, this);
    // 设置控制模式服务
    setOffboardCtlTypeSrv_ = nh_.advertiseService("offboard_control/set_offboard_ctl_type", &OffboardCtl::setOffboardCtlType, this);
    // 动态调整pid参数服务
    setPidGainsSrv_ = nh_.advertiseService("offboard_control/set_pid_gains", &OffboardCtl::setPidGains, this);
    // 判断无人机是否到点服务
    isUavArrivedSrv_ = nh_.advertiseService("offboard_control/is_arrived", &OffboardCtl::isUavArrived, this);
    // 设置offboard和解锁服务
    setUavTakeoffReadySrv_ = nh_.advertiseService("offboard_control/set_uav_takeoff_ready", &OffboardCtl::setUavTakeoffReady, this);

    // 解锁服务
    armingClient1_ = nh_.serviceClient<mavros_msgs::CommandBool>("uav1/mavros/cmd/arming");
    armingClient2_ = nh_.serviceClient<mavros_msgs::CommandBool>("uav2/mavros/cmd/arming");
    // 设置模式客户端
    setModeClient1_ = nh_.serviceClient<mavros_msgs::SetMode>("uav1/mavros/set_mode");
    setModeClient2_ = nh_.serviceClient<mavros_msgs::SetMode>("uav2/mavros/set_mode");
    
    // 轨迹生成器客户端
    trajGeneratorClient2_ = nh_.serviceClient<offboard_control::GenTrajOnline>("online_traj_generator/gen_traj_online");
    // 状态切换定时器
    stateSwitchTimer_ = nh_.createTimer(ros::Duration(controlPeriod), &OffboardCtl::stateSwitchTimerCallback, this);

    // 初始化控制模式
    // offbCtlType_= GOTO_SETPOINT_STEP;
    // offbCtlType_= GOTO_SETPOINT_CLOSED_LOOP;
    offbCtlType_= GOTO_SETPOINT_SMOOTH;

    // 初始化pid控制器
    pidX_.initPid(1.5, 0.0, 0.1, 0.0, 0.0, 0);
    pidY_.initPid(1.5, 0.0, 0.1, 0.0, 0.0, 0);
    pidZ_.initPid(1.5, 0.0, 0.0, 0.0, 0.0, 0);
}
OffboardCtl::~OffboardCtl()
{
    // 在这里添加任何需要的清理代码
}

// 位置环pid控制 ,返回位置环控制量
mavros_msgs::PositionTarget OffboardCtl::positionCtl(geometry_msgs::PoseStamped targetPoint, geometry_msgs::PoseStamped uavPoseLocal, double vz_min, double vz_max)
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
    // 输出限幅
    control_vz = control_vz > vz_max ? vz_max : control_vz;
    control_vz = control_vz < vz_min ? vz_min : control_vz;
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
// 给定一系列目标点，使得无人机能够以指定的速度经过这一系列目标点，并在每个目标点上停留一段时间


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
    isUpdateTargetPoint_ = true;
    return true;
}
// 获取平滑过渡点
bool OffboardCtl::getTargetPointRawLocal2()
{
    offboard_control::GenTrajOnline srv;
    srv.request.targPoint = uavTargetPoint2_;
    srv.request.pose = uavPoseLocal2_;
    srv.request.twist = uavTwistLocal2_;
    srv.request.imuData = uavImuData_;
    if(isUpdateTargetPoint_)
    {
        srv.request.isUpdateTarget = true;
        isUpdateTargetPoint_ = false;
    }
    else
    {
        srv.request.isUpdateTarget = false;
    }
    if(!trajGeneratorClient2_.call(srv))
    {
        ROS_ERROR_STREAM("getTargetPointRawLocal: trajGeneratorClient_ failed");
        return false;
    }
    // 获取平滑过渡点
    uavTargetPointRaw2_ = srv.response.setPointRaw;
    return true;
}
// 设置控制模式服务函数
bool OffboardCtl::setOffboardCtlType(offboard_control::SetOffboardCtlType::Request& req, offboard_control::SetOffboardCtlType::Response& res)
{
    preOffbCtlType = offbCtlType_;
    offbCtlType_ = req.offbCtlType;
    res.success = true;
    // 打印控制模式
    ROS_INFO_STREAM("setOffboardCtlType: " << offbCtlType_);
    return true;
}

// pid参数设置服务函数
bool OffboardCtl::setPidGains(offboard_control::SetPidGains::Request& req, offboard_control::SetPidGains::Response& res)
{
    // switch (req.pid_axis)
    // {
    //     case 0:
    //         pidX_.setGains(req.kp, req.ki, req.kd, req.i_max, req.i_min);
    //         break;
    //     case 1:
    //         pidY_.setGains(req.kp, req.ki, req.kd, req.i_max, req.i_min);
    //         break;
    //     case 2:
    //         pidZ_.setGains(req.kp, req.ki, req.kd, req.i_max, req.i_min);
    //         break;
    //     default:
    //         break;
    // }
    vz_max_ = req.vz_max;
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
            res.isArrived = isArrived(req.targetPoint, uavPoseLocal1_,req.precision);
            ROS_INFO_STREAM("isUavArrived: " << res.isArrived);
            break;
        case 2:
            res.isArrived = isArrived(req.targetPoint, uavPoseLocal2_,req.precision);
            ROS_INFO_STREAM("isUavArrived: " << res.isArrived);
            break;
        default:
            ROS_ERROR_STREAM("uavID is not correct.");
            res.isArrived = false;
            return false;
    }
    return true;
}
// 判断是否到达目标点
bool OffboardCtl::isArrived(const geometry_msgs::PoseStamped& targetPoint, const geometry_msgs::PoseStamped& uavPoseLocal, double precision)
{
    // 计算距离
    double distance_2 = pow(targetPoint.pose.position.x - uavPoseLocal.pose.position.x, 2) + 
                        pow(targetPoint.pose.position.y - uavPoseLocal.pose.position.y, 2) + 
                        pow(targetPoint.pose.position.z - uavPoseLocal.pose.position.z, 2);
    // 判断精度需要根据实际设置
    ROS_INFO_STREAM("isarrived: " << (distance_2 < pow(precision, 2)));
    ROS_INFO_STREAM("distance_2: " << distance_2 << "precision: " << pow(precision, 2));

    return (distance_2 < pow(precision, 2));
}

// 回调函数
// 小无人机在大无人机坐标系下的local坐标回调函数
void OffboardCtl::smallUavPoseInBigUavFrameCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    if(!isGetSmallUavPoseInBigUavFrameInit_)
    {
        smallUavPoseInBigUavFrameInit_ = *msg;
        isGetSmallUavPoseInBigUavFrameInit_ = true;
    }
}
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
void OffboardCtl::imuDataCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
    uavImuData_ = *msg;
    // 打印无人机姿态
    // ROS_INFO_STREAM("imuDataCallback: " << imuData_);
}
// 小无人机在大无人机坐标系下的目标位置->小无人机在自己local坐标系下的目标位置
geometry_msgs::PoseStamped OffboardCtl::uav1PoseInUav2FrameToUav1Frame(const geometry_msgs::PoseStamped& smallUavPoseInBigUavFrame)
{
    geometry_msgs::PoseStamped smallUavPoseInSmallUavFrame;
    smallUavPoseInSmallUavFrame = smallUavPoseInBigUavFrame;
    // 小无人机在大无人机坐标系下的local坐标转换为小无人机在自己local坐标系下的local坐标
    smallUavPoseInSmallUavFrame.pose.position.x -= smallUavPoseInBigUavFrameInit_.pose.position.x;
    smallUavPoseInSmallUavFrame.pose.position.y -= smallUavPoseInBigUavFrameInit_.pose.position.y;
    return smallUavPoseInSmallUavFrame;
}

// 运动模式切换
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
        // setpointLocalPub1_.publish(uavPoseLocal1_); // 持续发布无人机当前位置，即静止状态的位置，防止arm失败
        setpointLocalPub2_.publish(uavPoseLocal2_);
        
    }
    // 当切换控制模式时，先保持当前位置3s，然后再切换
    // if(preOffbCtlType != offbCtlType_)
    // {
    //     int i = 0;
    //     while(i < 60)
    //     {
    //         //打印信息
    //         ROS_INFO_STREAM("Waiting for state switch...");
    //         //运行频率20hz
    //         ros::Rate(20).sleep();
    //         // setpointLocalPub1_.publish(uavPoseLocal1_); // 持续发布无人机当前位置，即静止状态的位置，防止arm失败
    //         setpointLocalPub2_.publish(uavTargetPoint2_);
    //         setpointLocalPub1_.publish(uavTargetPoint1_);
    //         i++;
    //     }
    //     preOffbCtlType = offbCtlType_;
    // }
    // 状态机开始运行
    switch (offbCtlType_)
    {
        case GOTO_SETPOINT_STEP:
        {
            uavTargetPoint1_.header.stamp = ros::Time::now(); //设置时间戳
            setpointLocalPub1_.publish(uavTargetPoint1_); //发布目标位置
            uavTargetPoint2_.header.stamp = ros::Time::now(); //设置时间戳
            setpointLocalPub2_.publish(uavTargetPoint2_); //发布目标位置
            //打印信息
            // ROS_INFO_STREAM("offboard_control::OffboardCtlType::GOTO_SETPOINT_STEP: " << targetPoint_);
            ROS_INFO_STREAM("offboard_control::OffboardCtlType::GOTO_SETPOINT_STEP: uav1: " << uavPoseLocal1_<< "uav2: " << uavPoseLocal2_);

            break;
        }
        // 在原定点控制外环加位置闭环
        case GOTO_SETPOINT_CLOSED_LOOP:
        {
            uavTargetPointRaw2_=positionCtl(uavTargetPoint2_, uavPoseLocal2_, -vz_max_, vz_max_); //位置环pid控制
            setpointRawLocalPub2_.publish(uavTargetPointRaw2_); //发布目标位置

            uavTargetPoint1_ = uavTargetPoint2_;
            uavTargetPoint1_.pose.position.z -= 1.0;
            uavTargetPoint1_ = uav1PoseInUav2FrameToUav1Frame(uavTargetPoint1_);
            setpointLocalPub1_.publish(uavTargetPoint1_); //发布目标位置
            //打印信息
            // ROS_INFO_STREAM("offboard_control::OffboardCtlType::GOTO_SETPOINT_CLOSED_LOOP: " << targetPoint_);
            ROS_INFO_STREAM("offboard_control::OffboardCtlType::GOTO_SETPOINT_CLOSED_LOOP: " << uavPoseLocal1_);
            break;
        }
        // 到点平滑过渡
        case GOTO_SETPOINT_SMOOTH:
        {
            // getTargetPointRawLocal2(); //获取平滑过渡点
            // uavTargetPointRaw2_.header.stamp = ros::Time::now(); //设置时间戳
            // uavTargetPointRaw2_.coordinate_frame =
            // mavros_msgs::PositionTarget::FRAME_LOCAL_NED;
            // uavTargetPointRaw2_.type_mask =
            // mavros_msgs::PositionTarget::IGNORE_YAW_RATE;
            // setpointRawLocalPub2_.publish(uavTargetPointRaw2_);
            // trajTrackControler(uavPoseLocal2_, uavTwistLocal2_, uavTargetPointRaw2_);
            // uavTargetAttRaw2_.header.stamp = ros::Time::now(); //设置时间戳
            // uavTargetAttRaw2_.type_mask =
            //             mavros_msgs::AttitudeTarget::IGNORE_ROLL_RATE |
            //             mavros_msgs::AttitudeTarget::IGNORE_PITCH_RATE |
            //             mavros_msgs::AttitudeTarget::IGNORE_YAW_RATE ;
            // setpointRawAttPub2_.publish(uavTargetAttRaw2_);

            uavTargetPoint1_ = uavTargetPoint2_;
            // uavTargetPoint1_.pose.position.z -= 1.0;
            // setpointRawLocalPub1_.publish(positionCtl(uav1PoseInUav2FrameToUav1Frame(uavTargetPoint1_), uavPoseLocal1_)); //位置环pid控制
            // uavTargetPoint1_ = uav1PoseInUav2FrameToUav1Frame(uavTargetPoint1_);
            // getTargetPointRawLocal1(); //获取平滑过渡点
            uavTargetPointRaw1_.header.stamp = ros::Time::now(); //设置时间戳
            uavTargetPointRaw1_.coordinate_frame =
            mavros_msgs::PositionTarget::FRAME_LOCAL_NED;
            uavTargetPointRaw1_.type_mask =
            mavros_msgs::PositionTarget::IGNORE_YAW_RATE;
            // setpointRawLocalPub1_.publish(uavTargetPointRaw1_); //发布平滑过渡点

            getTargetPointRawLocal2(); //获取平滑过渡点
            uavTargetPointRaw2_.header.stamp = ros::Time::now(); //设置时间戳
            uavTargetPointRaw2_.coordinate_frame =
            mavros_msgs::PositionTarget::FRAME_LOCAL_NED;
            uavTargetPointRaw2_.type_mask =
            mavros_msgs::PositionTarget::IGNORE_YAW_RATE;
            setpointRawLocalPub2_.publish(uavTargetPointRaw2_);

            //打印信息
            ROS_INFO_STREAM("offboard_control::OffboardCtlType::GOTO_SETPOINT_SMOOTH");
            break;
        }
        // 实际控制,大无人机定点，小无人机跟随，只控制小无人机姿态
        case GOTO_SETPOINT_ACTUAL:
        {
            //获取平滑过渡点
            getTargetPointRawLocal2();
            uavTargetPointRaw2_.header.stamp = ros::Time::now(); //设置时间戳
            uavTargetPointRaw2_.coordinate_frame =
            mavros_msgs::PositionTarget::FRAME_LOCAL_NED;
            uavTargetPointRaw2_.type_mask =
            mavros_msgs::PositionTarget::IGNORE_YAW_RATE;
            setpointRawLocalPub2_.publish(uavTargetPointRaw2_); //发布平滑过渡点

            // 小无人机姿态控制
            // setpointRawAttPub1_.publish(smallUavTargetAttRaw(uavTargetPoint2_.pose.orientation)); //发布小无人机姿态控制量
            //打印信息
            ROS_INFO_STREAM("offboard_control::OffboardCtlType::GOTO_SETPOINT_ACTUAL");
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
    if(!ros::service::waitForService("uav1/mavros/set_mode", ros::Duration(5))&&
       !ros::service::waitForService("uav2/mavros/set_mode", ros::Duration(5)))
    {
        ROS_ERROR_STREAM("Failed to start offboard mode.");
        return -1;
    }
    else
    {
        ROS_INFO_STREAM("Start offboard mode.");
    }
    // 等待解锁
    if(!ros::service::waitForService("uav1/mavros/cmd/arming", ros::Duration(5))&&
       !ros::service::waitForService("uav2/mavros/cmd/arming", ros::Duration(5)))
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

    //等待其他节点启动
    ros::Duration(5).sleep();

    // 开启异步线程处理回调函数
    ros::MultiThreadedSpinner spinner(6);
    spinner.spin();

    ROS_INFO("OffboardCtl node has started.");

    
    

    return 0;
}
// 设置offboard和解锁服务函数,解锁及设置offboard模式成功返回true
bool OffboardCtl::setUavTakeoffReady(offboard_control::SetUavTakeoffReady::Request& req, offboard_control::SetUavTakeoffReady::Response& res)
{
    mavros_msgs::CommandBool arm_cmd; //解锁
    arm_cmd.request.value = true;
    mavros_msgs::SetMode offb_set_mode; //设置模式
    offb_set_mode.request.custom_mode = "OFFBOARD";
    // 判断uavID,解锁对应的无人机
    switch(req.uavID)
    {
        case 1:
            if(armingClient1_.call(arm_cmd) && arm_cmd.response.success)
            {
                ROS_INFO_STREAM("Uav1 armed");
                res.armed = true;
            }
            else
            {
                ROS_ERROR_STREAM("Uav1 arming failed");
                res.armed = false;
            }
            if(setModeClient1_.call(offb_set_mode) && offb_set_mode.response.mode_sent)
            {
                ROS_INFO_STREAM("Uav1 offboard enabled");
                res.offboard_enabled = true;
            }
            else
            {
                ROS_ERROR_STREAM("Uav1 offboard enable failed");
                res.offboard_enabled = false;
            }
            break;
        case 2:
            if(armingClient2_.call(arm_cmd) && arm_cmd.response.success)
            {
                ROS_INFO_STREAM("Uav2 armed");
                res.armed = true;
            }
            else
            {
                ROS_ERROR_STREAM("Uav2 arming failed");
                res.armed = false;
            }
            if(setModeClient2_.call(offb_set_mode) && offb_set_mode.response.mode_sent)
            {
                ROS_INFO_STREAM("Uav2 offboard enabled");
                res.offboard_enabled = true;
            }
            else
            {
                ROS_ERROR_STREAM("Uav2 offboard enable failed");
                res.offboard_enabled = false;
            }
            break;
    }
    return (res.armed && res.offboard_enabled);
}