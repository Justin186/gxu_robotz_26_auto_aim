// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rm_interfaces:srv/RunHandEyeCalibration.idl
// generated code does not contain a copyright notice
#include "rm_interfaces/srv/detail/run_hand_eye_calibration__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
rm_interfaces__srv__RunHandEyeCalibration_Request__init(rm_interfaces__srv__RunHandEyeCalibration_Request * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
rm_interfaces__srv__RunHandEyeCalibration_Request__fini(rm_interfaces__srv__RunHandEyeCalibration_Request * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
rm_interfaces__srv__RunHandEyeCalibration_Request__are_equal(const rm_interfaces__srv__RunHandEyeCalibration_Request * lhs, const rm_interfaces__srv__RunHandEyeCalibration_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
rm_interfaces__srv__RunHandEyeCalibration_Request__copy(
  const rm_interfaces__srv__RunHandEyeCalibration_Request * input,
  rm_interfaces__srv__RunHandEyeCalibration_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

rm_interfaces__srv__RunHandEyeCalibration_Request *
rm_interfaces__srv__RunHandEyeCalibration_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__srv__RunHandEyeCalibration_Request * msg = (rm_interfaces__srv__RunHandEyeCalibration_Request *)allocator.allocate(sizeof(rm_interfaces__srv__RunHandEyeCalibration_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rm_interfaces__srv__RunHandEyeCalibration_Request));
  bool success = rm_interfaces__srv__RunHandEyeCalibration_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rm_interfaces__srv__RunHandEyeCalibration_Request__destroy(rm_interfaces__srv__RunHandEyeCalibration_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rm_interfaces__srv__RunHandEyeCalibration_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence__init(rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__srv__RunHandEyeCalibration_Request * data = NULL;

  if (size) {
    data = (rm_interfaces__srv__RunHandEyeCalibration_Request *)allocator.zero_allocate(size, sizeof(rm_interfaces__srv__RunHandEyeCalibration_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rm_interfaces__srv__RunHandEyeCalibration_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rm_interfaces__srv__RunHandEyeCalibration_Request__fini(&data[i - 1]);
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
rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence__fini(rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence * array)
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
      rm_interfaces__srv__RunHandEyeCalibration_Request__fini(&array->data[i]);
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

rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence *
rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence * array = (rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence *)allocator.allocate(sizeof(rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence__destroy(rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence__are_equal(const rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence * lhs, const rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rm_interfaces__srv__RunHandEyeCalibration_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence__copy(
  const rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence * input,
  rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rm_interfaces__srv__RunHandEyeCalibration_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rm_interfaces__srv__RunHandEyeCalibration_Request * data =
      (rm_interfaces__srv__RunHandEyeCalibration_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rm_interfaces__srv__RunHandEyeCalibration_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rm_interfaces__srv__RunHandEyeCalibration_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rm_interfaces__srv__RunHandEyeCalibration_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `yaml_path`
#include "rosidl_runtime_c/string_functions.h"

bool
rm_interfaces__srv__RunHandEyeCalibration_Response__init(rm_interfaces__srv__RunHandEyeCalibration_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // yaml_path
  if (!rosidl_runtime_c__String__init(&msg->yaml_path)) {
    rm_interfaces__srv__RunHandEyeCalibration_Response__fini(msg);
    return false;
  }
  return true;
}

void
rm_interfaces__srv__RunHandEyeCalibration_Response__fini(rm_interfaces__srv__RunHandEyeCalibration_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // yaml_path
  rosidl_runtime_c__String__fini(&msg->yaml_path);
}

bool
rm_interfaces__srv__RunHandEyeCalibration_Response__are_equal(const rm_interfaces__srv__RunHandEyeCalibration_Response * lhs, const rm_interfaces__srv__RunHandEyeCalibration_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // yaml_path
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->yaml_path), &(rhs->yaml_path)))
  {
    return false;
  }
  return true;
}

bool
rm_interfaces__srv__RunHandEyeCalibration_Response__copy(
  const rm_interfaces__srv__RunHandEyeCalibration_Response * input,
  rm_interfaces__srv__RunHandEyeCalibration_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // yaml_path
  if (!rosidl_runtime_c__String__copy(
      &(input->yaml_path), &(output->yaml_path)))
  {
    return false;
  }
  return true;
}

rm_interfaces__srv__RunHandEyeCalibration_Response *
rm_interfaces__srv__RunHandEyeCalibration_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__srv__RunHandEyeCalibration_Response * msg = (rm_interfaces__srv__RunHandEyeCalibration_Response *)allocator.allocate(sizeof(rm_interfaces__srv__RunHandEyeCalibration_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rm_interfaces__srv__RunHandEyeCalibration_Response));
  bool success = rm_interfaces__srv__RunHandEyeCalibration_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rm_interfaces__srv__RunHandEyeCalibration_Response__destroy(rm_interfaces__srv__RunHandEyeCalibration_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rm_interfaces__srv__RunHandEyeCalibration_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence__init(rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__srv__RunHandEyeCalibration_Response * data = NULL;

  if (size) {
    data = (rm_interfaces__srv__RunHandEyeCalibration_Response *)allocator.zero_allocate(size, sizeof(rm_interfaces__srv__RunHandEyeCalibration_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rm_interfaces__srv__RunHandEyeCalibration_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rm_interfaces__srv__RunHandEyeCalibration_Response__fini(&data[i - 1]);
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
rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence__fini(rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence * array)
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
      rm_interfaces__srv__RunHandEyeCalibration_Response__fini(&array->data[i]);
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

rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence *
rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence * array = (rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence *)allocator.allocate(sizeof(rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence__destroy(rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence__are_equal(const rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence * lhs, const rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rm_interfaces__srv__RunHandEyeCalibration_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence__copy(
  const rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence * input,
  rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rm_interfaces__srv__RunHandEyeCalibration_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rm_interfaces__srv__RunHandEyeCalibration_Response * data =
      (rm_interfaces__srv__RunHandEyeCalibration_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rm_interfaces__srv__RunHandEyeCalibration_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rm_interfaces__srv__RunHandEyeCalibration_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rm_interfaces__srv__RunHandEyeCalibration_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
