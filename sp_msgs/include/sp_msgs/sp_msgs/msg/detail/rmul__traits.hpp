// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sp_msgs:msg/RMUL.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUL__TRAITS_HPP_
#define SP_MSGS__MSG__DETAIL__RMUL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sp_msgs/msg/detail/rmul__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace sp_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const RMUL & msg,
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
    out << ", ";
  }

  // member: cmd_type
  {
    out << "cmd_type: ";
    rosidl_generator_traits::value_to_yaml(msg.cmd_type, out);
    out << ", ";
  }

  // member: emergency_stop
  {
    out << "emergency_stop: ";
    rosidl_generator_traits::value_to_yaml(msg.emergency_stop, out);
    out << ", ";
  }

  // member: rfid_supply_arrived
  {
    out << "rfid_supply_arrived: ";
    rosidl_generator_traits::value_to_yaml(msg.rfid_supply_arrived, out);
    out << ", ";
  }

  // member: rfid_control_arrived
  {
    out << "rfid_control_arrived: ";
    rosidl_generator_traits::value_to_yaml(msg.rfid_control_arrived, out);
    out << ", ";
  }

  // member: stop_gimbal_scan
  {
    out << "stop_gimbal_scan: ";
    rosidl_generator_traits::value_to_yaml(msg.stop_gimbal_scan, out);
    out << ", ";
  }

  // member: chassis_spin
  {
    out << "chassis_spin: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_spin, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: current_hp
  {
    out << "current_hp: ";
    rosidl_generator_traits::value_to_yaml(msg.current_hp, out);
    out << ", ";
  }

  // member: is_attacked
  {
    out << "is_attacked: ";
    rosidl_generator_traits::value_to_yaml(msg.is_attacked, out);
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
  const RMUL & msg,
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

  // member: cmd_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cmd_type: ";
    rosidl_generator_traits::value_to_yaml(msg.cmd_type, out);
    out << "\n";
  }

  // member: emergency_stop
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "emergency_stop: ";
    rosidl_generator_traits::value_to_yaml(msg.emergency_stop, out);
    out << "\n";
  }

  // member: rfid_supply_arrived
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rfid_supply_arrived: ";
    rosidl_generator_traits::value_to_yaml(msg.rfid_supply_arrived, out);
    out << "\n";
  }

  // member: rfid_control_arrived
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rfid_control_arrived: ";
    rosidl_generator_traits::value_to_yaml(msg.rfid_control_arrived, out);
    out << "\n";
  }

  // member: stop_gimbal_scan
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stop_gimbal_scan: ";
    rosidl_generator_traits::value_to_yaml(msg.stop_gimbal_scan, out);
    out << "\n";
  }

  // member: chassis_spin
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_spin: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_spin, out);
    out << "\n";
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
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

  // member: is_attacked
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_attacked: ";
    rosidl_generator_traits::value_to_yaml(msg.is_attacked, out);
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

inline std::string to_yaml(const RMUL & msg, bool use_flow_style = false)
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
  const sp_msgs::msg::RMUL & msg,
  std::ostream & out, size_t indentation = 0)
{
  sp_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sp_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sp_msgs::msg::RMUL & msg)
{
  return sp_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sp_msgs::msg::RMUL>()
{
  return "sp_msgs::msg::RMUL";
}

template<>
inline const char * name<sp_msgs::msg::RMUL>()
{
  return "sp_msgs/msg/RMUL";
}

template<>
struct has_fixed_size<sp_msgs::msg::RMUL>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<sp_msgs::msg::RMUL>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<sp_msgs::msg::RMUL>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SP_MSGS__MSG__DETAIL__RMUL__TRAITS_HPP_
