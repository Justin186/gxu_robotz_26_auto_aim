// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rm_interfaces:msg/Measurement.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__MEASUREMENT__BUILDER_HPP_
#define RM_INTERFACES__MSG__DETAIL__MEASUREMENT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rm_interfaces/msg/detail/measurement__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rm_interfaces
{

namespace msg
{

namespace builder
{

class Init_Measurement_yaw2
{
public:
  explicit Init_Measurement_yaw2(::rm_interfaces::msg::Measurement & msg)
  : msg_(msg)
  {}
  ::rm_interfaces::msg::Measurement yaw2(::rm_interfaces::msg::Measurement::_yaw2_type arg)
  {
    msg_.yaw2 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::msg::Measurement msg_;
};

class Init_Measurement_z2
{
public:
  explicit Init_Measurement_z2(::rm_interfaces::msg::Measurement & msg)
  : msg_(msg)
  {}
  Init_Measurement_yaw2 z2(::rm_interfaces::msg::Measurement::_z2_type arg)
  {
    msg_.z2 = std::move(arg);
    return Init_Measurement_yaw2(msg_);
  }

private:
  ::rm_interfaces::msg::Measurement msg_;
};

class Init_Measurement_y2
{
public:
  explicit Init_Measurement_y2(::rm_interfaces::msg::Measurement & msg)
  : msg_(msg)
  {}
  Init_Measurement_z2 y2(::rm_interfaces::msg::Measurement::_y2_type arg)
  {
    msg_.y2 = std::move(arg);
    return Init_Measurement_z2(msg_);
  }

private:
  ::rm_interfaces::msg::Measurement msg_;
};

class Init_Measurement_x2
{
public:
  explicit Init_Measurement_x2(::rm_interfaces::msg::Measurement & msg)
  : msg_(msg)
  {}
  Init_Measurement_y2 x2(::rm_interfaces::msg::Measurement::_x2_type arg)
  {
    msg_.x2 = std::move(arg);
    return Init_Measurement_y2(msg_);
  }

private:
  ::rm_interfaces::msg::Measurement msg_;
};

class Init_Measurement_yaw1
{
public:
  explicit Init_Measurement_yaw1(::rm_interfaces::msg::Measurement & msg)
  : msg_(msg)
  {}
  Init_Measurement_x2 yaw1(::rm_interfaces::msg::Measurement::_yaw1_type arg)
  {
    msg_.yaw1 = std::move(arg);
    return Init_Measurement_x2(msg_);
  }

private:
  ::rm_interfaces::msg::Measurement msg_;
};

class Init_Measurement_z1
{
public:
  explicit Init_Measurement_z1(::rm_interfaces::msg::Measurement & msg)
  : msg_(msg)
  {}
  Init_Measurement_yaw1 z1(::rm_interfaces::msg::Measurement::_z1_type arg)
  {
    msg_.z1 = std::move(arg);
    return Init_Measurement_yaw1(msg_);
  }

private:
  ::rm_interfaces::msg::Measurement msg_;
};

class Init_Measurement_y1
{
public:
  explicit Init_Measurement_y1(::rm_interfaces::msg::Measurement & msg)
  : msg_(msg)
  {}
  Init_Measurement_z1 y1(::rm_interfaces::msg::Measurement::_y1_type arg)
  {
    msg_.y1 = std::move(arg);
    return Init_Measurement_z1(msg_);
  }

private:
  ::rm_interfaces::msg::Measurement msg_;
};

class Init_Measurement_x1
{
public:
  Init_Measurement_x1()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Measurement_y1 x1(::rm_interfaces::msg::Measurement::_x1_type arg)
  {
    msg_.x1 = std::move(arg);
    return Init_Measurement_y1(msg_);
  }

private:
  ::rm_interfaces::msg::Measurement msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::msg::Measurement>()
{
  return rm_interfaces::msg::builder::Init_Measurement_x1();
}

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__MEASUREMENT__BUILDER_HPP_
