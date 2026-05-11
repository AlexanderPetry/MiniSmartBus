// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from py_bus_interfaces:msg/DriverStatus.idl
// generated code does not contain a copyright notice

#include "py_bus_interfaces/msg/detail/driver_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
const rosidl_type_hash_t *
py_bus_interfaces__msg__DriverStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x27, 0xea, 0x7a, 0x50, 0x09, 0x2e, 0x3c, 0xd7,
      0xed, 0xc9, 0x3f, 0xeb, 0xb5, 0x2c, 0xeb, 0x84,
      0xcc, 0x43, 0x3b, 0x7d, 0xd3, 0x99, 0x50, 0x5b,
      0xf4, 0xac, 0xef, 0xe3, 0xd3, 0x3b, 0x35, 0x62,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
#endif

static char py_bus_interfaces__msg__DriverStatus__TYPE_NAME[] = "py_bus_interfaces/msg/DriverStatus";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";

// Define type names, field names, and default values
static char py_bus_interfaces__msg__DriverStatus__FIELD_NAME__stamp[] = "stamp";
static char py_bus_interfaces__msg__DriverStatus__FIELD_NAME__source[] = "source";
static char py_bus_interfaces__msg__DriverStatus__FIELD_NAME__rc_steering_us[] = "rc_steering_us";
static char py_bus_interfaces__msg__DriverStatus__FIELD_NAME__rc_throttle_us[] = "rc_throttle_us";
static char py_bus_interfaces__msg__DriverStatus__FIELD_NAME__commanded_speed_kmh[] = "commanded_speed_kmh";
static char py_bus_interfaces__msg__DriverStatus__FIELD_NAME__commanded_steering_deg[] = "commanded_steering_deg";
static char py_bus_interfaces__msg__DriverStatus__FIELD_NAME__applied_speed_kmh[] = "applied_speed_kmh";
static char py_bus_interfaces__msg__DriverStatus__FIELD_NAME__applied_steering_deg[] = "applied_steering_deg";
static char py_bus_interfaces__msg__DriverStatus__FIELD_NAME__batt_voltage[] = "batt_voltage";
static char py_bus_interfaces__msg__DriverStatus__FIELD_NAME__batt_pct[] = "batt_pct";
static char py_bus_interfaces__msg__DriverStatus__FIELD_NAME__raw_line[] = "raw_line";

static rosidl_runtime_c__type_description__Field py_bus_interfaces__msg__DriverStatus__FIELDS[] = {
  {
    {py_bus_interfaces__msg__DriverStatus__FIELD_NAME__stamp, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__DriverStatus__FIELD_NAME__source, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__DriverStatus__FIELD_NAME__rc_steering_us, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__DriverStatus__FIELD_NAME__rc_throttle_us, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__DriverStatus__FIELD_NAME__commanded_speed_kmh, 19, 19},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__DriverStatus__FIELD_NAME__commanded_steering_deg, 22, 22},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__DriverStatus__FIELD_NAME__applied_speed_kmh, 17, 17},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__DriverStatus__FIELD_NAME__applied_steering_deg, 20, 20},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__DriverStatus__FIELD_NAME__batt_voltage, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__DriverStatus__FIELD_NAME__batt_pct, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {py_bus_interfaces__msg__DriverStatus__FIELD_NAME__raw_line, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription py_bus_interfaces__msg__DriverStatus__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
py_bus_interfaces__msg__DriverStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {py_bus_interfaces__msg__DriverStatus__TYPE_NAME, 34, 34},
      {py_bus_interfaces__msg__DriverStatus__FIELDS, 11, 11},
    },
    {py_bus_interfaces__msg__DriverStatus__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "builtin_interfaces/Time stamp\n"
  "string source\n"
  "int32 rc_steering_us\n"
  "int32 rc_throttle_us\n"
  "float32 commanded_speed_kmh\n"
  "float32 commanded_steering_deg\n"
  "float32 applied_speed_kmh\n"
  "float32 applied_steering_deg\n"
  "float32 batt_voltage\n"
  "float32 batt_pct\n"
  "string raw_line";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
py_bus_interfaces__msg__DriverStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {py_bus_interfaces__msg__DriverStatus__TYPE_NAME, 34, 34},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 254, 254},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
py_bus_interfaces__msg__DriverStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *py_bus_interfaces__msg__DriverStatus__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
