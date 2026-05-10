// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sp_msgs:msg/RMUCEnemyTracks.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_ENEMY_TRACKS__BUILDER_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_ENEMY_TRACKS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sp_msgs/msg/detail/rmuc_enemy_tracks__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sp_msgs
{

namespace msg
{

namespace builder
{

class Init_RMUCEnemyTracks_enemy_y
{
public:
  explicit Init_RMUCEnemyTracks_enemy_y(::sp_msgs::msg::RMUCEnemyTracks & msg)
  : msg_(msg)
  {}
  ::sp_msgs::msg::RMUCEnemyTracks enemy_y(::sp_msgs::msg::RMUCEnemyTracks::_enemy_y_type arg)
  {
    msg_.enemy_y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sp_msgs::msg::RMUCEnemyTracks msg_;
};

class Init_RMUCEnemyTracks_enemy_x
{
public:
  explicit Init_RMUCEnemyTracks_enemy_x(::sp_msgs::msg::RMUCEnemyTracks & msg)
  : msg_(msg)
  {}
  Init_RMUCEnemyTracks_enemy_y enemy_x(::sp_msgs::msg::RMUCEnemyTracks::_enemy_x_type arg)
  {
    msg_.enemy_x = std::move(arg);
    return Init_RMUCEnemyTracks_enemy_y(msg_);
  }

private:
  ::sp_msgs::msg::RMUCEnemyTracks msg_;
};

class Init_RMUCEnemyTracks_header
{
public:
  Init_RMUCEnemyTracks_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RMUCEnemyTracks_enemy_x header(::sp_msgs::msg::RMUCEnemyTracks::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RMUCEnemyTracks_enemy_x(msg_);
  }

private:
  ::sp_msgs::msg::RMUCEnemyTracks msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sp_msgs::msg::RMUCEnemyTracks>()
{
  return sp_msgs::msg::builder::Init_RMUCEnemyTracks_header();
}

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUC_ENEMY_TRACKS__BUILDER_HPP_
