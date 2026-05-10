// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sp_msgs:msg/RMUCSentryDecisionStatus.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_SENTRY_DECISION_STATUS__BUILDER_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_SENTRY_DECISION_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sp_msgs/msg/detail/rmuc_sentry_decision_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sp_msgs
{

namespace msg
{

namespace builder
{

class Init_RMUCSentryDecisionStatus_exchanged_ammo_total
{
public:
  explicit Init_RMUCSentryDecisionStatus_exchanged_ammo_total(::sp_msgs::msg::RMUCSentryDecisionStatus & msg)
  : msg_(msg)
  {}
  ::sp_msgs::msg::RMUCSentryDecisionStatus exchanged_ammo_total(::sp_msgs::msg::RMUCSentryDecisionStatus::_exchanged_ammo_total_type arg)
  {
    msg_.exchanged_ammo_total = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sp_msgs::msg::RMUCSentryDecisionStatus msg_;
};

class Init_RMUCSentryDecisionStatus_current_posture
{
public:
  explicit Init_RMUCSentryDecisionStatus_current_posture(::sp_msgs::msg::RMUCSentryDecisionStatus & msg)
  : msg_(msg)
  {}
  Init_RMUCSentryDecisionStatus_exchanged_ammo_total current_posture(::sp_msgs::msg::RMUCSentryDecisionStatus::_current_posture_type arg)
  {
    msg_.current_posture = std::move(arg);
    return Init_RMUCSentryDecisionStatus_exchanged_ammo_total(msg_);
  }

private:
  ::sp_msgs::msg::RMUCSentryDecisionStatus msg_;
};

class Init_RMUCSentryDecisionStatus_header
{
public:
  Init_RMUCSentryDecisionStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RMUCSentryDecisionStatus_current_posture header(::sp_msgs::msg::RMUCSentryDecisionStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RMUCSentryDecisionStatus_current_posture(msg_);
  }

private:
  ::sp_msgs::msg::RMUCSentryDecisionStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sp_msgs::msg::RMUCSentryDecisionStatus>()
{
  return sp_msgs::msg::builder::Init_RMUCSentryDecisionStatus_header();
}

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUC_SENTRY_DECISION_STATUS__BUILDER_HPP_
