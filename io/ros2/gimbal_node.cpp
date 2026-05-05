#include "gimbal_node.hpp"
#include "tools/crc.hpp"
#include "tools/logger.hpp"
#include "io/ros2/ros2.hpp"
#include "sp_msgs/msg/rmul.hpp"

using namespace std::chrono_literals;

namespace io
{

GimbalNode::GimbalNode(const std::string & config_path) : Gimbal(config_path)
{
    ros2_ = std::make_shared<ROS2>();
    
    thread_ = std::make_unique<std::thread>(&GimbalNode::thread_loop, this);

    tools::logger()->info("GimbalNode thread started.");
}

bool GimbalNode::is_move = false;

GimbalNode::~GimbalNode()
{
    node_quit_ = true;
    if (thread_ && thread_->joinable()) {
        thread_->join();
    }
}

void GimbalNode::thread_loop()
{
  auto out_cmd_time = std::chrono::steady_clock::now();

  const auto timeout_Handle = std::chrono::milliseconds(300); 

  while (rclcpp::ok() && !node_quit_) {
    auto cmd_vel = ros2_->subscribe_cmd_vel();
    auto now = std::chrono::steady_clock::now();

    if (cmd_vel.has_value()) {
      out_cmd_time = now;
      this->send_cmd_vel(std::make_shared<geometry_msgs::msg::Twist>(cmd_vel.value()));
    }
    else {
      auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - out_cmd_time);

      if (time_diff > timeout_Handle) {
          this->send_cmd_vel_zero(std::make_shared<geometry_msgs::msg::Twist>());
      }
    }
    ros2_->publish(this->yaw());

    // 发布 RMUL 消息到 /robot_status 和 /game_status
    auto nav_state = this->nav_state(); // 获取当前状态以填充 RMUL 消息
    sp_msgs::msg::RMUL robot_status_msg;
    robot_status_msg.header.stamp = rclcpp::Clock().now();
    robot_status_msg.header.frame_id = "map";
    // 从父类获取自瞄状态
    bool is_enemy = this->is_detect_enemy(); 
    robot_status_msg.current_hp = nav_state.current_hp;
    robot_status_msg.game_progress = nav_state.game_progress;
    robot_status_msg.is_detect_enemy = is_enemy;

    // 调用 publish
    ros2_->publish_robot_status(robot_status_msg);
    ros2_->publish_game_status(robot_status_msg);

    std::this_thread::sleep_for(10ms);
  }
}

void GimbalNode::send_cmd_vel(const geometry_msgs::msg::Twist::SharedPtr msg)
{
    nav_tx_data_.linear_x = msg->linear.x;
    nav_tx_data_.linear_y = msg->linear.y;
    nav_tx_data_.linear_z = msg->linear.z;
    nav_tx_data_.angular_x = msg->angular.x;
    nav_tx_data_.angular_y = msg->angular.y;
    nav_tx_data_.angular_z = msg->angular.z;
    nav_tx_data_.crc16 = tools::get_crc16(
    reinterpret_cast<uint8_t *>(&nav_tx_data_), sizeof(nav_tx_data_) - sizeof(nav_tx_data_.crc16));
    
    if (nav_tx_data_.linear_x != 0 || nav_tx_data_.linear_y != 0)
    {
        is_move = true;
    }
    else
    {
        is_move = false;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    try {
    this->serial_.write(reinterpret_cast<uint8_t *>(&nav_tx_data_), sizeof(nav_tx_data_));
    } catch (const std::exception & e) {
    tools::logger()->warn("[Gimbal] Failed to write serial: {}", e.what());
    }
}

void GimbalNode::send_cmd_vel_zero(const geometry_msgs::msg::Twist::SharedPtr msg)
{
    nav_tx_data_.linear_x =0;
    nav_tx_data_.linear_y =0;
    nav_tx_data_.linear_z =0;
    nav_tx_data_.angular_x =0;
    nav_tx_data_.angular_y =0;
    nav_tx_data_.angular_z =0;
    nav_tx_data_.crc16 = tools::get_crc16(
        reinterpret_cast<uint8_t *>(&nav_tx_data_), sizeof(nav_tx_data_) - sizeof(nav_tx_data_.crc16));
    
    std::lock_guard<std::mutex> lock(mutex_);
    try {
    this->serial_.write(reinterpret_cast<uint8_t *>(&nav_tx_data_), sizeof(nav_tx_data_));
    } catch (const std::exception & e) {
    tools::logger()->warn("[Gimbal] Failed to write serial: {}", e.what());
    }
}

void GimbalNode::send(io::VisionToGimbal VisionToGimbal) {
    std::lock_guard<std::mutex> lock(mutex_);
    Gimbal::send(VisionToGimbal);
}
};