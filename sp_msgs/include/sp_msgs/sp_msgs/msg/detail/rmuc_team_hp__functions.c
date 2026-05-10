// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sp_msgs:msg/RMUCTeamHP.idl
// generated code does not contain a copyright notice
#include "sp_msgs/msg/detail/rmuc_team_hp__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
sp_msgs__msg__RMUCTeamHP__init(sp_msgs__msg__RMUCTeamHP * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    sp_msgs__msg__RMUCTeamHP__fini(msg);
    return false;
  }
  // outpost_hp
  // base_hp
  return true;
}

void
sp_msgs__msg__RMUCTeamHP__fini(sp_msgs__msg__RMUCTeamHP * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // outpost_hp
  // base_hp
}

bool
sp_msgs__msg__RMUCTeamHP__are_equal(const sp_msgs__msg__RMUCTeamHP * lhs, const sp_msgs__msg__RMUCTeamHP * rhs)
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
  // outpost_hp
  if (lhs->outpost_hp != rhs->outpost_hp) {
    return false;
  }
  // base_hp
  if (lhs->base_hp != rhs->base_hp) {
    return false;
  }
  return true;
}

bool
sp_msgs__msg__RMUCTeamHP__copy(
  const sp_msgs__msg__RMUCTeamHP * input,
  sp_msgs__msg__RMUCTeamHP * output)
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
  // outpost_hp
  output->outpost_hp = input->outpost_hp;
  // base_hp
  output->base_hp = input->base_hp;
  return true;
}

sp_msgs__msg__RMUCTeamHP *
sp_msgs__msg__RMUCTeamHP__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sp_msgs__msg__RMUCTeamHP * msg = (sp_msgs__msg__RMUCTeamHP *)allocator.allocate(sizeof(sp_msgs__msg__RMUCTeamHP), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sp_msgs__msg__RMUCTeamHP));
  bool success = sp_msgs__msg__RMUCTeamHP__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sp_msgs__msg__RMUCTeamHP__destroy(sp_msgs__msg__RMUCTeamHP * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sp_msgs__msg__RMUCTeamHP__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sp_msgs__msg__RMUCTeamHP__Sequence__init(sp_msgs__msg__RMUCTeamHP__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sp_msgs__msg__RMUCTeamHP * data = NULL;

  if (size) {
    data = (sp_msgs__msg__RMUCTeamHP *)allocator.zero_allocate(size, sizeof(sp_msgs__msg__RMUCTeamHP), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sp_msgs__msg__RMUCTeamHP__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sp_msgs__msg__RMUCTeamHP__fini(&data[i - 1]);
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
sp_msgs__msg__RMUCTeamHP__Sequence__fini(sp_msgs__msg__RMUCTeamHP__Sequence * array)
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
      sp_msgs__msg__RMUCTeamHP__fini(&array->data[i]);
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

sp_msgs__msg__RMUCTeamHP__Sequence *
sp_msgs__msg__RMUCTeamHP__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sp_msgs__msg__RMUCTeamHP__Sequence * array = (sp_msgs__msg__RMUCTeamHP__Sequence *)allocator.allocate(sizeof(sp_msgs__msg__RMUCTeamHP__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sp_msgs__msg__RMUCTeamHP__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sp_msgs__msg__RMUCTeamHP__Sequence__destroy(sp_msgs__msg__RMUCTeamHP__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sp_msgs__msg__RMUCTeamHP__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sp_msgs__msg__RMUCTeamHP__Sequence__are_equal(const sp_msgs__msg__RMUCTeamHP__Sequence * lhs, const sp_msgs__msg__RMUCTeamHP__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sp_msgs__msg__RMUCTeamHP__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sp_msgs__msg__RMUCTeamHP__Sequence__copy(
  const sp_msgs__msg__RMUCTeamHP__Sequence * input,
  sp_msgs__msg__RMUCTeamHP__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sp_msgs__msg__RMUCTeamHP);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sp_msgs__msg__RMUCTeamHP * data =
      (sp_msgs__msg__RMUCTeamHP *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sp_msgs__msg__RMUCTeamHP__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sp_msgs__msg__RMUCTeamHP__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sp_msgs__msg__RMUCTeamHP__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
