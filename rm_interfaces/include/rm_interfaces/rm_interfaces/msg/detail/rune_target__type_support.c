// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rm_interfaces:msg/RuneTarget.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rm_interfaces/msg/detail/rune_target__rosidl_typesupport_introspection_c.h"
#include "rm_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rm_interfaces/msg/detail/rune_target__functions.h"
#include "rm_interfaces/msg/detail/rune_target__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `pts`
#include "rm_interfaces/msg/point2d.h"
// Member `pts`
#include "rm_interfaces/msg/detail/point2d__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__RuneTarget_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rm_interfaces__msg__RuneTarget__init(message_memory);
}

void rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__RuneTarget_fini_function(void * message_memory)
{
  rm_interfaces__msg__RuneTarget__fini(message_memory);
}

size_t rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__size_function__RuneTarget__pts(
  const void * untyped_member)
{
  (void)untyped_member;
  return 5;
}

const void * rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__get_const_function__RuneTarget__pts(
  const void * untyped_member, size_t index)
{
  const rm_interfaces__msg__Point2d * member =
    (const rm_interfaces__msg__Point2d *)(untyped_member);
  return &member[index];
}

void * rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__get_function__RuneTarget__pts(
  void * untyped_member, size_t index)
{
  rm_interfaces__msg__Point2d * member =
    (rm_interfaces__msg__Point2d *)(untyped_member);
  return &member[index];
}

void rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__fetch_function__RuneTarget__pts(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rm_interfaces__msg__Point2d * item =
    ((const rm_interfaces__msg__Point2d *)
    rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__get_const_function__RuneTarget__pts(untyped_member, index));
  rm_interfaces__msg__Point2d * value =
    (rm_interfaces__msg__Point2d *)(untyped_value);
  *value = *item;
}

void rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__assign_function__RuneTarget__pts(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rm_interfaces__msg__Point2d * item =
    ((rm_interfaces__msg__Point2d *)
    rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__get_function__RuneTarget__pts(untyped_member, index));
  const rm_interfaces__msg__Point2d * value =
    (const rm_interfaces__msg__Point2d *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__RuneTarget_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces__msg__RuneTarget, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pts",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    5,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces__msg__RuneTarget, pts),  // bytes offset in struct
    NULL,  // default value
    rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__size_function__RuneTarget__pts,  // size() function pointer
    rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__get_const_function__RuneTarget__pts,  // get_const(index) function pointer
    rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__get_function__RuneTarget__pts,  // get(index) function pointer
    rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__fetch_function__RuneTarget__pts,  // fetch(index, &value) function pointer
    rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__assign_function__RuneTarget__pts,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "is_lost",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces__msg__RuneTarget, is_lost),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "is_big_rune",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces__msg__RuneTarget, is_big_rune),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__RuneTarget_message_members = {
  "rm_interfaces__msg",  // message namespace
  "RuneTarget",  // message name
  4,  // number of fields
  sizeof(rm_interfaces__msg__RuneTarget),
  rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__RuneTarget_message_member_array,  // message members
  rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__RuneTarget_init_function,  // function to initialize message memory (memory has to be allocated)
  rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__RuneTarget_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__RuneTarget_message_type_support_handle = {
  0,
  &rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__RuneTarget_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rm_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rm_interfaces, msg, RuneTarget)() {
  rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__RuneTarget_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__RuneTarget_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rm_interfaces, msg, Point2d)();
  if (!rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__RuneTarget_message_type_support_handle.typesupport_identifier) {
    rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__RuneTarget_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rm_interfaces__msg__RuneTarget__rosidl_typesupport_introspection_c__RuneTarget_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
