#include <ros/ros.h>
#include <Eigen/Geometry>
#include <ruckig/ruckig.hpp>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <sensor_msgs/Imu.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>

using namespace ruckig;

class DroneController {
private:
    ros::NodeHandle nh_;
    
    // ROS subscribers
    ros::Subscriber pose_sub_;
    ros::Subscriber vel_sub_;
    ros::Subscriber imu_sub_;
    ros::Subscriber state_sub_;
    
    // ROS publishers
    ros::Publisher setpoint_pub_;
    
    // ROS service clients
    ros::ServiceClient arming_client_;
    ros::ServiceClient set_mode_client_;
    
    // Current state
    std::array<double, 3> current_position_{0, 0, 0};
    std::array<double, 3> current_velocity_{0, 0, 0};
    std::array<double, 3> current_acceleration_{0, 0, 0};
    double current_yaw_{0};
    mavros_msgs::State current_state_;
    
    // Ruckig instances
    Ruckig<3> otg_pos_{0.01};  // Position OTG (3 DoF)
    InputParameter<3> input_pos_;
    OutputParameter<3> output_pos_;
    
    Ruckig<1> otg_yaw_{0.01};  // Yaw OTG (1 DoF)
    InputParameter<1> input_yaw_;
    OutputParameter<1> output_yaw_;

    // Control flags
    bool is_armed_{false};
    bool offboard_mode_activated_{false};
    bool trajectory_started_{false};

public:
    DroneController() {
        // Initialize subscribers
        pose_sub_ = nh_.subscribe("/mavros/local_position/pose", 1, 
            &DroneController::poseCallback, this);
        vel_sub_ = nh_.subscribe("/mavros/local_position/velocity_local", 1,
            &DroneController::velocityCallback, this);
        imu_sub_ = nh_.subscribe("/mavros/imu/data", 1,
            &DroneController::imuCallback, this);
        state_sub_ = nh_.subscribe("/mavros/state", 10,
            &DroneController::stateCallback, this);
            
        // Initialize publisher
        setpoint_pub_ = nh_.advertise<geometry_msgs::PoseStamped>(
            "/mavros/setpoint_position/local", 10);
            
        // Initialize service clients
        arming_client_ = nh_.serviceClient<mavros_msgs::CommandBool>(
            "/mavros/cmd/arming");
        set_mode_client_ = nh_.serviceClient<mavros_msgs::SetMode>(
            "/mavros/set_mode");

        // Configure Ruckig constraints
        setupPositionConstraints();
        setupYawConstraints();
    }

    void setupPositionConstraints() {
        input_pos_.max_velocity = {3.0, 3.0, 3.0};
        input_pos_.max_acceleration = {2.0, 2.0, 2.0};
        input_pos_.max_jerk = {4.0, 4.0, 4.0};
        
        // 初始目标位置设为起飞点上方2米
        input_pos_.target_position = {0.0, 0.0, 2.0};
        input_pos_.target_velocity = {0.0, 0.0, 0.0};
        input_pos_.target_acceleration = {0.0, 0.0, 0.0};
    }

    void setupYawConstraints() {
        input_yaw_.max_velocity = {1.0};
        input_yaw_.max_acceleration = {2.0};
        input_yaw_.max_jerk = {3.0};
        input_yaw_.target_position = {0.0};
        input_yaw_.target_velocity = {0.0};
        input_yaw_.target_acceleration = {0.0};
    }

    void stateCallback(const mavros_msgs::State::ConstPtr& msg) {
        current_state_ = *msg;
    }

    void poseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
        current_position_ = {
            msg->pose.position.x, 
            msg->pose.position.y, 
            msg->pose.position.z
        };
        
