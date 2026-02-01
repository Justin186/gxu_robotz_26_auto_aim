#ifndef IO__SUBSCRIBE2NAV_HPP
#define IO__SUBSCRIBE2NAV_HPP

#include <rclcpp/rclcpp.hpp>
#include <rclcpp/timer.hpp>
#include <vector>
#include <optional>

#include <geometry_msgs/msg/twist.hpp>
#include "tools/thread_safe_queue.hpp"

namespace io
{
class Subscribe2Nav : public rclcpp::Node
{
public:
  Subscribe2Nav();

  ~Subscribe2Nav();

  void start();

  std::optional<geometry_msgs::msg::Twist> subscribe_cmd_vel();

private:
  void cmd_vel_callback(const geometry_msgs::msg::Twist::SharedPtr msg);

  int cmd_vel_counter_;

  rclcpp::TimerBase::SharedPtr cmd_vel_timer_;

  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_subscription_;

  tools::ThreadSafeQueue<geometry_msgs::msg::Twist> cmd_vel_queue_;
};
}  // namespace io

#endif  // IO__SUBSCRIBE2NAV_HPP
