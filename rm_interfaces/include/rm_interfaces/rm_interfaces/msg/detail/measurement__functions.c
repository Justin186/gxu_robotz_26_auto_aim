// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rm_interfaces:msg/Measurement.idl
// generated code does not contain a copyright notice
#include "rm_interfaces/msg/detail/measurement__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
rm_interfaces__msg__Measurement__init(rm_interfaces__msg__Measurement * msg)
{
  if (!msg) {
    return false;
  }
  // x1
  // y1
  // z1
  // yaw1
  // x2
  // y2
  // z2
  // yaw2
  return true;
}

void
rm_interfaces__msg__Measurement__fini(rm_interfaces__msg__Measurement * msg)
{
  if (!msg) {
    return;
  }
  // x1
  // y1
  // z1
  // yaw1
  // x2
  // y2
  // z2
  // yaw2
}

bool
rm_interfaces__msg__Measurement__are_equal(const rm_interfaces__msg__Measurement * lhs, const rm_interfaces__msg__Measurement * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // x1
  if (lhs->x1 != rhs->x1) {
    return false;
  }
  // y1
  if (lhs->y1 != rhs->y1) {
    return false;
  }
  // z1
  if (lhs->z1 != rhs->z1) {
    return false;
  }
  // yaw1
  if (lhs->yaw1 != rhs->yaw1) {
    return false;
  }
  // x2
  if (lhs->x2 != rhs->x2) {
    return false;
  }
  // y2
  if (lhs->y2 != rhs->y2) {
    return false;
  }
  // z2
  if (lhs->z2 != rhs->z2) {
    return false;
  }
  // yaw2
  if (lhs->yaw2 != rhs->yaw2) {
    return false;
  }
  return true;
}

bool
rm_interfaces__msg__Measurement__copy(
  const rm_interfaces__msg__Measurement * input,
  rm_interfaces__msg__Measurement * output)
{
  if (!input || !output) {
    return false;
  }
  // x1
  output->x1 = input->x1;
  // y1
  output->y1 = input->y1;
  // z1
  output->z1 = input->z1;
  // yaw1
  output->yaw1 = input->yaw1;
  // x2
  output->x2 = input->x2;
  // y2
  output->y2 = input->y2;
  // z2
  output->z2 = input->z2;
  // yaw2
  output->yaw2 = input->yaw2;
  return true;
}

rm_interfaces__msg__Measurement *
rm_interfaces__msg__Measurement__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__msg__Measurement * msg = (rm_interfaces__msg__Measurement *)allocator.allocate(sizeof(rm_interfaces__msg__Measurement), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rm_interfaces__msg__Measurement));
  bool success = rm_interfaces__msg__Measurement__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rm_interfaces__msg__Measurement__destroy(rm_interfaces__msg__Measurement * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rm_interfaces__msg__Measurement__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rm_interfaces__msg__Measurement__Sequence__init(rm_interfaces__msg__Measurement__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__msg__Measurement * data = NULL;

  if (size) {
    data = (rm_interfaces__msg__Measurement *)allocator.zero_allocate(size, sizeof(rm_interfaces__msg__Measurement), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rm_interfaces__msg__Measurement__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rm_interfaces__msg__Measurement__fini(&data[i - 1]);
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
rm_interfaces__msg__Measurement__Sequence__fini(rm_interfaces__msg__Measurement__Sequence * array)
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
      rm_interfaces__msg__Measurement__fini(&array->data[i]);
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

rm_interfaces__msg__Measurement__Sequence *
rm_interfaces__msg__Measurement__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__msg__Measurement__Sequence * array = (rm_interfaces__msg__Measurement__Sequence *)allocator.allocate(sizeof(rm_interfaces__msg__Measurement__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rm_interfaces__msg__Measurement__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rm_interfaces__msg__Measurement__Sequence__destroy(rm_interfaces__msg__Measurement__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rm_interfaces__msg__Measurement__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rm_interfaces__msg__Measurement__Sequence__are_equal(const rm_interfaces__msg__Measurement__Sequence * lhs, const rm_interfaces__msg__Measurement__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rm_interfaces__msg__Measurement__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rm_interfaces__msg__Measurement__Sequence__copy(
  const rm_interfaces__msg__Measurement__Sequence * input,
  rm_interfaces__msg__Measurement__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rm_interfaces__msg__Measurement);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rm_interfaces__msg__Measurement * data =
      (rm_interfaces__msg__Measurement *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rm_interfaces__msg__Measurement__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rm_interfaces__msg__Measurement__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rm_interfaces__msg__Measurement__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
