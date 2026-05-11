// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from py_bus_interfaces:msg/DriverStatus.idl
// generated code does not contain a copyright notice
#include "py_bus_interfaces/msg/detail/driver_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `source`
// Member `raw_line`
#include "rosidl_runtime_c/string_functions.h"

bool
py_bus_interfaces__msg__DriverStatus__init(py_bus_interfaces__msg__DriverStatus * msg)
{
  if (!msg) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    py_bus_interfaces__msg__DriverStatus__fini(msg);
    return false;
  }
  // source
  if (!rosidl_runtime_c__String__init(&msg->source)) {
    py_bus_interfaces__msg__DriverStatus__fini(msg);
    return false;
  }
  // rc_steering_us
  // rc_throttle_us
  // commanded_speed_kmh
  // commanded_steering_deg
  // applied_speed_kmh
  // applied_steering_deg
  // batt_voltage
  // batt_pct
  // raw_line
  if (!rosidl_runtime_c__String__init(&msg->raw_line)) {
    py_bus_interfaces__msg__DriverStatus__fini(msg);
    return false;
  }
  return true;
}

void
py_bus_interfaces__msg__DriverStatus__fini(py_bus_interfaces__msg__DriverStatus * msg)
{
  if (!msg) {
    return;
  }
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // source
  rosidl_runtime_c__String__fini(&msg->source);
  // rc_steering_us
  // rc_throttle_us
  // commanded_speed_kmh
  // commanded_steering_deg
  // applied_speed_kmh
  // applied_steering_deg
  // batt_voltage
  // batt_pct
  // raw_line
  rosidl_runtime_c__String__fini(&msg->raw_line);
}

bool
py_bus_interfaces__msg__DriverStatus__are_equal(const py_bus_interfaces__msg__DriverStatus * lhs, const py_bus_interfaces__msg__DriverStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  // source
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->source), &(rhs->source)))
  {
    return false;
  }
  // rc_steering_us
  if (lhs->rc_steering_us != rhs->rc_steering_us) {
    return false;
  }
  // rc_throttle_us
  if (lhs->rc_throttle_us != rhs->rc_throttle_us) {
    return false;
  }
  // commanded_speed_kmh
  if (lhs->commanded_speed_kmh != rhs->commanded_speed_kmh) {
    return false;
  }
  // commanded_steering_deg
  if (lhs->commanded_steering_deg != rhs->commanded_steering_deg) {
    return false;
  }
  // applied_speed_kmh
  if (lhs->applied_speed_kmh != rhs->applied_speed_kmh) {
    return false;
  }
  // applied_steering_deg
  if (lhs->applied_steering_deg != rhs->applied_steering_deg) {
    return false;
  }
  // batt_voltage
  if (lhs->batt_voltage != rhs->batt_voltage) {
    return false;
  }
  // batt_pct
  if (lhs->batt_pct != rhs->batt_pct) {
    return false;
  }
  // raw_line
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->raw_line), &(rhs->raw_line)))
  {
    return false;
  }
  return true;
}

bool
py_bus_interfaces__msg__DriverStatus__copy(
  const py_bus_interfaces__msg__DriverStatus * input,
  py_bus_interfaces__msg__DriverStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  // source
  if (!rosidl_runtime_c__String__copy(
      &(input->source), &(output->source)))
  {
    return false;
  }
  // rc_steering_us
  output->rc_steering_us = input->rc_steering_us;
  // rc_throttle_us
  output->rc_throttle_us = input->rc_throttle_us;
  // commanded_speed_kmh
  output->commanded_speed_kmh = input->commanded_speed_kmh;
  // commanded_steering_deg
  output->commanded_steering_deg = input->commanded_steering_deg;
  // applied_speed_kmh
  output->applied_speed_kmh = input->applied_speed_kmh;
  // applied_steering_deg
  output->applied_steering_deg = input->applied_steering_deg;
  // batt_voltage
  output->batt_voltage = input->batt_voltage;
  // batt_pct
  output->batt_pct = input->batt_pct;
  // raw_line
  if (!rosidl_runtime_c__String__copy(
      &(input->raw_line), &(output->raw_line)))
  {
    return false;
  }
  return true;
}

py_bus_interfaces__msg__DriverStatus *
py_bus_interfaces__msg__DriverStatus__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  py_bus_interfaces__msg__DriverStatus * msg = (py_bus_interfaces__msg__DriverStatus *)allocator.allocate(sizeof(py_bus_interfaces__msg__DriverStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(py_bus_interfaces__msg__DriverStatus));
  bool success = py_bus_interfaces__msg__DriverStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
py_bus_interfaces__msg__DriverStatus__destroy(py_bus_interfaces__msg__DriverStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    py_bus_interfaces__msg__DriverStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
py_bus_interfaces__msg__DriverStatus__Sequence__init(py_bus_interfaces__msg__DriverStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  py_bus_interfaces__msg__DriverStatus * data = NULL;

  if (size) {
    data = (py_bus_interfaces__msg__DriverStatus *)allocator.zero_allocate(size, sizeof(py_bus_interfaces__msg__DriverStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = py_bus_interfaces__msg__DriverStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        py_bus_interfaces__msg__DriverStatus__fini(&data[i - 1]);
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
py_bus_interfaces__msg__DriverStatus__Sequence__fini(py_bus_interfaces__msg__DriverStatus__Sequence * array)
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
      py_bus_interfaces__msg__DriverStatus__fini(&array->data[i]);
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

py_bus_interfaces__msg__DriverStatus__Sequence *
py_bus_interfaces__msg__DriverStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  py_bus_interfaces__msg__DriverStatus__Sequence * array = (py_bus_interfaces__msg__DriverStatus__Sequence *)allocator.allocate(sizeof(py_bus_interfaces__msg__DriverStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = py_bus_interfaces__msg__DriverStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
py_bus_interfaces__msg__DriverStatus__Sequence__destroy(py_bus_interfaces__msg__DriverStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    py_bus_interfaces__msg__DriverStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
py_bus_interfaces__msg__DriverStatus__Sequence__are_equal(const py_bus_interfaces__msg__DriverStatus__Sequence * lhs, const py_bus_interfaces__msg__DriverStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!py_bus_interfaces__msg__DriverStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
py_bus_interfaces__msg__DriverStatus__Sequence__copy(
  const py_bus_interfaces__msg__DriverStatus__Sequence * input,
  py_bus_interfaces__msg__DriverStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(py_bus_interfaces__msg__DriverStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    py_bus_interfaces__msg__DriverStatus * data =
      (py_bus_interfaces__msg__DriverStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!py_bus_interfaces__msg__DriverStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          py_bus_interfaces__msg__DriverStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!py_bus_interfaces__msg__DriverStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
