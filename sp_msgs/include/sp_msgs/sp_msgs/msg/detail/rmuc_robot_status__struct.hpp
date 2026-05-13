// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sp_msgs:msg/RMUCRobotStatus.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_ROBOT_STATUS__STRUCT_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_ROBOT_STATUS__STRUCT_HPP_

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
# define DEPRECATED__sp_msgs__msg__RMUCRobotStatus __attribute__((deprecated))
#else
# define DEPRECATED__sp_msgs__msg__RMUCRobotStatus __declspec(deprecated)
#endif

namespace sp_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RMUCRobotStatus_
{
  using Type = RMUCRobotStatus_<ContainerAllocator>;

  explicit RMUCRobotStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_hp = 0;
      this->shooter_heat = 0;
      this->ammo_allow = 0;
      this->outpost_hp = 0;
      this->base_hp = 0;
      this->enemy_outpost_status = 0ul;
      this->is_detect_enemy = false;
    }
  }

  explicit RMUCRobotStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_hp = 0;
      this->shooter_heat = 0;
      this->ammo_allow = 0;
      this->outpost_hp = 0;
      this->base_hp = 0;
      this->enemy_outpost_status = 0ul;
      this->is_detect_enemy = false;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _current_hp_type =
    uint16_t;
  _current_hp_type current_hp;
  using _shooter_heat_type =
    uint16_t;
  _shooter_heat_type shooter_heat;
  using _ammo_allow_type =
    uint16_t;
  _ammo_allow_type ammo_allow;
  using _outpost_hp_type =
    uint16_t;
  _outpost_hp_type outpost_hp;
  using _base_hp_type =
    uint16_t;
  _base_hp_type base_hp;
  using _enemy_outpost_status_type =
    uint32_t;
  _enemy_outpost_status_type enemy_outpost_status;
  using _is_detect_enemy_type =
    bool;
  _is_detect_enemy_type is_detect_enemy;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__current_hp(
    const uint16_t & _arg)
  {
    this->current_hp = _arg;
    return *this;
  }
  Type & set__shooter_heat(
    const uint16_t & _arg)
  {
    this->shooter_heat = _arg;
    return *this;
  }
  Type & set__ammo_allow(
    const uint16_t & _arg)
  {
    this->ammo_allow = _arg;
    return *this;
  }
  Type & set__outpost_hp(
    const uint16_t & _arg)
  {
    this->outpost_hp = _arg;
    return *this;
  }
  Type & set__base_hp(
    const uint16_t & _arg)
  {
    this->base_hp = _arg;
    return *this;
  }
  Type & set__enemy_outpost_status(
    const uint32_t & _arg)
  {
    this->enemy_outpost_status = _arg;
    return *this;
  }
  Type & set__is_detect_enemy(
    const bool & _arg)
  {
    this->is_detect_enemy = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sp_msgs::msg::RMUCRobotStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const sp_msgs::msg::RMUCRobotStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sp_msgs::msg::RMUCRobotStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sp_msgs::msg::RMUCRobotStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sp_msgs::msg::RMUCRobotStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sp_msgs::msg::RMUCRobotStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sp_msgs::msg::RMUCRobotStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sp_msgs::msg::RMUCRobotStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sp_msgs::msg::RMUCRobotStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sp_msgs::msg::RMUCRobotStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sp_msgs__msg__RMUCRobotStatus
    std::shared_ptr<sp_msgs::msg::RMUCRobotStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sp_msgs__msg__RMUCRobotStatus
    std::shared_ptr<sp_msgs::msg::RMUCRobotStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RMUCRobotStatus_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->current_hp != other.current_hp) {
      return false;
    }
    if (this->shooter_heat != other.shooter_heat) {
      return false;
    }
    if (this->ammo_allow != other.ammo_allow) {
      return false;
    }
    if (this->outpost_hp != other.outpost_hp) {
      return false;
    }
    if (this->base_hp != other.base_hp) {
      return false;
    }
    if (this->enemy_outpost_status != other.enemy_outpost_status) {
      return false;
    }
    if (this->is_detect_enemy != other.is_detect_enemy) {
      return false;
    }
    return true;
  }
  bool operator!=(const RMUCRobotStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RMUCRobotStatus_

// alias to use template instance with default allocator
using RMUCRobotStatus =
  sp_msgs::msg::RMUCRobotStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUC_ROBOT_STATUS__STRUCT_HPP_
