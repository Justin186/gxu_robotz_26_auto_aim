#include "gimbal_node.h"
#include "tools/crc.hpp"
#include "tools/logger.hpp"
#include "tools/yaml.hpp"

namespace io
{

GimbalNode::GimbalNode(const std::string & config_path) : Gimbal(config_path), Node("gimbal_node")
{
    auto yaml = tools::load(config_path);
    auto cmd_vel_topic = tools::read<std::string>(yaml, "cmd_vel_topic");
    cmd_vel_subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
        cmd_vel_topic, 10, std::bind(
            &GimbalNode::send_cmd_vel,
            this,
            std::placeholders::_1
        ));
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