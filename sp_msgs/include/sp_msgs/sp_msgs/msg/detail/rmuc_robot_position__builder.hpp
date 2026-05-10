// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sp_msgs:msg/RMUCRobotPosition.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_ROBOT_POSITION__BUILDER_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_ROBOT_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sp_msgs/msg/detail/rmuc_robot_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sp_msgs
{

namespace msg
{

namespace builder
{

class Init_RMUCRobotPosition_is_at_nav_goal
{
public:
  explicit Init_RMUCRobotPosition_is_at_nav_goal(::sp_msgs::msg::RMUCRobotPosition & msg)
  : msg_(msg)
  {}
  ::sp_msgs::msg::RMUCRobotPosition is_at_nav_goal(::sp_msgs::msg::RMUCRobotPosition::_is_at_nav_goal_type arg)
  {
    msg_.is_at_nav_goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotPosition msg_;
};

class Init_RMUCRobotPosition_pose_y
{
public:
  explicit Init_RMUCRobotPosition_pose_y(::sp_msgs::msg::RMUCRobotPosition & msg)
  : msg_(msg)
  {}
  Init_RMUCRobotPosition_is_at_nav_goal pose_y(::sp_msgs::msg::RMUCRobotPosition::_pose_y_type arg)
  {
    msg_.pose_y = std::move(arg);
    return Init_RMUCRobotPosition_is_at_nav_goal(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotPosition msg_;
};

class Init_RMUCRobotPosition_pose_x
{
public:
  explicit Init_RMUCRobotPosition_pose_x(::sp_msgs::msg::RMUCRobotPosition & msg)
  : msg_(msg)
  {}
  Init_RMUCRobotPosition_pose_y pose_x(::sp_msgs::msg::RMUCRobotPosition::_pose_x_type arg)
  {
    msg_.pose_x = std::move(arg);
    return Init_RMUCRobotPosition_pose_y(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotPosition msg_;
};

class Init_RMUCRobotPosition_header
{
public:
  Init_RMUCRobotPosition_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RMUCRobotPosition_pose_x header(::sp_msgs::msg::RMUCRobotPosition::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RMUCRobotPosition_pose_x(msg_);
  }

private:
  ::sp_msgs::msg::RMUCRobotPosition msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sp_msgs::msg::RMUCRobotPosition>()
{
  return sp_msgs::msg::builder::Init_RMUCRobotPosition_header();
}

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUC_ROBOT_POSITION__BUILDER_HPP_
