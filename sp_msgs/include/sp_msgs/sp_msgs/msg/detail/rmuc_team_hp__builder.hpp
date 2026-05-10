// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sp_msgs:msg/RMUCTeamHP.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_TEAM_HP__BUILDER_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_TEAM_HP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sp_msgs/msg/detail/rmuc_team_hp__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sp_msgs
{

namespace msg
{

namespace builder
{

class Init_RMUCTeamHP_base_hp
{
public:
  explicit Init_RMUCTeamHP_base_hp(::sp_msgs::msg::RMUCTeamHP & msg)
  : msg_(msg)
  {}
  ::sp_msgs::msg::RMUCTeamHP base_hp(::sp_msgs::msg::RMUCTeamHP::_base_hp_type arg)
  {
    msg_.base_hp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sp_msgs::msg::RMUCTeamHP msg_;
};

class Init_RMUCTeamHP_outpost_hp
{
public:
  explicit Init_RMUCTeamHP_outpost_hp(::sp_msgs::msg::RMUCTeamHP & msg)
  : msg_(msg)
  {}
  Init_RMUCTeamHP_base_hp outpost_hp(::sp_msgs::msg::RMUCTeamHP::_outpost_hp_type arg)
  {
    msg_.outpost_hp = std::move(arg);
    return Init_RMUCTeamHP_base_hp(msg_);
  }

private:
  ::sp_msgs::msg::RMUCTeamHP msg_;
};

class Init_RMUCTeamHP_header
{
public:
  Init_RMUCTeamHP_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RMUCTeamHP_outpost_hp header(::sp_msgs::msg::RMUCTeamHP::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RMUCTeamHP_outpost_hp(msg_);
  }

private:
  ::sp_msgs::msg::RMUCTeamHP msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sp_msgs::msg::RMUCTeamHP>()
{
  return sp_msgs::msg::builder::Init_RMUCTeamHP_header();
}

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUC_TEAM_HP__BUILDER_HPP_