        tf2::Quaternion q(
            msg->pose.orientation.x,
            msg->pose.orientation.y,
            msg->pose.orientation.z,
            msg->pose.orientation.w);
        tf2::Matrix3x3 m(q);
        double roll, pitch, yaw;
        m.getRPY(roll, pitch, yaw);
        current_yaw_ = yaw;
    }

    void velocityCallback(const geometry_msgs::TwistStamped::ConstPtr& msg) {
        current_velocity_ = {
            msg->twist.linear.x,
            msg->twist.linear.y,
            msg->twist.linear.z
        };
    }

    void imuCallback(const sensor_msgs::Imu::ConstPtr& msg) {
        Eigen::Vector3d accel_body(
            msg->linear_acceleration.x,
            msg->linear_acceleration.y,
            msg->linear_acceleration.z);
        
        tf2::Quaternion q(
            msg->orientation.x,
            msg->orientation.y,
            msg->orientation.z,
            msg->orientation.w);
        Eigen::Quaterniond eigen_q(q.w(), q.x(), q.y(), q.z());
        Eigen::Matrix3d rotation_matrix = eigen_q.toRotationMatrix();
        
        Eigen::Vector3d accel_enu = rotation_matrix * accel_body;
        accel_enu.z() -= 9.81;
        
        current_acceleration_ = {
            accel_enu.x(), 
            accel_enu.y(), 
            accel_enu.z()
        };
    }

    bool setMode(const std::string& mode) {
        mavros_msgs::SetMode srv;
        srv.request.custom_mode = mode;
        if(set_mode_client_.call(srv)) {
            return srv.response.mode_sent;
        }
        return false;
    }

    bool arm(bool arm) {
        mavros_msgs::CommandBool srv;
        srv.request.value = arm;
        if(arming_client_.call(srv)) {
            return srv.response.success;
        }
        return false;
    }

    void run() {
        ros::Rate rate(20);  // 初始频率20Hz用于模式切换
        
        // Step 1: 等待MAVROS连接
        while(ros::ok() && !current_state_.connected) {
            ros::spinOnce();
            rate.sleep();
        }
        
        // Step 2: 发送初始设定点
        geometry_msgs::PoseStamped init_pose;
        init_pose.pose.position.z = 2.0;
        for(int i = 0; ros::ok() && i < 100; ++i) {
            setpoint_pub_.publish(init_pose);
            ros::spinOnce();
            rate.sleep();
        }
        
        // Step 3: 切换至Offboard模式
        if(setMode("OFFBOARD")) {
            ROS_INFO("Offboard模式已激活");
            offboard_mode_activated_ = true;
        } else {
            ROS_ERROR("无法切换至Offboard模式");
            return;
        }
        
        // Step 4: 解锁无人机
        if(arm(true)) {
            ROS_INFO("无人机已解锁");
            is_armed_ = true;
        } else {
            ROS_ERROR("无人机解锁失败");
            return;
        }
        
        // 提升控制频率至100Hz
        rate = ros::Rate(100);
        
        // Step 5: 主控制循环
        while(ros::ok()) {
            // 更新Ruckig输入
            input_pos_.current_position = current_position_;
            input_pos_.current_velocity = current_velocity_;
            input_pos_.current_acceleration = current_acceleration_;
            
            input_yaw_.current_position = {current_yaw_};
            input_yaw_.current_velocity = {0.0};
            input_yaw_.current_acceleration = {0.0};
            
            // 检查是否到达起飞高度
            if(!trajectory_started_ && current_position_[2] > 1.8) {
                ROS_INFO("到达起飞高度，开始主轨迹");
                input_pos_.target_position = {5.0, 5.0, 5.0};  // 设置最终目标
                trajectory_started_ = true;
            }
            
            // 生成轨迹
            auto result_pos = otg_pos_.update(input_pos_, output_pos_);
            auto result_yaw = otg_yaw_.update(input_yaw_, output_yaw_);
            
            if(result_pos == Result::Working && result_yaw == Result::Working) {
                publishSetpoint(output_pos_.new_position, output_yaw_.new_position[0]);
            }
            
            // 传递状态到下一周期
            output_pos_.pass_to_input(input_pos_);
            output_yaw_.pass_to_input(input_yaw_);
            
            rate.sleep();
            ros::spinOnce();
        }
    }

    void publishSetpoint(const std::array<double, 3>& position, double yaw) {
        geometry_msgs::PoseStamped msg;
        msg.header.stamp = ros::Time::now();
        
        msg.pose.position.x = position[0];
        msg.pose.position.y = position[1];
        msg.pose.position.z = position[2];
        
        tf2::Quaternion q;
        q.setRPY(0, 0, yaw);
        msg.pose.orientation.x = q.x();
        msg.pose.orientation.y = q.y();
        msg.pose.orientation.z = q.z();
        msg.pose.orientation.w = q.w();
        
        setpoint_pub_.publish(msg);
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "drone_controller");
    DroneController controller;
    controller.run();
    return 0;
}