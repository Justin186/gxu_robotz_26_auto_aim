#ifndef IO__ROS2_HPP
#define IO__ROS2_HPP

#include "publish2nav.hpp"
#include "subscribe2nav.hpp"

#include <opencv2/opencv.hpp>
#include <chrono>
#include <mutex>
#include <optional>
#include <sp_msgs/msg/rmuc_game_status.hpp>
#include <sp_msgs/msg/rmuc_robot_status.hpp>
#include <sp_msgs/msg/rmuc_robot_buff.hpp>
#include <sp_msgs/msg/rmuc_sentry_cmd.hpp>

namespace io
{
class ROS2
{
public:
  ROS2();

  ~ROS2();

  void publish(const Eigen::Vector4d & target_pos);
  void publish(const float & yaw);
  void publish_robot_status(const sp_msgs::msg::RMUCRobotStatus & msg);
  void publish_game_status(const sp_msgs::msg::RMUCGameStatus & msg);
  void publish_robot_buff(const sp_msgs::msg::RMUCRobotBuff & msg);

  std::optional<geometry_msgs::msg::Twist> subscribe_cmd_vel();
  uint8_t get_sentry_cmd_posture();
  bool get_image(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp);
  void clear_image();

private:
  std::shared_ptr<Publish2Nav> publish2nav_;
  std::shared_ptr<rclcpp::Node> node_;
  rclcpp::Publisher<sp_msgs::msg::RMUCRobotStatus>::SharedPtr robot_status_publisher_;
  rclcpp::Publisher<sp_msgs::msg::RMUCGameStatus>::SharedPtr game_status_publisher_;
  rclcpp::Publisher<sp_msgs::msg::RMUCRobotBuff>::SharedPtr robot_buff_publisher_;
  std::shared_ptr<Subscribe2Nav> subscribe2nav_;
  std::mutex robot_status_publish_mutex_;
  std::chrono::steady_clock::time_point last_robot_status_publish_time_{};
  bool robot_status_publish_started_ = false;

  std::unique_ptr<std::thread> publish_spin_thread_;
  std::unique_ptr<std::thread> subscribe_spin_thread_;
};

}  // namespace io
#endif
