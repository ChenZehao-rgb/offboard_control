#include <ros/ros.h>
#include <mavros_msgs/CommandLong.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "set_actuator_command");
    ros::NodeHandle nh;

    ros::ServiceClient command_client = nh.serviceClient<mavros_msgs::CommandLong>("/uav1/mavros/cmd/command");

    mavros_msgs::CommandLong srv;
    srv.request.broadcast = false;
    srv.request.command = 187; // MAV_CMD_DO_SET_ACTUATOR
    srv.request.param1 = 1;    // AUX1
    srv.request.param2 = 0.5;  // AUX2
    srv.request.param3 = 0.8;

    if (command_client.call(srv))
    {
        ROS_INFO("Command sent successfully");
    }
    else
    {
        ROS_ERROR("Failed to send command");
    }

    return 0;
}