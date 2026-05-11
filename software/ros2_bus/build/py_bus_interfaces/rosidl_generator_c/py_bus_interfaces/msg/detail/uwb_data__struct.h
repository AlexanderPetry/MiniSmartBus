// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from py_bus_interfaces:msg/UwbData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/uwb_data.h"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__UWB_DATA__STRUCT_H_
#define PY_BUS_INTERFACES__MSG__DETAIL__UWB_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/UwbData in the package py_bus_interfaces.
typedef struct py_bus_interfaces__msg__UwbData
{
  float x;
  float y;
  double ts;
} py_bus_interfaces__msg__UwbData;

// Struct for a sequence of py_bus_interfaces__msg__UwbData.
typedef struct py_bus_interfaces__msg__UwbData__Sequence
{
  py_bus_interfaces__msg__UwbData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} py_bus_interfaces__msg__UwbData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__UWB_DATA__STRUCT_H_
