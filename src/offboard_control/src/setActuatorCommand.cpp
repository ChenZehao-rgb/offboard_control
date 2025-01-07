#include <ros/ros.h>
#include <mavros_msgs/CommandLong.h>
#include <offboard_control/cameraControl.h>
#include <offboard_control/Measure.h>
#include <std_srvs/SetBool.h>
#include <numeric>
#include <vector>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/Range.h>

class ActuatorCommandManager
{
public:
    ActuatorCommandManager(ros::NodeHandle &nh)
    {
        command_client_ = nh.serviceClient<mavros_msgs::CommandLong>("/uav1/mavros/cmd/command");
        setCameraControlClient_ = nh.serviceClient<offboard_control::cameraControl>("/offboard/camera_control");
        sensor_data_sub_ = nh.subscribe("/transform/sensor_data", 10, &ActuatorCommandManager::getSensorData, this);
        smallUavPoseInBigUavFrameSub_ = nh.subscribe("/transform/small_uav_pose_in_big_uav_frame", 10, &ActuatorCommandManager::smallUavPoseInBigUavFrameCallback, this);
        bigUavPoseSub_ = nh.subscribe("/uav2/mavros/local_position/pose", 10, &ActuatorCommandManager::bigUavPoseCallback, this);
        dist_pub = nh.advertise<sensor_msgs::Range>("/uav1/mavros/distance_sensor/laser_1_sub", 10);
        while (ros::ok())
        {
            // sendLidarData();
            ros::spinOnce();
            ros::Rate(10).sleep();
            if(sensorDate_.is_valid)
            {
                if(sensorDate_.z - 0.5 < 0.05 && sensorDate_.x < 0.05)
                {
                    setActuatorCommand(true);
                    // delay 30s
                    for(int i = 0; i < 30; i++)
                    {
                        ros::spinOnce();
                        ros::Rate(1).sleep();
                        ROS_INFO_STREAM("Grasping : " << i << "s ...");
                    }
                    ROS_INFO_STREAM("Grasp success...");
                    break;
                }
            }
        }
        // holding 10s
        for(int i = 0; i < 10; i++)
        {
            ros::spinOnce();
            ros::Rate(1).sleep();
            ROS_INFO_STREAM("Holding : " << i << "s ...");
        }
        setActuatorCommand(false);
    }
    void sendLidarData()
    {
        sensor_msgs::Range range_msg;
        range_msg.header.stamp = ros::Time::now();
        range_msg.header.frame_id = "lidarlite_laser";
        range_msg.radiation_type = sensor_msgs::Range::INFRARED;
        range_msg.field_of_view = 0.001;
        range_msg.min_range = 0;
        range_msg.max_range = 1000;
        range_msg.range = 328.66;  
        dist_pub.publish(range_msg);
    }
    bool setActuatorCommand(bool grasp)
    {
        mavros_msgs::CommandLong srv;
        srv.request.broadcast = false;
        srv.request.command = 187; // MAV_CMD_DO_SET_ACTUATOR
        srv.request.param2 = grasp ? 1 : -1;  // AUX2
        if (command_client_.call(srv) && srv.response.success)
        {
            ROS_INFO("Command sent successfully");
            return true;
        }
        else
        {
            ROS_ERROR("Failed to send command");
            return false;
        }
    }
    void test_grasp()
    {
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
                ros::Rate(30).sleep();
                if (sensorDate_.is_valid) {
                    sensor_z_readings.push_back(sensorDate_.z);
                    sensor_y_readings.push_back(sensorDate_.x);
                    ROS_INFO_STREAM("Sensor data is valid, z: " << sensorDate_.z << ", x: " << sensorDate_.x);
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
        while(ros::ok())
        {
            ros::spinOnce();
            ros::Rate(30).sleep();
            ROS_INFO_STREAM("Big uav need to adjust y position..., adjust to: " << sensor_y + smallUav_y);
            ROS_INFO_STREAM("Now small uav y: " << smallUavPoseInBigUavFrame_.pose.position.y << ", now big uav y: " << bigUavPose_.pose.position.y);
        }
        // if (sensor_valid) {
        //     // 根据传感器数据调整y坐标, make sure how to get believe y,
        //     targetPointInOnLineState_.pose.position.y = sensor_y + smallUav_y;
        //     setTargetPoint(targetPointInOnLineState_, 2);
        //     ROS_INFO_STREAM("Adjust y position..., adjust y: " << sensor_y + smallUav_y - uavPoseLocalSub2_.pose.position.y);
        //     if (isUavArrived(targetPointInOnLineState_, 2, targetPointError1))
        //     {
        //         ROS_INFO_STREAM("Adjust y position success...");
        //         onLinestate = DESCEND;
        //     }
        // }
    }

private:
    ros::ServiceClient command_client_;
    ros::ServiceClient setCameraControlClient_;
    ros::Subscriber sensor_data_sub_;
    ros::Subscriber smallUavPoseInBigUavFrameSub_, bigUavPoseSub_;
    ros::Publisher dist_pub, dist_pub2;
    ros::Publisher pose_pub, pose_pub2;
    geometry_msgs::PoseStamped smallUavPoseInBigUavFrame_, bigUavPose_;
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
    void bigUavPoseCallback(const geometry_msgs::PoseStamped::ConstPtr &msg)
    {
        bigUavPose_ = *msg;
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

    ROS_INFO("Ready to set actuator command.");
    
    ros::AsyncSpinner spinner(2);
    spinner.start();
    // manager.test_camera();
    ActuatorCommandManager manager(nh);

    return 0;
}