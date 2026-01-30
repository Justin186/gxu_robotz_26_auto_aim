#ifndef IO__PBLISH2NAV_HPP
#define IO__PBLISH2NAV_HPP

#include <Eigen/Dense>  // For Eigen::Vector3d
#include <chrono>
#include <deque>
#include <memory>
#include <mutex>
#include <optional>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sp_msgs/msg/float32_stamped.hpp"

namespace io
{
class Publish2Nav : public rclcpp::Node
{
public:
  Publish2Nav();

  ~Publish2Nav();

  void start();

  void send_target_pos(const Eigen::Vector4d & data);
  void send_yaw(const float & yaw);

private:
  // ROS2 发布者
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr target_pos_pub_;
  rclcpp::Publisher<sp_msgs::msg::Float32Stamped>::SharedPtr yaw_pub_;
};

}  // namespace io

#endif  // Publish2Nav_HPP_
