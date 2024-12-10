#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>
#include <sstream>

int main(int argc, char** argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "follow_cable_node");
    ros::NodeHandle nh;

    // 创建发布者
    ros::Publisher keyboard_pub = nh.advertise<std_msgs::String>("/keyboard_input", 10);

    // 设置循环频率
    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        // 获取键盘输入
        std::string input;
        std::getline(std::cin, input);

        // 创建消息并发布
        std_msgs::String msg;
        msg.data = input;
        keyboard_pub.publish(msg);

        // 处理回调函数
        ros::spinOnce();

        // 睡眠以保持循环频率
        loop_rate.sleep();
    }

    return 0;
}