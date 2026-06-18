// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rm_interfaces:msg/ChassisCmd.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__CHASSIS_CMD__STRUCT_HPP_
#define RM_INTERFACES__MSG__DETAIL__CHASSIS_CMD__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'twist'
#include "geometry_msgs/msg/detail/twist__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rm_interfaces__msg__ChassisCmd __attribute__((deprecated))
#else
# define DEPRECATED__rm_interfaces__msg__ChassisCmd __declspec(deprecated)
#endif

namespace rm_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ChassisCmd_
{
  using Type = ChassisCmd_<ContainerAllocator>;

  explicit ChassisCmd_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    twist(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_spining = false;
      this->is_navigating = false;
    }
  }

  explicit ChassisCmd_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    twist(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_spining = false;
      this->is_navigating = false;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _is_spining_type =
    bool;
  _is_spining_type is_spining;
  using _is_navigating_type =
    bool;
  _is_navigating_type is_navigating;
  using _twist_type =
    geometry_msgs::msg::Twist_<ContainerAllocator>;
  _twist_type twist;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__is_spining(
    const bool & _arg)
  {
    this->is_spining = _arg;
    return *this;
  }
  Type & set__is_navigating(
    const bool & _arg)
  {
    this->is_navigating = _arg;
    return *this;
  }
  Type & set__twist(
    const geometry_msgs::msg::Twist_<ContainerAllocator> & _arg)
  {
    this->twist = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rm_interfaces::msg::ChassisCmd_<ContainerAllocator> *;
  using ConstRawPtr =
    const rm_interfaces::msg::ChassisCmd_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rm_interfaces::msg::ChassisCmd_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rm_interfaces::msg::ChassisCmd_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::ChassisCmd_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::ChassisCmd_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::ChassisCmd_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::ChassisCmd_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rm_interfaces::msg::ChassisCmd_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rm_interfaces::msg::ChassisCmd_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rm_interfaces__msg__ChassisCmd
    std::shared_ptr<rm_interfaces::msg::ChassisCmd_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rm_interfaces__msg__ChassisCmd
    std::shared_ptr<rm_interfaces::msg::ChassisCmd_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ChassisCmd_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->is_spining != other.is_spining) {
      return false;
    }
    if (this->is_navigating != other.is_navigating) {
      return false;
    }
    if (this->twist != other.twist) {
      return false;
    }
    return true;
  }
  bool operator!=(const ChassisCmd_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ChassisCmd_

// alias to use template instance with default allocator
using ChassisCmd =
  rm_interfaces::msg::ChassisCmd_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__CHASSIS_CMD__STRUCT_HPP_
