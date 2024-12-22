#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/NavSatFix.h>
#include <WGS84toCartesian.hpp>

#define M_PI 3.14159265358979323846

class UavCoordinateTrans
{
public:
    UavCoordinateTrans(ros::NodeHandle& nh)
    {
        // 订阅无人机本地位置
        uavPoseSub1 = nh.subscribe<geometry_msgs::PoseStamped>("uav1/mavros/local_position/pose", 10, &UavCoordinateTrans::poseCallback1, this);
        uavPoseSub2 = nh.subscribe<geometry_msgs::PoseStamped>("uav2/mavros/local_position/pose", 10, &UavCoordinateTrans::poseCallback2, this);
        // 订阅无人机地理位置
        uavGeoPoseSub1 = nh.subscribe<sensor_msgs::NavSatFix>("uav1/mavros/global_position/global", 10, &UavCoordinateTrans::geoPoseCallback1, this);
        uavGeoPoseSub2 = nh.subscribe<sensor_msgs::NavSatFix>("uav2/mavros/global_position/global", 10, &UavCoordinateTrans::geoPoseCallback2, this);
        // 发布大无人机目标位置
        bigUavTargetPosePub = nh.advertise<geometry_msgs::PoseStamped>("/transform/big_uav_target_pose", 10);
        // 发布小无人机在大无人机坐标系下的local坐标
        smallUavPoseInBigUavFramePub = nh.advertise<geometry_msgs::PoseStamped>("/transform/small_uav_pose_in_big_uav_frame", 10);
    }

    void spin()
    {
        while (ros::ok())
        {
            ros::Rate(10).sleep();
            ros::spinOnce();
            gps_to_local();
            calculateBigUavPose();
            // ROS_INFO_STREAM("smallUavPoseInBigUavFrame_: " << smallUavPoseInBigUavFrame_);
        }
    }

private:
    // 订阅和发布
    ros::Subscriber uavPoseSub1, uavPoseSub2, uavGeoPoseSub1, uavGeoPoseSub2;
    ros::Publisher bigUavTargetPosePub, smallUavPoseInBigUavFramePub;

    // 小无人机local坐标
    geometry_msgs::PoseStamped smallUavLocalPose_;
    // 大无人机local坐标
    geometry_msgs::PoseStamped bigUavLocalPose_;
    // 大无人机地理坐标
    sensor_msgs::NavSatFix bigUavGeoPose_;
    // 小无人机地理坐标
    sensor_msgs::NavSatFix smallUavGeoPose_;
    // 小无人机在大无人机坐标系下的local坐标
    geometry_msgs::PoseStamped smallUavPoseInBigUavFrame_;
    // 小无人机坐标系下偏移量
    double delta_x = 0.5, delta_y = 0.5, delta_yaw = 30 * M_PI / 180;
    // 大无人机需要调整到的位置
    geometry_msgs::PoseStamped bigUavTargetPose_;

    void poseCallback1(const geometry_msgs::PoseStamped::ConstPtr& msg)
    {
        smallUavLocalPose_ = *msg;
    }

    void poseCallback2(const geometry_msgs::PoseStamped::ConstPtr& msg)
    {
        bigUavLocalPose_ = *msg;
    }

    void geoPoseCallback1(const sensor_msgs::NavSatFix::ConstPtr& msg)
    {
        smallUavGeoPose_ = *msg;
    }

    void geoPoseCallback2(const sensor_msgs::NavSatFix::ConstPtr& msg)
    {
        bigUavGeoPose_ = *msg;
    }

    void quat2RPY(const geometry_msgs::Quaternion &quat, double &roll, double &pitch, double &yaw)
    {
        tf2::Quaternion q(quat.x, quat.y, quat.z, quat.w);
        tf2::Matrix3x3 m(q);
        m.getRPY(roll, pitch, yaw);
    }

    // geo->local
    void gps_to_local()
    {
        std::array<double, 2> delta_EN;
        delta_EN = wgs84::toCartesian({bigUavGeoPose_.latitude, bigUavGeoPose_.longitude}, {smallUavGeoPose_.latitude, smallUavGeoPose_.longitude});
        smallUavPoseInBigUavFrame_.pose.position.x = bigUavLocalPose_.pose.position.x + delta_EN[0];
        smallUavPoseInBigUavFrame_.pose.position.y = bigUavLocalPose_.pose.position.y + delta_EN[1];
        smallUavPoseInBigUavFrame_.pose.position.z = smallUavLocalPose_.pose.position.z;
        smallUavPoseInBigUavFrame_.pose.orientation = smallUavLocalPose_.pose.orientation;
        smallUavPoseInBigUavFramePub.publish(smallUavPoseInBigUavFrame_);
    }

    // 通过小无人机的相对位置和偏移量计算大无人机的位置
    void calculateBigUavPose()
    {
        bigUavTargetPose_.pose.position.x = smallUavPoseInBigUavFrame_.pose.position.x + delta_x;
        bigUavTargetPose_.pose.position.y = smallUavPoseInBigUavFrame_.pose.position.y + delta_y;
        bigUavTargetPose_.pose.position.z = bigUavLocalPose_.pose.position.z;
        // 小无人机四元数->欧拉角，yaw+delta_yaw，再转回四元数
        double roll, pitch, yaw;
        quat2RPY(smallUavPoseInBigUavFrame_.pose.orientation, roll, pitch, yaw);
        yaw += delta_yaw;
        tf2::Quaternion q;
        q.setRPY(roll, pitch, yaw);
        bigUavTargetPose_.pose.orientation.x = q.x();
        bigUavTargetPose_.pose.orientation.y = q.y();
        bigUavTargetPose_.pose.orientation.z = q.z();
        bigUavTargetPose_.pose.orientation.w = q.w();
        // 发布坐标
        bigUavTargetPosePub.publish(bigUavTargetPose_);
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "uav_coordinate_trans");
    ros::NodeHandle nh;
    UavCoordinateTrans uavCoordinateTrans(nh);
    uavCoordinateTrans.spin();
    return 0;
}