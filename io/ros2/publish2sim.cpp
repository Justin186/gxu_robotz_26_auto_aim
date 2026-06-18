#include "publish2sim.hpp"
#include "tools/yaml.hpp"

namespace io
{

publish2sim::publish2sim(rclcpp::Node::SharedPtr node, const std::string & config_path)
: node_(node)
{
  auto yaml = tools::load(config_path);
  auto topic = tools::read<std::string>(yaml, "cmd_topic", "/rm_gimbal/cmd");
  
  publisher_ = node_->create_publisher<rm_interfaces::msg::GimbalCmd>(topic, 10);
  
  RCLCPP_INFO(node_->get_logger(), "Gimbal cmd publisher initialized on topic: %s", topic.c_str());
}

publish2sim::~publish2sim() = default;

void publish2sim::send_gimbal_cmd(
  double pitch, 
  double yaw, 
  double yaw_diff, 
  double pitch_diff, 
  double distance, 
  bool fire_advice)
{
  auto msg = rm_interfaces::msg::GimbalCmd();
  
  msg.pitch = pitch;
  msg.yaw = yaw;
  msg.yaw_diff = yaw_diff;
  msg.pitch_diff = pitch_diff;
  msg.distance = distance;
  msg.fire_advice = fire_advice;
  msg.header.stamp = node_->get_clock()->now();
  msg.header.frame_id = "gimbal_cmd";
  
  publisher_->publish(msg);
}

}  // namespace io