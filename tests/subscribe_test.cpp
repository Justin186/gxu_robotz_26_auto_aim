#include <rclcpp/rclcpp.hpp>
#include <thread>

#include "io/ros2/ros2.hpp"
#include "tools/exiter.hpp"
#include "tools/logger.hpp"

int main(int argc, char ** argv)
{
  tools::Exiter exiter;
  io::ROS2 ros2;

  while (!exiter.exit()) {
    auto x = ros2.subscribe_cmd_vel();
    tools::logger()->info(
      "linear x:{}, y:{}, z:{} angular x:{}, y:{}, z:{}", x.linear.x, x.linear.y, x.linear.z,
      x.angular.x, x.angular.y, x.angular.z);

    std::this_thread::sleep_for(std::chrono::microseconds(500));
  }
  return 0;
}
