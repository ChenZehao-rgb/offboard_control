#include <traj_generator/online_traj_generator.h>

void quat2RPY(const geometry_msgs::Quaternion &quat, double &roll,
              double &pitch, double &yaw) {
  tf::Quaternion q(quat.x, quat.y, quat.z, quat.w);
  tf::Matrix3x3 m(q);
  m.getRPY(roll, pitch, yaw);
  return;
}

OnlineTrajGenerator::OnlineTrajGenerator(const ros::NodeHandle &nh)
  : TrajGenerator(), nh_{nh} {
    genTarjSer_ = nh_.advertiseService("online_traj_generator/gen_traj_online",
                                        &OnlineTrajGenerator::genTrajOnline, this);
    ruckigStatePub_ = nh_.advertise<sensor_msgs::JointState>(
                      "/online_traj_generator/ruckig_state", 10);
    ruckigCommandPub_ = nh_.advertise<sensor_msgs::JointState>(
                        "/online_traj_generator/ruckig_command", 10);
    ruckigTargPub_ = nh_.advertise<sensor_msgs::JointState>(
                        "/online_traj_generator/ruckig_targ", 10);
  };

OnlineTrajGenerator::~OnlineTrajGenerator(){};

void OnlineTrajGenerator::updateTrajGeneratorState(){
  state_.position[0] = uavPoseLocal_.pose.position.x;
  state_.position[1] = uavPoseLocal_.pose.position.y;
  state_.position[2] = uavPoseLocal_.pose.position.z;
  double roll, pitch, yaw;
  quat2RPY(uavPoseLocal_.pose.orientation, roll, pitch, yaw);
  state_.position[3] = yaw;

  state_.velocity[0] = uavTwistLocal_.twist.linear.x;
  state_.velocity[1] = uavTwistLocal_.twist.linear.y;
  state_.velocity[2] = uavTwistLocal_.twist.linear.z;
  state_.velocity[3] = uavImuData_.angular_velocity.z;

  state_.effort[0] = uavImuData_.linear_acceleration.x;
  state_.effort[1] = uavImuData_.linear_acceleration.y;
  state_.effort[2] = uavImuData_.linear_acceleration.z - 9.81;
}

void OnlineTrajGenerator::updateTrajGeneratorTarg(){
  targ_.position[0] = targPointLocal_.pose.position.x;
  targ_.position[1] = targPointLocal_.pose.position.y;
  targ_.position[2] = targPointLocal_.pose.position.z;
  targ_.position[3] = M_PI_2;
  // velocity and acceleration are set to zero
}

void OnlineTrajGenerator::updateSetPointRaw(){
  setPointRawLocal_.position.x = command_.position[0];
  setPointRawLocal_.position.y = command_.position[1];
  setPointRawLocal_.position.z = command_.position[2];
  setPointRawLocal_.yaw = command_.position[3];


  setPointRawLocal_.velocity.x = command_.velocity[0];
  setPointRawLocal_.velocity.y = command_.velocity[1];
  setPointRawLocal_.velocity.z = command_.velocity[2];
  setPointRawLocal_.yaw_rate = command_.velocity[3];

  setPointRawLocal_.acceleration_or_force.x = command_.effort[0];
  setPointRawLocal_.acceleration_or_force.y = command_.effort[1];
  setPointRawLocal_.acceleration_or_force.z = command_.effort[2];
}

bool OnlineTrajGenerator::genTrajOnline(
    offboard_control::GenTrajOnline::Request &req,
    offboard_control::GenTrajOnline::Response &res) {
  ROS_WARN_STREAM_THROTTLE(10, "call genTrajOnline once");

  targPointLocal_ = req.targPoint;
  uavPoseLocal_ = req.pose;
  uavTwistLocal_ = req.twist;
  uavImuData_ = req.imuData;

  updateTrajGeneratorState();
  
  updateTrajGeneratorTarg();

  if (!trajGenerate()) {
    res.success = false;
    ROS_ERROR_STREAM("trajGenerate: genTrajOnline failed");
    return false;
  }
  updateSetPointRaw();
  ruckigStatePub_.publish(state_);
  ruckigTargPub_.publish(targ_);
  ruckigCommandPub_.publish(command_);

  res.setPointRaw = setPointRawLocal_;
  res.success = true;

  return true;
}

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "online_traj_generator");
  ros::NodeHandle nh;
  ros::AsyncSpinner spinner(2);
  spinner.start();
  OnlineTrajGenerator onlineTrajGen(nh);
  while (ros::ok()) {
    ros::Duration(1.0).sleep();
  }
  return 0;
}


