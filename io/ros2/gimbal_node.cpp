#include "gimbal_node.hpp"
#include "tools/crc.hpp"
#include "tools/logger.hpp"
#include "io/ros2/ros2.hpp"

namespace io
{

GimbalNode::GimbalNode(const std::string & config_path) : Gimbal(config_path)
{
    ros2_ = std::make_shared<ROS2>();
    
    thread_ = std::make_unique<std::thread>([this]() {
        while (rclcpp::ok() && !node_quit_) {
            auto cmd_vel = ros2_->subscribe_cmd_vel();
            this->send_cmd_vel(std::make_shared<geometry_msgs::msg::Twist>(cmd_vel));
            ros2_->publish(this->yaw());
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });

    tools::logger()->info("GimbalNode thread started.");
}
GimbalNode::~GimbalNode()
{
    node_quit_ = true;
    if (thread_ && thread_->joinable()) {
        thread_->join();
    }
}

void GimbalNode::send_cmd_vel(const geometry_msgs::msg::Twist::SharedPtr msg)
{
    nav_tx_data_.linear_x = msg->linear.x;
    nav_tx_data_.linear_y = msg->linear.y;
    nav_tx_data_.linear_z = msg->linear.z;
    nav_tx_data_.angular_x = msg->angular.x;
    nav_tx_data_.angular_y = msg->angular.y;
    nav_tx_data_.angular_z = msg->angular.z;
    nav_tx_data_.crc16 = tools::get_crc16(
        reinterpret_cast<uint8_t *>(&nav_tx_data_), sizeof(nav_tx_data_) - sizeof(nav_tx_data_.crc16));
    
    std::lock_guard<std::mutex> lock(mutex_);
    try {
    this->serial_.write(reinterpret_cast<uint8_t *>(&nav_tx_data_), sizeof(nav_tx_data_));
    } catch (const std::exception & e) {
    tools::logger()->warn("[Gimbal] Failed to write serial: {}", e.what());
    }
}

void GimbalNode::send(io::VisionToGimbal VisionToGimbal) {
    std::lock_guard<std::mutex> lock(mutex_);
    Gimbal::send(VisionToGimbal);
}
};