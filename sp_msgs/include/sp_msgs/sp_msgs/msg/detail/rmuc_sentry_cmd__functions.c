// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sp_msgs:msg/RMUCSentryCmd.idl
// generated code does not contain a copyright notice
#include "sp_msgs/msg/detail/rmuc_sentry_cmd__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
sp_msgs__msg__RMUCSentryCmd__init(sp_msgs__msg__RMUCSentryCmd * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    sp_msgs__msg__RMUCSentryCmd__fini(msg);
    return false;
  }
  // cmd_posture
  // cmd_confirm_respawn
  return true;
}

void
sp_msgs__msg__RMUCSentryCmd__fini(sp_msgs__msg__RMUCSentryCmd * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // cmd_posture
  // cmd_confirm_respawn
}

bool
sp_msgs__msg__RMUCSentryCmd__are_equal(const sp_msgs__msg__RMUCSentryCmd * lhs, const sp_msgs__msg__RMUCSentryCmd * rhs)
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
  // cmd_posture
  if (lhs->cmd_posture != rhs->cmd_posture) {
    return false;
  }
  // cmd_confirm_respawn
  if (lhs->cmd_confirm_respawn != rhs->cmd_confirm_respawn) {
    return false;
  }
  return true;
}

bool
sp_msgs__msg__RMUCSentryCmd__copy(
  const sp_msgs__msg__RMUCSentryCmd * input,
  sp_msgs__msg__RMUCSentryCmd * output)
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
  // cmd_posture
  output->cmd_posture = input->cmd_posture;
  // cmd_confirm_respawn
  output->cmd_confirm_respawn = input->cmd_confirm_respawn;
  return true;
}

sp_msgs__msg__RMUCSentryCmd *
sp_msgs__msg__RMUCSentryCmd__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sp_msgs__msg__RMUCSentryCmd * msg = (sp_msgs__msg__RMUCSentryCmd *)allocator.allocate(sizeof(sp_msgs__msg__RMUCSentryCmd), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sp_msgs__msg__RMUCSentryCmd));
  bool success = sp_msgs__msg__RMUCSentryCmd__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sp_msgs__msg__RMUCSentryCmd__destroy(sp_msgs__msg__RMUCSentryCmd * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sp_msgs__msg__RMUCSentryCmd__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sp_msgs__msg__RMUCSentryCmd__Sequence__init(sp_msgs__msg__RMUCSentryCmd__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sp_msgs__msg__RMUCSentryCmd * data = NULL;

  if (size) {
    data = (sp_msgs__msg__RMUCSentryCmd *)allocator.zero_allocate(size, sizeof(sp_msgs__msg__RMUCSentryCmd), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sp_msgs__msg__RMUCSentryCmd__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sp_msgs__msg__RMUCSentryCmd__fini(&data[i - 1]);
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
sp_msgs__msg__RMUCSentryCmd__Sequence__fini(sp_msgs__msg__RMUCSentryCmd__Sequence * array)
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
      sp_msgs__msg__RMUCSentryCmd__fini(&array->data[i]);
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

sp_msgs__msg__RMUCSentryCmd__Sequence *
sp_msgs__msg__RMUCSentryCmd__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sp_msgs__msg__RMUCSentryCmd__Sequence * array = (sp_msgs__msg__RMUCSentryCmd__Sequence *)allocator.allocate(sizeof(sp_msgs__msg__RMUCSentryCmd__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sp_msgs__msg__RMUCSentryCmd__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sp_msgs__msg__RMUCSentryCmd__Sequence__destroy(sp_msgs__msg__RMUCSentryCmd__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sp_msgs__msg__RMUCSentryCmd__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sp_msgs__msg__RMUCSentryCmd__Sequence__are_equal(const sp_msgs__msg__RMUCSentryCmd__Sequence * lhs, const sp_msgs__msg__RMUCSentryCmd__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sp_msgs__msg__RMUCSentryCmd__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sp_msgs__msg__RMUCSentryCmd__Sequence__copy(
  const sp_msgs__msg__RMUCSentryCmd__Sequence * input,
  sp_msgs__msg__RMUCSentryCmd__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sp_msgs__msg__RMUCSentryCmd);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sp_msgs__msg__RMUCSentryCmd * data =
      (sp_msgs__msg__RMUCSentryCmd *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sp_msgs__msg__RMUCSentryCmd__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sp_msgs__msg__RMUCSentryCmd__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sp_msgs__msg__RMUCSentryCmd__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
