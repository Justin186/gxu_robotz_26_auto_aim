// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rm_interfaces:msg/DebugLight.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__DEBUG_LIGHT__STRUCT_H_
#define RM_INTERFACES__MSG__DETAIL__DEBUG_LIGHT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/DebugLight in the package rm_interfaces.
typedef struct rm_interfaces__msg__DebugLight
{
  int32_t center_x;
  bool is_light;
  float ratio;
  float angle;
} rm_interfaces__msg__DebugLight;

// Struct for a sequence of rm_interfaces__msg__DebugLight.
typedef struct rm_interfaces__msg__DebugLight__Sequence
{
  rm_interfaces__msg__DebugLight * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rm_interfaces__msg__DebugLight__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RM_INTERFACES__MSG__DETAIL__DEBUG_LIGHT__STRUCT_H_
