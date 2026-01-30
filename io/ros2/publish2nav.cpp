#include "publish2nav.hpp"

#include <Eigen/Dense>
#include <chrono>
#include <memory>
#include <thread>

#include "tools/logger.hpp"

namespace io
{

Publish2Nav::Publish2Nav() : Node("auto_aim_publisher")
{
  target_pos_pub_ = this->create_publisher<std_msgs::msg::String>("auto_aim_target_pos", 10);
  yaw_pub_ = this->create_publisher<sp_msgs::msg::Float32Stamped>("auto_aim_yaw", 10);

  RCLCPP_INFO(this->get_logger(), "auto_aim_publisher node initialized.");
}

Publish2Nav::~Publish2Nav()
{
  RCLCPP_INFO(this->get_logger(), "auto_aim_publisher node shutting down.");
}

void Publish2Nav::send_target_pos(const Eigen::Vector4d & target_pos)
{
  // 创建消息
  auto message = std::make_shared<std_msgs::msg::String>();

  // 将 Eigen::Vector3d 数据转换为字符串并存储在消息中
  message->data = std::to_string(target_pos[0]) + "," + std::to_string(target_pos[1]) + "," +
                  std::to_string(target_pos[2]) + "," + std::to_string(target_pos[3]);

  // 发布消息
  target_pos_pub_->publish(*message);

  // RCLCPP_INFO(
  //   this->get_logger(), "auto_aim_publisher node sent message: '%s'",
  //   message->data.c_str());
}

void Publish2Nav::send_yaw(const float & yaw)
{
  // 创建消息
  auto message = std::make_shared<sp_msgs::msg::Float32Stamped>();

  message->header.stamp = this->now();

  // 将 Eigen::Vector3d 数据转换为字符串并存储在消息中
  message->data = yaw;

  // 发布消息
  yaw_pub_->publish(*message);

  // RCLCPP_INFO(
  //   this->get_logger(), "auto_aim_publisher node sent message: '%f'",
  //   message->data);
}

void Publish2Nav::start()
{
  RCLCPP_INFO(this->get_logger(), "auto_aim_publisher node starting to spin...");
  rclcpp::spin(this->shared_from_this());
}

}  // namespace io
