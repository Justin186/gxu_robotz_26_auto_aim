// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sp_msgs:msg/RMUCTeamHP.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_TEAM_HP__STRUCT_HPP_
#define SP_MSGS__MSG__DETAIL__RMUC_TEAM_HP__STRUCT_HPP_

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
# define DEPRECATED__sp_msgs__msg__RMUCTeamHP __attribute__((deprecated))
#else
# define DEPRECATED__sp_msgs__msg__RMUCTeamHP __declspec(deprecated)
#endif

namespace sp_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RMUCTeamHP_
{
  using Type = RMUCTeamHP_<ContainerAllocator>;

  explicit RMUCTeamHP_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->outpost_hp = 0;
      this->base_hp = 0;
    }
  }

  explicit RMUCTeamHP_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->outpost_hp = 0;
      this->base_hp = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _outpost_hp_type =
    uint16_t;
  _outpost_hp_type outpost_hp;
  using _base_hp_type =
    uint16_t;
  _base_hp_type base_hp;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
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

  // constant declarations

  // pointer types
  using RawPtr =
    sp_msgs::msg::RMUCTeamHP_<ContainerAllocator> *;
  using ConstRawPtr =
    const sp_msgs::msg::RMUCTeamHP_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sp_msgs::msg::RMUCTeamHP_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sp_msgs::msg::RMUCTeamHP_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sp_msgs::msg::RMUCTeamHP_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sp_msgs::msg::RMUCTeamHP_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sp_msgs::msg::RMUCTeamHP_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sp_msgs::msg::RMUCTeamHP_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sp_msgs::msg::RMUCTeamHP_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sp_msgs::msg::RMUCTeamHP_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sp_msgs__msg__RMUCTeamHP
    std::shared_ptr<sp_msgs::msg::RMUCTeamHP_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sp_msgs__msg__RMUCTeamHP
    std::shared_ptr<sp_msgs::msg::RMUCTeamHP_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RMUCTeamHP_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->outpost_hp != other.outpost_hp) {
      return false;
    }
    if (this->base_hp != other.base_hp) {
      return false;
    }
    return true;
  }
  bool operator!=(const RMUCTeamHP_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RMUCTeamHP_

// alias to use template instance with default allocator
using RMUCTeamHP =
  sp_msgs::msg::RMUCTeamHP_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sp_msgs

#endif  // SP_MSGS__MSG__DETAIL__RMUC_TEAM_HP__STRUCT_HPP_
