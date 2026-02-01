#include "gimbal_node.hpp"
#include "tools/crc.hpp"
#include "tools/logger.hpp"
#include "io/ros2/ros2.hpp"
#include "sp_msgs/msg/rmul.hpp"

namespace io
{

GimbalNode::GimbalNode(const std::string & config_path) : Gimbal(config_path)
{
    ros2_ = std::make_shared<ROS2>();
    
    thread_ = std::make_unique<std::thread>(&GimbalNode::thread_loop, this);

    tools::logger()->info("GimbalNode thread started.");
}
GimbalNode::~GimbalNode()
{
    node_quit_ = true;
    if (thread_ && thread_->joinable()) {
        thread_->join();
    }
}

void GimbalNode::thread_loop()
{
  while (rclcpp::ok() && !node_quit_) {
    auto cmd_vel = ros2_->subscribe_cmd_vel();
    if (cmd_vel.has_value()) {
      this->send_cmd_vel(std::make_shared<geometry_msgs::msg::Twist>(cmd_vel.value()));
    }
    ros2_->publish(this->yaw());

    // 发布 RMUL 消息到 /robot_status
    auto nav_state = this->nav_state();
    sp_msgs::msg::RMUL rmul_msg;
    rmul_msg.header.stamp = rclcpp::Clock().now();
    rmul_msg.header.frame_id = "map";
    rmul_msg.game_progress = nav_state.game_progress;
    rmul_msg.stage_remain_time = nav_state.stage_remain_time;
    rmul_msg.rfid_supply_arrived = nav_state.rfid_supply_arrived;
    rmul_msg.rfid_control_arrived = nav_state.rfid_control_arrived;

    // 从父类获取自瞄状态
    bool is_enemy = this->is_detect_enemy(); 
    rmul_msg.stop_gimbal_scan = is_enemy; // 检测到敌人则停止扫描
    rmul_msg.current_hp = nav_state.current_hp;
    rmul_msg.is_attacked = nav_state.is_attacked;
    rmul_msg.is_detect_enemy = is_enemy; 

    // 调用特定的 publish 重载
    ros2_->publish(rmul_msg);

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
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