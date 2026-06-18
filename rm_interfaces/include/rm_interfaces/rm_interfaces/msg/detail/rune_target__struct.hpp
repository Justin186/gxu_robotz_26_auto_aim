// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rm_interfaces:msg/RuneTarget.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__RUNE_TARGET__STRUCT_HPP_
#define RM_INTERFACES__MSG__DETAIL__RUNE_TARGET__STRUCT_HPP_

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
// Member 'pts'
#include "rm_interfaces/msg/detail/point2d__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rm_interfaces__msg__RuneTarget __attribute__((deprecated))
#else
# define DEPRECATED__rm_interfaces__msg__RuneTarget __declspec(deprecated)
#endif

namespace rm_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RuneTarget_
{
  using Type = RuneTarget_<ContainerAllocator>;

  explicit RuneTarget_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pts.fill(rm_interfaces::msg::Point2d_<ContainerAllocator>{_init});
      this->is_lost = false;
      this->is_big_rune = false;
    }
  }

  explicit RuneTarget_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    pts(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pts.fill(rm_interfaces::msg::Point2d_<ContainerAllocator>{_alloc, _init});
      this->is_lost = false;
      this->is_big_rune = false;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _pts_type =
    std::array<rm_interfaces::msg::Point2d_<ContainerAllocator>, 5>;
  _pts_type pts;
  using _is_lost_type =
    bool;
  _is_lost_type is_lost;
  using _is_big_rune_type =
    bool;
  _is_big_rune_type is_big_rune;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__pts(
    const std::array<rm_interfaces::msg::Point2d_<ContainerAllocator>, 5> & _arg)
  {
    this->pts = _arg;
    return *this;
  }
  Type & set__is_lost(
    const bool & _arg)
  {
    this->is_lost = _arg;
    return *this;
  }
  Type & set__is_big_rune(
    const bool & _arg)
  {
    this->is_big_rune = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rm_interfaces::msg::RuneTarget_<ContainerAllocator> *;
  using ConstRawPtr =
    const rm_interfaces::msg::RuneTarget_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rm_interfaces::msg::RuneTarget_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rm_interfaces::msg::RuneTarget_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::RuneTarget_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::RuneTarget_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::RuneTarget_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::RuneTarget_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rm_interfaces::msg::RuneTarget_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rm_interfaces::msg::RuneTarget_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rm_interfaces__msg__RuneTarget
    std::shared_ptr<rm_interfaces::msg::RuneTarget_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rm_interfaces__msg__RuneTarget
    std::shared_ptr<rm_interfaces::msg::RuneTarget_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RuneTarget_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->pts != other.pts) {
      return false;
    }
    if (this->is_lost != other.is_lost) {
      return false;
    }
    if (this->is_big_rune != other.is_big_rune) {
      return false;
    }
    return true;
  }
  bool operator!=(const RuneTarget_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RuneTarget_

// alias to use template instance with default allocator
using RuneTarget =
  rm_interfaces::msg::RuneTarget_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__RUNE_TARGET__STRUCT_HPP_
