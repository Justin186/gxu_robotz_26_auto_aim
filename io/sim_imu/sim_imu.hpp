#ifndef IO__SIM_IMU_HPP
#define IO__SIM_IMU_HPP

#include <Eigen/Geometry>
#include <atomic>
#include <chrono>
#include <mutex>
#include <string>
#include <thread>
#include <tuple>

#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tools/thread_safe_queue.hpp"
#include "tools/math_tools.hpp"

namespace io
{

struct SimIMUState
{
  float yaw = 0.0f;
  float yaw_vel = 0.0f;
  float pitch = 0.0f;
  float pitch_vel = 0.0f;
  float bullet_speed = 0.0f;
  uint16_t bullet_count = 0;
  int8_t yaw_offset = 0;
  int8_t pitch_offset = 0;
};

class SimIMU
{
public:
  // 使用外部传入的节点（推荐）
  SimIMU(rclcpp::Node::SharedPtr node, const std::string & config_path);
  
  // 或者自己创建节点（不推荐，但兼容）
  SimIMU(const std::string & config_path);
  
  ~SimIMU();

  SimIMUState state() const;
  
  // 和原 Gimbal 完全一样的 q() 接口，带时间同步插值
  Eigen::Quaterniond q(std::chrono::steady_clock::time_point t);
  
  bool get_current_quat(Eigen::Quaterniond & quat);

private:
  void tf_callback(const tf2_msgs::msg::TFMessage::SharedPtr msg);
  void setup(rclcpp::Node::SharedPtr node, const std::string & config_path);

  rclcpp::Node::SharedPtr node_;
  rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr tf_subscription_;
  std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
  
  // 和原 Gimbal 完全一样的队列类型
  tools::ThreadSafeQueue<std::tuple<Eigen::Quaterniond, std::chrono::steady_clock::time_point>>
    pose_queue_{1000};  // 和原 Gimbal 一样大小
  
  mutable std::mutex mutex_;
  SimIMUState state_;
  
  std::string odom_frame_;
  std::string gimbal_frame_;
};

}  // namespace io

#endif