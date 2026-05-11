// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from py_bus_interfaces:msg/UwbData.idl
// generated code does not contain a copyright notice
#include "py_bus_interfaces/msg/detail/uwb_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
py_bus_interfaces__msg__UwbData__init(py_bus_interfaces__msg__UwbData * msg)
{
  if (!msg) {
    return false;
  }
  // x
  // y
  // ts
  return true;
}

void
py_bus_interfaces__msg__UwbData__fini(py_bus_interfaces__msg__UwbData * msg)
{
  if (!msg) {
    return;
  }
  // x
  // y
  // ts
}

bool
py_bus_interfaces__msg__UwbData__are_equal(const py_bus_interfaces__msg__UwbData * lhs, const py_bus_interfaces__msg__UwbData * rhs)
{
  if (!lhs || !rhs) {
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
  // ts
  if (lhs->ts != rhs->ts) {
    return false;
  }
  return true;
}

bool
py_bus_interfaces__msg__UwbData__copy(
  const py_bus_interfaces__msg__UwbData * input,
  py_bus_interfaces__msg__UwbData * output)
{
  if (!input || !output) {
    return false;
  }
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // ts
  output->ts = input->ts;
  return true;
}

py_bus_interfaces__msg__UwbData *
py_bus_interfaces__msg__UwbData__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  py_bus_interfaces__msg__UwbData * msg = (py_bus_interfaces__msg__UwbData *)allocator.allocate(sizeof(py_bus_interfaces__msg__UwbData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(py_bus_interfaces__msg__UwbData));
  bool success = py_bus_interfaces__msg__UwbData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
py_bus_interfaces__msg__UwbData__destroy(py_bus_interfaces__msg__UwbData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    py_bus_interfaces__msg__UwbData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
py_bus_interfaces__msg__UwbData__Sequence__init(py_bus_interfaces__msg__UwbData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  py_bus_interfaces__msg__UwbData * data = NULL;

  if (size) {
    data = (py_bus_interfaces__msg__UwbData *)allocator.zero_allocate(size, sizeof(py_bus_interfaces__msg__UwbData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = py_bus_interfaces__msg__UwbData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        py_bus_interfaces__msg__UwbData__fini(&data[i - 1]);
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
py_bus_interfaces__msg__UwbData__Sequence__fini(py_bus_interfaces__msg__UwbData__Sequence * array)
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
      py_bus_interfaces__msg__UwbData__fini(&array->data[i]);
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

py_bus_interfaces__msg__UwbData__Sequence *
py_bus_interfaces__msg__UwbData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  py_bus_interfaces__msg__UwbData__Sequence * array = (py_bus_interfaces__msg__UwbData__Sequence *)allocator.allocate(sizeof(py_bus_interfaces__msg__UwbData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = py_bus_interfaces__msg__UwbData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
py_bus_interfaces__msg__UwbData__Sequence__destroy(py_bus_interfaces__msg__UwbData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    py_bus_interfaces__msg__UwbData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
py_bus_interfaces__msg__UwbData__Sequence__are_equal(const py_bus_interfaces__msg__UwbData__Sequence * lhs, const py_bus_interfaces__msg__UwbData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!py_bus_interfaces__msg__UwbData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
py_bus_interfaces__msg__UwbData__Sequence__copy(
  const py_bus_interfaces__msg__UwbData__Sequence * input,
  py_bus_interfaces__msg__UwbData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(py_bus_interfaces__msg__UwbData);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    py_bus_interfaces__msg__UwbData * data =
      (py_bus_interfaces__msg__UwbData *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!py_bus_interfaces__msg__UwbData__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          py_bus_interfaces__msg__UwbData__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!py_bus_interfaces__msg__UwbData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
