#include "subscribe2nav.hpp"

#include <sstream>
#include <vector>
#include <cv_bridge/cv_bridge.h>

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

      // 【新增】在这里向 ROS 订阅那个发图片的节点（话题名比如叫 "/camera/image_raw" ，需根据你实车的话题改名）
  image_subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
    "/odin1/image", 10,
    std::bind(&Subscribe2Nav::image_callback, this, std::placeholders::_1));

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
  // 锁住，别人别动，我要覆盖旧旧图片了
  std::lock_guard<std::mutex> lock(img_mutex_);
  try {
    // 通过 cv_bridge 瞬间把 ROS 的消息转换成我们在 C++ 熟悉好用的 cv::Mat
    latest_img_ = cv_bridge::toCvCopy(msg, "bgr8")->image;
    
    // 把 ROS 的发件时间转换为本地时间戳
    auto stamp = msg->header.stamp;
    latest_stamp_ = std::chrono::steady_clock::time_point(
        std::chrono::seconds(stamp.sec) + std::chrono::nanoseconds(stamp.nanosec)
    );
  } catch (cv_bridge::Exception& e) {
    RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
  }
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
  // 若根本没收到过图片（比如网络断了或发送端没开），就返回 false 表示目前没有图 
  if (latest_img_.empty()) return false; 
  
  // 安全地把最新的图片（克隆一份）和时间交出去
  img = latest_img_.clone();
  timestamp = latest_stamp_;
  return true;
}

}  // namespace io