// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rm_interfaces:msg/Armor.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__ARMOR__STRUCT_HPP_
#define RM_INTERFACES__MSG__DETAIL__ARMOR__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rm_interfaces__msg__Armor __attribute__((deprecated))
#else
# define DEPRECATED__rm_interfaces__msg__Armor __declspec(deprecated)
#endif

namespace rm_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Armor_
{
  using Type = Armor_<ContainerAllocator>;

  explicit Armor_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->number = "";
      this->type = "";
      this->distance_to_image_center = 0.0f;
    }
  }

  explicit Armor_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : number(_alloc),
    type(_alloc),
    pose(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->number = "";
      this->type = "";
      this->distance_to_image_center = 0.0f;
    }
  }

  // field types and members
  using _number_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _number_type number;
  using _type_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _type_type type;
  using _distance_to_image_center_type =
    float;
  _distance_to_image_center_type distance_to_image_center;
  using _pose_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _pose_type pose;

  // setters for named parameter idiom
  Type & set__number(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->number = _arg;
    return *this;
  }
  Type & set__type(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->type = _arg;
    return *this;
  }
  Type & set__distance_to_image_center(
    const float & _arg)
  {
    this->distance_to_image_center = _arg;
    return *this;
  }
  Type & set__pose(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->pose = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rm_interfaces::msg::Armor_<ContainerAllocator> *;
  using ConstRawPtr =
    const rm_interfaces::msg::Armor_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rm_interfaces::msg::Armor_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rm_interfaces::msg::Armor_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::Armor_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::Armor_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::Armor_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::Armor_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rm_interfaces::msg::Armor_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rm_interfaces::msg::Armor_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rm_interfaces__msg__Armor
    std::shared_ptr<rm_interfaces::msg::Armor_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rm_interfaces__msg__Armor
    std::shared_ptr<rm_interfaces::msg::Armor_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Armor_ & other) const
  {
    if (this->number != other.number) {
      return false;
    }
    if (this->type != other.type) {
      return false;
    }
    if (this->distance_to_image_center != other.distance_to_image_center) {
      return false;
    }
    if (this->pose != other.pose) {
      return false;
    }
    return true;
  }
  bool operator!=(const Armor_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Armor_

// alias to use template instance with default allocator
using Armor =
  rm_interfaces::msg::Armor_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__ARMOR__STRUCT_HPP_
