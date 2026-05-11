// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from py_bus_interfaces:msg/DriverCommand.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "py_bus_interfaces/msg/detail/driver_command__rosidl_typesupport_introspection_c.h"
#include "py_bus_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "py_bus_interfaces/msg/detail/driver_command__functions.h"
#include "py_bus_interfaces/msg/detail/driver_command__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void py_bus_interfaces__msg__DriverCommand__rosidl_typesupport_introspection_c__DriverCommand_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  py_bus_interfaces__msg__DriverCommand__init(message_memory);
}

void py_bus_interfaces__msg__DriverCommand__rosidl_typesupport_introspection_c__DriverCommand_fini_function(void * message_memory)
{
  py_bus_interfaces__msg__DriverCommand__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember py_bus_interfaces__msg__DriverCommand__rosidl_typesupport_introspection_c__DriverCommand_message_member_array[2] = {
  {
    "speed_kmh",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(py_bus_interfaces__msg__DriverCommand, speed_kmh),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "steering_deg",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(py_bus_interfaces__msg__DriverCommand, steering_deg),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers py_bus_interfaces__msg__DriverCommand__rosidl_typesupport_introspection_c__DriverCommand_message_members = {
  "py_bus_interfaces__msg",  // message namespace
  "DriverCommand",  // message name
  2,  // number of fields
  sizeof(py_bus_interfaces__msg__DriverCommand),
  false,  // has_any_key_member_
  py_bus_interfaces__msg__DriverCommand__rosidl_typesupport_introspection_c__DriverCommand_message_member_array,  // message members
  py_bus_interfaces__msg__DriverCommand__rosidl_typesupport_introspection_c__DriverCommand_init_function,  // function to initialize message memory (memory has to be allocated)
  py_bus_interfaces__msg__DriverCommand__rosidl_typesupport_introspection_c__DriverCommand_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t py_bus_interfaces__msg__DriverCommand__rosidl_typesupport_introspection_c__DriverCommand_message_type_support_handle = {
  0,
  &py_bus_interfaces__msg__DriverCommand__rosidl_typesupport_introspection_c__DriverCommand_message_members,
  get_message_typesupport_handle_function,
  &py_bus_interfaces__msg__DriverCommand__get_type_hash,
  &py_bus_interfaces__msg__DriverCommand__get_type_description,
  &py_bus_interfaces__msg__DriverCommand__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_py_bus_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, py_bus_interfaces, msg, DriverCommand)() {
  if (!py_bus_interfaces__msg__DriverCommand__rosidl_typesupport_introspection_c__DriverCommand_message_type_support_handle.typesupport_identifier) {
    py_bus_interfaces__msg__DriverCommand__rosidl_typesupport_introspection_c__DriverCommand_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &py_bus_interfaces__msg__DriverCommand__rosidl_typesupport_introspection_c__DriverCommand_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
