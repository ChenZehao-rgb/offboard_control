#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include "FollowCable.h"
//几种控制模式定义
#define GOTO_SETPOINT_STEP 0
#define GOTO_SETPOINT_CLOSED_LOOP 1
#define GOTO_SETPOINT_SMOOTH 2
#define GOTO_SETPOINT_RELATIVE 3
FollowCable::FollowCable(const ros::NodeHandle& nh) : nh_(nh), isGetOnlinePoint_(false), isSendOnlinePoint_(false), isGetCommand_(false), isGetCrossPoint_(false)
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
    // 无人机返航点服务
    setUavReturnClient1_ = nh_.serviceClient<mavros_msgs::SetMode>("/uav1/mavros/set_mode");
    setUavReturnClient2_ = nh_.serviceClient<mavros_msgs::SetMode>("/uav2/mavros/set_mode");
    // 键盘输入订阅
    keyboardSub_ = nh_.subscribe("/keyboard_input", 10, &FollowCable::keyboardCallback, this);
    // 无人机本地位置订阅
    uavPoseSub2_ = nh_.subscribe("uav2/mavros/local_position/pose", 10, &FollowCable::uavPoseLocalCallback2, this);
    // 无人机home位置订阅
    uavHomeSub1_ = nh_.subscribe("uav1/mavros/home_position/home", 10, &FollowCable::uavHomePoseCallback1, this);
    uavHomeSub2_ = nh_.subscribe("uav2/mavros/home_position/home", 10, &FollowCable::uavHomePoseCallback2, this);
    // 小无人机在大无人机坐标系下的local坐标订阅
    smallUavPoseInBigUavFrameSub_ = nh_.subscribe("/transform/small_uav_pose_in_big_uav_frame", 10, &FollowCable::smallUavPoseInBigUavFrameCallback, this);
    // 由小无人机相对坐标转换得到的大无人机目标位置订阅
    bigUavTargetPoseSub_ = nh_.subscribe("/transform/big_uav_target_pose", 10, &FollowCable::bigUavTargetPoseCallback, this);
    // 发布状态机控制状态
    status_pub_ = nh_.advertise<offboard_control::Status>("/status_topic", 10);
    // 控制状态机
    controlLoop_ = nh_.createTimer(ros::Duration(controlPeriod), &FollowCable::controlLoop, this);
    // 定时器发送状态信息
    statusPubTimer_ = nh_.createTimer(ros::Duration(1.0), &FollowCable::publishStatus, this);
    // 初始化状态
    stateControl_.state_ctrl_type = offboard_control::StateControl::TAKEOFF;
    previousStateControl_.state_ctrl_type = offboard_control::StateControl::TAKEOFF;
    // 读取参数
    readParameters(nh_);
    // 等待其他节点启动
    ros::Duration(5).sleep();
    setOffboardCtlType(GOTO_SETPOINT_SMOOTH);
    // 发送大无人机目标位置
    setUavTakeoffReady(2);
    setTargetPoint(takeOffPoint2_,2);
    // 等待大飞机起飞
    ros::Duration(5).sleep();
    // 发送小无人机解锁指令，offboardCtl会自动获取大无人机下方1m位置作为小无人机的起飞位置
    setUavTakeoffReady(1);
    // 延时5s,等待无人机起飞
    ros::Duration(5).sleep();
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
    geometry_msgs::PoseStamped testPose1, testPose2;
    testPose1.pose.position.x = 1.0;
    testPose1.pose.position.y = 1.0;
    testPose1.pose.position.z = 1.0;
    testPose1.pose.orientation.x = 0.0;
    testPose1.pose.orientation.y = 0.0;
    testPose1.pose.orientation.z = 0.0;
    testPose1.pose.orientation.w = 1.0;
    testPose2 = testPose1;
    testPose2.pose.position.x += -2;
    testPose2.pose.position.y += -2;
    setTargetPoint(testPose1,1);
    setTargetPoint(testPose2,2);
    ROS_INFO_STREAM("testPoseTrans: " << testPose1);
    ROS_INFO_STREAM("testPoseTrans: " << testPose2);
    while(1)
    {
        ros::spinOnce();
        ros::Rate(1).sleep();
        ROS_INFO_STREAM("uavPoseLocalSub1_: " << uavPoseLocalSub1_);
        ROS_INFO_STREAM("uavPoseLocalSub2_: " << uavPoseLocalSub2_);
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
// 根据线结构传感器的测量结果，判断姿态调整是否到位
bool FollowCable::isAjusted(const geometry_msgs::PoseStamped& cablePose)
{
    // 延时等待3s
    ros::Duration(3).sleep();
    // 计算角度差
    double yaw_diff = tf::getYaw(cablePose.pose.orientation) - tf::getYaw(uavPoseLocalSub1_.pose.orientation);
    ROS_INFO_STREAM("yaw_diff: " << yaw_diff);
    if (fabs(yaw_diff) < 5)
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
    // 循环20次
    for(int i = 0; i < 20; i++)
    {
        ros::spinOnce();
        ros::Rate(1).sleep();
        ROS_INFO_STREAM("Grasping : " << i << "s ...");
    }
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
    for(int i = 0; i < 3; i++)
    {
        ros::spinOnce();
        ros::Rate(1).sleep();
        ROS_INFO_STREAM("storeCableInfo : " << i << "s ...");
    }
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
void FollowCable::followCablePoints(std::vector<geometry_msgs::PoseStamped> &waypoints)
{
    while (!waypoints.empty())
    {
        geometry_msgs::PoseStamped waypoint = waypoints.front(); // 获取第一个目标点
        geometry_msgs::PoseStamped wayPointUav1, wayPointUav2; // 定义无人机本地坐标系下的目标点
        // 大无人机坐标
        wayPointUav2 = waypoint;
        wayPointUav2.pose.position.z += rope_length;
        setTargetPoint(wayPointUav2, 2);
        // 等待到达目标点
        while (ros::ok())
        {
            ros::spinOnce();
            ros::Rate(1).sleep();
            // 检查是否到达目标点
            if (isUavArrived(wayPointUav2, 2, targetPointError1))
            {
                // 存储采集到的索道信息
                if (storeCableInfo())
                {
                    ROS_INFO_STREAM("Arrived waypoint: " << wayPointUav2 << ", get cable info ...");
                    waypoints.erase(waypoints.begin()); // 删除已经到达的点
                    break; // 跳出 while 循环，继续下一个目标点
                }
            }
        }
    }
}
void FollowCable::publishStatus(const ros::TimerEvent&)
{
    // 发送当前运行状态
    offboard_control::Status status_msg;
    status_msg.state = std::to_string(stateControl_.state_ctrl_type);
    status_msg.uav2_position = uavPoseLocalSub2_.pose;
    status_msg.uav2_orientation = uavPoseLocalSub2_.pose.orientation;
    status_pub_.publish(status_msg);
}
void FollowCable::waitForCommand() {
    // 定义一个映射，将字符串命令映射到整数值
    std::map<std::string, int> command_map = {
        {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}
    };
    // 当ROS节点处于运行状态且尚未接收到命令时，进入循环
    while(ros::ok() && !isGetCommand_)
    {
        // 从话题"/command_topic"中等待接收消息，超时时间为1秒
        std_msgs::String::ConstPtr command_msg = ros::topic::waitForMessage<std_msgs::String>("/command_topic", ros::Duration(1.0));
        // 如果接收到消息
        if (command_msg) {
            // 在命令映射中查找接收到的命令
            auto it = command_map.find(command_msg->data);
            // 如果找到匹配的命令
            if (it != command_map.end()) {
                // 更新状态控制类型为对应的整数值
                stateControl_.state_ctrl_type = it->second;
                // 标记已接收到命令
                isGetCommand_ = true;
                // 退出函数
                return;
            } else {
                // 如果命令无效，输出错误信息
                ROS_ERROR_STREAM("Invalid command: " << command_msg->data);
            }
        }
        // 休眠0.1秒
        ros::Rate(10).sleep();
    }
}
// 状态机
void FollowCable::controlLoop(const ros::TimerEvent&)
{
    // 等待无人机起飞
    while(ros::ok() && stateControl_.state_ctrl_type == offboard_control::StateControl::TAKEOFF)
    { 
        // 如果大飞机到达起飞点，起飞成功
        if(isUavArrived(takeOffPoint2_,2,targetPointError1))
        {
            preStateControlStr_ = "Takeoff";
            stateControl_.state_ctrl_type = offboard_control::StateControl::ARRIVE_ONLINE_POINT;
            ROS_INFO_STREAM("Takeoff success, and arrive online point...");
            break;
        }
        ROS_INFO_STREAM("Waiting for takeoff..., uavpose2: "<<uavPoseLocalSub2_);
        ros::Rate(1).sleep();
    }
    // 当状态切换时，等待命令
    if(previousStateControl_.state_ctrl_type != stateControl_.state_ctrl_type)
    {
        ROS_INFO_STREAM( preStateControlStr_ << " is down, waiting for command...");
        waitForCommand();
    }
    // 运动控制状态机逻辑
    switch (stateControl_.state_ctrl_type)
    {
        // 控制大小无人机均到达上线点
        case offboard_control::StateControl::ARRIVE_ONLINE_POINT:
        {
            ROS_INFO("Go to online point...");
            // testPoseTrans(); // 测试坐标转换
            // 获取上线坐标
            if(!isGetOnlinePoint_)
            {
                // 越过节点或者初始的上线点
                onLineCablePoint2UavPoint(cablePoints_.front(), onLinePoint1_, onLinePoint2_, onLinePoint_Z);
                isGetOnlinePoint_ = true;
            }
            // 发送大飞机上线点
            if(!isSendOnlinePoint_)
            {
                setTargetPoint(onLinePoint2_,2);
                isSendOnlinePoint_ = true;
            }
            // 判断小飞机是否到达onLinePoint1_
            if(isUavArrived(onLinePoint2_,2,targetPointError1))
            {
                previousStateControl_.state_ctrl_type = stateControl_.state_ctrl_type; // 保存上一个状态
                preStateControlStr_ = "Arrive on line point";
                stateControl_.state_ctrl_type = offboard_control::StateControl::AJUST_ATTITUDE;
                ROS_INFO_STREAM("Arrived on line point, and adjust attitude...");
                // 重置标志位
                isGetOnlinePoint_ = false;
                isSendOnlinePoint_ = false;
                isArrivedOnlinePoint_ = false;
                isGetCommand_ = false;
            }
            break;
        }
        // 当大小飞机都到点后，执行调整姿态
        case offboard_control::StateControl::AJUST_ATTITUDE:
        {
            ROS_INFO("Ajust attitude...");
            // 根据传感器获取大小飞机需要运动的相对位置/角度
            if(!isGetAjustPose_)
            {
                // 发送获取的大无人机坐标
                setTargetPoint(bigUavTargetPose_,2);
                // 只发送小无人机旋转角度，即bigUavTargetPose_的orientation
                // setTargetPoint(uavRalPose1_,1);
                // setTargetPoint(uavRalPose2_,2);
                isGetAjustPose_ = true;
            }
            // 通过获取线结构传感器的测量结果，判断大小飞机是否到达相对位置/角度
            if(isAjusted(bigUavTargetPose_))
            {
                // 已经调整好位置，准备降落上线
                previousStateControl_.state_ctrl_type = stateControl_.state_ctrl_type; // 保存上一个状态
                preStateControlStr_ = "Ajust attitude";
                stateControl_.state_ctrl_type = offboard_control::StateControl::ON_LINE;
                ROS_INFO_STREAM("Ajust attitude success, and prepare to land on line...");
                // setOffboardCtlType(GOTO_SETPOINT_STEP);
                // 重置标志位
                isGetCommand_ = false;
                isGetAjustPose_ = false;
            }
            break;
        }
        // 大小无人机上线操作
        case offboard_control::StateControl::ON_LINE:
        {
            ROS_INFO("On line...");
            // 和之前的x,y一样，只是z值目标点降低
            if(!isGetOnlinePoint_)
            {
                onLineCablePoint2UavPoint(cablePoints_.front(), onLinePoint1_, onLinePoint2_, 0);
                isGetOnlinePoint_ = true;
                // 控制大飞机下降
                setTargetPoint(onLinePoint2_,2); // 降落过程可能需要根据线结构传感器的测量结果实时调整
            }
            // 判断小飞机是否到达，判断范围根据线结构传感器的测量范围来定
            if(isUavArrived(onLinePoint2_,2,0.1))
            {
                // 控制爪子抓住索道
                if(graspCable())
                {
                    previousStateControl_.state_ctrl_type = stateControl_.state_ctrl_type; // 保存上一个状态
                    preStateControlStr_ = "On line";
                    stateControl_.state_ctrl_type = offboard_control::StateControl::FOLLOW_CABLE;
                    // 重置标志位
                    isGetCommand_ = false;
                    isGetOnlinePoint_ = false;
                    // 删除已经上线的点
                    cablePoints_.erase(cablePoints_.begin());
                    ROS_INFO_STREAM("Grasp cable success, and follow cable...");
                }
                else
                {
                    ROS_ERROR_STREAM("Grasp cable failed.");
                    releaseCable(); // 释放索道
                    // 返回上线点上方，重新调整姿态后再次尝试上线
                    if(onLineFailCnt++ < 2) //上线失败次数小于2，即至多2次上线失败
                    {
                        previousStateControl_.state_ctrl_type = stateControl_.state_ctrl_type; // 保存上一个状态
                        // 重置标志位
                        isGetCommand_ = false;

                        stateControl_.state_ctrl_type = offboard_control::StateControl::ARRIVE_ONLINE_POINT;
                        // 修改上线点距索道的距离，比第一次低一些
                        onLinePoint_Z -= 0.5;
                        ROS_INFO_STREAM("Release cable success, and back to on line point...");
                    }
                    else
                    {
                        previousStateControl_.state_ctrl_type = stateControl_.state_ctrl_type; // 保存上一个状态
                        // 重置标志位
                        isGetCommand_ = false;
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
            // 这里面加个保险措施，出问题了，先松爪、退出offboard转人工或者直接返航
            if (!all_waypoints_.empty())
            {
                followCablePoints(all_waypoints_.front());
                // 检测完这一段后后面还有点
                if (all_waypoints_.front().empty())
                {
                    all_waypoints_.erase(all_waypoints_.begin());
                }
            }
            if (all_waypoints_.empty())
            {
                previousStateControl_.state_ctrl_type = stateControl_.state_ctrl_type; // 保存上一个状态
                // 重置标志位
                isGetCommand_ = false;
                // 释放索道
                releaseCable();
                // 任务完成，返航
                stateControl_.state_ctrl_type = offboard_control::StateControl::LAND;
            }
            else
            {
                previousStateControl_.state_ctrl_type = stateControl_.state_ctrl_type; // 保存上一个状态
                // 重置标志位
                isGetCommand_ = false;
                preStateControlStr_ = "Follow cable";
                stateControl_.state_ctrl_type = offboard_control::StateControl::CROSS_NODE;
                // 释放索道
                releaseCable();
            }
            break;
        }
        case offboard_control::StateControl::CROSS_NODE:
        {
            // 跨越节点
            ROS_INFO("Crossing node...");
            // 如果没有获取上线点
            if(!isGetCrossPoint_)
            {
                // 大飞机先上升到现在位置的上方2m
                crossPoint_ = uavPoseLocalSub2_;
                crossPoint_.pose.position.z += 2;
                // 控制大飞机上升
                setTargetPoint(crossPoint_,2);
                isGetCrossPoint_ = true;
            }
            if(isUavArrived(crossPoint_,2,targetPointError1))
                {
                    if(!isGetOnlinePoint_)
                    {
                        // 获取下一节点的上线坐标,且保持大飞机高度不变跨越节点
                        onLineCablePoint2UavPoint(cablePoints_.front(), onLinePoint1_, onLinePoint2_, 2+onLinePoint_Z);
                        // 发送大飞机上线点
                        setTargetPoint(onLinePoint2_,2);
                        isGetOnlinePoint_ = true;
                    }
                }
            // 判断大无人机是否到达
            if(isUavArrived(onLinePoint2_,2,targetPointError1))
            {
                previousStateControl_.state_ctrl_type = stateControl_.state_ctrl_type; // 保存上一个状态
                preStateControlStr_ = "Cross node";
                stateControl_.state_ctrl_type = offboard_control::StateControl::ARRIVE_ONLINE_POINT;
                ROS_INFO_STREAM("Crossed node, and arrive on line point...");
                // 重置标志位
                isGetOnlinePoint_ = false;
                isSendOnlinePoint_ = false;
                isArrivedOnlinePoint_ = false;
                isGetCommand_ = false;
                isGetCrossPoint_ = false;
            }
            break;
        }
        case offboard_control::StateControl::LAND:
        {
            // 降落
            mavros_msgs::SetMode land_set_mode;
            land_set_mode.request.custom_mode = "AUTO.RTL";
            if (setUavReturnClient1_.call(land_set_mode) && setUavReturnClient2_.call(land_set_mode))
            {
                ROS_INFO("Return to home...");
            }
            else
            {
                ROS_ERROR("Failed to return to home...");
            }
            break;
        }
        default:
            break;
    }
    
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
    // uavPoseGlobalPub1_.publish(uavPoseGlobal1_);
}
void FollowCable::uavPoseLocalCallback2(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    // 更新无人机本地位置
    uavPoseLocalSub2_ = *msg;
    // uavPoseGlobalPub2_.publish(uavPoseGlobal2_);
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
// 小无人机在大无人机坐标系下的local坐标回调函数
void FollowCable::smallUavPoseInBigUavFrameCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    // 更新小无人机在大无人机坐标系下的local坐标
    smallUavPoseInBigUavFrame_ = *msg;
}
// 由小无人机相对坐标转换得到的大无人机目标位置回调函数
void FollowCable::bigUavTargetPoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    // 更新大无人机目标位置
    bigUavTargetPose_ = *msg;
}
// 读取参数
void FollowCable::readParameters(ros::NodeHandle& nh) {
    // 读取takeoff_points
    nh.getParam("takeoff_points/uav1/position_x", takeOffPoint1_.pose.position.x);
    nh.getParam("takeoff_points/uav1/position_y", takeOffPoint1_.pose.position.y);
    nh.getParam("takeoff_points/uav1/position_z", takeOffPoint1_.pose.position.z);
    nh.getParam("takeoff_points/uav1/orientation_x", takeOffPoint1_.pose.orientation.x);
    nh.getParam("takeoff_points/uav1/orientation_y", takeOffPoint1_.pose.orientation.y);
    nh.getParam("takeoff_points/uav1/orientation_z", takeOffPoint1_.pose.orientation.z);
    nh.getParam("takeoff_points/uav1/orientation_w", takeOffPoint1_.pose.orientation.w);

    nh.getParam("takeoff_points/uav2/position_x", takeOffPoint2_.pose.position.x);
    nh.getParam("takeoff_points/uav2/position_y", takeOffPoint2_.pose.position.y);
    nh.getParam("takeoff_points/uav2/position_z", takeOffPoint2_.pose.position.z);
    nh.getParam("takeoff_points/uav2/orientation_x", takeOffPoint2_.pose.orientation.x);
    nh.getParam("takeoff_points/uav2/orientation_y", takeOffPoint2_.pose.orientation.y);
    nh.getParam("takeoff_points/uav2/orientation_z", takeOffPoint2_.pose.orientation.z);
    nh.getParam("takeoff_points/uav2/orientation_w", takeOffPoint2_.pose.orientation.w);

    // 读取rope_length
    nh.getParam("size/rope/length", rope_length);
    // 读取小飞机携带爪子尺寸
    nh.getParam("size/claw/diameter", claw_diameter);
    // 读取waypoints_set_1
    XmlRpc::XmlRpcValue waypoints;
    std::vector<geometry_msgs::PoseStamped> waypoints_set_1_;
    nh.getParam("waypoints_set_1", waypoints);
    for (int i = 0; i < waypoints.size(); ++i) {
        geometry_msgs::PoseStamped waypoint;
        waypoint.pose.position.x = static_cast<double>(waypoints[i]["position"]["x"]);
        waypoint.pose.position.y = static_cast<double>(waypoints[i]["position"]["y"]);
        waypoint.pose.position.z = static_cast<double>(waypoints[i]["position"]["z"]);
        waypoint.pose.orientation.x = static_cast<double>(waypoints[i]["orientation"]["x"]);
        waypoint.pose.orientation.y = static_cast<double>(waypoints[i]["orientation"]["y"]);
        waypoint.pose.orientation.z = static_cast<double>(waypoints[i]["orientation"]["z"]);
        waypoint.pose.orientation.w = static_cast<double>(waypoints[i]["orientation"]["w"]);
        waypoints_set_1_.push_back(waypoint);
    }
    all_waypoints_.push_back(waypoints_set_1_);
    cablePoints_.push_back(waypoints_set_1_.front());
    // 读取waypoints_set_2
    std::vector<geometry_msgs::PoseStamped> waypoints_set_2_;
    nh.getParam("waypoints_set_2", waypoints);
    for (int i = 0; i < waypoints.size(); ++i) {
        geometry_msgs::PoseStamped waypoint;
        waypoint.pose.position.x = static_cast<double>(waypoints[i]["position"]["x"]);
        waypoint.pose.position.y = static_cast<double>(waypoints[i]["position"]["y"]);
        waypoint.pose.position.z = static_cast<double>(waypoints[i]["position"]["z"]);
        waypoint.pose.orientation.x = static_cast<double>(waypoints[i]["orientation"]["x"]);
        waypoint.pose.orientation.y = static_cast<double>(waypoints[i]["orientation"]["y"]);
        waypoint.pose.orientation.z = static_cast<double>(waypoints[i]["orientation"]["z"]);
        waypoint.pose.orientation.w = static_cast<double>(waypoints[i]["orientation"]["w"]);
        waypoints_set_2_.push_back(waypoint);
    }
    all_waypoints_.push_back(waypoints_set_2_);
    cablePoints_.push_back(waypoints_set_2_.front());
    // 打印读取到的参数
    ROS_INFO_STREAM("Takeoff point of uav1: " << takeOffPoint1_);
    ROS_INFO_STREAM("Takeoff point of uav2: " << takeOffPoint2_);
    ROS_INFO_STREAM("Home point of uav1: " << uavHomePoint1_);
    ROS_INFO_STREAM("Home point of uav2: " << uavHomePoint2_);
    ROS_INFO_STREAM("Rope length: " << rope_length);
    ROS_INFO_STREAM("Waypoints set 1: " << waypoints_set_1_.size() << " points");
    ROS_INFO_STREAM("Waypoints set 2: " << waypoints_set_2_.size() << " points");
    ROS_INFO_STREAM("Cable points: " << cablePoints_.size() << " points");
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