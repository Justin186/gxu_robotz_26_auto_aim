// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rm_interfaces:msg/DebugLight.idl
// generated code does not contain a copyright notice
#include "rm_interfaces/msg/detail/debug_light__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
rm_interfaces__msg__DebugLight__init(rm_interfaces__msg__DebugLight * msg)
{
  if (!msg) {
    return false;
  }
  // center_x
  // is_light
  // ratio
  // angle
  return true;
}

void
rm_interfaces__msg__DebugLight__fini(rm_interfaces__msg__DebugLight * msg)
{
  if (!msg) {
    return;
  }
  // center_x
  // is_light
  // ratio
  // angle
}

bool
rm_interfaces__msg__DebugLight__are_equal(const rm_interfaces__msg__DebugLight * lhs, const rm_interfaces__msg__DebugLight * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // center_x
  if (lhs->center_x != rhs->center_x) {
    return false;
  }
  // is_light
  if (lhs->is_light != rhs->is_light) {
    return false;
  }
  // ratio
  if (lhs->ratio != rhs->ratio) {
    return false;
  }
  // angle
  if (lhs->angle != rhs->angle) {
    return false;
  }
  return true;
}

bool
rm_interfaces__msg__DebugLight__copy(
  const rm_interfaces__msg__DebugLight * input,
  rm_interfaces__msg__DebugLight * output)
{
  if (!input || !output) {
    return false;
  }
  // center_x
  output->center_x = input->center_x;
  // is_light
  output->is_light = input->is_light;
  // ratio
  output->ratio = input->ratio;
  // angle
  output->angle = input->angle;
  return true;
}

rm_interfaces__msg__DebugLight *
rm_interfaces__msg__DebugLight__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__msg__DebugLight * msg = (rm_interfaces__msg__DebugLight *)allocator.allocate(sizeof(rm_interfaces__msg__DebugLight), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rm_interfaces__msg__DebugLight));
  bool success = rm_interfaces__msg__DebugLight__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rm_interfaces__msg__DebugLight__destroy(rm_interfaces__msg__DebugLight * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rm_interfaces__msg__DebugLight__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rm_interfaces__msg__DebugLight__Sequence__init(rm_interfaces__msg__DebugLight__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__msg__DebugLight * data = NULL;

  if (size) {
    data = (rm_interfaces__msg__DebugLight *)allocator.zero_allocate(size, sizeof(rm_interfaces__msg__DebugLight), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rm_interfaces__msg__DebugLight__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rm_interfaces__msg__DebugLight__fini(&data[i - 1]);
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
rm_interfaces__msg__DebugLight__Sequence__fini(rm_interfaces__msg__DebugLight__Sequence * array)
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
      rm_interfaces__msg__DebugLight__fini(&array->data[i]);
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

rm_interfaces__msg__DebugLight__Sequence *
rm_interfaces__msg__DebugLight__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__msg__DebugLight__Sequence * array = (rm_interfaces__msg__DebugLight__Sequence *)allocator.allocate(sizeof(rm_interfaces__msg__DebugLight__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rm_interfaces__msg__DebugLight__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rm_interfaces__msg__DebugLight__Sequence__destroy(rm_interfaces__msg__DebugLight__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rm_interfaces__msg__DebugLight__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rm_interfaces__msg__DebugLight__Sequence__are_equal(const rm_interfaces__msg__DebugLight__Sequence * lhs, const rm_interfaces__msg__DebugLight__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rm_interfaces__msg__DebugLight__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rm_interfaces__msg__DebugLight__Sequence__copy(
  const rm_interfaces__msg__DebugLight__Sequence * input,
  rm_interfaces__msg__DebugLight__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rm_interfaces__msg__DebugLight);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rm_interfaces__msg__DebugLight * data =
      (rm_interfaces__msg__DebugLight *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rm_interfaces__msg__DebugLight__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rm_interfaces__msg__DebugLight__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rm_interfaces__msg__DebugLight__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
