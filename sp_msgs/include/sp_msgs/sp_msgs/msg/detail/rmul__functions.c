// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sp_msgs:msg/RMUL.idl
// generated code does not contain a copyright notice
#include "sp_msgs/msg/detail/rmul__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
sp_msgs__msg__RMUL__init(sp_msgs__msg__RMUL * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    sp_msgs__msg__RMUL__fini(msg);
    return false;
  }
  // game_progress
  // stage_remain_time
  // cmd_type
  // emergency_stop
  // rfid_supply_arrived
  // rfid_control_arrived
  // stop_gimbal_scan
  // chassis_spin
  // x
  // y
  // current_hp
  // is_attacked
  // is_detect_enemy
  return true;
}

void
sp_msgs__msg__RMUL__fini(sp_msgs__msg__RMUL * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // game_progress
  // stage_remain_time
  // cmd_type
  // emergency_stop
  // rfid_supply_arrived
  // rfid_control_arrived
  // stop_gimbal_scan
  // chassis_spin
  // x
  // y
  // current_hp
  // is_attacked
  // is_detect_enemy
}

bool
sp_msgs__msg__RMUL__are_equal(const sp_msgs__msg__RMUL * lhs, const sp_msgs__msg__RMUL * rhs)
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
  // game_progress
  if (lhs->game_progress != rhs->game_progress) {
    return false;
  }
  // stage_remain_time
  if (lhs->stage_remain_time != rhs->stage_remain_time) {
    return false;
  }
  // cmd_type
  if (lhs->cmd_type != rhs->cmd_type) {
    return false;
  }
  // emergency_stop
  if (lhs->emergency_stop != rhs->emergency_stop) {
    return false;
  }
  // rfid_supply_arrived
  if (lhs->rfid_supply_arrived != rhs->rfid_supply_arrived) {
    return false;
  }
  // rfid_control_arrived
  if (lhs->rfid_control_arrived != rhs->rfid_control_arrived) {
    return false;
  }
  // stop_gimbal_scan
  if (lhs->stop_gimbal_scan != rhs->stop_gimbal_scan) {
    return false;
  }
  // chassis_spin
  if (lhs->chassis_spin != rhs->chassis_spin) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // current_hp
  if (lhs->current_hp != rhs->current_hp) {
    return false;
  }
  // is_attacked
  if (lhs->is_attacked != rhs->is_attacked) {
    return false;
  }
  // is_detect_enemy
  if (lhs->is_detect_enemy != rhs->is_detect_enemy) {
    return false;
  }
  return true;
}

bool
sp_msgs__msg__RMUL__copy(
  const sp_msgs__msg__RMUL * input,
  sp_msgs__msg__RMUL * output)
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
  // game_progress
  output->game_progress = input->game_progress;
  // stage_remain_time
  output->stage_remain_time = input->stage_remain_time;
  // cmd_type
  output->cmd_type = input->cmd_type;
  // emergency_stop
  output->emergency_stop = input->emergency_stop;
  // rfid_supply_arrived
  output->rfid_supply_arrived = input->rfid_supply_arrived;
  // rfid_control_arrived
  output->rfid_control_arrived = input->rfid_control_arrived;
  // stop_gimbal_scan
  output->stop_gimbal_scan = input->stop_gimbal_scan;
  // chassis_spin
  output->chassis_spin = input->chassis_spin;
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // current_hp
  output->current_hp = input->current_hp;
  // is_attacked
  output->is_attacked = input->is_attacked;
  // is_detect_enemy
  output->is_detect_enemy = input->is_detect_enemy;
  return true;
}

sp_msgs__msg__RMUL *
sp_msgs__msg__RMUL__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sp_msgs__msg__RMUL * msg = (sp_msgs__msg__RMUL *)allocator.allocate(sizeof(sp_msgs__msg__RMUL), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sp_msgs__msg__RMUL));
  bool success = sp_msgs__msg__RMUL__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sp_msgs__msg__RMUL__destroy(sp_msgs__msg__RMUL * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sp_msgs__msg__RMUL__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sp_msgs__msg__RMUL__Sequence__init(sp_msgs__msg__RMUL__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sp_msgs__msg__RMUL * data = NULL;

  if (size) {
    data = (sp_msgs__msg__RMUL *)allocator.zero_allocate(size, sizeof(sp_msgs__msg__RMUL), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sp_msgs__msg__RMUL__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sp_msgs__msg__RMUL__fini(&data[i - 1]);
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
sp_msgs__msg__RMUL__Sequence__fini(sp_msgs__msg__RMUL__Sequence * array)
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
      sp_msgs__msg__RMUL__fini(&array->data[i]);
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

sp_msgs__msg__RMUL__Sequence *
sp_msgs__msg__RMUL__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sp_msgs__msg__RMUL__Sequence * array = (sp_msgs__msg__RMUL__Sequence *)allocator.allocate(sizeof(sp_msgs__msg__RMUL__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sp_msgs__msg__RMUL__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sp_msgs__msg__RMUL__Sequence__destroy(sp_msgs__msg__RMUL__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sp_msgs__msg__RMUL__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sp_msgs__msg__RMUL__Sequence__are_equal(const sp_msgs__msg__RMUL__Sequence * lhs, const sp_msgs__msg__RMUL__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sp_msgs__msg__RMUL__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sp_msgs__msg__RMUL__Sequence__copy(
  const sp_msgs__msg__RMUL__Sequence * input,
  sp_msgs__msg__RMUL__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sp_msgs__msg__RMUL);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sp_msgs__msg__RMUL * data =
      (sp_msgs__msg__RMUL *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sp_msgs__msg__RMUL__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sp_msgs__msg__RMUL__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sp_msgs__msg__RMUL__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
