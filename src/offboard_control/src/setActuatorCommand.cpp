#include <ros/ros.h>
#include <mavros_msgs/CommandLong.h>
#include <offboard_control/cameraControl.h>
#include <offboard_control/Measure.h>
#include <std_srvs/SetBool.h>
#include <numeric>
#include <vector>
#include <geometry_msgs/PoseStamped.h>

class ActuatorCommandManager
{
public:
    ActuatorCommandManager(ros::NodeHandle &nh)
    {
        command_client_ = nh.serviceClient<mavros_msgs::CommandLong>("/uav1/mavros/cmd/command");
        setCameraControlClient_ = nh.serviceClient<offboard_control::cameraControl>("/offboard/camera_control");
        sensor_data_sub_ = nh.subscribe("/transform/sensor_data", 10, &ActuatorCommandManager::getSensorData, this);
        smallUavPoseInBigUavFrameSub_ = nh.subscribe("/transform/small_uav_pose_in_big_uav_frame", 10, &ActuatorCommandManager::smallUavPoseInBigUavFrameCallback, this);
    }

    bool setActuatorCommand(std_srvs::SetBool::Request &req, std_srvs::SetBool::Response &res)
    {
        mavros_msgs::CommandLong srv;
        srv.request.broadcast = false;
        srv.request.command = 187; // MAV_CMD_DO_SET_ACTUATOR
        srv.request.param1 = req.data ? 1 : 0; // Set param1 based on request
        srv.request.param2 = req.data ? 0.5 : 0.0; // Set param2 based on request
        srv.request.param3 = req.data ? 0.8 : 0.0; // Set param3 based on request

        if (command_client_.call(srv))
        {
            res.success = true;
            res.message = "Command sent successfully";
            ROS_INFO("Command sent successfully");
        }
        else
        {
            res.success = false;
            res.message = "Failed to send command";
            ROS_ERROR("Failed to send command");
        }

        return true;
    }

    void test_camera()
    {
        sendCameraControlCommand(1);
        bool sensor_valid = false;
        const int num_readings = 100;
        std::vector<float> sensor_z_readings, sensor_y_readings;
        std::vector<float> smallUav_z_readings, smallUav_y_readings;
        for (int attempt = 0; attempt < 3; ++attempt) {
            sensor_z_readings.clear();
            sensor_y_readings.clear();
            smallUav_z_readings.clear();
            smallUav_y_readings.clear();

            // Collect sensor data for 5 seconds (100 readings at 20Hz)
            for (int i = 0; i < num_readings; ++i) {
                ros::spinOnce();
                ros::Rate(20).sleep();
                if (sensorDate_.is_valid) {
                    sensor_z_readings.push_back(sensorDate_.z);
                    sensor_y_readings.push_back(sensorDate_.x);
                }
                smallUav_z_readings.push_back(smallUavPoseInBigUavFrame_.pose.position.z);
                smallUav_y_readings.push_back(smallUavPoseInBigUavFrame_.pose.position.y);
            }
            if (!sensor_z_readings.empty()) {
                float sum_z = std::accumulate(sensor_z_readings.begin(), sensor_z_readings.end(), 0.0f);
                float sum_y = std::accumulate(sensor_y_readings.begin(), sensor_y_readings.end(), 0.0f);
                sensor_z = sum_z / sensor_z_readings.size();
                sensor_y = sum_y / sensor_y_readings.size();
                float sum_smallUav_z = std::accumulate(smallUav_z_readings.begin(), smallUav_z_readings.end(), 0.0f);
                float sum_smallUav_y = std::accumulate(smallUav_y_readings.begin(), smallUav_y_readings.end(), 0.0f);
                smallUav_y = sum_smallUav_y / smallUav_y_readings.size();
                smallUav_z = sum_smallUav_z / smallUav_z_readings.size();
                ROS_INFO_STREAM("Sensor data is valid, average z: " << sensor_z << ", average y: " << sensor_y);
                ROS_INFO_STREAM("Now height is: " << smallUav_z);
                actual_z = judgeSensorZ(sensor_z, smallUav_z);
                sensor_valid = true;
                break;
            } else {
                ROS_INFO_STREAM("Sensor data is invalid on attempt " << (attempt + 1));
            }
        }

        if (!sensor_valid) {
            ROS_INFO("Sensor data is invalid after 3 attempts");
        }
    }

private:
    ros::ServiceClient command_client_;
    ros::ServiceClient setCameraControlClient_;
    ros::Subscriber sensor_data_sub_;
    ros::Subscriber smallUavPoseInBigUavFrameSub_;
    geometry_msgs::PoseStamped smallUavPoseInBigUavFrame_;
    offboard_control::Measure sensorDate_;
    double sensor_z, sensor_y, smallUav_z, smallUav_y, actual_z;

    void getSensorData(const offboard_control::Measure::ConstPtr &msg)
    {
        sensorDate_ = *msg;
    }

    void smallUavPoseInBigUavFrameCallback(const geometry_msgs::PoseStamped::ConstPtr &msg)
    {
        smallUavPoseInBigUavFrame_ = *msg;
    }

    void sendCameraControlCommand(int command)
    {
        offboard_control::cameraControl cameraControl;
        cameraControl.request.command = command;
        if(setCameraControlClient_.call(cameraControl) && cameraControl.response.success)
        {
            ROS_INFO_STREAM("Send camera control command success");
        }
        else
        {
            ROS_ERROR_STREAM("Send camera control command failed");
        }
    }

    double judgeSensorZ(double sensor_z, double local_z)
    {
        if (fabs(sensor_z - local_z) < 0.05)
        {
            return (sensor_z + local_z) / 2;
        }
        else {
            return sensor_z < local_z ? sensor_z : local_z;
        }
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "set_actuator_command");
    ros::NodeHandle nh;

    ActuatorCommandManager manager(nh);

    ros::ServiceServer service = nh.advertiseService("set_actuator_command", &ActuatorCommandManager::setActuatorCommand, &manager);
    ROS_INFO("Ready to set actuator command.");
    
    ros::spin();

    return 0;
}