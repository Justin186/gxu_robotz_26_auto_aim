// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rm_interfaces:msg/DebugRuneAngle.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__DEBUG_RUNE_ANGLE__BUILDER_HPP_
#define RM_INTERFACES__MSG__DETAIL__DEBUG_RUNE_ANGLE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rm_interfaces/msg/detail/debug_rune_angle__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rm_interfaces
{

namespace msg
{

namespace builder
{

class Init_DebugRuneAngle_data
{
public:
  explicit Init_DebugRuneAngle_data(::rm_interfaces::msg::DebugRuneAngle & msg)
  : msg_(msg)
  {}
  ::rm_interfaces::msg::DebugRuneAngle data(::rm_interfaces::msg::DebugRuneAngle::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::msg::DebugRuneAngle msg_;
};

class Init_DebugRuneAngle_header
{
public:
  Init_DebugRuneAngle_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DebugRuneAngle_data header(::rm_interfaces::msg::DebugRuneAngle::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_DebugRuneAngle_data(msg_);
  }

private:
  ::rm_interfaces::msg::DebugRuneAngle msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::msg::DebugRuneAngle>()
{
  return rm_interfaces::msg::builder::Init_DebugRuneAngle_header();
}

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__DEBUG_RUNE_ANGLE__BUILDER_HPP_
