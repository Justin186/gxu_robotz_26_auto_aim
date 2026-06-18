#ifndef IO__PUBLISH2SIM_HPP
#define IO__PUBLISH2SIM_HPP

#include <rclcpp/rclcpp.hpp>
#include "rm_interfaces/msg/gimbal_cmd.hpp"

namespace io
{
class publish2sim
{
public:
  publish2sim(rclcpp::Node::SharedPtr node, const std::string & config_path);
  ~publish2sim();

  void send_gimbal_cmd(
    double pitch, 
    double yaw, 
    double yaw_diff, 
    double pitch_diff, 
    double distance, 
    bool fire_advice);

private:
  rclcpp::Node::SharedPtr node_;
  rclcpp::Publisher<rm_interfaces::msg::GimbalCmd>::SharedPtr publisher_;
};

}  // namespace io
#endif