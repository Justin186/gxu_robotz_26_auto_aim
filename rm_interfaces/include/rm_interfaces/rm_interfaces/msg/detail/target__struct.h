// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rm_interfaces:msg/Target.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__TARGET__STRUCT_H_
#define RM_INTERFACES__MSG__DETAIL__TARGET__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'id'
#include "rosidl_runtime_c/string.h"
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'velocity'
#include "geometry_msgs/msg/detail/vector3__struct.h"

/// Struct defined in msg/Target in the package rm_interfaces.
typedef struct rm_interfaces__msg__Target
{
  std_msgs__msg__Header header;
  bool tracking;
  rosidl_runtime_c__String id;
  int32_t armors_num;
  geometry_msgs__msg__Point position;
  geometry_msgs__msg__Vector3 velocity;
  double yaw;
  double v_yaw;
  double radius_1;
  double radius_2;
  double d_za;
  double d_zc;
  double yaw_diff;
  double position_diff;
} rm_interfaces__msg__Target;

// Struct for a sequence of rm_interfaces__msg__Target.
typedef struct rm_interfaces__msg__Target__Sequence
{
  rm_interfaces__msg__Target * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rm_interfaces__msg__Target__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RM_INTERFACES__MSG__DETAIL__TARGET__STRUCT_H_
