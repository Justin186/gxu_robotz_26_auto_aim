// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rm_interfaces:msg/DebugArmor.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__DEBUG_ARMOR__BUILDER_HPP_
#define RM_INTERFACES__MSG__DETAIL__DEBUG_ARMOR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rm_interfaces/msg/detail/debug_armor__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rm_interfaces
{

namespace msg
{

namespace builder
{

class Init_DebugArmor_angle
{
public:
  explicit Init_DebugArmor_angle(::rm_interfaces::msg::DebugArmor & msg)
  : msg_(msg)
  {}
  ::rm_interfaces::msg::DebugArmor angle(::rm_interfaces::msg::DebugArmor::_angle_type arg)
  {
    msg_.angle = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::msg::DebugArmor msg_;
};

class Init_DebugArmor_center_distance
{
public:
  explicit Init_DebugArmor_center_distance(::rm_interfaces::msg::DebugArmor & msg)
  : msg_(msg)
  {}
  Init_DebugArmor_angle center_distance(::rm_interfaces::msg::DebugArmor::_center_distance_type arg)
  {
    msg_.center_distance = std::move(arg);
    return Init_DebugArmor_angle(msg_);
  }

private:
  ::rm_interfaces::msg::DebugArmor msg_;
};

class Init_DebugArmor_light_ratio
{
public:
  explicit Init_DebugArmor_light_ratio(::rm_interfaces::msg::DebugArmor & msg)
  : msg_(msg)
  {}
  Init_DebugArmor_center_distance light_ratio(::rm_interfaces::msg::DebugArmor::_light_ratio_type arg)
  {
    msg_.light_ratio = std::move(arg);
    return Init_DebugArmor_center_distance(msg_);
  }

private:
  ::rm_interfaces::msg::DebugArmor msg_;
};

class Init_DebugArmor_type
{
public:
  explicit Init_DebugArmor_type(::rm_interfaces::msg::DebugArmor & msg)
  : msg_(msg)
  {}
  Init_DebugArmor_light_ratio type(::rm_interfaces::msg::DebugArmor::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_DebugArmor_light_ratio(msg_);
  }

private:
  ::rm_interfaces::msg::DebugArmor msg_;
};

class Init_DebugArmor_center_x
{
public:
  Init_DebugArmor_center_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DebugArmor_type center_x(::rm_interfaces::msg::DebugArmor::_center_x_type arg)
  {
    msg_.center_x = std::move(arg);
    return Init_DebugArmor_type(msg_);
  }

private:
  ::rm_interfaces::msg::DebugArmor msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::msg::DebugArmor>()
{
  return rm_interfaces::msg::builder::Init_DebugArmor_center_x();
}

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__DEBUG_ARMOR__BUILDER_HPP_
