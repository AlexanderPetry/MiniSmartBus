// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from py_bus_interfaces:msg/DriverStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/driver_status.h"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_STATUS__STRUCT_H_
#define PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'source'
// Member 'raw_line'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/DriverStatus in the package py_bus_interfaces.
typedef struct py_bus_interfaces__msg__DriverStatus
{
  builtin_interfaces__msg__Time stamp;
  rosidl_runtime_c__String source;
  int32_t rc_steering_us;
  int32_t rc_throttle_us;
  float commanded_speed_kmh;
  float commanded_steering_deg;
  float applied_speed_kmh;
  float applied_steering_deg;
  float batt_voltage;
  float batt_pct;
  rosidl_runtime_c__String raw_line;
} py_bus_interfaces__msg__DriverStatus;

// Struct for a sequence of py_bus_interfaces__msg__DriverStatus.
typedef struct py_bus_interfaces__msg__DriverStatus__Sequence
{
  py_bus_interfaces__msg__DriverStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} py_bus_interfaces__msg__DriverStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_STATUS__STRUCT_H_
