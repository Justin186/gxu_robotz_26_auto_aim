// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rm_interfaces:msg/DebugArmors.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__DEBUG_ARMORS__STRUCT_H_
#define RM_INTERFACES__MSG__DETAIL__DEBUG_ARMORS__STRUCT_H_

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
#include "rm_interfaces/msg/detail/debug_armor__struct.h"

/// Struct defined in msg/DebugArmors in the package rm_interfaces.
typedef struct rm_interfaces__msg__DebugArmors
{
  rm_interfaces__msg__DebugArmor__Sequence data;
} rm_interfaces__msg__DebugArmors;

// Struct for a sequence of rm_interfaces__msg__DebugArmors.
typedef struct rm_interfaces__msg__DebugArmors__Sequence
{
  rm_interfaces__msg__DebugArmors * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rm_interfaces__msg__DebugArmors__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RM_INTERFACES__MSG__DETAIL__DEBUG_ARMORS__STRUCT_H_
