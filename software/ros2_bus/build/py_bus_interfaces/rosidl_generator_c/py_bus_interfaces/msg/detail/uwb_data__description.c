// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from py_bus_interfaces:msg/UwbData.idl
// generated code does not contain a copyright notice

#include "py_bus_interfaces/msg/detail/uwb_data__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
const rosidl_type_hash_t *
py_bus_interfaces__msg__UwbData__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xef, 0xa6, 0x1c, 0x0a, 0x11, 0xe3, 0x20, 0x78,
      0xde, 0x24, 0xc4, 0xdc, 0x8f, 0xa0, 0x4e, 0x4b,
      0xf3, 0xbc, 0x5b, 0x1a, 0x76, 0xf1, 0x7d, 0xdc,
      0x4e, 0x83, 0xa0, 0xdf, 0x30, 0xa0, 0xc9, 0x68,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char py_bus_interfaces__msg__UwbData__TYPE_NAME[] = "py_bus_interfaces/msg/UwbData";

// Define type names, field names, and default values
static char py_bus_interfaces__msg__UwbData__FIELD_NAME__x[] = "x";
static char py_bus_interfaces__msg__UwbData__FIELD_NAME__y[] = "y";
static char py_bus_interfaces__msg__UwbData__FIELD_NAME__ts[] = "ts";

static rosidl_runtime_c__type_description__Field py_bus_interfaces__msg__UwbData__FIELDS[] = {
  {
    {py_bus_interfaces__msg__UwbData__FIELD_NAME__x, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__UwbData__FIELD_NAME__y, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__UwbData__FIELD_NAME__ts, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
py_bus_interfaces__msg__UwbData__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {py_bus_interfaces__msg__UwbData__TYPE_NAME, 29, 29},
      {py_bus_interfaces__msg__UwbData__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32 x\n"
  "float32 y\n"
  "float64 ts";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
py_bus_interfaces__msg__UwbData__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {py_bus_interfaces__msg__UwbData__TYPE_NAME, 29, 29},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 31, 31},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
py_bus_interfaces__msg__UwbData__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *py_bus_interfaces__msg__UwbData__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
