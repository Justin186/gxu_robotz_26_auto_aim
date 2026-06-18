// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rm_interfaces:msg/PlanGimbalCmd.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__PLAN_GIMBAL_CMD__BUILDER_HPP_
#define RM_INTERFACES__MSG__DETAIL__PLAN_GIMBAL_CMD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rm_interfaces/msg/detail/plan_gimbal_cmd__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rm_interfaces
{

namespace msg
{

namespace builder
{

class Init_PlanGimbalCmd_ref_pitch_acc
{
public:
  explicit Init_PlanGimbalCmd_ref_pitch_acc(::rm_interfaces::msg::PlanGimbalCmd & msg)
  : msg_(msg)
  {}
  ::rm_interfaces::msg::PlanGimbalCmd ref_pitch_acc(::rm_interfaces::msg::PlanGimbalCmd::_ref_pitch_acc_type arg)
  {
    msg_.ref_pitch_acc = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::msg::PlanGimbalCmd msg_;
};

class Init_PlanGimbalCmd_ref_pitch_vel
{
public:
  explicit Init_PlanGimbalCmd_ref_pitch_vel(::rm_interfaces::msg::PlanGimbalCmd & msg)
  : msg_(msg)
  {}
  Init_PlanGimbalCmd_ref_pitch_acc ref_pitch_vel(::rm_interfaces::msg::PlanGimbalCmd::_ref_pitch_vel_type arg)
  {
    msg_.ref_pitch_vel = std::move(arg);
    return Init_PlanGimbalCmd_ref_pitch_acc(msg_);
  }

private:
  ::rm_interfaces::msg::PlanGimbalCmd msg_;
};

class Init_PlanGimbalCmd_ref_pitch
{
public:
  explicit Init_PlanGimbalCmd_ref_pitch(::rm_interfaces::msg::PlanGimbalCmd & msg)
  : msg_(msg)
  {}
  Init_PlanGimbalCmd_ref_pitch_vel ref_pitch(::rm_interfaces::msg::PlanGimbalCmd::_ref_pitch_type arg)
  {
    msg_.ref_pitch = std::move(arg);
    return Init_PlanGimbalCmd_ref_pitch_vel(msg_);
  }

private:
  ::rm_interfaces::msg::PlanGimbalCmd msg_;
};

class Init_PlanGimbalCmd_ref_yaw_acc
{
public:
  explicit Init_PlanGimbalCmd_ref_yaw_acc(::rm_interfaces::msg::PlanGimbalCmd & msg)
  : msg_(msg)
  {}
  Init_PlanGimbalCmd_ref_pitch ref_yaw_acc(::rm_interfaces::msg::PlanGimbalCmd::_ref_yaw_acc_type arg)
  {
    msg_.ref_yaw_acc = std::move(arg);
    return Init_PlanGimbalCmd_ref_pitch(msg_);
  }

private:
  ::rm_interfaces::msg::PlanGimbalCmd msg_;
};

class Init_PlanGimbalCmd_ref_yaw_vel
{
public:
  explicit Init_PlanGimbalCmd_ref_yaw_vel(::rm_interfaces::msg::PlanGimbalCmd & msg)
  : msg_(msg)
  {}
  Init_PlanGimbalCmd_ref_yaw_acc ref_yaw_vel(::rm_interfaces::msg::PlanGimbalCmd::_ref_yaw_vel_type arg)
  {
    msg_.ref_yaw_vel = std::move(arg);
    return Init_PlanGimbalCmd_ref_yaw_acc(msg_);
  }

private:
  ::rm_interfaces::msg::PlanGimbalCmd msg_;
};

class Init_PlanGimbalCmd_ref_yaw
{
public:
  explicit Init_PlanGimbalCmd_ref_yaw(::rm_interfaces::msg::PlanGimbalCmd & msg)
  : msg_(msg)
  {}
  Init_PlanGimbalCmd_ref_yaw_vel ref_yaw(::rm_interfaces::msg::PlanGimbalCmd::_ref_yaw_type arg)
  {
    msg_.ref_yaw = std::move(arg);
    return Init_PlanGimbalCmd_ref_yaw_vel(msg_);
  }

private:
  ::rm_interfaces::msg::PlanGimbalCmd msg_;
};

class Init_PlanGimbalCmd_header
{
public:
  Init_PlanGimbalCmd_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlanGimbalCmd_ref_yaw header(::rm_interfaces::msg::PlanGimbalCmd::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_PlanGimbalCmd_ref_yaw(msg_);
  }

private:
  ::rm_interfaces::msg::PlanGimbalCmd msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::msg::PlanGimbalCmd>()
{
  return rm_interfaces::msg::builder::Init_PlanGimbalCmd_header();
}

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__PLAN_GIMBAL_CMD__BUILDER_HPP_
