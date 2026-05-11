// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from py_bus_interfaces:msg/ImuData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/imu_data.h"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__IMU_DATA__STRUCT_H_
#define PY_BUS_INTERFACES__MSG__DETAIL__IMU_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/ImuData in the package py_bus_interfaces.
typedef struct py_bus_interfaces__msg__ImuData
{
  int32_t sample_id;
  float accel_x;
  float accel_y;
  float accel_z;
  float temp;
  float gyro_x;
  float gyro_y;
  float gyro_z;
} py_bus_interfaces__msg__ImuData;

// Struct for a sequence of py_bus_interfaces__msg__ImuData.
typedef struct py_bus_interfaces__msg__ImuData__Sequence
{
  py_bus_interfaces__msg__ImuData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} py_bus_interfaces__msg__ImuData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__IMU_DATA__STRUCT_H_
