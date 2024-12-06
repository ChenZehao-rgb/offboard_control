#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "follow_cable_node");
    ros::NodeHandle nh;

    ROS_INFO("FollowCable node has started.");

    ros::spin();

    return 0;
}