// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from py_bus_interfaces:msg/DriverCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/driver_command.h"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_COMMAND__STRUCT_H_
#define PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/DriverCommand in the package py_bus_interfaces.
typedef struct py_bus_interfaces__msg__DriverCommand
{
  float speed_kmh;
  float steering_deg;
} py_bus_interfaces__msg__DriverCommand;

// Struct for a sequence of py_bus_interfaces__msg__DriverCommand.
typedef struct py_bus_interfaces__msg__DriverCommand__Sequence
{
  py_bus_interfaces__msg__DriverCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} py_bus_interfaces__msg__DriverCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_COMMAND__STRUCT_H_
