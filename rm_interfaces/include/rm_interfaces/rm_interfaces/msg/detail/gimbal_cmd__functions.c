// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rm_interfaces:msg/GimbalCmd.idl
// generated code does not contain a copyright notice
#include "rm_interfaces/msg/detail/gimbal_cmd__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
rm_interfaces__msg__GimbalCmd__init(rm_interfaces__msg__GimbalCmd * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    rm_interfaces__msg__GimbalCmd__fini(msg);
    return false;
  }
  // pitch
  // yaw
  // yaw_diff
  // pitch_diff
  // distance
  // fire_advice
  return true;
}

void
rm_interfaces__msg__GimbalCmd__fini(rm_interfaces__msg__GimbalCmd * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // pitch
  // yaw
  // yaw_diff
  // pitch_diff
  // distance
  // fire_advice
}

bool
rm_interfaces__msg__GimbalCmd__are_equal(const rm_interfaces__msg__GimbalCmd * lhs, const rm_interfaces__msg__GimbalCmd * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // pitch
  if (lhs->pitch != rhs->pitch) {
    return false;
  }
  // yaw
  if (lhs->yaw != rhs->yaw) {
    return false;
  }
  // yaw_diff
  if (lhs->yaw_diff != rhs->yaw_diff) {
    return false;
  }
  // pitch_diff
  if (lhs->pitch_diff != rhs->pitch_diff) {
    return false;
  }
  // distance
  if (lhs->distance != rhs->distance) {
    return false;
  }
  // fire_advice
  if (lhs->fire_advice != rhs->fire_advice) {
    return false;
  }
  return true;
}

bool
rm_interfaces__msg__GimbalCmd__copy(
  const rm_interfaces__msg__GimbalCmd * input,
  rm_interfaces__msg__GimbalCmd * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // pitch
  output->pitch = input->pitch;
  // yaw
  output->yaw = input->yaw;
  // yaw_diff
  output->yaw_diff = input->yaw_diff;
  // pitch_diff
  output->pitch_diff = input->pitch_diff;
  // distance
  output->distance = input->distance;
  // fire_advice
  output->fire_advice = input->fire_advice;
  return true;
}

rm_interfaces__msg__GimbalCmd *
rm_interfaces__msg__GimbalCmd__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__msg__GimbalCmd * msg = (rm_interfaces__msg__GimbalCmd *)allocator.allocate(sizeof(rm_interfaces__msg__GimbalCmd), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rm_interfaces__msg__GimbalCmd));
  bool success = rm_interfaces__msg__GimbalCmd__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rm_interfaces__msg__GimbalCmd__destroy(rm_interfaces__msg__GimbalCmd * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rm_interfaces__msg__GimbalCmd__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rm_interfaces__msg__GimbalCmd__Sequence__init(rm_interfaces__msg__GimbalCmd__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__msg__GimbalCmd * data = NULL;

  if (size) {
    data = (rm_interfaces__msg__GimbalCmd *)allocator.zero_allocate(size, sizeof(rm_interfaces__msg__GimbalCmd), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rm_interfaces__msg__GimbalCmd__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rm_interfaces__msg__GimbalCmd__fini(&data[i - 1]);
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
rm_interfaces__msg__GimbalCmd__Sequence__fini(rm_interfaces__msg__GimbalCmd__Sequence * array)
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
      rm_interfaces__msg__GimbalCmd__fini(&array->data[i]);
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

rm_interfaces__msg__GimbalCmd__Sequence *
rm_interfaces__msg__GimbalCmd__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__msg__GimbalCmd__Sequence * array = (rm_interfaces__msg__GimbalCmd__Sequence *)allocator.allocate(sizeof(rm_interfaces__msg__GimbalCmd__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rm_interfaces__msg__GimbalCmd__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rm_interfaces__msg__GimbalCmd__Sequence__destroy(rm_interfaces__msg__GimbalCmd__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rm_interfaces__msg__GimbalCmd__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rm_interfaces__msg__GimbalCmd__Sequence__are_equal(const rm_interfaces__msg__GimbalCmd__Sequence * lhs, const rm_interfaces__msg__GimbalCmd__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rm_interfaces__msg__GimbalCmd__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rm_interfaces__msg__GimbalCmd__Sequence__copy(
  const rm_interfaces__msg__GimbalCmd__Sequence * input,
  rm_interfaces__msg__GimbalCmd__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rm_interfaces__msg__GimbalCmd);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rm_interfaces__msg__GimbalCmd * data =
      (rm_interfaces__msg__GimbalCmd *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rm_interfaces__msg__GimbalCmd__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rm_interfaces__msg__GimbalCmd__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rm_interfaces__msg__GimbalCmd__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
