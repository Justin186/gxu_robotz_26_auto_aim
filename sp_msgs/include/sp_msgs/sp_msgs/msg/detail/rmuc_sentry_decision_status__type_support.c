// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from sp_msgs:msg/RMUCSentryDecisionStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "sp_msgs/msg/detail/rmuc_sentry_decision_status__rosidl_typesupport_introspection_c.h"
#include "sp_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "sp_msgs/msg/detail/rmuc_sentry_decision_status__functions.h"
#include "sp_msgs/msg/detail/rmuc_sentry_decision_status__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void sp_msgs__msg__RMUCSentryDecisionStatus__rosidl_typesupport_introspection_c__RMUCSentryDecisionStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  sp_msgs__msg__RMUCSentryDecisionStatus__init(message_memory);
}

void sp_msgs__msg__RMUCSentryDecisionStatus__rosidl_typesupport_introspection_c__RMUCSentryDecisionStatus_fini_function(void * message_memory)
{
  sp_msgs__msg__RMUCSentryDecisionStatus__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember sp_msgs__msg__RMUCSentryDecisionStatus__rosidl_typesupport_introspection_c__RMUCSentryDecisionStatus_message_member_array[3] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sp_msgs__msg__RMUCSentryDecisionStatus, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "current_posture",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sp_msgs__msg__RMUCSentryDecisionStatus, current_posture),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "exchanged_ammo_total",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sp_msgs__msg__RMUCSentryDecisionStatus, exchanged_ammo_total),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers sp_msgs__msg__RMUCSentryDecisionStatus__rosidl_typesupport_introspection_c__RMUCSentryDecisionStatus_message_members = {
  "sp_msgs__msg",  // message namespace
  "RMUCSentryDecisionStatus",  // message name
  3,  // number of fields
  sizeof(sp_msgs__msg__RMUCSentryDecisionStatus),
  sp_msgs__msg__RMUCSentryDecisionStatus__rosidl_typesupport_introspection_c__RMUCSentryDecisionStatus_message_member_array,  // message members
  sp_msgs__msg__RMUCSentryDecisionStatus__rosidl_typesupport_introspection_c__RMUCSentryDecisionStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  sp_msgs__msg__RMUCSentryDecisionStatus__rosidl_typesupport_introspection_c__RMUCSentryDecisionStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t sp_msgs__msg__RMUCSentryDecisionStatus__rosidl_typesupport_introspection_c__RMUCSentryDecisionStatus_message_type_support_handle = {
  0,
  &sp_msgs__msg__RMUCSentryDecisionStatus__rosidl_typesupport_introspection_c__RMUCSentryDecisionStatus_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_sp_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sp_msgs, msg, RMUCSentryDecisionStatus)() {
  sp_msgs__msg__RMUCSentryDecisionStatus__rosidl_typesupport_introspection_c__RMUCSentryDecisionStatus_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!sp_msgs__msg__RMUCSentryDecisionStatus__rosidl_typesupport_introspection_c__RMUCSentryDecisionStatus_message_type_support_handle.typesupport_identifier) {
    sp_msgs__msg__RMUCSentryDecisionStatus__rosidl_typesupport_introspection_c__RMUCSentryDecisionStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &sp_msgs__msg__RMUCSentryDecisionStatus__rosidl_typesupport_introspection_c__RMUCSentryDecisionStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
