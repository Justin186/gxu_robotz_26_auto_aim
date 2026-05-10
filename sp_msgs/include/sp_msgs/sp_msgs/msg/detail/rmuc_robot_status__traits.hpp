// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sp_msgs:msg/RMUCRobotStatus.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_ROBOT_STATUS__TRAITS_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_ROBOT_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sp_msgs/msg/detail/rmuc_robot_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace sp_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const RMUCRobotStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: current_hp
  {
    out << "current_hp: ";
    rosidl_generator_traits::value_to_yaml(msg.current_hp, out);
    out << ", ";
  }

  // member: shooter_heat
  {
    out << "shooter_heat: ";
    rosidl_generator_traits::value_to_yaml(msg.shooter_heat, out);
    out << ", ";
  }

  // member: ammo_allow
  {
    out << "ammo_allow: ";
    rosidl_generator_traits::value_to_yaml(msg.ammo_allow, out);
    out << ", ";
  }

  // member: outpost_hp
  {
    out << "outpost_hp: ";
    rosidl_generator_traits::value_to_yaml(msg.outpost_hp, out);
    out << ", ";
  }

  // member: base_hp
  {
    out << "base_hp: ";
    rosidl_generator_traits::value_to_yaml(msg.base_hp, out);
    out << ", ";
  }

  // member: is_detect_enemy
  {
    out << "is_detect_enemy: ";
    rosidl_generator_traits::value_to_yaml(msg.is_detect_enemy, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RMUCRobotStatus & msg,
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

  // member: current_hp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_hp: ";
    rosidl_generator_traits::value_to_yaml(msg.current_hp, out);
    out << "\n";
  }

  // member: shooter_heat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "shooter_heat: ";
    rosidl_generator_traits::value_to_yaml(msg.shooter_heat, out);
    out << "\n";
  }

  // member: ammo_allow
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ammo_allow: ";
    rosidl_generator_traits::value_to_yaml(msg.ammo_allow, out);
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

  // member: base_hp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "base_hp: ";
    rosidl_generator_traits::value_to_yaml(msg.base_hp, out);
    out << "\n";
  }

  // member: is_detect_enemy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_detect_enemy: ";
    rosidl_generator_traits::value_to_yaml(msg.is_detect_enemy, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RMUCRobotStatus & msg, bool use_flow_style = false)
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
  const sp_msgs::msg::RMUCRobotStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  sp_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sp_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sp_msgs::msg::RMUCRobotStatus & msg)
{
  return sp_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sp_msgs::msg::RMUCRobotStatus>()
{
  return "sp_msgs::msg::RMUCRobotStatus";
}

template<>
inline const char * name<sp_msgs::msg::RMUCRobotStatus>()
{
  return "sp_msgs/msg/RMUCRobotStatus";
}

template<>
struct has_fixed_size<sp_msgs::msg::RMUCRobotStatus>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<sp_msgs::msg::RMUCRobotStatus>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<sp_msgs::msg::RMUCRobotStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SP_MSGS__MSG__DETAIL__RMUC_ROBOT_STATUS__TRAITS_HPP_
