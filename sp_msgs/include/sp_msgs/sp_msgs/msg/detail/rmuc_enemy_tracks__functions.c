// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sp_msgs:msg/RMUCEnemyTracks.idl
// generated code does not contain a copyright notice
#include "sp_msgs/msg/detail/rmuc_enemy_tracks__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `enemy_x`
// Member `enemy_y`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
sp_msgs__msg__RMUCEnemyTracks__init(sp_msgs__msg__RMUCEnemyTracks * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    sp_msgs__msg__RMUCEnemyTracks__fini(msg);
    return false;
  }
  // enemy_x
  if (!rosidl_runtime_c__float__Sequence__init(&msg->enemy_x, 0)) {
    sp_msgs__msg__RMUCEnemyTracks__fini(msg);
    return false;
  }
  // enemy_y
  if (!rosidl_runtime_c__float__Sequence__init(&msg->enemy_y, 0)) {
    sp_msgs__msg__RMUCEnemyTracks__fini(msg);
    return false;
  }
  return true;
}

void
sp_msgs__msg__RMUCEnemyTracks__fini(sp_msgs__msg__RMUCEnemyTracks * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // enemy_x
  rosidl_runtime_c__float__Sequence__fini(&msg->enemy_x);
  // enemy_y
  rosidl_runtime_c__float__Sequence__fini(&msg->enemy_y);
}

bool
sp_msgs__msg__RMUCEnemyTracks__are_equal(const sp_msgs__msg__RMUCEnemyTracks * lhs, const sp_msgs__msg__RMUCEnemyTracks * rhs)
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
  // enemy_x
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->enemy_x), &(rhs->enemy_x)))
  {
    return false;
  }
  // enemy_y
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->enemy_y), &(rhs->enemy_y)))
  {
    return false;
  }
  return true;
}

bool
sp_msgs__msg__RMUCEnemyTracks__copy(
  const sp_msgs__msg__RMUCEnemyTracks * input,
  sp_msgs__msg__RMUCEnemyTracks * output)
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
  // enemy_x
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->enemy_x), &(output->enemy_x)))
  {
    return false;
  }
  // enemy_y
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->enemy_y), &(output->enemy_y)))
  {
    return false;
  }
  return true;
}

sp_msgs__msg__RMUCEnemyTracks *
sp_msgs__msg__RMUCEnemyTracks__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sp_msgs__msg__RMUCEnemyTracks * msg = (sp_msgs__msg__RMUCEnemyTracks *)allocator.allocate(sizeof(sp_msgs__msg__RMUCEnemyTracks), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sp_msgs__msg__RMUCEnemyTracks));
  bool success = sp_msgs__msg__RMUCEnemyTracks__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sp_msgs__msg__RMUCEnemyTracks__destroy(sp_msgs__msg__RMUCEnemyTracks * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sp_msgs__msg__RMUCEnemyTracks__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sp_msgs__msg__RMUCEnemyTracks__Sequence__init(sp_msgs__msg__RMUCEnemyTracks__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sp_msgs__msg__RMUCEnemyTracks * data = NULL;

  if (size) {
    data = (sp_msgs__msg__RMUCEnemyTracks *)allocator.zero_allocate(size, sizeof(sp_msgs__msg__RMUCEnemyTracks), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sp_msgs__msg__RMUCEnemyTracks__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sp_msgs__msg__RMUCEnemyTracks__fini(&data[i - 1]);
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
sp_msgs__msg__RMUCEnemyTracks__Sequence__fini(sp_msgs__msg__RMUCEnemyTracks__Sequence * array)
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
      sp_msgs__msg__RMUCEnemyTracks__fini(&array->data[i]);
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

sp_msgs__msg__RMUCEnemyTracks__Sequence *
sp_msgs__msg__RMUCEnemyTracks__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sp_msgs__msg__RMUCEnemyTracks__Sequence * array = (sp_msgs__msg__RMUCEnemyTracks__Sequence *)allocator.allocate(sizeof(sp_msgs__msg__RMUCEnemyTracks__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sp_msgs__msg__RMUCEnemyTracks__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sp_msgs__msg__RMUCEnemyTracks__Sequence__destroy(sp_msgs__msg__RMUCEnemyTracks__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sp_msgs__msg__RMUCEnemyTracks__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sp_msgs__msg__RMUCEnemyTracks__Sequence__are_equal(const sp_msgs__msg__RMUCEnemyTracks__Sequence * lhs, const sp_msgs__msg__RMUCEnemyTracks__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sp_msgs__msg__RMUCEnemyTracks__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sp_msgs__msg__RMUCEnemyTracks__Sequence__copy(
  const sp_msgs__msg__RMUCEnemyTracks__Sequence * input,
  sp_msgs__msg__RMUCEnemyTracks__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sp_msgs__msg__RMUCEnemyTracks);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sp_msgs__msg__RMUCEnemyTracks * data =
      (sp_msgs__msg__RMUCEnemyTracks *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sp_msgs__msg__RMUCEnemyTracks__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sp_msgs__msg__RMUCEnemyTracks__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sp_msgs__msg__RMUCEnemyTracks__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
