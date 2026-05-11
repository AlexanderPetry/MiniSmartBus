// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from py_bus_interfaces:msg/UwbData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/uwb_data.hpp"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__UWB_DATA__TRAITS_HPP_
#define PY_BUS_INTERFACES__MSG__DETAIL__UWB_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "py_bus_interfaces/msg/detail/uwb_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace py_bus_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const UwbData & msg,
  std::ostream & out)
{
  out << "{";
  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: ts
  {
    out << "ts: ";
    rosidl_generator_traits::value_to_yaml(msg.ts, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const UwbData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: ts
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ts: ";
    rosidl_generator_traits::value_to_yaml(msg.ts, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const UwbData & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace py_bus_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use py_bus_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const py_bus_interfaces::msg::UwbData & msg,
  std::ostream & out, size_t indentation = 0)
{
  py_bus_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use py_bus_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const py_bus_interfaces::msg::UwbData & msg)
{
  return py_bus_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<py_bus_interfaces::msg::UwbData>()
{
  return "py_bus_interfaces::msg::UwbData";
}

template<>
inline const char * name<py_bus_interfaces::msg::UwbData>()
{
  return "py_bus_interfaces/msg/UwbData";
}

template<>
struct has_fixed_size<py_bus_interfaces::msg::UwbData>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<py_bus_interfaces::msg::UwbData>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<py_bus_interfaces::msg::UwbData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__UWB_DATA__TRAITS_HPP_
