// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sp_msgs:msg/RMUL.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUL__STRUCT_HPP_
#define SP_MSGS__MSG__DETAIL__RMUL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sp_msgs__msg__RMUL __attribute__((deprecated))
#else
# define DEPRECATED__sp_msgs__msg__RMUL __declspec(deprecated)
#endif

namespace sp_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RMUL_
{
  using Type = RMUL_<ContainerAllocator>;

  explicit RMUL_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->game_progress = 0;
      this->stage_remain_time = 0;
      this->current_hp = 0;
      this->is_attacked = 0;
      this->shooter_heat = 0;
      this->rfid_supply_arrived = false;
      this->rfid_control_arrived = false;
      this->cmd_type = 0l;
      this->emergency_stop = false;
      this->stop_gimbal_scan = false;
      this->chassis_spin = false;
      this->x = 0.0f;
      this->y = 0.0f;
      this->is_detect_enemy = false;
      this->is_at_nav_goal = false;
    }
  }

  explicit RMUL_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->game_progress = 0;
      this->stage_remain_time = 0;
      this->current_hp = 0;
      this->is_attacked = 0;
      this->shooter_heat = 0;
      this->rfid_supply_arrived = false;
      this->rfid_control_arrived = false;
      this->cmd_type = 0l;
      this->emergency_stop = false;
      this->stop_gimbal_scan = false;
      this->chassis_spin = false;
      this->x = 0.0f;
      this->y = 0.0f;
      this->is_detect_enemy = false;
      this->is_at_nav_goal = false;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _game_progress_type =
    uint8_t;
  _game_progress_type game_progress;
  using _stage_remain_time_type =
    uint16_t;
  _stage_remain_time_type stage_remain_time;
  using _current_hp_type =
    uint16_t;
  _current_hp_type current_hp;
  using _is_attacked_type =
    uint8_t;
  _is_attacked_type is_attacked;
  using _shooter_heat_type =
    uint16_t;
  _shooter_heat_type shooter_heat;
  using _rfid_supply_arrived_type =
    bool;
  _rfid_supply_arrived_type rfid_supply_arrived;
  using _rfid_control_arrived_type =
    bool;
  _rfid_control_arrived_type rfid_control_arrived;
  using _cmd_type_type =
    int32_t;
  _cmd_type_type cmd_type;
  using _emergency_stop_type =
    bool;
  _emergency_stop_type emergency_stop;
  using _stop_gimbal_scan_type =
    bool;
  _stop_gimbal_scan_type stop_gimbal_scan;
  using _chassis_spin_type =
    bool;
  _chassis_spin_type chassis_spin;
  using _x_type =
    float;
  _x_type x;
  using _y_type =
    float;
  _y_type y;
  using _is_detect_enemy_type =
    bool;
  _is_detect_enemy_type is_detect_enemy;
  using _is_at_nav_goal_type =
    bool;
  _is_at_nav_goal_type is_at_nav_goal;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__game_progress(
    const uint8_t & _arg)
  {
    this->game_progress = _arg;
    return *this;
  }
  Type & set__stage_remain_time(
    const uint16_t & _arg)
  {
    this->stage_remain_time = _arg;
    return *this;
  }
  Type & set__current_hp(
    const uint16_t & _arg)
  {
    this->current_hp = _arg;
    return *this;
  }
  Type & set__is_attacked(
    const uint8_t & _arg)
  {
    this->is_attacked = _arg;
    return *this;
  }
  Type & set__shooter_heat(
    const uint16_t & _arg)
  {
    this->shooter_heat = _arg;
    return *this;
  }
  Type & set__rfid_supply_arrived(
    const bool & _arg)
  {
    this->rfid_supply_arrived = _arg;
    return *this;
  }
  Type & set__rfid_control_arrived(
    const bool & _arg)
  {
    this->rfid_control_arrived = _arg;
    return *this;
  }
  Type & set__cmd_type(
    const int32_t & _arg)
  {
    this->cmd_type = _arg;
    return *this;
  }
  Type & set__emergency_stop(
    const bool & _arg)
  {
    this->emergency_stop = _arg;
    return *this;
  }
  Type & set__stop_gimbal_scan(
    const bool & _arg)
  {
    this->stop_gimbal_scan = _arg;
    return *this;
  }
  Type & set__chassis_spin(
    const bool & _arg)
  {
    this->chassis_spin = _arg;
    return *this;
  }
  Type & set__x(
    const float & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const float & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__is_detect_enemy(
    const bool & _arg)
  {
    this->is_detect_enemy = _arg;
    return *this;
  }
  Type & set__is_at_nav_goal(
    const bool & _arg)
  {
    this->is_at_nav_goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sp_msgs::msg::RMUL_<ContainerAllocator> *;
  using ConstRawPtr =
    const sp_msgs::msg::RMUL_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sp_msgs::msg::RMUL_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sp_msgs::msg::RMUL_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sp_msgs::msg::RMUL_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sp_msgs::msg::RMUL_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sp_msgs::msg::RMUL_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sp_msgs::msg::RMUL_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sp_msgs::msg::RMUL_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sp_msgs::msg::RMUL_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sp_msgs__msg__RMUL
    std::shared_ptr<sp_msgs::msg::RMUL_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sp_msgs__msg__RMUL
    std::shared_ptr<sp_msgs::msg::RMUL_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RMUL_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->game_progress != other.game_progress) {
      return false;
    }
    if (this->stage_remain_time != other.stage_remain_time) {
      return false;
    }
    if (this->current_hp != other.current_hp) {
      return false;
    }
    if (this->is_attacked != other.is_attacked) {
      return false;
    }
    if (this->shooter_heat != other.shooter_heat) {
      return false;
    }
    if (this->rfid_supply_arrived != other.rfid_supply_arrived) {
      return false;
    }
    if (this->rfid_control_arrived != other.rfid_control_arrived) {
      return false;
    }
    if (this->cmd_type != other.cmd_type) {
      return false;
    }
    if (this->emergency_stop != other.emergency_stop) {
      return false;
    }
    if (this->stop_gimbal_scan != other.stop_gimbal_scan) {
      return false;
    }
    if (this->chassis_spin != other.chassis_spin) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->is_detect_enemy != other.is_detect_enemy) {
      return false;
    }
    if (this->is_at_nav_goal != other.is_at_nav_goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const RMUL_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RMUL_

// alias to use template instance with default allocator
using RMUL =
  sp_msgs::msg::RMUL_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUL__STRUCT_HPP_
