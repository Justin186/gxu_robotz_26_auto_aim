// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from rm_interfaces:msg/RuneTarget.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "rm_interfaces/msg/detail/rune_target__struct.hpp"
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

void RuneTarget_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) rm_interfaces::msg::RuneTarget(_init);
}

void RuneTarget_fini_function(void * message_memory)
{
  auto typed_message = static_cast<rm_interfaces::msg::RuneTarget *>(message_memory);
  typed_message->~RuneTarget();
}

size_t size_function__RuneTarget__pts(const void * untyped_member)
{
  (void)untyped_member;
  return 5;
}

const void * get_const_function__RuneTarget__pts(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<rm_interfaces::msg::Point2d, 5> *>(untyped_member);
  return &member[index];
}

void * get_function__RuneTarget__pts(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<rm_interfaces::msg::Point2d, 5> *>(untyped_member);
  return &member[index];
}

void fetch_function__RuneTarget__pts(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const rm_interfaces::msg::Point2d *>(
    get_const_function__RuneTarget__pts(untyped_member, index));
  auto & value = *reinterpret_cast<rm_interfaces::msg::Point2d *>(untyped_value);
  value = item;
}

void assign_function__RuneTarget__pts(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<rm_interfaces::msg::Point2d *>(
    get_function__RuneTarget__pts(untyped_member, index));
  const auto & value = *reinterpret_cast<const rm_interfaces::msg::Point2d *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember RuneTarget_message_member_array[4] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces::msg::RuneTarget, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "pts",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<rm_interfaces::msg::Point2d>(),  // members of sub message
    true,  // is array
    5,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces::msg::RuneTarget, pts),  // bytes offset in struct
    nullptr,  // default value
    size_function__RuneTarget__pts,  // size() function pointer
    get_const_function__RuneTarget__pts,  // get_const(index) function pointer
    get_function__RuneTarget__pts,  // get(index) function pointer
    fetch_function__RuneTarget__pts,  // fetch(index, &value) function pointer
    assign_function__RuneTarget__pts,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "is_lost",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces::msg::RuneTarget, is_lost),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "is_big_rune",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rm_interfaces::msg::RuneTarget, is_big_rune),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers RuneTarget_message_members = {
  "rm_interfaces::msg",  // message namespace
  "RuneTarget",  // message name
  4,  // number of fields
  sizeof(rm_interfaces::msg::RuneTarget),
  RuneTarget_message_member_array,  // message members
  RuneTarget_init_function,  // function to initialize message memory (memory has to be allocated)
  RuneTarget_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t RuneTarget_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &RuneTarget_message_members,
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
get_message_type_support_handle<rm_interfaces::msg::RuneTarget>()
{
  return &::rm_interfaces::msg::rosidl_typesupport_introspection_cpp::RuneTarget_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rm_interfaces, msg, RuneTarget)() {
  return &::rm_interfaces::msg::rosidl_typesupport_introspection_cpp::RuneTarget_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
