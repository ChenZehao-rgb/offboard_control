#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>
#include <sstream>
#include <offboard_control/Status.h>
std::string status;
void statusCallback(const offboard_control::Status::ConstPtr& msg)
{
    status = msg->state;
}
int main(int argc, char** argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "follow_cable_node");
    ros::NodeHandle nh;

    // 创建发布者
    ros::Publisher keyboard_pub = nh.advertise<std_msgs::String>("/keyboard_input", 10);
    ros::Publisher command_pub = nh.advertise<std_msgs::String>("/command_topic", 10);
    ros::Subscriber status_sub = nh.subscribe("/status_topic", 10, statusCallback);
    // 设置循环频率
    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        // 输出状态控制类型信息
        ROS_INFO("Control_States:");
        ROS_INFO("0: TAKEOFF");
        ROS_INFO("1: ARRIVE_ONLINE_POINT");
        ROS_INFO("2: AJUST_ATTITUDE");
        ROS_INFO("3: ON_LINE");
        ROS_INFO("4: FOLLOW_CABLE");
        ROS_INFO("5: APPROACH_NODE");
        ROS_INFO("6: CROSS_NODE");
        ROS_INFO("7: LAND");
        ROS_INFO("Please input the control state: ");
        // 获取键盘输入
        std::string input;
        std::getline(std::cin, input);

        // 创建消息并发布
        std_msgs::String msg;
        msg.data = input;
        // keyboard_pub.publish(msg);
        command_pub.publish(msg);

        // 延时以等待状态更新
        ros::Duration(0.5).sleep();
        if(status == input)
        {
            ROS_INFO_STREAM("Status refresh: " << status);
        }
        // 处理回调函数
        ros::spinOnce();

        // 睡眠以保持循环频率
        loop_rate.sleep();
    }

    return 0;
}