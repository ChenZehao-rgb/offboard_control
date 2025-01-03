#include "cameraCommand.h"
#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/String.h>
#include <boost/asio.hpp>
#include <boost/asio/ip/udp.hpp>
#include "offboard_control/Measure.h"
#include "offboard_control/cameraControl.h"
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
        } catch (boost::system::system_error& e) {
            ROS_ERROR("Failed to initialize UDP socket: %s", e.what());
            ros::shutdown();
        }
        pointPub = nh.advertise<offboard_control::Measure>("/transform/sensor_data", 10);
        cameraControlService = nh.advertiseService("offboard/camera_control", &CameraCommandNode::cameraControlCallback, this);
        getCameraInstallParam(nh);
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
            rate.sleep();
        }
    }

private:
    io_service io;
    udp::socket socket;
    udp::endpoint target_endpoint;
    ros::Publisher pointPub;
    ros::Subscriber getControlSensorSub;
    ros::ServiceServer cameraControlService;
    double error_x, error_y, error_z;
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

    bool cameraControlCallback(offboard_control::cameraControl::Request &req,
                               offboard_control::cameraControl::Response &res)
    {
        if (req.command == 1) {
            sendStartMeasureCommand();
            res.success = true;
            ROS_INFO("Started measurement");
        } else if (req.command == 0) {
            sendEndMeasureCommand();
            res.success = true;
            ROS_INFO("Ended measurement");
        } else {
            res.success = false;
            ROS_WARN("Received invalid command: %d", req.command);
        }
        return true;
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
                measure.x = x-error_x;
                measure.z = z-error_z;
                ROS_INFO("Measurement success: x = %f, z = %f", x, z);
            }
        } else {
            measure.is_valid = false;
            ROS_WARN("Received unexpected response from sensor");
        }
        pointPub.publish(measure);
    }
    //   sensor_install:
    //   error_x: 0.1
    //   error_y: 0.1
    void getCameraInstallParam(ros::NodeHandle& nh)
    {
        // 读取相机安装参数
        nh.param("sensor_install/error_x", error_x, 0.1);
        nh.param("sensor_install/error_y", error_y, 0.1);
        nh.param("sensor_install/error_z", error_z, 0.1);
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "camera_command_node");
    ros::NodeHandle nh;
    CameraCommandNode cameraCommandNode(nh);
    ros::AsyncSpinner spinner(2);
    spinner.start();
    cameraCommandNode.spin();
    return 0;
}