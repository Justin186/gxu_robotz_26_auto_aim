// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sp_msgs:msg/RMUCEnemyTracks.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_ENEMY_TRACKS__TRAITS_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_ENEMY_TRACKS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sp_msgs/msg/detail/rmuc_enemy_tracks__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace sp_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const RMUCEnemyTracks & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: enemy_x
  {
    if (msg.enemy_x.size() == 0) {
      out << "enemy_x: []";
    } else {
      out << "enemy_x: [";
      size_t pending_items = msg.enemy_x.size();
      for (auto item : msg.enemy_x) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: enemy_y
  {
    if (msg.enemy_y.size() == 0) {
      out << "enemy_y: []";
    } else {
      out << "enemy_y: [";
      size_t pending_items = msg.enemy_y.size();
      for (auto item : msg.enemy_y) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RMUCEnemyTracks & msg,
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

  // member: enemy_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.enemy_x.size() == 0) {
      out << "enemy_x: []\n";
    } else {
      out << "enemy_x:\n";
      for (auto item : msg.enemy_x) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: enemy_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.enemy_y.size() == 0) {
      out << "enemy_y: []\n";
    } else {
      out << "enemy_y:\n";
      for (auto item : msg.enemy_y) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RMUCEnemyTracks & msg, bool use_flow_style = false)
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
  const sp_msgs::msg::RMUCEnemyTracks & msg,
  std::ostream & out, size_t indentation = 0)
{
  sp_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sp_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sp_msgs::msg::RMUCEnemyTracks & msg)
{
  return sp_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sp_msgs::msg::RMUCEnemyTracks>()
{
  return "sp_msgs::msg::RMUCEnemyTracks";
}

template<>
inline const char * name<sp_msgs::msg::RMUCEnemyTracks>()
{
  return "sp_msgs/msg/RMUCEnemyTracks";
}

template<>
struct has_fixed_size<sp_msgs::msg::RMUCEnemyTracks>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<sp_msgs::msg::RMUCEnemyTracks>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<sp_msgs::msg::RMUCEnemyTracks>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SP_MSGS__MSG__DETAIL__RMUC_ENEMY_TRACKS__TRAITS_HPP_
