#include "ros2.hpp"
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
void ROS2::publish_robot_status(const sp_msgs::msg::RMUCRobotStatus & msg) { robot_status_publisher_->publish(msg); }
void ROS2::publish_game_status(const sp_msgs::msg::RMUCGameStatus & msg) { game_status_publisher_->publish(msg); }
void ROS2::publish_robot_buff(const sp_msgs::msg::RMUCRobotBuff & msg) { robot_buff_publisher_->publish(msg); }

std::optional<geometry_msgs::msg::Twist> ROS2::subscribe_cmd_vel()
{
  return subscribe2nav_->subscribe_cmd_vel();
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
