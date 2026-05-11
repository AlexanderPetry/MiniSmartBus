// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from py_bus_interfaces:msg/ImuData.idl
// generated code does not contain a copyright notice
#include "py_bus_interfaces/msg/detail/imu_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
py_bus_interfaces__msg__ImuData__init(py_bus_interfaces__msg__ImuData * msg)
{
  if (!msg) {
    return false;
  }
  // sample_id
  // accel_x
  // accel_y
  // accel_z
  // temp
  // gyro_x
  // gyro_y
  // gyro_z
  return true;
}

void
py_bus_interfaces__msg__ImuData__fini(py_bus_interfaces__msg__ImuData * msg)
{
  if (!msg) {
    return;
  }
  // sample_id
  // accel_x
  // accel_y
  // accel_z
  // temp
  // gyro_x
  // gyro_y
  // gyro_z
}

bool
py_bus_interfaces__msg__ImuData__are_equal(const py_bus_interfaces__msg__ImuData * lhs, const py_bus_interfaces__msg__ImuData * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // sample_id
  if (lhs->sample_id != rhs->sample_id) {
    return false;
  }
  // accel_x
  if (lhs->accel_x != rhs->accel_x) {
    return false;
  }
  // accel_y
  if (lhs->accel_y != rhs->accel_y) {
    return false;
  }
  // accel_z
  if (lhs->accel_z != rhs->accel_z) {
    return false;
  }
  // temp
  if (lhs->temp != rhs->temp) {
    return false;
  }
  // gyro_x
  if (lhs->gyro_x != rhs->gyro_x) {
    return false;
  }
  // gyro_y
  if (lhs->gyro_y != rhs->gyro_y) {
    return false;
  }
  // gyro_z
  if (lhs->gyro_z != rhs->gyro_z) {
    return false;
  }
  return true;
}

bool
py_bus_interfaces__msg__ImuData__copy(
  const py_bus_interfaces__msg__ImuData * input,
  py_bus_interfaces__msg__ImuData * output)
{
  if (!input || !output) {
    return false;
  }
  // sample_id
  output->sample_id = input->sample_id;
  // accel_x
  output->accel_x = input->accel_x;
  // accel_y
  output->accel_y = input->accel_y;
  // accel_z
  output->accel_z = input->accel_z;
  // temp
  output->temp = input->temp;
  // gyro_x
  output->gyro_x = input->gyro_x;
  // gyro_y
  output->gyro_y = input->gyro_y;
  // gyro_z
  output->gyro_z = input->gyro_z;
  return true;
}

py_bus_interfaces__msg__ImuData *
py_bus_interfaces__msg__ImuData__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  py_bus_interfaces__msg__ImuData * msg = (py_bus_interfaces__msg__ImuData *)allocator.allocate(sizeof(py_bus_interfaces__msg__ImuData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(py_bus_interfaces__msg__ImuData));
  bool success = py_bus_interfaces__msg__ImuData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
py_bus_interfaces__msg__ImuData__destroy(py_bus_interfaces__msg__ImuData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    py_bus_interfaces__msg__ImuData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
py_bus_interfaces__msg__ImuData__Sequence__init(py_bus_interfaces__msg__ImuData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  py_bus_interfaces__msg__ImuData * data = NULL;

  if (size) {
    data = (py_bus_interfaces__msg__ImuData *)allocator.zero_allocate(size, sizeof(py_bus_interfaces__msg__ImuData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = py_bus_interfaces__msg__ImuData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        py_bus_interfaces__msg__ImuData__fini(&data[i - 1]);
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
py_bus_interfaces__msg__ImuData__Sequence__fini(py_bus_interfaces__msg__ImuData__Sequence * array)
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
      py_bus_interfaces__msg__ImuData__fini(&array->data[i]);
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

py_bus_interfaces__msg__ImuData__Sequence *
py_bus_interfaces__msg__ImuData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  py_bus_interfaces__msg__ImuData__Sequence * array = (py_bus_interfaces__msg__ImuData__Sequence *)allocator.allocate(sizeof(py_bus_interfaces__msg__ImuData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = py_bus_interfaces__msg__ImuData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
py_bus_interfaces__msg__ImuData__Sequence__destroy(py_bus_interfaces__msg__ImuData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    py_bus_interfaces__msg__ImuData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
py_bus_interfaces__msg__ImuData__Sequence__are_equal(const py_bus_interfaces__msg__ImuData__Sequence * lhs, const py_bus_interfaces__msg__ImuData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!py_bus_interfaces__msg__ImuData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
py_bus_interfaces__msg__ImuData__Sequence__copy(
  const py_bus_interfaces__msg__ImuData__Sequence * input,
  py_bus_interfaces__msg__ImuData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(py_bus_interfaces__msg__ImuData);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    py_bus_interfaces__msg__ImuData * data =
      (py_bus_interfaces__msg__ImuData *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!py_bus_interfaces__msg__ImuData__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          py_bus_interfaces__msg__ImuData__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!py_bus_interfaces__msg__ImuData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
