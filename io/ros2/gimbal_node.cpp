#include "gimbal_node.hpp"
#include "tools/crc.hpp"
#include "tools/logger.hpp"
#include "io/ros2/ros2.hpp"

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
  auto Out_cmd_time = std::chrono::steady_clock::now();
  auto last_nav_send_time = Out_cmd_time;

  const auto timeout_Handle = std::chrono::milliseconds(300); 
  const auto nav_send_interval = std::chrono::milliseconds(10);

  while (rclcpp::ok() && !node_quit_) {
    auto cmd_vel = ros2_->subscribe_cmd_vel();
    auto now = std::chrono::steady_clock::now();

    if (cmd_vel.has_value()) {
      Out_cmd_time = now;
      if (now - last_nav_send_time >= nav_send_interval) {
        last_nav_send_time = now;
        this->send_cmd_vel(std::make_shared<geometry_msgs::msg::Twist>(cmd_vel.value()), ros2_->get_sentry_cmd_posture());
      }
    }
    else {
      auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - Out_cmd_time);

      if (time_diff > timeout_Handle && now - last_nav_send_time >= nav_send_interval) {
          last_nav_send_time = now;
          this->send_cmd_vel_zero(std::make_shared<geometry_msgs::msg::Twist>(), ros2_->get_sentry_cmd_posture());
      }
    }
    ros2_->publish(this->yaw());

    const auto nav_state = this->nav_state();
    const bool is_enemy = this->is_detect_enemy();

    sp_msgs::msg::RMUCGameStatus game_status_msg;
    game_status_msg.game_progress = nav_state.game_progress;
    game_status_msg.stage_remain_time = nav_state.stage_remain_time;

    sp_msgs::msg::RMUCRobotStatus robot_status_msg;
    robot_status_msg.current_hp = nav_state.current_hp;
    robot_status_msg.shooter_heat = nav_state.shooter_17mm_barrel_heat;
    robot_status_msg.ammo_allow = nav_state.projectile_allowance_17mm;
    robot_status_msg.is_detect_enemy = is_enemy;
    // tools::logger()->debug("is_detect_enemy: {}", is_enemy);
    robot_status_msg.base_hp = nav_state.base_Hp;
    robot_status_msg.outpost_hp = nav_state.outpost_Hp;

    sp_msgs::msg::RMUCRobotBuff robot_buff_msg;
    robot_buff_msg.vulnerability_pct = nav_state.vulnerability_buff;

    ros2_->publish_robot_status(robot_status_msg);
    ros2_->publish_robot_buff(robot_buff_msg);
    ros2_->publish_game_status(game_status_msg);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void GimbalNode::send_cmd_vel(const geometry_msgs::msg::Twist::SharedPtr msg, uint8_t cmd_posture)
{
    NavToGimbal nav_tx_data;
    nav_tx_data.linear_x = msg->linear.x;
    nav_tx_data.linear_y = msg->linear.y;
    nav_tx_data.linear_z = msg->linear.z;
    nav_tx_data.angular_x = msg->angular.x;
    nav_tx_data.angular_y = msg->angular.y;
    nav_tx_data.angular_z = msg->angular.z;
    nav_tx_data.move_mode = cmd_posture;
    // tools::logger()->debug("normal cmd has send: {}");

    nav_tx_data.crc16 = tools::get_crc16(
        reinterpret_cast<uint8_t *>(&nav_tx_data), sizeof(nav_tx_data) - sizeof(nav_tx_data.crc16));
    
        if (nav_tx_data.linear_x != 0 || nav_tx_data.linear_y != 0)
    {
        is_move = true;
    }
    else
    {
        is_move = false;
    }

    std::lock_guard<std::mutex> lock(serial_mutex_);
    try {
    this->serial_.write(reinterpret_cast<uint8_t *>(&nav_tx_data), sizeof(nav_tx_data));
    } catch (const std::exception & e) {
    tools::logger()->warn("[Gimbal] Failed to write serial: {}", e.what());
    }
}

void GimbalNode::send_cmd_vel_zero(const geometry_msgs::msg::Twist::SharedPtr msg, uint8_t cmd_posture)
{
    NavToGimbal nav_tx_data;
    nav_tx_data.linear_x =0;
    nav_tx_data.linear_y =0;
    nav_tx_data.linear_z =0;
    nav_tx_data.angular_x =0;
    nav_tx_data.angular_y =0;
    nav_tx_data.angular_z =0;
    nav_tx_data.move_mode =cmd_posture;
    // tools::logger()->debug("zero cmd has send");
    nav_tx_data.crc16 = tools::get_crc16(
        reinterpret_cast<uint8_t *>(&nav_tx_data), sizeof(nav_tx_data) - sizeof(nav_tx_data.crc16));
    
    std::lock_guard<std::mutex> lock(serial_mutex_);
    try {
    this->serial_.write(reinterpret_cast<uint8_t *>(&nav_tx_data), sizeof(nav_tx_data));
    } catch (const std::exception & e) {
    tools::logger()->warn("[Gimbal] Failed to write serial: {}", e.what());
    }
}

void GimbalNode::send_cmd_vel_debug(const geometry_msgs::msg::Twist::SharedPtr msg)
{  
    auto limit = 1.5;
    
    auto speed_limit = [&](auto ori_speed) -> float {
        if (ori_speed > limit) return limit;
        if (ori_speed < -limit) return -limit;
        return (float)ori_speed;
    };

    NavToGimbal nav_tx_data;
    nav_tx_data.linear_x =speed_limit(msg->linear.x);
    nav_tx_data.linear_y =speed_limit(msg->linear.y);
    nav_tx_data.linear_z =speed_limit(msg->linear.z);
    nav_tx_data.angular_x =speed_limit(msg->angular.x);
    nav_tx_data.angular_y =speed_limit(msg->angular.y);
    nav_tx_data.angular_z =0;
    nav_tx_data.crc16 = tools::get_crc16(
        reinterpret_cast<uint8_t *>(&nav_tx_data), sizeof(nav_tx_data) - sizeof(nav_tx_data.crc16));
    
    std::lock_guard<std::mutex> lock(serial_mutex_);
    try {
    this->serial_.write(reinterpret_cast<uint8_t *>(&nav_tx_data), sizeof(nav_tx_data));
    } catch (const std::exception & e) {
    tools::logger()->warn("[Gimbal] Failed to write serial: {}", e.what());
    }
}

bool GimbalNode::get_image(cv::Mat & img, std::chrono::steady_clock::time_point & timestamp)
{
    if (!ros2_) return false;
    return ros2_->get_image(img, timestamp);
}

void GimbalNode::clear_image()
{
    if (ros2_) {
        ros2_->clear_image();
    }
}
};
