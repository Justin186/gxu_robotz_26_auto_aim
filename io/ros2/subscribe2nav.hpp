#ifndef IO__SUBSCRIBE2NAV_HPP
#define IO__SUBSCRIBE2NAV_HPP

#include <rclcpp/rclcpp.hpp>
#include <rclcpp/timer.hpp>
#include <vector>
#include <optional>
#include <chrono>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/msg/image.hpp>

#include <geometry_msgs/msg/twist.hpp>
#include <sp_msgs/msg/rmuc_sentry_cmd.hpp>
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
  uint8_t get_sentry_cmd_posture() const { return current_posture_.load(); }
  bool get_image(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp);
  void clear_image();

private:
  void cmd_vel_callback(const geometry_msgs::msg::Twist::SharedPtr msg);
  void image_callback(const sensor_msgs::msg::Image::ConstSharedPtr msg);
  void sentry_cmd_callback(const sp_msgs::msg::RMUCSentryCmd::SharedPtr msg);

  int cmd_vel_counter_;

  rclcpp::TimerBase::SharedPtr cmd_vel_timer_;

  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_subscription_;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscription_;
  rclcpp::Subscription<sp_msgs::msg::RMUCSentryCmd>::SharedPtr sentry_cmd_subscription_;

  tools::ThreadSafeQueue<geometry_msgs::msg::Twist> cmd_vel_queue_;
  std::atomic<uint8_t> current_posture_{0};
  std::mutex img_mutex_;
  cv::Mat latest_img_;
  std::chrono::steady_clock::time_point latest_stamp_;
};
}  // namespace io

#endif  // IO__SUBSCRIBE2NAV_HPP
