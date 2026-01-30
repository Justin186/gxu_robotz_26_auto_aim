#include "subscribe2nav.hpp"

#include <sstream>
#include <vector>

namespace io
{

Subscribe2Nav::Subscribe2Nav()
: Node("nav_subscriber"),
  cmd_vel_queue_(1),
  cmd_vel_counter_(0)
{
  cmd_vel_subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
    "/cmd_vel", 10,
    std::bind(&Subscribe2Nav::cmd_vel_callback, this, std::placeholders::_1));

  RCLCPP_INFO(this->get_logger(), "nav_subscriber node initialized.");
}

Subscribe2Nav::~Subscribe2Nav()
{
  RCLCPP_INFO(this->get_logger(), "nav_subscriber node shutting down.");
}

void Subscribe2Nav::cmd_vel_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
{
  cmd_vel_queue_.clear();
  cmd_vel_queue_.push(*msg);

  cmd_vel_counter_++;

  if (cmd_vel_counter_ >= 2) {
    if (cmd_vel_timer_) {
      cmd_vel_timer_->cancel();
    }
    cmd_vel_timer_ = this->create_wall_timer(std::chrono::milliseconds(1500), [this]() {
      cmd_vel_queue_.clear();
      cmd_vel_timer_ = 0;
      RCLCPP_INFO(
        this->get_logger(), "Cmd_vel queue cleared due to inactivity after two messages.");
    });
  }
}

void Subscribe2Nav::start()
{
  RCLCPP_INFO(this->get_logger(), "nav_subscriber node Starting to spin...");
  rclcpp::spin(this->shared_from_this());
}

geometry_msgs::msg::Twist Subscribe2Nav::subscribe_cmd_vel()
{
  geometry_msgs::msg::Twist msg;
  if (cmd_vel_queue_.empty()) {
    return msg;
  }

  cmd_vel_queue_.back(msg);
  // RCLCPP_INFO(
  //   this->get_logger(), "Subscribe cmd_vel at: linear(%f, %f, %f), angular(%f, %f, %f)",
  //   msg.linear.x, msg.linear.y, msg.linear.z, msg.angular.x, msg.angular.y, msg.angular.z);

  return msg;
}

}  // namespace io