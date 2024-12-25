#include "cameraCommand.h"
#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include <boost/asio.hpp>

using namespace boost::asio;

class CameraCommandNode
{
public:
    CameraCommandNode(ros::NodeHandle& nh)
        : serial(io, "/dev/ttyUSB0") // 替换为实际的串口设备
    {
        serial.set_option(serial_port_base::baud_rate(9600));
        pointPub = nh.advertise<geometry_msgs::Point>("/transform/sensor_data", 10);
    }

    void spin()
    {
        ros::Rate rate(10); // 10 Hz
        while (ros::ok())
        {
            sendCommand();
            receiveResponse();
            ros::spinOnce();
            rate.sleep();
        }
    }

private:
    io_service io;
    serial_port serial;
    ros::Publisher pointPub;

    void sendCommand()
    {
        ooCommandStruct cmd;
        startMeasure(cmd);

        // 序列化命令
        unsigned char buffer[sizeof(cmd)];
        serializeCommand(cmd, buffer);

        // 通过串口发送命令
        write(serial, boost::asio::buffer(buffer, sizeof(buffer)));
        ROS_INFO("Command sent: 0x55 0xAA 5 41 0");
    }

    void receiveResponse()
    {
        // 接收传感器返回的指令
        unsigned char recv_buffer[sizeof(ooCommandStruct)];
        read(serial, buffer(recv_buffer, sizeof(recv_buffer)));

        // 反序列化接收到的指令
        ooCommandStruct recv_cmd;
        deserializeCommand(recv_buffer, recv_cmd);

        // 检查是否为测量成功应答
        if (recv_cmd.uc55 == 0x55 && recv_cmd.ucAA == 0xAA && recv_cmd.ucCmd == 5 && recv_cmd.ucError == 0 && recv_cmd.lenData == 8)
        {
            float x = *reinterpret_cast<float*>(recv_cmd.pcData);
            float z = *reinterpret_cast<float*>(recv_cmd.pcData + sizeof(float));
            ROS_INFO("Measurement success: x = %f, z = %f", x, z);

            // 发布x, y信息
            geometry_msgs::Point point;
            point.x = x;
            point.z = z;
            pointPub.publish(point);
        }
        else
        {
            ROS_WARN("Received unexpected response from sensor");
        }
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