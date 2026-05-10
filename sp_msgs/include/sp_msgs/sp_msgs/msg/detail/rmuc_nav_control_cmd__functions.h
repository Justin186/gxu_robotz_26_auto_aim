// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from sp_msgs:msg/RMUCNavControlCmd.idl
// generated code does not contain a copyright notice

#ifndef SP_MSGS__MSG__DETAIL__RMUC_NAV_CONTROL_CMD__FUNCTIONS_H_
#define SP_MSGS__MSG__DETAIL__RMUC_NAV_CONTROL_CMD__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "sp_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "sp_msgs/msg/detail/rmuc_nav_control_cmd__struct.h"

/// Initialize msg/RMUCNavControlCmd message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * sp_msgs__msg__RMUCNavControlCmd
 * )) before or use
 * sp_msgs__msg__RMUCNavControlCmd__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_sp_msgs
bool
sp_msgs__msg__RMUCNavControlCmd__init(sp_msgs__msg__RMUCNavControlCmd * msg);

/// Finalize msg/RMUCNavControlCmd message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sp_msgs
void
sp_msgs__msg__RMUCNavControlCmd__fini(sp_msgs__msg__RMUCNavControlCmd * msg);

/// Create msg/RMUCNavControlCmd message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * sp_msgs__msg__RMUCNavControlCmd__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_sp_msgs
sp_msgs__msg__RMUCNavControlCmd *
sp_msgs__msg__RMUCNavControlCmd__create();

/// Destroy msg/RMUCNavControlCmd message.
/**
 * It calls
 * sp_msgs__msg__RMUCNavControlCmd__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sp_msgs
void
sp_msgs__msg__RMUCNavControlCmd__destroy(sp_msgs__msg__RMUCNavControlCmd * msg);

/// Check for msg/RMUCNavControlCmd message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_sp_msgs
bool
sp_msgs__msg__RMUCNavControlCmd__are_equal(const sp_msgs__msg__RMUCNavControlCmd * lhs, const sp_msgs__msg__RMUCNavControlCmd * rhs);

/// Copy a msg/RMUCNavControlCmd message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_sp_msgs
bool
sp_msgs__msg__RMUCNavControlCmd__copy(
  const sp_msgs__msg__RMUCNavControlCmd * input,
  sp_msgs__msg__RMUCNavControlCmd * output);

/// Initialize array of msg/RMUCNavControlCmd messages.
/**
 * It allocates the memory for the number of elements and calls
 * sp_msgs__msg__RMUCNavControlCmd__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_sp_msgs
bool
sp_msgs__msg__RMUCNavControlCmd__Sequence__init(sp_msgs__msg__RMUCNavControlCmd__Sequence * array, size_t size);

/// Finalize array of msg/RMUCNavControlCmd messages.
/**
 * It calls
 * sp_msgs__msg__RMUCNavControlCmd__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sp_msgs
void
sp_msgs__msg__RMUCNavControlCmd__Sequence__fini(sp_msgs__msg__RMUCNavControlCmd__Sequence * array);

/// Create array of msg/RMUCNavControlCmd messages.
/**
 * It allocates the memory for the array and calls
 * sp_msgs__msg__RMUCNavControlCmd__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_sp_msgs
sp_msgs__msg__RMUCNavControlCmd__Sequence *
sp_msgs__msg__RMUCNavControlCmd__Sequence__create(size_t size);

/// Destroy array of msg/RMUCNavControlCmd messages.
/**
 * It calls
 * sp_msgs__msg__RMUCNavControlCmd__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sp_msgs
void
sp_msgs__msg__RMUCNavControlCmd__Sequence__destroy(sp_msgs__msg__RMUCNavControlCmd__Sequence * array);

/// Check for msg/RMUCNavControlCmd message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_sp_msgs
bool
sp_msgs__msg__RMUCNavControlCmd__Sequence__are_equal(const sp_msgs__msg__RMUCNavControlCmd__Sequence * lhs, const sp_msgs__msg__RMUCNavControlCmd__Sequence * rhs);

/// Copy an array of msg/RMUCNavControlCmd messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_sp_msgs
bool
sp_msgs__msg__RMUCNavControlCmd__Sequence__copy(
  const sp_msgs__msg__RMUCNavControlCmd__Sequence * input,
  sp_msgs__msg__RMUCNavControlCmd__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // SP_MSGS__MSG__DETAIL__RMUC_NAV_CONTROL_CMD__FUNCTIONS_H_
