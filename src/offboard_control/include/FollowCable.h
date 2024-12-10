#ifndef FOLLOWCABLE_H
#define FOLLOWCABLE_H

#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <geometry_msgs/PoseStamped.h>

#include "offboard_control/SetTargetPoint.h"
#include "offboard_control/SetOffboardCtlType.h"
#include "offboard_control/SetPidGains.h"

class FollowCable {
public:
    FollowCable(const ros::NodeHandle& nh);
    ~FollowCable();
    void setTargetPoint(const geometry_msgs::PoseStamped& targetPoint);
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
    ros::ServiceClient setOffboardCtlTypeClient_; //设置控制模式客户端
    ros::ServiceClient setPidGainsClient_; //设置pid参数客户端

    // 键盘输入
    ros::Subscriber keyboardSub_;
};

#endif // FOLLOWCABLE_H