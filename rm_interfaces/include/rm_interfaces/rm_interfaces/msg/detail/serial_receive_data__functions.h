// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from rm_interfaces:msg/SerialReceiveData.idl
// generated code does not contain a copyright notice

#ifndef RM_INTERFACES__MSG__DETAIL__SERIAL_RECEIVE_DATA__FUNCTIONS_H_
#define RM_INTERFACES__MSG__DETAIL__SERIAL_RECEIVE_DATA__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "rm_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "rm_interfaces/msg/detail/serial_receive_data__struct.h"

/// Initialize msg/SerialReceiveData message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * rm_interfaces__msg__SerialReceiveData
 * )) before or use
 * rm_interfaces__msg__SerialReceiveData__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_rm_interfaces
bool
rm_interfaces__msg__SerialReceiveData__init(rm_interfaces__msg__SerialReceiveData * msg);

/// Finalize msg/SerialReceiveData message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rm_interfaces
void
rm_interfaces__msg__SerialReceiveData__fini(rm_interfaces__msg__SerialReceiveData * msg);

/// Create msg/SerialReceiveData message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * rm_interfaces__msg__SerialReceiveData__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rm_interfaces
rm_interfaces__msg__SerialReceiveData *
rm_interfaces__msg__SerialReceiveData__create();

/// Destroy msg/SerialReceiveData message.
/**
 * It calls
 * rm_interfaces__msg__SerialReceiveData__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rm_interfaces
void
rm_interfaces__msg__SerialReceiveData__destroy(rm_interfaces__msg__SerialReceiveData * msg);

/// Check for msg/SerialReceiveData message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_rm_interfaces
bool
rm_interfaces__msg__SerialReceiveData__are_equal(const rm_interfaces__msg__SerialReceiveData * lhs, const rm_interfaces__msg__SerialReceiveData * rhs);

/// Copy a msg/SerialReceiveData message.
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
ROSIDL_GENERATOR_C_PUBLIC_rm_interfaces
bool
rm_interfaces__msg__SerialReceiveData__copy(
  const rm_interfaces__msg__SerialReceiveData * input,
  rm_interfaces__msg__SerialReceiveData * output);

/// Initialize array of msg/SerialReceiveData messages.
/**
 * It allocates the memory for the number of elements and calls
 * rm_interfaces__msg__SerialReceiveData__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_rm_interfaces
bool
rm_interfaces__msg__SerialReceiveData__Sequence__init(rm_interfaces__msg__SerialReceiveData__Sequence * array, size_t size);

/// Finalize array of msg/SerialReceiveData messages.
/**
 * It calls
 * rm_interfaces__msg__SerialReceiveData__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rm_interfaces
void
rm_interfaces__msg__SerialReceiveData__Sequence__fini(rm_interfaces__msg__SerialReceiveData__Sequence * array);

/// Create array of msg/SerialReceiveData messages.
/**
 * It allocates the memory for the array and calls
 * rm_interfaces__msg__SerialReceiveData__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_rm_interfaces
rm_interfaces__msg__SerialReceiveData__Sequence *
rm_interfaces__msg__SerialReceiveData__Sequence__create(size_t size);

/// Destroy array of msg/SerialReceiveData messages.
/**
 * It calls
 * rm_interfaces__msg__SerialReceiveData__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_rm_interfaces
void
rm_interfaces__msg__SerialReceiveData__Sequence__destroy(rm_interfaces__msg__SerialReceiveData__Sequence * array);

/// Check for msg/SerialReceiveData message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_rm_interfaces
bool
rm_interfaces__msg__SerialReceiveData__Sequence__are_equal(const rm_interfaces__msg__SerialReceiveData__Sequence * lhs, const rm_interfaces__msg__SerialReceiveData__Sequence * rhs);

/// Copy an array of msg/SerialReceiveData messages.
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
ROSIDL_GENERATOR_C_PUBLIC_rm_interfaces
bool
rm_interfaces__msg__SerialReceiveData__Sequence__copy(
  const rm_interfaces__msg__SerialReceiveData__Sequence * input,
  rm_interfaces__msg__SerialReceiveData__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // RM_INTERFACES__MSG__DETAIL__SERIAL_RECEIVE_DATA__FUNCTIONS_H_
