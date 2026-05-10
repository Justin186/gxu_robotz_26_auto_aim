// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sp_msgs:msg/RMUCGameStatus.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_GAME_STATUS__TRAITS_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_GAME_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sp_msgs/msg/detail/rmuc_game_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace sp_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const RMUCGameStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: game_progress
  {
    out << "game_progress: ";
    rosidl_generator_traits::value_to_yaml(msg.game_progress, out);
    out << ", ";
  }

  // member: stage_remain_time
  {
    out << "stage_remain_time: ";
    rosidl_generator_traits::value_to_yaml(msg.stage_remain_time, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RMUCGameStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: game_progress
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "game_progress: ";
    rosidl_generator_traits::value_to_yaml(msg.game_progress, out);
    out << "\n";
  }

  // member: stage_remain_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stage_remain_time: ";
    rosidl_generator_traits::value_to_yaml(msg.stage_remain_time, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RMUCGameStatus & msg, bool use_flow_style = false)
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

}  // namespace sp_msgs

namespace rosidl_generator_traits
{

[[deprecated("use sp_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const sp_msgs::msg::RMUCGameStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  sp_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sp_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sp_msgs::msg::RMUCGameStatus & msg)
{
  return sp_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sp_msgs::msg::RMUCGameStatus>()
{
  return "sp_msgs::msg::RMUCGameStatus";
}

template<>
inline const char * name<sp_msgs::msg::RMUCGameStatus>()
{
  return "sp_msgs/msg/RMUCGameStatus";
}

template<>
struct has_fixed_size<sp_msgs::msg::RMUCGameStatus>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<sp_msgs::msg::RMUCGameStatus>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<sp_msgs::msg::RMUCGameStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SP_MSGS__MSG__DETAIL__RMUC_GAME_STATUS__TRAITS_HPP_
