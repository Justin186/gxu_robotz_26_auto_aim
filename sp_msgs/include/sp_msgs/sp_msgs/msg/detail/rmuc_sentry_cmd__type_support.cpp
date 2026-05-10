// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from sp_msgs:msg/RMUCSentryCmd.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "sp_msgs/msg/detail/rmuc_sentry_cmd__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace sp_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void RMUCSentryCmd_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) sp_msgs::msg::RMUCSentryCmd(_init);
}

void RMUCSentryCmd_fini_function(void * message_memory)
{
  auto typed_message = static_cast<sp_msgs::msg::RMUCSentryCmd *>(message_memory);
  typed_message->~RMUCSentryCmd();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember RMUCSentryCmd_message_member_array[3] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sp_msgs::msg::RMUCSentryCmd, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "cmd_posture",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sp_msgs::msg::RMUCSentryCmd, cmd_posture),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "cmd_confirm_respawn",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sp_msgs::msg::RMUCSentryCmd, cmd_confirm_respawn),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers RMUCSentryCmd_message_members = {
  "sp_msgs::msg",  // message namespace
  "RMUCSentryCmd",  // message name
  3,  // number of fields
  sizeof(sp_msgs::msg::RMUCSentryCmd),
  RMUCSentryCmd_message_member_array,  // message members
  RMUCSentryCmd_init_function,  // function to initialize message memory (memory has to be allocated)
  RMUCSentryCmd_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t RMUCSentryCmd_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &RMUCSentryCmd_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace sp_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<sp_msgs::msg::RMUCSentryCmd>()
{
  return &::sp_msgs::msg::rosidl_typesupport_introspection_cpp::RMUCSentryCmd_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, sp_msgs, msg, RMUCSentryCmd)() {
  return &::sp_msgs::msg::rosidl_typesupport_introspection_cpp::RMUCSentryCmd_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
