// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rm_interfaces:msg/Measurement.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__MEASUREMENT__STRUCT_H_
#define RM_INTERFACES__MSG__DETAIL__MEASUREMENT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Measurement in the package rm_interfaces.
typedef struct rm_interfaces__msg__Measurement
{
  double x1;
  double y1;
  double z1;
  double yaw1;
  double x2;
  double y2;
  double z2;
  double yaw2;
} rm_interfaces__msg__Measurement;

// Struct for a sequence of rm_interfaces__msg__Measurement.
typedef struct rm_interfaces__msg__Measurement__Sequence
{
  rm_interfaces__msg__Measurement * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rm_interfaces__msg__Measurement__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RM_INTERFACES__MSG__DETAIL__MEASUREMENT__STRUCT_H_
