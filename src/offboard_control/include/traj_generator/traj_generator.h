#ifndef TRAJ_GENERATOR_H
#define TRAJ_GENERATOR_H

#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <ruckig/ruckig.hpp>
#include <vector>
#include "std_msgs/Bool.h"
#include "std_msgs/Int32.h"

#define YAW_VEL_LIMIT 0.2
#define YAW_ACC_LIMIT 2.0
#define YAW_JERK_LIMIT 20.0

namespace traj_generator{
const int STATE_NUM = 4;
const double Ts = 0.05;
const double POS_ERROR_TOLERATE = 0.05;
const double YAW_ERROR_TOLERATE = 0.05;

const std::vector<double> VEL_LIMIT = {10.0, 10.0, 2.0, YAW_VEL_LIMIT};
const std::vector<double> ACC_LIMIT = {1.0, 1.0, 1.0, YAW_ACC_LIMIT};
const std::vector<double> JERK_LIMIT = {0.7, 0.7, 0.5, YAW_JERK_LIMIT};

class TrajGenerator {
public:
    TrajGenerator(){
        state_.name = {"pos_x", "pos_y", "pos_z", "yaw"};
        state_.position = {0.0, 0.0, 0.0, 0.0};
        state_.velocity = {0.0, 0.0, 0.0, 0.0};
        state_.effort = {0.0, 0.0, 0.0, 0.0};

        command_.name = {"pos_x", "pos_y", "pos_z", "yaw"};
        command_.position = {0.0, 0.0, 0.0, 0.0};
        command_.velocity = {0.0, 0.0, 0.0, 0.0};
        command_.effort = {0.0, 0.0, 0.0, 0.0};

        targ_.name = {"pos_x", "pos_y", "pos_z", "yaw"};
        targ_.position = {0.0, 0.0, 0.0, 0.0};
        targ_.velocity = {0.0, 0.0, 0.0, 0.0};
        targ_.effort = {0.0, 0.0, 0.0, 0.0};

        initRuckig();
    };
    ~TrajGenerator(){};

    void initRuckig(){
        for(std::size_t id = 0; id < STATE_NUM; id++){
            ruckigInput_.max_velocity[id] = VEL_LIMIT[id];
            ruckigInput_.max_acceleration[id] = ACC_LIMIT[id];
            ruckigInput_.max_jerk[id] = JERK_LIMIT[id];
        }

        for(std::size_t id = 0; id < STATE_NUM; id++){
            ruckigInput_.current_position[id] = 0.0;
            ruckigInput_.current_velocity[id] = 0.0;
            ruckigInput_.current_acceleration[id] = 0.0;
        }

        for(std::size_t id = 0; id < STATE_NUM; id++){
            ruckigInput_.target_position[id] = 0.0;
            ruckigInput_.target_velocity[id] = 0.0;
            ruckigInput_.target_acceleration[id] = 0.0;
        }

        return;
    };

    bool trajGenerate(){
        for (std::size_t id = 0; id < STATE_NUM; id++){
            ruckigInput_.current_position[id] = state_.position[id];
            ruckigInput_.current_velocity[id] = state_.velocity[id];
            ruckigInput_.current_acceleration[id] = state_.effort[id];
        }

        for (std::size_t id = 0; id < STATE_NUM; id++){
            ruckigInput_.target_position[id] = targ_.position[id];
            ruckigInput_.target_velocity[id] = 0.0;
            ruckigInput_.target_acceleration[id] = 0.0;
        }

        ruckig::Result res = ruckigOtg_.update(ruckigInput_, ruckigOutput_);
        if (res == ruckig::Result::Working || res == ruckig::Result::Finished ){
            for (std::size_t id = 0; id < STATE_NUM; id++) {
            command_.position[id] = ruckigOutput_.new_position[id];
            command_.velocity[id] = ruckigOutput_.new_velocity[id];
            command_.effort[id] = ruckigOutput_.new_acceleration[id];
        }
        return true;
        }else{
            switch (res) {
        case ruckig::Result::Error:  // Unclassified error
          ROS_ERROR_STREAM(
              "TrajGenerator::trajGenerate: ruckig res is \"Error\"");
          break;
        case ruckig::Result::ErrorInvalidInput:  // Error in the input parameter
          ROS_ERROR_STREAM(
              "TrajGenerator::trajGenerate: ruckig res is "
              "\"ErrorInvalidInput\"");
          break;
        case ruckig::Result::ErrorTrajectoryDuration:  // The trajectory
                                                       // duration exceed the
                                                       // numeral limits
          ROS_ERROR_STREAM(
              "TrajGenerator::trajGenerate: ruckig res is "
              "\"ErrorTrajectoryDuration\"");
          break;
        case ruckig::Result::
            ErrorExecutionTimeCalculation:  // Error during the extremel time
                                            // calculation (Step 1)
          ROS_ERROR_STREAM(
              "TrajGenerator::trajGenerate: ruckig res is "
              "\"ErrorExecutionTimeCalculation\"");
          break;
        case ruckig::Result::
            ErrorSynchronizationCalculation:  // Error during the
                                              // synchronization calculation
                                              // (Step 2)
          ROS_ERROR_STREAM(
              "TrajGenerator::trajGenerate: ruckig res is "
              "\"ErrorSynchronizationCalculation\"");
          break;
        default:;
      }
      return false;
      }
    };

    // States
    sensor_msgs::JointState state_;

    // Commands
    sensor_msgs::JointState command_;

    // targ
    sensor_msgs::JointState targ_;

    std::vector<double> velocityLimits_;
    std::vector<double> accLimits_;

protected:
    ruckig::Ruckig<STATE_NUM> ruckigOtg_{Ts};
    ruckig::InputParameter<STATE_NUM> ruckigInput_;
    ruckig::OutputParameter<STATE_NUM> ruckigOutput_;
};
}
#endif