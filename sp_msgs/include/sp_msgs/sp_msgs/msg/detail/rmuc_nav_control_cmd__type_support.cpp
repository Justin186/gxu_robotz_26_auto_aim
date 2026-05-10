// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from sp_msgs:msg/RMUCNavControlCmd.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "sp_msgs/msg/detail/rmuc_nav_control_cmd__struct.hpp"
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

void RMUCNavControlCmd_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) sp_msgs::msg::RMUCNavControlCmd(_init);
}

void RMUCNavControlCmd_fini_function(void * message_memory)
{
  auto typed_message = static_cast<sp_msgs::msg::RMUCNavControlCmd *>(message_memory);
  typed_message->~RMUCNavControlCmd();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember RMUCNavControlCmd_message_member_array[2] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sp_msgs::msg::RMUCNavControlCmd, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "cmd_type",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sp_msgs::msg::RMUCNavControlCmd, cmd_type),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers RMUCNavControlCmd_message_members = {
  "sp_msgs::msg",  // message namespace
  "RMUCNavControlCmd",  // message name
  2,  // number of fields
  sizeof(sp_msgs::msg::RMUCNavControlCmd),
  RMUCNavControlCmd_message_member_array,  // message members
  RMUCNavControlCmd_init_function,  // function to initialize message memory (memory has to be allocated)
  RMUCNavControlCmd_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t RMUCNavControlCmd_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &RMUCNavControlCmd_message_members,
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
get_message_type_support_handle<sp_msgs::msg::RMUCNavControlCmd>()
{
  return &::sp_msgs::msg::rosidl_typesupport_introspection_cpp::RMUCNavControlCmd_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, sp_msgs, msg, RMUCNavControlCmd)() {
  return &::sp_msgs::msg::rosidl_typesupport_introspection_cpp::RMUCNavControlCmd_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
