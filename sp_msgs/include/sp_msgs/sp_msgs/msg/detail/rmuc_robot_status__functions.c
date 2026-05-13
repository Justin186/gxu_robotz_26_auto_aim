// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sp_msgs:msg/RMUCRobotStatus.idl
// generated code does not contain a copyright notice
#include "sp_msgs/msg/detail/rmuc_robot_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
sp_msgs__msg__RMUCRobotStatus__init(sp_msgs__msg__RMUCRobotStatus * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    sp_msgs__msg__RMUCRobotStatus__fini(msg);
    return false;
  }
  // current_hp
  // shooter_heat
  // ammo_allow
  // outpost_hp
  // base_hp
  // enemy_outpost_status
  // is_detect_enemy
  return true;
}

void
sp_msgs__msg__RMUCRobotStatus__fini(sp_msgs__msg__RMUCRobotStatus * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // current_hp
  // shooter_heat
  // ammo_allow
  // outpost_hp
  // base_hp
  // enemy_outpost_status
  // is_detect_enemy
}

bool
sp_msgs__msg__RMUCRobotStatus__are_equal(const sp_msgs__msg__RMUCRobotStatus * lhs, const sp_msgs__msg__RMUCRobotStatus * rhs)
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
  // current_hp
  if (lhs->current_hp != rhs->current_hp) {
    return false;
  }
  // shooter_heat
  if (lhs->shooter_heat != rhs->shooter_heat) {
    return false;
  }
  // ammo_allow
  if (lhs->ammo_allow != rhs->ammo_allow) {
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
  // enemy_outpost_status
  if (lhs->enemy_outpost_status != rhs->enemy_outpost_status) {
    return false;
  }
  // is_detect_enemy
  if (lhs->is_detect_enemy != rhs->is_detect_enemy) {
    return false;
  }
  return true;
}

bool
sp_msgs__msg__RMUCRobotStatus__copy(
  const sp_msgs__msg__RMUCRobotStatus * input,
  sp_msgs__msg__RMUCRobotStatus * output)
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
  // current_hp
  output->current_hp = input->current_hp;
  // shooter_heat
  output->shooter_heat = input->shooter_heat;
  // ammo_allow
  output->ammo_allow = input->ammo_allow;
  // outpost_hp
  output->outpost_hp = input->outpost_hp;
  // base_hp
  output->base_hp = input->base_hp;
  // enemy_outpost_status
  output->enemy_outpost_status = input->enemy_outpost_status;
  // is_detect_enemy
  output->is_detect_enemy = input->is_detect_enemy;
  return true;
}

sp_msgs__msg__RMUCRobotStatus *
sp_msgs__msg__RMUCRobotStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sp_msgs__msg__RMUCRobotStatus * msg = (sp_msgs__msg__RMUCRobotStatus *)allocator.allocate(sizeof(sp_msgs__msg__RMUCRobotStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sp_msgs__msg__RMUCRobotStatus));
  bool success = sp_msgs__msg__RMUCRobotStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sp_msgs__msg__RMUCRobotStatus__destroy(sp_msgs__msg__RMUCRobotStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sp_msgs__msg__RMUCRobotStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sp_msgs__msg__RMUCRobotStatus__Sequence__init(sp_msgs__msg__RMUCRobotStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sp_msgs__msg__RMUCRobotStatus * data = NULL;

  if (size) {
    data = (sp_msgs__msg__RMUCRobotStatus *)allocator.zero_allocate(size, sizeof(sp_msgs__msg__RMUCRobotStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sp_msgs__msg__RMUCRobotStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sp_msgs__msg__RMUCRobotStatus__fini(&data[i - 1]);
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
sp_msgs__msg__RMUCRobotStatus__Sequence__fini(sp_msgs__msg__RMUCRobotStatus__Sequence * array)
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
      sp_msgs__msg__RMUCRobotStatus__fini(&array->data[i]);
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

sp_msgs__msg__RMUCRobotStatus__Sequence *
sp_msgs__msg__RMUCRobotStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sp_msgs__msg__RMUCRobotStatus__Sequence * array = (sp_msgs__msg__RMUCRobotStatus__Sequence *)allocator.allocate(sizeof(sp_msgs__msg__RMUCRobotStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sp_msgs__msg__RMUCRobotStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sp_msgs__msg__RMUCRobotStatus__Sequence__destroy(sp_msgs__msg__RMUCRobotStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sp_msgs__msg__RMUCRobotStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sp_msgs__msg__RMUCRobotStatus__Sequence__are_equal(const sp_msgs__msg__RMUCRobotStatus__Sequence * lhs, const sp_msgs__msg__RMUCRobotStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sp_msgs__msg__RMUCRobotStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sp_msgs__msg__RMUCRobotStatus__Sequence__copy(
  const sp_msgs__msg__RMUCRobotStatus__Sequence * input,
  sp_msgs__msg__RMUCRobotStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sp_msgs__msg__RMUCRobotStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sp_msgs__msg__RMUCRobotStatus * data =
      (sp_msgs__msg__RMUCRobotStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sp_msgs__msg__RMUCRobotStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sp_msgs__msg__RMUCRobotStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sp_msgs__msg__RMUCRobotStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
