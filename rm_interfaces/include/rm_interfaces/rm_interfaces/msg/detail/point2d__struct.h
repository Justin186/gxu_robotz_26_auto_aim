// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rm_interfaces:msg/Point2d.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__POINT2D__STRUCT_H_
#define RM_INTERFACES__MSG__DETAIL__POINT2D__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Point2d in the package rm_interfaces.
typedef struct rm_interfaces__msg__Point2d
{
  float x;
  float y;
} rm_interfaces__msg__Point2d;

// Struct for a sequence of rm_interfaces__msg__Point2d.
typedef struct rm_interfaces__msg__Point2d__Sequence
{
  rm_interfaces__msg__Point2d * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rm_interfaces__msg__Point2d__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RM_INTERFACES__MSG__DETAIL__POINT2D__STRUCT_H_
