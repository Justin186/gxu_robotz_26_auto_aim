// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rm_interfaces:msg/DebugLights.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__DEBUG_LIGHTS__STRUCT_H_
#define RM_INTERFACES__MSG__DETAIL__DEBUG_LIGHTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'data'
#include "rm_interfaces/msg/detail/debug_light__struct.h"

/// Struct defined in msg/DebugLights in the package rm_interfaces.
typedef struct rm_interfaces__msg__DebugLights
{
  rm_interfaces__msg__DebugLight__Sequence data;
} rm_interfaces__msg__DebugLights;

// Struct for a sequence of rm_interfaces__msg__DebugLights.
typedef struct rm_interfaces__msg__DebugLights__Sequence
{
  rm_interfaces__msg__DebugLights * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rm_interfaces__msg__DebugLights__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RM_INTERFACES__MSG__DETAIL__DEBUG_LIGHTS__STRUCT_H_
