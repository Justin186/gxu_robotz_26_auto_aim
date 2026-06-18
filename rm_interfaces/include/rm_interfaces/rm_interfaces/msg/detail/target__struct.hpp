// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rm_interfaces:msg/Target.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__TARGET__STRUCT_HPP_
#define RM_INTERFACES__MSG__DETAIL__TARGET__STRUCT_HPP_

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
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.hpp"
// Member 'velocity'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rm_interfaces__msg__Target __attribute__((deprecated))
#else
# define DEPRECATED__rm_interfaces__msg__Target __declspec(deprecated)
#endif

namespace rm_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Target_
{
  using Type = Target_<ContainerAllocator>;

  explicit Target_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    position(_init),
    velocity(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tracking = false;
      this->id = "";
      this->armors_num = 0l;
      this->yaw = 0.0;
      this->v_yaw = 0.0;
      this->radius_1 = 0.0;
      this->radius_2 = 0.0;
      this->d_za = 0.0;
      this->d_zc = 0.0;
      this->yaw_diff = 0.0;
      this->position_diff = 0.0;
    }
  }

  explicit Target_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    id(_alloc),
    position(_alloc, _init),
    velocity(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tracking = false;
      this->id = "";
      this->armors_num = 0l;
      this->yaw = 0.0;
      this->v_yaw = 0.0;
      this->radius_1 = 0.0;
      this->radius_2 = 0.0;
      this->d_za = 0.0;
      this->d_zc = 0.0;
      this->yaw_diff = 0.0;
      this->position_diff = 0.0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _tracking_type =
    bool;
  _tracking_type tracking;
  using _id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _id_type id;
  using _armors_num_type =
    int32_t;
  _armors_num_type armors_num;
  using _position_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _position_type position;
  using _velocity_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _velocity_type velocity;
  using _yaw_type =
    double;
  _yaw_type yaw;
  using _v_yaw_type =
    double;
  _v_yaw_type v_yaw;
  using _radius_1_type =
    double;
  _radius_1_type radius_1;
  using _radius_2_type =
    double;
  _radius_2_type radius_2;
  using _d_za_type =
    double;
  _d_za_type d_za;
  using _d_zc_type =
    double;
  _d_zc_type d_zc;
  using _yaw_diff_type =
    double;
  _yaw_diff_type yaw_diff;
  using _position_diff_type =
    double;
  _position_diff_type position_diff;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__tracking(
    const bool & _arg)
  {
    this->tracking = _arg;
    return *this;
  }
  Type & set__id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__armors_num(
    const int32_t & _arg)
  {
    this->armors_num = _arg;
    return *this;
  }
  Type & set__position(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__velocity(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__yaw(
    const double & _arg)
  {
    this->yaw = _arg;
    return *this;
  }
  Type & set__v_yaw(
    const double & _arg)
  {
    this->v_yaw = _arg;
    return *this;
  }
  Type & set__radius_1(
    const double & _arg)
  {
    this->radius_1 = _arg;
    return *this;
  }
  Type & set__radius_2(
    const double & _arg)
  {
    this->radius_2 = _arg;
    return *this;
  }
  Type & set__d_za(
    const double & _arg)
  {
    this->d_za = _arg;
    return *this;
  }
  Type & set__d_zc(
    const double & _arg)
  {
    this->d_zc = _arg;
    return *this;
  }
  Type & set__yaw_diff(
    const double & _arg)
  {
    this->yaw_diff = _arg;
    return *this;
  }
  Type & set__position_diff(
    const double & _arg)
  {
    this->position_diff = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rm_interfaces::msg::Target_<ContainerAllocator> *;
  using ConstRawPtr =
    const rm_interfaces::msg::Target_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rm_interfaces::msg::Target_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rm_interfaces::msg::Target_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::Target_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::Target_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rm_interfaces::msg::Target_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rm_interfaces::msg::Target_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rm_interfaces::msg::Target_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rm_interfaces::msg::Target_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rm_interfaces__msg__Target
    std::shared_ptr<rm_interfaces::msg::Target_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rm_interfaces__msg__Target
    std::shared_ptr<rm_interfaces::msg::Target_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Target_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->tracking != other.tracking) {
      return false;
    }
    if (this->id != other.id) {
      return false;
    }
    if (this->armors_num != other.armors_num) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    if (this->v_yaw != other.v_yaw) {
      return false;
    }
    if (this->radius_1 != other.radius_1) {
      return false;
    }
    if (this->radius_2 != other.radius_2) {
      return false;
    }
    if (this->d_za != other.d_za) {
      return false;
    }
    if (this->d_zc != other.d_zc) {
      return false;
    }
    if (this->yaw_diff != other.yaw_diff) {
      return false;
    }
    if (this->position_diff != other.position_diff) {
      return false;
    }
    return true;
  }
  bool operator!=(const Target_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Target_

// alias to use template instance with default allocator
using Target =
  rm_interfaces::msg::Target_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rm_interfaces

#endif  // RM_INTERFACES__MSG__DETAIL__TARGET__STRUCT_HPP_
