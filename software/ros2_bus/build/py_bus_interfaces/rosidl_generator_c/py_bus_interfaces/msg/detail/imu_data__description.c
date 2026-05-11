// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from py_bus_interfaces:msg/ImuData.idl
// generated code does not contain a copyright notice

#include "py_bus_interfaces/msg/detail/imu_data__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
const rosidl_type_hash_t *
py_bus_interfaces__msg__ImuData__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xf8, 0x17, 0x95, 0x90, 0x54, 0x83, 0xac, 0xc5,
      0xea, 0x7c, 0x18, 0xd6, 0xf8, 0x62, 0xa3, 0x73,
      0x0a, 0xce, 0x73, 0xaa, 0x5c, 0xf7, 0x26, 0xda,
      0x6d, 0x76, 0xa9, 0xc3, 0x86, 0x84, 0x4a, 0x76,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char py_bus_interfaces__msg__ImuData__TYPE_NAME[] = "py_bus_interfaces/msg/ImuData";

// Define type names, field names, and default values
static char py_bus_interfaces__msg__ImuData__FIELD_NAME__sample_id[] = "sample_id";
static char py_bus_interfaces__msg__ImuData__FIELD_NAME__accel_x[] = "accel_x";
static char py_bus_interfaces__msg__ImuData__FIELD_NAME__accel_y[] = "accel_y";
static char py_bus_interfaces__msg__ImuData__FIELD_NAME__accel_z[] = "accel_z";
static char py_bus_interfaces__msg__ImuData__FIELD_NAME__temp[] = "temp";
static char py_bus_interfaces__msg__ImuData__FIELD_NAME__gyro_x[] = "gyro_x";
static char py_bus_interfaces__msg__ImuData__FIELD_NAME__gyro_y[] = "gyro_y";
static char py_bus_interfaces__msg__ImuData__FIELD_NAME__gyro_z[] = "gyro_z";

static rosidl_runtime_c__type_description__Field py_bus_interfaces__msg__ImuData__FIELDS[] = {
  {
    {py_bus_interfaces__msg__ImuData__FIELD_NAME__sample_id, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__ImuData__FIELD_NAME__accel_x, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__ImuData__FIELD_NAME__accel_y, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__ImuData__FIELD_NAME__accel_z, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__ImuData__FIELD_NAME__temp, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__ImuData__FIELD_NAME__gyro_x, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__ImuData__FIELD_NAME__gyro_y, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__ImuData__FIELD_NAME__gyro_z, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
py_bus_interfaces__msg__ImuData__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {py_bus_interfaces__msg__ImuData__TYPE_NAME, 29, 29},
      {py_bus_interfaces__msg__ImuData__FIELDS, 8, 8},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "int32 sample_id\n"
  "float32 accel_x\n"
  "float32 accel_y\n"
  "float32 accel_z\n"
  "float32 temp\n"
  "float32 gyro_x\n"
  "float32 gyro_y\n"
  "float32 gyro_z";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
py_bus_interfaces__msg__ImuData__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {py_bus_interfaces__msg__ImuData__TYPE_NAME, 29, 29},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 122, 122},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
py_bus_interfaces__msg__ImuData__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *py_bus_interfaces__msg__ImuData__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
