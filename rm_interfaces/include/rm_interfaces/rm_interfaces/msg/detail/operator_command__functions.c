// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rm_interfaces:msg/OperatorCommand.idl
// generated code does not contain a copyright notice
#include "rm_interfaces/msg/detail/operator_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
rm_interfaces__msg__OperatorCommand__init(rm_interfaces__msg__OperatorCommand * msg)
{
  if (!msg) {
    return false;
  }
  // is_retreating
  // is_drone_avoiding
  // is_outpost_attacking
  return true;
}

void
rm_interfaces__msg__OperatorCommand__fini(rm_interfaces__msg__OperatorCommand * msg)
{
  if (!msg) {
    return;
  }
  // is_retreating
  // is_drone_avoiding
  // is_outpost_attacking
}

bool
rm_interfaces__msg__OperatorCommand__are_equal(const rm_interfaces__msg__OperatorCommand * lhs, const rm_interfaces__msg__OperatorCommand * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // is_retreating
  if (lhs->is_retreating != rhs->is_retreating) {
    return false;
  }
  // is_drone_avoiding
  if (lhs->is_drone_avoiding != rhs->is_drone_avoiding) {
    return false;
  }
  // is_outpost_attacking
  if (lhs->is_outpost_attacking != rhs->is_outpost_attacking) {
    return false;
  }
  return true;
}

bool
rm_interfaces__msg__OperatorCommand__copy(
  const rm_interfaces__msg__OperatorCommand * input,
  rm_interfaces__msg__OperatorCommand * output)
{
  if (!input || !output) {
    return false;
  }
  // is_retreating
  output->is_retreating = input->is_retreating;
  // is_drone_avoiding
  output->is_drone_avoiding = input->is_drone_avoiding;
  // is_outpost_attacking
  output->is_outpost_attacking = input->is_outpost_attacking;
  return true;
}

rm_interfaces__msg__OperatorCommand *
rm_interfaces__msg__OperatorCommand__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__msg__OperatorCommand * msg = (rm_interfaces__msg__OperatorCommand *)allocator.allocate(sizeof(rm_interfaces__msg__OperatorCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rm_interfaces__msg__OperatorCommand));
  bool success = rm_interfaces__msg__OperatorCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rm_interfaces__msg__OperatorCommand__destroy(rm_interfaces__msg__OperatorCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rm_interfaces__msg__OperatorCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rm_interfaces__msg__OperatorCommand__Sequence__init(rm_interfaces__msg__OperatorCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__msg__OperatorCommand * data = NULL;

  if (size) {
    data = (rm_interfaces__msg__OperatorCommand *)allocator.zero_allocate(size, sizeof(rm_interfaces__msg__OperatorCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rm_interfaces__msg__OperatorCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rm_interfaces__msg__OperatorCommand__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rm_interfaces__msg__OperatorCommand__Sequence__fini(rm_interfaces__msg__OperatorCommand__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rm_interfaces__msg__OperatorCommand__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rm_interfaces__msg__OperatorCommand__Sequence *
rm_interfaces__msg__OperatorCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__msg__OperatorCommand__Sequence * array = (rm_interfaces__msg__OperatorCommand__Sequence *)allocator.allocate(sizeof(rm_interfaces__msg__OperatorCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rm_interfaces__msg__OperatorCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rm_interfaces__msg__OperatorCommand__Sequence__destroy(rm_interfaces__msg__OperatorCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rm_interfaces__msg__OperatorCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rm_interfaces__msg__OperatorCommand__Sequence__are_equal(const rm_interfaces__msg__OperatorCommand__Sequence * lhs, const rm_interfaces__msg__OperatorCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rm_interfaces__msg__OperatorCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rm_interfaces__msg__OperatorCommand__Sequence__copy(
  const rm_interfaces__msg__OperatorCommand__Sequence * input,
  rm_interfaces__msg__OperatorCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rm_interfaces__msg__OperatorCommand);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rm_interfaces__msg__OperatorCommand * data =
      (rm_interfaces__msg__OperatorCommand *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rm_interfaces__msg__OperatorCommand__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rm_interfaces__msg__OperatorCommand__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rm_interfaces__msg__OperatorCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
