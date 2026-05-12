#include "subscribe2nav.hpp"

#include <cstring>
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

  image_subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
    "/odin1/image", 10,
    std::bind(&Subscribe2Nav::image_callback, this, std::placeholders::_1));

  sentry_cmd_subscription_ = this->create_subscription<sp_msgs::msg::RMUCSentryCmd>(
    "/sentry_cmd", 10,
    std::bind(&Subscribe2Nav::sentry_cmd_callback, this, std::placeholders::_1));

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

void Subscribe2Nav::image_callback(const sensor_msgs::msg::Image::ConstSharedPtr msg)
{
  std::lock_guard<std::mutex> lock(img_mutex_);
  if (msg->encoding != "bgr8") {
    RCLCPP_ERROR(this->get_logger(), "Unsupported image encoding: %s", msg->encoding.c_str());
    return;
  }

  if (msg->data.empty()) return;

  cv::Mat img(static_cast<int>(msg->height), static_cast<int>(msg->width), CV_8UC3);
  const auto row_bytes = static_cast<size_t>(msg->width) * 3;
  for (size_t row = 0; row < msg->height; ++row) {
    std::memcpy(
      img.ptr(static_cast<int>(row)),
      msg->data.data() + row * msg->step,
      row_bytes);
  }

  latest_img_ = img;
  auto stamp = msg->header.stamp;
  latest_stamp_ = std::chrono::steady_clock::time_point(
    std::chrono::seconds(stamp.sec) + std::chrono::nanoseconds(stamp.nanosec));
}

void Subscribe2Nav::start()
{
  RCLCPP_INFO(this->get_logger(), "nav_subscriber node Starting to spin...");
  rclcpp::spin(this->shared_from_this());
}

std::optional<geometry_msgs::msg::Twist> Subscribe2Nav::subscribe_cmd_vel()
{
  if (cmd_vel_queue_.empty()) {
    return std::nullopt;
  }

  return cmd_vel_queue_.pop();
}

bool Subscribe2Nav::get_image(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp)
{
  std::lock_guard<std::mutex> lock(img_mutex_);
  if (latest_img_.empty()) return false;

  img = latest_img_.clone();
  timestamp = latest_stamp_;
  latest_img_.release();
  return true;
}

void Subscribe2Nav::clear_image()
{
  std::lock_guard<std::mutex> lock(img_mutex_);
  latest_img_.release();
}

void Subscribe2Nav::sentry_cmd_callback(const sp_msgs::msg::RMUCSentryCmd::SharedPtr msg)
{
  current_posture_.store(msg->cmd_posture);
  // RCLCPP_INFO(this->get_logger(), "Received sentry cmd_posture: %d", msg->cmd_posture);
}

}  // namespace io
