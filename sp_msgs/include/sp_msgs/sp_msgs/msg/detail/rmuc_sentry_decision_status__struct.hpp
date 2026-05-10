// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sp_msgs:msg/RMUCSentryDecisionStatus.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_SENTRY_DECISION_STATUS__STRUCT_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_SENTRY_DECISION_STATUS__STRUCT_HPP_

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
# define DEPRECATED__sp_msgs__msg__RMUCSentryDecisionStatus __attribute__((deprecated))
#else
# define DEPRECATED__sp_msgs__msg__RMUCSentryDecisionStatus __declspec(deprecated)
#endif

namespace sp_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RMUCSentryDecisionStatus_
{
  using Type = RMUCSentryDecisionStatus_<ContainerAllocator>;

  explicit RMUCSentryDecisionStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_posture = 0;
      this->exchanged_ammo_total = 0;
    }
  }

  explicit RMUCSentryDecisionStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_posture = 0;
      this->exchanged_ammo_total = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _current_posture_type =
    uint8_t;
  _current_posture_type current_posture;
  using _exchanged_ammo_total_type =
    uint16_t;
  _exchanged_ammo_total_type exchanged_ammo_total;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__current_posture(
    const uint8_t & _arg)
  {
    this->current_posture = _arg;
    return *this;
  }
  Type & set__exchanged_ammo_total(
    const uint16_t & _arg)
  {
    this->exchanged_ammo_total = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sp_msgs::msg::RMUCSentryDecisionStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const sp_msgs::msg::RMUCSentryDecisionStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sp_msgs::msg::RMUCSentryDecisionStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sp_msgs::msg::RMUCSentryDecisionStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sp_msgs::msg::RMUCSentryDecisionStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sp_msgs::msg::RMUCSentryDecisionStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sp_msgs::msg::RMUCSentryDecisionStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sp_msgs::msg::RMUCSentryDecisionStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sp_msgs::msg::RMUCSentryDecisionStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sp_msgs::msg::RMUCSentryDecisionStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sp_msgs__msg__RMUCSentryDecisionStatus
    std::shared_ptr<sp_msgs::msg::RMUCSentryDecisionStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sp_msgs__msg__RMUCSentryDecisionStatus
    std::shared_ptr<sp_msgs::msg::RMUCSentryDecisionStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RMUCSentryDecisionStatus_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->current_posture != other.current_posture) {
      return false;
    }
    if (this->exchanged_ammo_total != other.exchanged_ammo_total) {
      return false;
    }
    return true;
  }
  bool operator!=(const RMUCSentryDecisionStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RMUCSentryDecisionStatus_

// alias to use template instance with default allocator
using RMUCSentryDecisionStatus =
  sp_msgs::msg::RMUCSentryDecisionStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUC_SENTRY_DECISION_STATUS__STRUCT_HPP_
