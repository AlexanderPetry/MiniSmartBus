// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from py_bus_interfaces:msg/DriverCommand.idl
// generated code does not contain a copyright notice

#include "py_bus_interfaces/msg/detail/driver_command__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
const rosidl_type_hash_t *
py_bus_interfaces__msg__DriverCommand__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xcd, 0xaa, 0x8d, 0x55, 0x72, 0x64, 0x70, 0xdb,
      0xdd, 0x46, 0xbd, 0x05, 0x24, 0x9d, 0x0a, 0xef,
      0x06, 0xa0, 0x82, 0xd7, 0x66, 0x49, 0xc3, 0x47,
      0x96, 0xd5, 0xdf, 0xca, 0x56, 0x7c, 0x83, 0xb5,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char py_bus_interfaces__msg__DriverCommand__TYPE_NAME[] = "py_bus_interfaces/msg/DriverCommand";

// Define type names, field names, and default values
static char py_bus_interfaces__msg__DriverCommand__FIELD_NAME__speed_kmh[] = "speed_kmh";
static char py_bus_interfaces__msg__DriverCommand__FIELD_NAME__steering_deg[] = "steering_deg";

static rosidl_runtime_c__type_description__Field py_bus_interfaces__msg__DriverCommand__FIELDS[] = {
  {
    {py_bus_interfaces__msg__DriverCommand__FIELD_NAME__speed_kmh, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__DriverCommand__FIELD_NAME__steering_deg, 12, 12},
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
py_bus_interfaces__msg__DriverCommand__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {py_bus_interfaces__msg__DriverCommand__TYPE_NAME, 35, 35},
      {py_bus_interfaces__msg__DriverCommand__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32 speed_kmh\n"
  "float32 steering_deg";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
py_bus_interfaces__msg__DriverCommand__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {py_bus_interfaces__msg__DriverCommand__TYPE_NAME, 35, 35},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 39, 39},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
py_bus_interfaces__msg__DriverCommand__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *py_bus_interfaces__msg__DriverCommand__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
