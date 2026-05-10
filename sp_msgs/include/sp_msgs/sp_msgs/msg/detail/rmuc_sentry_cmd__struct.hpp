// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sp_msgs:msg/RMUCSentryCmd.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_SENTRY_CMD__STRUCT_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_SENTRY_CMD__STRUCT_HPP_

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
# define DEPRECATED__sp_msgs__msg__RMUCSentryCmd __attribute__((deprecated))
#else
# define DEPRECATED__sp_msgs__msg__RMUCSentryCmd __declspec(deprecated)
#endif

namespace sp_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RMUCSentryCmd_
{
  using Type = RMUCSentryCmd_<ContainerAllocator>;

  explicit RMUCSentryCmd_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cmd_posture = 0;
      this->cmd_confirm_respawn = false;
    }
  }

  explicit RMUCSentryCmd_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cmd_posture = 0;
      this->cmd_confirm_respawn = false;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _cmd_posture_type =
    uint8_t;
  _cmd_posture_type cmd_posture;
  using _cmd_confirm_respawn_type =
    bool;
  _cmd_confirm_respawn_type cmd_confirm_respawn;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__cmd_posture(
    const uint8_t & _arg)
  {
    this->cmd_posture = _arg;
    return *this;
  }
  Type & set__cmd_confirm_respawn(
    const bool & _arg)
  {
    this->cmd_confirm_respawn = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sp_msgs::msg::RMUCSentryCmd_<ContainerAllocator> *;
  using ConstRawPtr =
    const sp_msgs::msg::RMUCSentryCmd_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sp_msgs::msg::RMUCSentryCmd_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sp_msgs::msg::RMUCSentryCmd_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sp_msgs::msg::RMUCSentryCmd_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sp_msgs::msg::RMUCSentryCmd_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sp_msgs::msg::RMUCSentryCmd_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sp_msgs::msg::RMUCSentryCmd_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sp_msgs::msg::RMUCSentryCmd_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sp_msgs::msg::RMUCSentryCmd_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sp_msgs__msg__RMUCSentryCmd
    std::shared_ptr<sp_msgs::msg::RMUCSentryCmd_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sp_msgs__msg__RMUCSentryCmd
    std::shared_ptr<sp_msgs::msg::RMUCSentryCmd_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RMUCSentryCmd_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->cmd_posture != other.cmd_posture) {
      return false;
    }
    if (this->cmd_confirm_respawn != other.cmd_confirm_respawn) {
      return false;
    }
    return true;
  }
  bool operator!=(const RMUCSentryCmd_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RMUCSentryCmd_

// alias to use template instance with default allocator
using RMUCSentryCmd =
  sp_msgs::msg::RMUCSentryCmd_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUC_SENTRY_CMD__STRUCT_HPP_
