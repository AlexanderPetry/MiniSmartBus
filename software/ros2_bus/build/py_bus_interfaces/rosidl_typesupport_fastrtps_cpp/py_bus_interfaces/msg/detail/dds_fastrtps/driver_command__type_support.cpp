// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from py_bus_interfaces:msg/DriverCommand.idl
// generated code does not contain a copyright notice
#include "py_bus_interfaces/msg/detail/driver_command__rosidl_typesupport_fastrtps_cpp.hpp"
#include "py_bus_interfaces/msg/detail/driver_command__functions.h"
#include "py_bus_interfaces/msg/detail/driver_command__struct.hpp"

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace py_bus_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{


bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_py_bus_interfaces
cdr_serialize(
  const py_bus_interfaces::msg::DriverCommand & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: speed_kmh
  cdr << ros_message.speed_kmh;

  // Member: steering_deg
  cdr << ros_message.steering_deg;

  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_py_bus_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  py_bus_interfaces::msg::DriverCommand & ros_message)
{
  // Member: speed_kmh
  cdr >> ros_message.speed_kmh;

  // Member: steering_deg
  cdr >> ros_message.steering_deg;

  return true;
}  // NOLINT(readability/fn_size)


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_py_bus_interfaces
get_serialized_size(
  const py_bus_interfaces::msg::DriverCommand & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: speed_kmh
  {
    size_t item_size = sizeof(ros_message.speed_kmh);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: steering_deg
  {
    size_t item_size = sizeof(ros_message.steering_deg);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_py_bus_interfaces
max_serialized_size_DriverCommand(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Member: speed_kmh
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // Member: steering_deg
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = py_bus_interfaces::msg::DriverCommand;
    is_plain =
      (
      offsetof(DataType, steering_deg) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_py_bus_interfaces
cdr_serialize_key(
  const py_bus_interfaces::msg::DriverCommand & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: speed_kmh
  cdr << ros_message.speed_kmh;

  // Member: steering_deg
  cdr << ros_message.steering_deg;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_py_bus_interfaces
get_serialized_size_key(
  const py_bus_interfaces::msg::DriverCommand & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: speed_kmh
  {
    size_t item_size = sizeof(ros_message.speed_kmh);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: steering_deg
  {
    size_t item_size = sizeof(ros_message.steering_deg);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_py_bus_interfaces
max_serialized_size_key_DriverCommand(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Member: speed_kmh
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: steering_deg
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = py_bus_interfaces::msg::DriverCommand;
    is_plain =
      (
      offsetof(DataType, steering_deg) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}


static bool _DriverCommand__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const py_bus_interfaces::msg::DriverCommand *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _DriverCommand__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<py_bus_interfaces::msg::DriverCommand *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _DriverCommand__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const py_bus_interfaces::msg::DriverCommand *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _DriverCommand__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_DriverCommand(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _DriverCommand__callbacks = {
  "py_bus_interfaces::msg",
  "DriverCommand",
  _DriverCommand__cdr_serialize,
  _DriverCommand__cdr_deserialize,
  _DriverCommand__get_serialized_size,
  _DriverCommand__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _DriverCommand__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_DriverCommand__callbacks,
  get_message_typesupport_handle_function,
  &py_bus_interfaces__msg__DriverCommand__get_type_hash,
  &py_bus_interfaces__msg__DriverCommand__get_type_description,
  &py_bus_interfaces__msg__DriverCommand__get_type_description_sources,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace py_bus_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_py_bus_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<py_bus_interfaces::msg::DriverCommand>()
{
  return &py_bus_interfaces::msg::typesupport_fastrtps_cpp::_DriverCommand__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, py_bus_interfaces, msg, DriverCommand)() {
  return &py_bus_interfaces::msg::typesupport_fastrtps_cpp::_DriverCommand__handle;
}

#ifdef __cplusplus
}
#endif
