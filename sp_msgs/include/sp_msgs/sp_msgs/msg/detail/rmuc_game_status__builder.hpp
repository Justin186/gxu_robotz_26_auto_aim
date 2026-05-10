// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sp_msgs:msg/RMUCGameStatus.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_GAME_STATUS__BUILDER_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_GAME_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sp_msgs/msg/detail/rmuc_game_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sp_msgs
{

namespace msg
{

namespace builder
{

class Init_RMUCGameStatus_stage_remain_time
{
public:
  explicit Init_RMUCGameStatus_stage_remain_time(::sp_msgs::msg::RMUCGameStatus & msg)
  : msg_(msg)
  {}
  ::sp_msgs::msg::RMUCGameStatus stage_remain_time(::sp_msgs::msg::RMUCGameStatus::_stage_remain_time_type arg)
  {
    msg_.stage_remain_time = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sp_msgs::msg::RMUCGameStatus msg_;
};

class Init_RMUCGameStatus_game_progress
{
public:
  explicit Init_RMUCGameStatus_game_progress(::sp_msgs::msg::RMUCGameStatus & msg)
  : msg_(msg)
  {}
  Init_RMUCGameStatus_stage_remain_time game_progress(::sp_msgs::msg::RMUCGameStatus::_game_progress_type arg)
  {
    msg_.game_progress = std::move(arg);
    return Init_RMUCGameStatus_stage_remain_time(msg_);
  }

private:
  ::sp_msgs::msg::RMUCGameStatus msg_;
};

class Init_RMUCGameStatus_header
{
public:
  Init_RMUCGameStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RMUCGameStatus_game_progress header(::sp_msgs::msg::RMUCGameStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RMUCGameStatus_game_progress(msg_);
  }

private:
  ::sp_msgs::msg::RMUCGameStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sp_msgs::msg::RMUCGameStatus>()
{
  return sp_msgs::msg::builder::Init_RMUCGameStatus_header();
}

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUC_GAME_STATUS__BUILDER_HPP_
