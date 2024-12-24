// filepath: /home/chen/catkin_ws/src/observer_node/src/observer_node.cpp
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <offboard_control/Status.h> // 替换为你的包名
#include <iostream>

void statusCallback(const offboard_control::Status::ConstPtr& msg) {
    std::cout << "Current state: " << msg->state << std::endl;
    std::cout << "UAV2 position: " << msg->uav2_position << std::endl;
    std::cout << "UAV2 orientation: " << msg->uav2_orientation << std::endl;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "observer_node");
    ros::NodeHandle nh;

    ros::Subscriber status_sub = nh.subscribe("/status_topic", 10, statusCallback);

    ros::spin();
    return 0;
}