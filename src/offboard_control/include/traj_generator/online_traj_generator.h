#ifndef OFFBOARD_TRAJ_GENERATOR_H
#define OFFBOARD_TRAJ_GENERATOR_H

#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <mavros_msgs/PositionTarget.h>
#include <ros/ros.h>
#include <tf/tf.h>

#include "offboard_control/GenTrajOnline.h"
#include "traj_generator/traj_generator.h"

using namespace traj_generator;

class OnlineTrajGenerator : public TrajGenerator {
public:
    OnlineTrajGenerator(const ros::NodeHandle &nh);
    ~OnlineTrajGenerator();

    void updateTrajGeneratorState();
    void updateTrajGeneratorTarg();
    void updateSetPointRaw();

    bool genTrajOnline(offboard_control::GenTrajOnline::Request &req,
                       offboard_control::GenTrajOnline::Response &res);

    ros::NodeHandle nh_;
    mavros_msgs::PositionTarget setPointRawLocal_;
    geometry_msgs::PoseStamped targPointLocal_;
    geometry_msgs::PoseStamped uavPoseLocal_;
    geometry_msgs::TwistStamped uavTwistLocal_;

    ros::Publisher ruckigStatePub_;
    ros::Publisher ruckigCommandPub_;
    ros::Publisher ruckigTargPub_;

    ros::ServiceServer genTarjSer1_;
    ros::ServiceServer genTarjSer2_;
};

#endif
