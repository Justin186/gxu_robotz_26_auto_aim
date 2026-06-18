// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rm_interfaces:msg/PlanGimbalCmd.idl
// generated code does not contain a copyright notice
#include "rm_interfaces/msg/detail/plan_gimbal_cmd__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
rm_interfaces__msg__PlanGimbalCmd__init(rm_interfaces__msg__PlanGimbalCmd * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    rm_interfaces__msg__PlanGimbalCmd__fini(msg);
    return false;
  }
  // ref_yaw
  // ref_yaw_vel
  // ref_yaw_acc
  // ref_pitch
  // ref_pitch_vel
  // ref_pitch_acc
  return true;
}

void
rm_interfaces__msg__PlanGimbalCmd__fini(rm_interfaces__msg__PlanGimbalCmd * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // ref_yaw
  // ref_yaw_vel
  // ref_yaw_acc
  // ref_pitch
  // ref_pitch_vel
  // ref_pitch_acc
}

bool
rm_interfaces__msg__PlanGimbalCmd__are_equal(const rm_interfaces__msg__PlanGimbalCmd * lhs, const rm_interfaces__msg__PlanGimbalCmd * rhs)
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
  // ref_yaw
  if (lhs->ref_yaw != rhs->ref_yaw) {
    return false;
  }
  // ref_yaw_vel
  if (lhs->ref_yaw_vel != rhs->ref_yaw_vel) {
    return false;
  }
  // ref_yaw_acc
  if (lhs->ref_yaw_acc != rhs->ref_yaw_acc) {
    return false;
  }
  // ref_pitch
  if (lhs->ref_pitch != rhs->ref_pitch) {
    return false;
  }
  // ref_pitch_vel
  if (lhs->ref_pitch_vel != rhs->ref_pitch_vel) {
    return false;
  }
  // ref_pitch_acc
  if (lhs->ref_pitch_acc != rhs->ref_pitch_acc) {
    return false;
  }
  return true;
}

bool
rm_interfaces__msg__PlanGimbalCmd__copy(
  const rm_interfaces__msg__PlanGimbalCmd * input,
  rm_interfaces__msg__PlanGimbalCmd * output)
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
  // ref_yaw
  output->ref_yaw = input->ref_yaw;
  // ref_yaw_vel
  output->ref_yaw_vel = input->ref_yaw_vel;
  // ref_yaw_acc
  output->ref_yaw_acc = input->ref_yaw_acc;
  // ref_pitch
  output->ref_pitch = input->ref_pitch;
  // ref_pitch_vel
  output->ref_pitch_vel = input->ref_pitch_vel;
  // ref_pitch_acc
  output->ref_pitch_acc = input->ref_pitch_acc;
  return true;
}

rm_interfaces__msg__PlanGimbalCmd *
rm_interfaces__msg__PlanGimbalCmd__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__msg__PlanGimbalCmd * msg = (rm_interfaces__msg__PlanGimbalCmd *)allocator.allocate(sizeof(rm_interfaces__msg__PlanGimbalCmd), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rm_interfaces__msg__PlanGimbalCmd));
  bool success = rm_interfaces__msg__PlanGimbalCmd__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rm_interfaces__msg__PlanGimbalCmd__destroy(rm_interfaces__msg__PlanGimbalCmd * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rm_interfaces__msg__PlanGimbalCmd__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rm_interfaces__msg__PlanGimbalCmd__Sequence__init(rm_interfaces__msg__PlanGimbalCmd__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__msg__PlanGimbalCmd * data = NULL;

  if (size) {
    data = (rm_interfaces__msg__PlanGimbalCmd *)allocator.zero_allocate(size, sizeof(rm_interfaces__msg__PlanGimbalCmd), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rm_interfaces__msg__PlanGimbalCmd__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rm_interfaces__msg__PlanGimbalCmd__fini(&data[i - 1]);
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
rm_interfaces__msg__PlanGimbalCmd__Sequence__fini(rm_interfaces__msg__PlanGimbalCmd__Sequence * array)
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
      rm_interfaces__msg__PlanGimbalCmd__fini(&array->data[i]);
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

rm_interfaces__msg__PlanGimbalCmd__Sequence *
rm_interfaces__msg__PlanGimbalCmd__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__msg__PlanGimbalCmd__Sequence * array = (rm_interfaces__msg__PlanGimbalCmd__Sequence *)allocator.allocate(sizeof(rm_interfaces__msg__PlanGimbalCmd__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rm_interfaces__msg__PlanGimbalCmd__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rm_interfaces__msg__PlanGimbalCmd__Sequence__destroy(rm_interfaces__msg__PlanGimbalCmd__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rm_interfaces__msg__PlanGimbalCmd__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rm_interfaces__msg__PlanGimbalCmd__Sequence__are_equal(const rm_interfaces__msg__PlanGimbalCmd__Sequence * lhs, const rm_interfaces__msg__PlanGimbalCmd__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rm_interfaces__msg__PlanGimbalCmd__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rm_interfaces__msg__PlanGimbalCmd__Sequence__copy(
  const rm_interfaces__msg__PlanGimbalCmd__Sequence * input,
  rm_interfaces__msg__PlanGimbalCmd__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rm_interfaces__msg__PlanGimbalCmd);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rm_interfaces__msg__PlanGimbalCmd * data =
      (rm_interfaces__msg__PlanGimbalCmd *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rm_interfaces__msg__PlanGimbalCmd__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rm_interfaces__msg__PlanGimbalCmd__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rm_interfaces__msg__PlanGimbalCmd__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
