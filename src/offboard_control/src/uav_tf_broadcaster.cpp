#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/PoseStamped.h>
#include "FollowCable.h"
void poseCallback1(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    static tf::TransformBroadcaster br;
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(msg->pose.position.x, msg->pose.position.y, msg->pose.position.z));
    transform.setRotation(tf::Quaternion(msg->pose.orientation.x, msg->pose.orientation.y, msg->pose.orientation.z, msg->pose.orientation.w));
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "uav1"));
}
void poseCallback2(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    static tf::TransformBroadcaster br;
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(msg->pose.position.x, msg->pose.position.y, msg->pose.position.z));
    transform.setRotation(tf::Quaternion(msg->pose.orientation.x, msg->pose.orientation.y, msg->pose.orientation.z, msg->pose.orientation.w));
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "uav2"));
}
int main(int argc, char** argv)
{
    ros::init(argc, argv, "uav_tf_broadcaster");
    ros::NodeHandle nh;
    ros::Subscriber uavPoseSub1 = nh.subscribe<geometry_msgs::PoseStamped>("uav1/mavros/local_position/pose", 10, &poseCallback1);
    ros::Subscriber uavPoseSub2 = nh.subscribe<geometry_msgs::PoseStamped>("uav2/mavros/local_position/pose", 10, &poseCallback2);
    ros::spin();
    return 0;
}

