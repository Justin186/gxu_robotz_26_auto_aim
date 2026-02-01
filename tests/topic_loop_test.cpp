#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>
#include <thread>

#include "io/ros2/ros2.hpp"
#include "tools/exiter.hpp"
#include "tools/logger.hpp"

int main(int argc, char ** argv)
{
  tools::Exiter exiter;
  io::ROS2 ros2;
  auto node = std::make_shared<rclcpp::Node>("topic_loop_tester");
  auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

  int i = 0;
  while (!exiter.exit()) {
    geometry_msgs::msg::Twist msg;
    msg.linear.x = i;
    publisher->publish(msg);
    RCLCPP_INFO(node->get_logger(), "msg send linear.x: %f", msg.linear.x);

    i++;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    auto x = ros2.subscribe_cmd_vel();
    if (x.has_value()) {
      tools::logger()->info("receive linear.x: {}", x->linear.x);
    } else {
      tools::logger()->info("receive no cmd_vel");
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (i > 1000) break;
  }

  return 0;
}
