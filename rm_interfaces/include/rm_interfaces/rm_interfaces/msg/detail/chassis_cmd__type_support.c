// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rm_interfaces:msg/ChassisCmd.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rm_interfaces/msg/detail/chassis_cmd__rosidl_typesupport_introspection_c.h"
#include "rm_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rm_interfaces/msg/detail/chassis_cmd__functions.h"
#include "rm_interfaces/msg/detail/chassis_cmd__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `twist`
#include "geometry_msgs/msg/twist.h"
// Member `twist`
#include "geometry_msgs/msg/detail/twist__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rm_interfaces__msg__ChassisCmd__rosidl_typesupport_introspection_c__ChassisCmd_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rm_interfaces__msg__ChassisCmd__init(message_memory);
}

void rm_interfaces__msg__ChassisCmd__rosidl_typesupport_introspection_c__ChassisCmd_fini_function(void * message_memory)
{
  rm_interfaces__msg__ChassisCmd__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember rm_interfaces__msg__ChassisCmd__rosidl_typesupport_introspection_c__ChassisCmd_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces__msg__ChassisCmd, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "is_spining",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces__msg__ChassisCmd, is_spining),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "is_navigating",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces__msg__ChassisCmd, is_navigating),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "twist",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces__msg__ChassisCmd, twist),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rm_interfaces__msg__ChassisCmd__rosidl_typesupport_introspection_c__ChassisCmd_message_members = {
  "rm_interfaces__msg",  // message namespace
  "ChassisCmd",  // message name
  4,  // number of fields
  sizeof(rm_interfaces__msg__ChassisCmd),
  rm_interfaces__msg__ChassisCmd__rosidl_typesupport_introspection_c__ChassisCmd_message_member_array,  // message members
  rm_interfaces__msg__ChassisCmd__rosidl_typesupport_introspection_c__ChassisCmd_init_function,  // function to initialize message memory (memory has to be allocated)
  rm_interfaces__msg__ChassisCmd__rosidl_typesupport_introspection_c__ChassisCmd_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rm_interfaces__msg__ChassisCmd__rosidl_typesupport_introspection_c__ChassisCmd_message_type_support_handle = {
  0,
  &rm_interfaces__msg__ChassisCmd__rosidl_typesupport_introspection_c__ChassisCmd_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rm_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rm_interfaces, msg, ChassisCmd)() {
  rm_interfaces__msg__ChassisCmd__rosidl_typesupport_introspection_c__ChassisCmd_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  rm_interfaces__msg__ChassisCmd__rosidl_typesupport_introspection_c__ChassisCmd_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Twist)();
  if (!rm_interfaces__msg__ChassisCmd__rosidl_typesupport_introspection_c__ChassisCmd_message_type_support_handle.typesupport_identifier) {
    rm_interfaces__msg__ChassisCmd__rosidl_typesupport_introspection_c__ChassisCmd_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rm_interfaces__msg__ChassisCmd__rosidl_typesupport_introspection_c__ChassisCmd_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
