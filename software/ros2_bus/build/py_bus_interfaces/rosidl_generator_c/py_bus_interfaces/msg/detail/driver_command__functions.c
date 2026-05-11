// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from py_bus_interfaces:msg/DriverCommand.idl
// generated code does not contain a copyright notice
#include "py_bus_interfaces/msg/detail/driver_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
py_bus_interfaces__msg__DriverCommand__init(py_bus_interfaces__msg__DriverCommand * msg)
{
  if (!msg) {
    return false;
  }
  // speed_kmh
  // steering_deg
  return true;
}

void
py_bus_interfaces__msg__DriverCommand__fini(py_bus_interfaces__msg__DriverCommand * msg)
{
  if (!msg) {
    return;
  }
  // speed_kmh
  // steering_deg
}

bool
py_bus_interfaces__msg__DriverCommand__are_equal(const py_bus_interfaces__msg__DriverCommand * lhs, const py_bus_interfaces__msg__DriverCommand * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // speed_kmh
  if (lhs->speed_kmh != rhs->speed_kmh) {
    return false;
  }
  // steering_deg
  if (lhs->steering_deg != rhs->steering_deg) {
    return false;
  }
  return true;
}

bool
py_bus_interfaces__msg__DriverCommand__copy(
  const py_bus_interfaces__msg__DriverCommand * input,
  py_bus_interfaces__msg__DriverCommand * output)
{
  if (!input || !output) {
    return false;
  }
  // speed_kmh
  output->speed_kmh = input->speed_kmh;
  // steering_deg
  output->steering_deg = input->steering_deg;
  return true;
}

py_bus_interfaces__msg__DriverCommand *
py_bus_interfaces__msg__DriverCommand__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  py_bus_interfaces__msg__DriverCommand * msg = (py_bus_interfaces__msg__DriverCommand *)allocator.allocate(sizeof(py_bus_interfaces__msg__DriverCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(py_bus_interfaces__msg__DriverCommand));
  bool success = py_bus_interfaces__msg__DriverCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
py_bus_interfaces__msg__DriverCommand__destroy(py_bus_interfaces__msg__DriverCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    py_bus_interfaces__msg__DriverCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
py_bus_interfaces__msg__DriverCommand__Sequence__init(py_bus_interfaces__msg__DriverCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  py_bus_interfaces__msg__DriverCommand * data = NULL;

  if (size) {
    data = (py_bus_interfaces__msg__DriverCommand *)allocator.zero_allocate(size, sizeof(py_bus_interfaces__msg__DriverCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = py_bus_interfaces__msg__DriverCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        py_bus_interfaces__msg__DriverCommand__fini(&data[i - 1]);
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
py_bus_interfaces__msg__DriverCommand__Sequence__fini(py_bus_interfaces__msg__DriverCommand__Sequence * array)
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
      py_bus_interfaces__msg__DriverCommand__fini(&array->data[i]);
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

py_bus_interfaces__msg__DriverCommand__Sequence *
py_bus_interfaces__msg__DriverCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  py_bus_interfaces__msg__DriverCommand__Sequence * array = (py_bus_interfaces__msg__DriverCommand__Sequence *)allocator.allocate(sizeof(py_bus_interfaces__msg__DriverCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = py_bus_interfaces__msg__DriverCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
py_bus_interfaces__msg__DriverCommand__Sequence__destroy(py_bus_interfaces__msg__DriverCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    py_bus_interfaces__msg__DriverCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
py_bus_interfaces__msg__DriverCommand__Sequence__are_equal(const py_bus_interfaces__msg__DriverCommand__Sequence * lhs, const py_bus_interfaces__msg__DriverCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!py_bus_interfaces__msg__DriverCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
py_bus_interfaces__msg__DriverCommand__Sequence__copy(
  const py_bus_interfaces__msg__DriverCommand__Sequence * input,
  py_bus_interfaces__msg__DriverCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(py_bus_interfaces__msg__DriverCommand);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    py_bus_interfaces__msg__DriverCommand * data =
      (py_bus_interfaces__msg__DriverCommand *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!py_bus_interfaces__msg__DriverCommand__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          py_bus_interfaces__msg__DriverCommand__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!py_bus_interfaces__msg__DriverCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
