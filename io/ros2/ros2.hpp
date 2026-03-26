#ifndef IO__ROS2_HPP
#define IO__ROS2_HPP

#include "publish2nav.hpp"
#include "subscribe2nav.hpp"

#include <optional>
#include <sp_msgs/msg/rmul.hpp>

namespace io
{
class ROS2
{
public:
  ROS2();

  ~ROS2();

  void publish(const Eigen::Vector4d & target_pos);
  void publish(const float & yaw);
  void publish_robot_status(const sp_msgs::msg::RMUL & msg);
  void publish_game_status(const sp_msgs::msg::RMUL & msg);

  std::optional<geometry_msgs::msg::Twist> subscribe_cmd_vel();

private:
  std::shared_ptr<Publish2Nav> publish2nav_;
  std::shared_ptr<rclcpp::Node> node_;
  rclcpp::Publisher<sp_msgs::msg::RMUL>::SharedPtr robot_status_publisher_;
  rclcpp::Publisher<sp_msgs::msg::RMUL>::SharedPtr game_status_publisher_;
  std::shared_ptr<Subscribe2Nav> subscribe2nav_;

  std::unique_ptr<std::thread> publish_spin_thread_;
  std::unique_ptr<std::thread> subscribe_spin_thread_;
};

}  // namespace io
#endif