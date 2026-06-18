// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from rm_interfaces:msg/JudgeSystemData.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "rm_interfaces/msg/detail/judge_system_data__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace rm_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void JudgeSystemData_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) rm_interfaces::msg::JudgeSystemData(_init);
}

void JudgeSystemData_fini_function(void * message_memory)
{
  auto typed_message = static_cast<rm_interfaces::msg::JudgeSystemData *>(message_memory);
  typed_message->~JudgeSystemData();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember JudgeSystemData_message_member_array[5] = {
  {
    "game_status",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces::msg::JudgeSystemData, game_status),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "remaining_time",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces::msg::JudgeSystemData, remaining_time),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "blood",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces::msg::JudgeSystemData, blood),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "outpost_hp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces::msg::JudgeSystemData, outpost_hp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "operator_command",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<rm_interfaces::msg::OperatorCommand>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces::msg::JudgeSystemData, operator_command),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers JudgeSystemData_message_members = {
  "rm_interfaces::msg",  // message namespace
  "JudgeSystemData",  // message name
  5,  // number of fields
  sizeof(rm_interfaces::msg::JudgeSystemData),
  JudgeSystemData_message_member_array,  // message members
  JudgeSystemData_init_function,  // function to initialize message memory (memory has to be allocated)
  JudgeSystemData_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t JudgeSystemData_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &JudgeSystemData_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace rm_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rm_interfaces::msg::JudgeSystemData>()
{
  return &::rm_interfaces::msg::rosidl_typesupport_introspection_cpp::JudgeSystemData_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rm_interfaces, msg, JudgeSystemData)() {
  return &::rm_interfaces::msg::rosidl_typesupport_introspection_cpp::JudgeSystemData_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
