// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rm_interfaces:msg/Armors.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__ARMORS__STRUCT_H_
#define RM_INTERFACES__MSG__DETAIL__ARMORS__STRUCT_H_

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
// Member 'armors'
#include "rm_interfaces/msg/detail/armor__struct.h"

/// Struct defined in msg/Armors in the package rm_interfaces.
typedef struct rm_interfaces__msg__Armors
{
  std_msgs__msg__Header header;
  rm_interfaces__msg__Armor__Sequence armors;
} rm_interfaces__msg__Armors;

// Struct for a sequence of rm_interfaces__msg__Armors.
typedef struct rm_interfaces__msg__Armors__Sequence
{
  rm_interfaces__msg__Armors * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rm_interfaces__msg__Armors__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RM_INTERFACES__MSG__DETAIL__ARMORS__STRUCT_H_
