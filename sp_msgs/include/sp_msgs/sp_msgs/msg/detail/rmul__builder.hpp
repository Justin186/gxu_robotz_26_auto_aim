// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sp_msgs:msg/RMUL.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUL__BUILDER_HPP_
#define SP_MSGS__MSG__DETAIL__RMUL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sp_msgs/msg/detail/rmul__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sp_msgs
{

namespace msg
{

namespace builder
{

class Init_RMUL_is_at_nav_goal
{
public:
  explicit Init_RMUL_is_at_nav_goal(::sp_msgs::msg::RMUL & msg)
  : msg_(msg)
  {}
  ::sp_msgs::msg::RMUL is_at_nav_goal(::sp_msgs::msg::RMUL::_is_at_nav_goal_type arg)
  {
    msg_.is_at_nav_goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

class Init_RMUL_is_detect_enemy
{
public:
  explicit Init_RMUL_is_detect_enemy(::sp_msgs::msg::RMUL & msg)
  : msg_(msg)
  {}
  Init_RMUL_is_at_nav_goal is_detect_enemy(::sp_msgs::msg::RMUL::_is_detect_enemy_type arg)
  {
    msg_.is_detect_enemy = std::move(arg);
    return Init_RMUL_is_at_nav_goal(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

class Init_RMUL_y
{
public:
  explicit Init_RMUL_y(::sp_msgs::msg::RMUL & msg)
  : msg_(msg)
  {}
  Init_RMUL_is_detect_enemy y(::sp_msgs::msg::RMUL::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_RMUL_is_detect_enemy(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

class Init_RMUL_x
{
public:
  explicit Init_RMUL_x(::sp_msgs::msg::RMUL & msg)
  : msg_(msg)
  {}
  Init_RMUL_y x(::sp_msgs::msg::RMUL::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_RMUL_y(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

class Init_RMUL_chassis_spin
{
public:
  explicit Init_RMUL_chassis_spin(::sp_msgs::msg::RMUL & msg)
  : msg_(msg)
  {}
  Init_RMUL_x chassis_spin(::sp_msgs::msg::RMUL::_chassis_spin_type arg)
  {
    msg_.chassis_spin = std::move(arg);
    return Init_RMUL_x(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

class Init_RMUL_stop_gimbal_scan
{
public:
  explicit Init_RMUL_stop_gimbal_scan(::sp_msgs::msg::RMUL & msg)
  : msg_(msg)
  {}
  Init_RMUL_chassis_spin stop_gimbal_scan(::sp_msgs::msg::RMUL::_stop_gimbal_scan_type arg)
  {
    msg_.stop_gimbal_scan = std::move(arg);
    return Init_RMUL_chassis_spin(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

class Init_RMUL_emergency_stop
{
public:
  explicit Init_RMUL_emergency_stop(::sp_msgs::msg::RMUL & msg)
  : msg_(msg)
  {}
  Init_RMUL_stop_gimbal_scan emergency_stop(::sp_msgs::msg::RMUL::_emergency_stop_type arg)
  {
    msg_.emergency_stop = std::move(arg);
    return Init_RMUL_stop_gimbal_scan(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

class Init_RMUL_cmd_type
{
public:
  explicit Init_RMUL_cmd_type(::sp_msgs::msg::RMUL & msg)
  : msg_(msg)
  {}
  Init_RMUL_emergency_stop cmd_type(::sp_msgs::msg::RMUL::_cmd_type_type arg)
  {
    msg_.cmd_type = std::move(arg);
    return Init_RMUL_emergency_stop(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

class Init_RMUL_rfid_control_arrived
{
public:
  explicit Init_RMUL_rfid_control_arrived(::sp_msgs::msg::RMUL & msg)
  : msg_(msg)
  {}
  Init_RMUL_cmd_type rfid_control_arrived(::sp_msgs::msg::RMUL::_rfid_control_arrived_type arg)
  {
    msg_.rfid_control_arrived = std::move(arg);
    return Init_RMUL_cmd_type(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

class Init_RMUL_rfid_supply_arrived
{
public:
  explicit Init_RMUL_rfid_supply_arrived(::sp_msgs::msg::RMUL & msg)
  : msg_(msg)
  {}
  Init_RMUL_rfid_control_arrived rfid_supply_arrived(::sp_msgs::msg::RMUL::_rfid_supply_arrived_type arg)
  {
    msg_.rfid_supply_arrived = std::move(arg);
    return Init_RMUL_rfid_control_arrived(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

class Init_RMUL_shooter_heat
{
public:
  explicit Init_RMUL_shooter_heat(::sp_msgs::msg::RMUL & msg)
  : msg_(msg)
  {}
  Init_RMUL_rfid_supply_arrived shooter_heat(::sp_msgs::msg::RMUL::_shooter_heat_type arg)
  {
    msg_.shooter_heat = std::move(arg);
    return Init_RMUL_rfid_supply_arrived(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

class Init_RMUL_is_attacked
{
public:
  explicit Init_RMUL_is_attacked(::sp_msgs::msg::RMUL & msg)
  : msg_(msg)
  {}
  Init_RMUL_shooter_heat is_attacked(::sp_msgs::msg::RMUL::_is_attacked_type arg)
  {
    msg_.is_attacked = std::move(arg);
    return Init_RMUL_shooter_heat(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

class Init_RMUL_current_hp
{
public:
  explicit Init_RMUL_current_hp(::sp_msgs::msg::RMUL & msg)
  : msg_(msg)
  {}
  Init_RMUL_is_attacked current_hp(::sp_msgs::msg::RMUL::_current_hp_type arg)
  {
    msg_.current_hp = std::move(arg);
    return Init_RMUL_is_attacked(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

class Init_RMUL_stage_remain_time
{
public:
  explicit Init_RMUL_stage_remain_time(::sp_msgs::msg::RMUL & msg)
  : msg_(msg)
  {}
  Init_RMUL_current_hp stage_remain_time(::sp_msgs::msg::RMUL::_stage_remain_time_type arg)
  {
    msg_.stage_remain_time = std::move(arg);
    return Init_RMUL_current_hp(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

class Init_RMUL_game_progress
{
public:
  explicit Init_RMUL_game_progress(::sp_msgs::msg::RMUL & msg)
  : msg_(msg)
  {}
  Init_RMUL_stage_remain_time game_progress(::sp_msgs::msg::RMUL::_game_progress_type arg)
  {
    msg_.game_progress = std::move(arg);
    return Init_RMUL_stage_remain_time(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

class Init_RMUL_header
{
public:
  Init_RMUL_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RMUL_game_progress header(::sp_msgs::msg::RMUL::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RMUL_game_progress(msg_);
  }

private:
  ::sp_msgs::msg::RMUL msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sp_msgs::msg::RMUL>()
{
  return sp_msgs::msg::builder::Init_RMUL_header();
}

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUL__BUILDER_HPP_
