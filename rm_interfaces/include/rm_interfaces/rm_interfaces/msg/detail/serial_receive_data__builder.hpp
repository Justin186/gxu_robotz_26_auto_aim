// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rm_interfaces:msg/SerialReceiveData.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__SERIAL_RECEIVE_DATA__BUILDER_HPP_
#define RM_INTERFACES__MSG__DETAIL__SERIAL_RECEIVE_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rm_interfaces/msg/detail/serial_receive_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rm_interfaces
{

namespace msg
{

namespace builder
{

class Init_SerialReceiveData_judge_system_data
{
public:
  explicit Init_SerialReceiveData_judge_system_data(::rm_interfaces::msg::SerialReceiveData & msg)
  : msg_(msg)
  {}
  ::rm_interfaces::msg::SerialReceiveData judge_system_data(::rm_interfaces::msg::SerialReceiveData::_judge_system_data_type arg)
  {
    msg_.judge_system_data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::msg::SerialReceiveData msg_;
};

class Init_SerialReceiveData_pitch
{
public:
  explicit Init_SerialReceiveData_pitch(::rm_interfaces::msg::SerialReceiveData & msg)
  : msg_(msg)
  {}
  Init_SerialReceiveData_judge_system_data pitch(::rm_interfaces::msg::SerialReceiveData::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_SerialReceiveData_judge_system_data(msg_);
  }

private:
  ::rm_interfaces::msg::SerialReceiveData msg_;
};

class Init_SerialReceiveData_yaw
{
public:
  explicit Init_SerialReceiveData_yaw(::rm_interfaces::msg::SerialReceiveData & msg)
  : msg_(msg)
  {}
  Init_SerialReceiveData_pitch yaw(::rm_interfaces::msg::SerialReceiveData::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_SerialReceiveData_pitch(msg_);
  }

private:
  ::rm_interfaces::msg::SerialReceiveData msg_;
};

class Init_SerialReceiveData_roll
{
public:
  explicit Init_SerialReceiveData_roll(::rm_interfaces::msg::SerialReceiveData & msg)
  : msg_(msg)
  {}
  Init_SerialReceiveData_yaw roll(::rm_interfaces::msg::SerialReceiveData::_roll_type arg)
  {
    msg_.roll = std::move(arg);
    return Init_SerialReceiveData_yaw(msg_);
  }

private:
  ::rm_interfaces::msg::SerialReceiveData msg_;
};

class Init_SerialReceiveData_bullet_speed
{
public:
  explicit Init_SerialReceiveData_bullet_speed(::rm_interfaces::msg::SerialReceiveData & msg)
  : msg_(msg)
  {}
  Init_SerialReceiveData_roll bullet_speed(::rm_interfaces::msg::SerialReceiveData::_bullet_speed_type arg)
  {
    msg_.bullet_speed = std::move(arg);
    return Init_SerialReceiveData_roll(msg_);
  }

private:
  ::rm_interfaces::msg::SerialReceiveData msg_;
};

class Init_SerialReceiveData_mode
{
public:
  explicit Init_SerialReceiveData_mode(::rm_interfaces::msg::SerialReceiveData & msg)
  : msg_(msg)
  {}
  Init_SerialReceiveData_bullet_speed mode(::rm_interfaces::msg::SerialReceiveData::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_SerialReceiveData_bullet_speed(msg_);
  }

private:
  ::rm_interfaces::msg::SerialReceiveData msg_;
};

class Init_SerialReceiveData_header
{
public:
  Init_SerialReceiveData_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SerialReceiveData_mode header(::rm_interfaces::msg::SerialReceiveData::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_SerialReceiveData_mode(msg_);
  }

private:
  ::rm_interfaces::msg::SerialReceiveData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::msg::SerialReceiveData>()
{
  return rm_interfaces::msg::builder::Init_SerialReceiveData_header();
}

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__SERIAL_RECEIVE_DATA__BUILDER_HPP_
