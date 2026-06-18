// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rm_interfaces:msg/JudgeSystemData.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__JUDGE_SYSTEM_DATA__TRAITS_HPP_
#define RM_INTERFACES__MSG__DETAIL__JUDGE_SYSTEM_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rm_interfaces/msg/detail/judge_system_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'operator_command'
#include "rm_interfaces/msg/detail/operator_command__traits.hpp"

namespace rm_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const JudgeSystemData & msg,
  std::ostream & out)
{
  out << "{";
  // member: game_status
  {
    out << "game_status: ";
    rosidl_generator_traits::value_to_yaml(msg.game_status, out);
    out << ", ";
  }

  // member: remaining_time
  {
    out << "remaining_time: ";
    rosidl_generator_traits::value_to_yaml(msg.remaining_time, out);
    out << ", ";
  }

  // member: blood
  {
    out << "blood: ";
    rosidl_generator_traits::value_to_yaml(msg.blood, out);
    out << ", ";
  }

  // member: outpost_hp
  {
    out << "outpost_hp: ";
    rosidl_generator_traits::value_to_yaml(msg.outpost_hp, out);
    out << ", ";
  }

  // member: operator_command
  {
    out << "operator_command: ";
    to_flow_style_yaml(msg.operator_command, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const JudgeSystemData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: game_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "game_status: ";
    rosidl_generator_traits::value_to_yaml(msg.game_status, out);
    out << "\n";
  }

  // member: remaining_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "remaining_time: ";
    rosidl_generator_traits::value_to_yaml(msg.remaining_time, out);
    out << "\n";
  }

  // member: blood
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "blood: ";
    rosidl_generator_traits::value_to_yaml(msg.blood, out);
    out << "\n";
  }

  // member: outpost_hp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "outpost_hp: ";
    rosidl_generator_traits::value_to_yaml(msg.outpost_hp, out);
    out << "\n";
  }

  // member: operator_command
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "operator_command:\n";
    to_block_style_yaml(msg.operator_command, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const JudgeSystemData & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace rm_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use rm_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rm_interfaces::msg::JudgeSystemData & msg,
  std::ostream & out, size_t indentation = 0)
{
  rm_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rm_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const rm_interfaces::msg::JudgeSystemData & msg)
{
  return rm_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rm_interfaces::msg::JudgeSystemData>()
{
  return "rm_interfaces::msg::JudgeSystemData";
}

template<>
inline const char * name<rm_interfaces::msg::JudgeSystemData>()
{
  return "rm_interfaces/msg/JudgeSystemData";
}

template<>
struct has_fixed_size<rm_interfaces::msg::JudgeSystemData>
  : std::integral_constant<bool, has_fixed_size<rm_interfaces::msg::OperatorCommand>::value> {};

template<>
struct has_bounded_size<rm_interfaces::msg::JudgeSystemData>
  : std::integral_constant<bool, has_bounded_size<rm_interfaces::msg::OperatorCommand>::value> {};

template<>
struct is_message<rm_interfaces::msg::JudgeSystemData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RM_INTERFACES__MSG__DETAIL__JUDGE_SYSTEM_DATA__TRAITS_HPP_
