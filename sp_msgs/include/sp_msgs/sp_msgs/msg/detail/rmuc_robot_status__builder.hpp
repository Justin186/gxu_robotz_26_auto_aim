// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sp_msgs:msg/RMUCRobotStatus.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_ROBOT_STATUS__BUILDER_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_ROBOT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sp_msgs/msg/detail/rmuc_robot_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sp_msgs
{

namespace msg
{

namespace builder
{

class Init_RMUCRobotStatus_is_detect_enemy
{
public:
  explicit Init_RMUCRobotStatus_is_detect_enemy(::sp_msgs::msg::RMUCRobotStatus & msg)
  : msg_(msg)
  {}
  ::sp_msgs::msg::RMUCRobotStatus is_detect_enemy(::sp_msgs::msg::RMUCRobotStatus::_is_detect_enemy_type arg)
  {
    msg_.is_detect_enemy = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotStatus msg_;
};

class Init_RMUCRobotStatus_base_hp
{
public:
  explicit Init_RMUCRobotStatus_base_hp(::sp_msgs::msg::RMUCRobotStatus & msg)
  : msg_(msg)
  {}
  Init_RMUCRobotStatus_is_detect_enemy base_hp(::sp_msgs::msg::RMUCRobotStatus::_base_hp_type arg)
  {
    msg_.base_hp = std::move(arg);
    return Init_RMUCRobotStatus_is_detect_enemy(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotStatus msg_;
};

class Init_RMUCRobotStatus_outpost_hp
{
public:
  explicit Init_RMUCRobotStatus_outpost_hp(::sp_msgs::msg::RMUCRobotStatus & msg)
  : msg_(msg)
  {}
  Init_RMUCRobotStatus_base_hp outpost_hp(::sp_msgs::msg::RMUCRobotStatus::_outpost_hp_type arg)
  {
    msg_.outpost_hp = std::move(arg);
    return Init_RMUCRobotStatus_base_hp(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotStatus msg_;
};

class Init_RMUCRobotStatus_ammo_allow
{
public:
  explicit Init_RMUCRobotStatus_ammo_allow(::sp_msgs::msg::RMUCRobotStatus & msg)
  : msg_(msg)
  {}
  Init_RMUCRobotStatus_outpost_hp ammo_allow(::sp_msgs::msg::RMUCRobotStatus::_ammo_allow_type arg)
  {
    msg_.ammo_allow = std::move(arg);
    return Init_RMUCRobotStatus_outpost_hp(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotStatus msg_;
};

class Init_RMUCRobotStatus_shooter_heat
{
public:
  explicit Init_RMUCRobotStatus_shooter_heat(::sp_msgs::msg::RMUCRobotStatus & msg)
  : msg_(msg)
  {}
  Init_RMUCRobotStatus_ammo_allow shooter_heat(::sp_msgs::msg::RMUCRobotStatus::_shooter_heat_type arg)
  {
    msg_.shooter_heat = std::move(arg);
    return Init_RMUCRobotStatus_ammo_allow(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotStatus msg_;
};

class Init_RMUCRobotStatus_current_hp
{
public:
  explicit Init_RMUCRobotStatus_current_hp(::sp_msgs::msg::RMUCRobotStatus & msg)
  : msg_(msg)
  {}
  Init_RMUCRobotStatus_shooter_heat current_hp(::sp_msgs::msg::RMUCRobotStatus::_current_hp_type arg)
  {
    msg_.current_hp = std::move(arg);
    return Init_RMUCRobotStatus_shooter_heat(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotStatus msg_;
};

class Init_RMUCRobotStatus_header
{
public:
  Init_RMUCRobotStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RMUCRobotStatus_current_hp header(::sp_msgs::msg::RMUCRobotStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RMUCRobotStatus_current_hp(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sp_msgs::msg::RMUCRobotStatus>()
{
  return sp_msgs::msg::builder::Init_RMUCRobotStatus_header();
}

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUC_ROBOT_STATUS__BUILDER_HPP_
