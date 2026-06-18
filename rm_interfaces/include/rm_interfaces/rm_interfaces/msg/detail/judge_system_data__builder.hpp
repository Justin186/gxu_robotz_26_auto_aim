// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rm_interfaces:msg/JudgeSystemData.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__JUDGE_SYSTEM_DATA__BUILDER_HPP_
#define RM_INTERFACES__MSG__DETAIL__JUDGE_SYSTEM_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rm_interfaces/msg/detail/judge_system_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rm_interfaces
{

namespace msg
{

namespace builder
{

class Init_JudgeSystemData_operator_command
{
public:
  explicit Init_JudgeSystemData_operator_command(::rm_interfaces::msg::JudgeSystemData & msg)
  : msg_(msg)
  {}
  ::rm_interfaces::msg::JudgeSystemData operator_command(::rm_interfaces::msg::JudgeSystemData::_operator_command_type arg)
  {
    msg_.operator_command = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rm_interfaces::msg::JudgeSystemData msg_;
};

class Init_JudgeSystemData_outpost_hp
{
public:
  explicit Init_JudgeSystemData_outpost_hp(::rm_interfaces::msg::JudgeSystemData & msg)
  : msg_(msg)
  {}
  Init_JudgeSystemData_operator_command outpost_hp(::rm_interfaces::msg::JudgeSystemData::_outpost_hp_type arg)
  {
    msg_.outpost_hp = std::move(arg);
    return Init_JudgeSystemData_operator_command(msg_);
  }

private:
  ::rm_interfaces::msg::JudgeSystemData msg_;
};

class Init_JudgeSystemData_blood
{
public:
  explicit Init_JudgeSystemData_blood(::rm_interfaces::msg::JudgeSystemData & msg)
  : msg_(msg)
  {}
  Init_JudgeSystemData_outpost_hp blood(::rm_interfaces::msg::JudgeSystemData::_blood_type arg)
  {
    msg_.blood = std::move(arg);
    return Init_JudgeSystemData_outpost_hp(msg_);
  }

private:
  ::rm_interfaces::msg::JudgeSystemData msg_;
};

class Init_JudgeSystemData_remaining_time
{
public:
  explicit Init_JudgeSystemData_remaining_time(::rm_interfaces::msg::JudgeSystemData & msg)
  : msg_(msg)
  {}
  Init_JudgeSystemData_blood remaining_time(::rm_interfaces::msg::JudgeSystemData::_remaining_time_type arg)
  {
    msg_.remaining_time = std::move(arg);
    return Init_JudgeSystemData_blood(msg_);
  }

private:
  ::rm_interfaces::msg::JudgeSystemData msg_;
};

class Init_JudgeSystemData_game_status
{
public:
  Init_JudgeSystemData_game_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_JudgeSystemData_remaining_time game_status(::rm_interfaces::msg::JudgeSystemData::_game_status_type arg)
  {
    msg_.game_status = std::move(arg);
    return Init_JudgeSystemData_remaining_time(msg_);
  }

private:
  ::rm_interfaces::msg::JudgeSystemData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rm_interfaces::msg::JudgeSystemData>()
{
  return rm_interfaces::msg::builder::Init_JudgeSystemData_game_status();
}

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__JUDGE_SYSTEM_DATA__BUILDER_HPP_
