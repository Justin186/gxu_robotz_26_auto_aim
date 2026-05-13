#include "ros2.hpp"
#include "tools/logger.hpp"
#include "tools/crc.hpp"

namespace io
{
ROS2::ROS2()
{
  rclcpp::init(0, nullptr);
  node_ = std::make_shared<rclcpp::Node>("ros2_interface_node");
  robot_status_publisher_ = node_->create_publisher<sp_msgs::msg::RMUCRobotStatus>("/robot_status", 10);
  game_status_publisher_ = node_->create_publisher<sp_msgs::msg::RMUCGameStatus>("/game_status", 10);
  robot_buff_publisher_ = node_->create_publisher<sp_msgs::msg::RMUCRobotBuff>("/robot_buff", 10);

  publish2nav_ = std::make_shared<Publish2Nav>();

  subscribe2nav_ = std::make_shared<Subscribe2Nav>();

  publish_spin_thread_ = std::make_unique<std::thread>([this]() { publish2nav_->start(); });

  subscribe_spin_thread_ = std::make_unique<std::thread>([this]() { subscribe2nav_->start(); });
}

ROS2::~ROS2()
{
  rclcpp::shutdown();
  publish_spin_thread_->join();
  subscribe_spin_thread_->join();
}

void ROS2::publish(const Eigen::Vector4d & target_pos) { publish2nav_->send_target_pos(target_pos); }
void ROS2::publish(const float & yaw) { publish2nav_->send_yaw(yaw); }
void ROS2::publish_robot_status(const sp_msgs::msg::RMUCRobotStatus & msg)
{
  const auto now = std::chrono::steady_clock::now();
  const auto publish_interval = std::chrono::milliseconds(100);

  std::lock_guard<std::mutex> lock(robot_status_publish_mutex_);
  if (
    robot_status_publish_started_ &&
    now - last_robot_status_publish_time_ < publish_interval)
  {
    return;
  }

  robot_status_publish_started_ = true;
  last_robot_status_publish_time_ = now;
  robot_status_publisher_->publish(msg);
  tools::logger()->debug("publish robot_status");
}
void ROS2::publish_game_status(const sp_msgs::msg::RMUCGameStatus & msg) { game_status_publisher_->publish(msg); }
void ROS2::publish_robot_buff(const sp_msgs::msg::RMUCRobotBuff & msg) { robot_buff_publisher_->publish(msg); }

std::optional<geometry_msgs::msg::Twist> ROS2::subscribe_cmd_vel()
{
  return subscribe2nav_->subscribe_cmd_vel();
}

uint8_t ROS2::get_sentry_cmd_posture()
{
  return subscribe2nav_->get_sentry_cmd_posture();
}

bool ROS2::get_image(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp)
{
  return subscribe2nav_->get_image(img, timestamp);
}

void ROS2::clear_image()
{
  subscribe2nav_->clear_image();
}

}  // namespace io
