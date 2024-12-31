#include "cameraCommand.h"
#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/String.h>
#include <boost/asio.hpp>
#include <boost/asio/ip/udp.hpp>
#include "offboard_control/Measure.h"

using namespace boost::asio;
using boost::asio::ip::udp;

class CameraCommandNode
{
public:
    CameraCommandNode(ros::NodeHandle& nh)
        : socket(io, udp::endpoint(udp::v4(), 9999))  // Changed local port to 9998
    {
        try {
            // Define target endpoint
            target_endpoint = udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8888);

            pointPub = nh.advertise<offboard_control::Measure>("/transform/sensor_data", 10);
            getControlSensorSub = nh.subscribe("/transform/sensor_switch", 10, &CameraCommandNode::getControlSensorCallback, this);
        } catch (boost::system::system_error& e) {
            ROS_ERROR("Failed to initialize UDP socket: %s", e.what());
            ros::shutdown();
        }
    }

    void spin()
    {
        ros::Rate rate(30); // 30 Hz
        // sendStartMeasureCommand();
        sendEndMeasureCommand();
        while (ros::ok())
        {
            try {
                receiveResponse();
            } catch (boost::system::system_error& e) {
                ROS_ERROR("Error receiving data: %s", e.what());
            }
            ros::spinOnce();
            rate.sleep();
        }
    }

private:
    io_service io;
    udp::socket socket;
    udp::endpoint target_endpoint;
    ros::Publisher pointPub;
    ros::Subscriber getControlSensorSub;

    void sendStartMeasureCommand()
    {
        ooCommandStruct cmd;
        startMeasure(cmd);
        unsigned char buffer[sizeof(cmd)];
        serializeCommand(cmd, buffer);
        socket.send_to(boost::asio::buffer(buffer, sizeof(buffer)), target_endpoint);
        ROS_INFO_STREAM("Sent start measure command");
    }

    void sendEndMeasureCommand()
    {
        ooCommandStruct cmd;
        endMeasure(cmd);
        unsigned char buffer[sizeof(cmd)];
        serializeCommand(cmd, buffer);
        socket.send_to(boost::asio::buffer(buffer, sizeof(buffer)), target_endpoint);
        ROS_INFO_STREAM("Sent end measure command");
    }

    void getControlSensorCallback(const std_msgs::String::ConstPtr& msg)
    {
        ROS_INFO_STREAM("Received control sensor switch command: " << msg->data);
        if (msg->data == "start") {
            sendStartMeasureCommand();
        } else if (msg->data == "end") {
            sendEndMeasureCommand();
        } else {
            ROS_WARN("Received unexpected control sensor switch command: %s", msg->data.c_str());
        }
    }

    void receiveResponse()
    {
        // 接收传感器返回的数据
        unsigned char recv_buffer[1024];
        udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(boost::asio::buffer(recv_buffer), sender_endpoint);
        ROS_INFO("Received message of length: %zu", len);

        // 反序列化接收到的数据
        offboard_control::Measure measure;
        if (len >= 16 && recv_buffer[0] == 0x55 && recv_buffer[1] == 0xAA && recv_buffer[2] == 5 && recv_buffer[3] == 0 && recv_buffer[4] == 8) {
            float x = *reinterpret_cast<float*>(recv_buffer + 8);
            float z = *reinterpret_cast<float*>(recv_buffer + 12);
            // if measure x,z is nan, then it is invalid
            if (std::isnan(x) || std::isnan(z)) {
                measure.is_valid = false;
                ROS_WARN("Measurement failed: x = %f, z = %f", x, z);
            } else {
                measure.is_valid = true;
                measure.x = x;
                measure.z = z;
                ROS_INFO("Measurement success: x = %f, z = %f", x, z);
            }
        } else {
            measure.is_valid = false;
            ROS_WARN("Received unexpected response from sensor");
        }
        pointPub.publish(measure);
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "camera_command_node");
    ros::NodeHandle nh;
    CameraCommandNode cameraCommandNode(nh);
    cameraCommandNode.spin();
    return 0;
}