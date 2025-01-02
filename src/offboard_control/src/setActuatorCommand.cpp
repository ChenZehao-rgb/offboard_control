#include <ros/ros.h>
#include <mavros_msgs/CommandLong.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "set_actuator_command");
    ros::NodeHandle nh;

    ros::ServiceClient command_client = nh.serviceClient<mavros_msgs::CommandLong>("/uav1/mavros/cmd/command");

    mavros_msgs::CommandLong srv;
    srv.request.command = 183; // MAV_CMD_DO_SET_SERVO
    srv.request.param1 = 1;    // Servo number (1-8 for AUX1-AUX8)
    srv.request.param2 = 1500; // PWM value (1000-2000)

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