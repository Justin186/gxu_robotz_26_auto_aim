// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sp_msgs:msg/RMUCNavControlCmd.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_NAV_CONTROL_CMD__STRUCT_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_NAV_CONTROL_CMD__STRUCT_HPP_

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
# define DEPRECATED__sp_msgs__msg__RMUCNavControlCmd __attribute__((deprecated))
#else
# define DEPRECATED__sp_msgs__msg__RMUCNavControlCmd __declspec(deprecated)
#endif

namespace sp_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RMUCNavControlCmd_
{
  using Type = RMUCNavControlCmd_<ContainerAllocator>;

  explicit RMUCNavControlCmd_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cmd_type = 0l;
    }
  }

  explicit RMUCNavControlCmd_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cmd_type = 0l;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _cmd_type_type =
    int32_t;
  _cmd_type_type cmd_type;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__cmd_type(
    const int32_t & _arg)
  {
    this->cmd_type = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sp_msgs::msg::RMUCNavControlCmd_<ContainerAllocator> *;
  using ConstRawPtr =
    const sp_msgs::msg::RMUCNavControlCmd_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sp_msgs::msg::RMUCNavControlCmd_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sp_msgs::msg::RMUCNavControlCmd_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sp_msgs::msg::RMUCNavControlCmd_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sp_msgs::msg::RMUCNavControlCmd_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sp_msgs::msg::RMUCNavControlCmd_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sp_msgs::msg::RMUCNavControlCmd_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sp_msgs::msg::RMUCNavControlCmd_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sp_msgs::msg::RMUCNavControlCmd_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sp_msgs__msg__RMUCNavControlCmd
    std::shared_ptr<sp_msgs::msg::RMUCNavControlCmd_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sp_msgs__msg__RMUCNavControlCmd
    std::shared_ptr<sp_msgs::msg::RMUCNavControlCmd_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RMUCNavControlCmd_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->cmd_type != other.cmd_type) {
      return false;
    }
    return true;
  }
  bool operator!=(const RMUCNavControlCmd_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RMUCNavControlCmd_

// alias to use template instance with default allocator
using RMUCNavControlCmd =
  sp_msgs::msg::RMUCNavControlCmd_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUC_NAV_CONTROL_CMD__STRUCT_HPP_
