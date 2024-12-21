// filepath: /home/chen/catkin_ws/src/observer_node/src/observer_node.cpp
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/PoseStamped.h>

void uavPoseCallback1(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    ROS_INFO("UAV1 Position: [x: %f, y: %f, z: %f]", msg->pose.position.x, msg->pose.position.y, msg->pose.position.z);
}

void uavPoseCallback2(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    ROS_INFO("UAV2 Position: [x: %f, y: %f, z: %f]", msg->pose.position.x, msg->pose.position.y, msg->pose.position.z);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "observer_node");
    ros::NodeHandle nh;

    // 订阅FollowCable节点发布的无人机位置
    ros::Subscriber uavPoseSub1 = nh.subscribe("/offboard_control/uav1_local_position", 10, uavPoseCallback1);
    ros::Subscriber uavPoseSub2 = nh.subscribe("/offboard_control/uav2_local_position", 10, uavPoseCallback2);

    ros::spin();
    return 0;
}