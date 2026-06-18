// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rm_interfaces:msg/OperatorCommand.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__OPERATOR_COMMAND__STRUCT_HPP_
#define RM_INTERFACES__MSG__DETAIL__OPERATOR_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__rm_interfaces__msg__OperatorCommand __attribute__((deprecated))
#else
# define DEPRECATED__rm_interfaces__msg__OperatorCommand __declspec(deprecated)
#endif

namespace rm_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct OperatorCommand_
{
  using Type = OperatorCommand_<ContainerAllocator>;

  explicit OperatorCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_retreating = 0;
      this->is_drone_avoiding = 0;
      this->is_outpost_attacking = 0;
    }
  }

  explicit OperatorCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_retreating = 0;
      this->is_drone_avoiding = 0;
      this->is_outpost_attacking = 0;
    }
  }

  // field types and members
  using _is_retreating_type =
    uint8_t;
  _is_retreating_type is_retreating;
  using _is_drone_avoiding_type =
    uint8_t;
  _is_drone_avoiding_type is_drone_avoiding;
  using _is_outpost_attacking_type =
    uint8_t;
  _is_outpost_attacking_type is_outpost_attacking;

  // setters for named parameter idiom
  Type & set__is_retreating(
    const uint8_t & _arg)
  {
    this->is_retreating = _arg;
    return *this;
  }
  Type & set__is_drone_avoiding(
    const uint8_t & _arg)
  {
    this->is_drone_avoiding = _arg;
    return *this;
  }
  Type & set__is_outpost_attacking(
    const uint8_t & _arg)
  {
    this->is_outpost_attacking = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rm_interfaces::msg::OperatorCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const rm_interfaces::msg::OperatorCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rm_interfaces::msg::OperatorCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rm_interfaces::msg::OperatorCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::OperatorCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::OperatorCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::OperatorCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::OperatorCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rm_interfaces::msg::OperatorCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rm_interfaces::msg::OperatorCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rm_interfaces__msg__OperatorCommand
    std::shared_ptr<rm_interfaces::msg::OperatorCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rm_interfaces__msg__OperatorCommand
    std::shared_ptr<rm_interfaces::msg::OperatorCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const OperatorCommand_ & other) const
  {
    if (this->is_retreating != other.is_retreating) {
      return false;
    }
    if (this->is_drone_avoiding != other.is_drone_avoiding) {
      return false;
    }
    if (this->is_outpost_attacking != other.is_outpost_attacking) {
      return false;
    }
    return true;
  }
  bool operator!=(const OperatorCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct OperatorCommand_

// alias to use template instance with default allocator
using OperatorCommand =
  rm_interfaces::msg::OperatorCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__OPERATOR_COMMAND__STRUCT_HPP_
