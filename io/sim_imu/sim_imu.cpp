#include "sim_imu.hpp"

#include <cmath>
#include <Eigen/Geometry>

#include "tools/logger.hpp"
#include "tools/yaml.hpp"
#include "tools/math_tools.hpp"

namespace io
{

SimIMU::SimIMU(rclcpp::Node::SharedPtr node, const std::string & config_path)
{
  setup(node, config_path);
}

SimIMU::SimIMU(const std::string & config_path)
{
  // 自己创建节点（不推荐）
  auto node = std::make_shared<rclcpp::Node>("sim_imu_node");
  setup(node, config_path);
}

void SimIMU::setup(rclcpp::Node::SharedPtr node, const std::string & config_path)
{
  node_ = node;
  
  auto yaml = tools::load(config_path);
  odom_frame_ = tools::read<std::string>(yaml, "odom_frame", "odom");
  gimbal_frame_ = tools::read<std::string>(yaml, "gimbal_frame", "gimbal_link");
  
  tf_buffer_ = std::make_shared<tf2_ros::Buffer>(node_->get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
  
  tf_subscription_ = node_->create_subscription<tf2_msgs::msg::TFMessage>(
    "/tf", 100,
    std::bind(&SimIMU::tf_callback, this, std::placeholders::_1));
  
  RCLCPP_INFO(node_->get_logger(), 
    "SimIMU initialized. Subscribed to /tf, tracking frame: %s, queue size: 1000", 
    gimbal_frame_.c_str());
}

SimIMU::~SimIMU()
{
  RCLCPP_INFO(node_->get_logger(), "SimIMU shutting down.");
}

void SimIMU::tf_callback(const tf2_msgs::msg::TFMessage::SharedPtr msg)
{
  geometry_msgs::msg::TransformStamped transform;
  
  // 查找 gimbal_link
  for (const auto& tf : msg->transforms) {
    if (tf.child_frame_id == gimbal_frame_ || 
        tf.child_frame_id == "/" + gimbal_frame_) {
      transform = tf;
      break;
    }
  }
  
  if (transform.child_frame_id.empty()) {
    try {
      transform = tf_buffer_->lookupTransform(
        odom_frame_, gimbal_frame_,
        tf2::TimePointZero,
        tf2::durationFromSec(0.01)
      );
    } catch (const tf2::TransformException & ex) {
      return;
    }
  }
  
  if (transform.child_frame_id.empty()) {
    return;
  }
  
  // 提取四元数
  const auto& quat = transform.transform.rotation;
  Eigen::Quaterniond q(quat.w, quat.x, quat.y, quat.z);
  
  auto timestamp = std::chrono::steady_clock::now();
  
  // 推入队列（和原 Gimbal 完全一样）
  pose_queue_.push({q, timestamp});
  
  // 更新状态（欧拉角）
  Eigen::Vector3d euler = q.toRotationMatrix().eulerAngles(2, 1, 0);
  
  std::lock_guard<std::mutex> lock(mutex_);
  state_.yaw = euler.x() * 180.0 / M_PI;
  state_.pitch = euler.y() * 180.0 / M_PI;
}

SimIMUState SimIMU::state() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return state_;
}

// ===== 完全复制原 Gimbal 的 q() 实现 =====
Eigen::Quaterniond SimIMU::q(std::chrono::steady_clock::time_point t)
{
  while (true) {
    // 弹出最早的数据作为 q_a
    auto [q_a, t_a] = pose_queue_.pop();
    
    // 看下一个数据作为 q_b
    auto [q_b, t_b] = pose_queue_.front();
    
    // 计算插值系数
    auto t_ab = tools::delta_time(t_a, t_b);
    auto t_ac = tools::delta_time(t_a, t);
    auto k = t_ac / t_ab;
    
    // SLERP 插值
    Eigen::Quaterniond q_c = q_a.slerp(k, q_b).normalized();
    
    // 如果 t 比 t_a 还早，返回 q_a
    if (t < t_a) return q_c;
    
    // 如果 t 在 [t_a, t_b] 区间内，返回插值结果
    if (!(t_a < t && t <= t_b)) continue;
    
    return q_c;
  }
}

bool SimIMU::get_current_quat(Eigen::Quaterniond & quat)
{
  if (pose_queue_.empty()) {
    return false;
  }
  auto [q, t] = pose_queue_.front();
  quat = q;
  return true;
}

}  // namespace io