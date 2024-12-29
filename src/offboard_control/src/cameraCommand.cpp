#include "cameraCommand.h"
#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "offboard_control/Measure.h"

using namespace boost::asio;
using boost::asio::ip::tcp;

class CameraCommandNode
{
public:
    CameraCommandNode(ros::NodeHandle& nh)
        : socket(io)
    {
        try {
            // Connect to TCP server
            tcp::resolver resolver(io);
            tcp::resolver::query query("127.0.0.1", "12345"); // Replace with actual server IP and port
            tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
            boost::asio::connect(socket, endpoint_iterator);

            pointPub = nh.advertise<offboard_control::Measure>("/transform/sensor_data", 10);
        } catch (boost::system::system_error& e) {
            ROS_ERROR("Failed to connect to server: %s", e.what());
            ros::shutdown();
        }
    }

    void spin()
    {
        ros::Rate rate(10); // 10 Hz
        while (ros::ok())
        {
            try {
                receiveResponse();
            } catch (boost::system::system_error& e) {
                if (e.code() == boost::asio::error::eof) {
                    ROS_WARN("Connection closed by server");
                    break;
                } else {
                    ROS_ERROR("Error receiving data: %s", e.what());
                }
            }
            ros::spinOnce();
            rate.sleep();
        }
    }

private:
    io_service io;
    tcp::socket socket;
    ros::Publisher pointPub;

    void receiveResponse()
    {
        // 接收传感器返回的数据
        char recv_buffer[128];
        size_t len = socket.read_some(boost::asio::buffer(recv_buffer));
        std::string message(recv_buffer, len);
        ROS_INFO("Received message: %s", message.c_str());

        // 反序列化接收到的数据
        // unsigned char recv_buffer[sizeof(ooCommandStruct)];
        // boost::asio::read(socket, boost::asio::buffer(recv_buffer, sizeof(recv_buffer)));

        // 反序列化接收到的数据
        // ooCommandStruct recv_cmd;
        // deserializeCommand(recv_buffer, recv_cmd);
        // offboard_control::Measure measure;
        // 检查是否为测量成功应答
        // if (recv_cmd.uc55 == 0x55 && recv_cmd.ucAA == 0xAA && recv_cmd.ucCmd == 5 && recv_cmd.ucError == 0 && recv_cmd.lenData == 8)
        // {
        //     float x = *reinterpret_cast<float*>(recv_cmd.pcData);
        //     float z = *reinterpret_cast<float*>(recv_cmd.pcData + sizeof(float));
        //     ROS_INFO("Measurement success: x = %f, z = %f", x, z);

        //     // 发布x, y信息
        //     measure.is_valid = true;
        //     measure.x = x;
        //     measure.z = z;
        // }
        // else
        // {
        //     measure.is_valid = false;
        //     ROS_WARN("Received unexpected response from sensor");
        // }
        // pointPub.publish(measure);
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