// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from py_bus_interfaces:msg/DriverCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/driver_command.hpp"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_COMMAND__TRAITS_HPP_
#define PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "py_bus_interfaces/msg/detail/driver_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace py_bus_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const DriverCommand & msg,
  std::ostream & out)
{
  out << "{";
  // member: speed_kmh
  {
    out << "speed_kmh: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_kmh, out);
    out << ", ";
  }

  // member: steering_deg
  {
    out << "steering_deg: ";
    rosidl_generator_traits::value_to_yaml(msg.steering_deg, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DriverCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: speed_kmh
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed_kmh: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_kmh, out);
    out << "\n";
  }

  // member: steering_deg
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "steering_deg: ";
    rosidl_generator_traits::value_to_yaml(msg.steering_deg, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DriverCommand & msg, bool use_flow_style = false)
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
  const py_bus_interfaces::msg::DriverCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  py_bus_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use py_bus_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const py_bus_interfaces::msg::DriverCommand & msg)
{
  return py_bus_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<py_bus_interfaces::msg::DriverCommand>()
{
  return "py_bus_interfaces::msg::DriverCommand";
}

template<>
inline const char * name<py_bus_interfaces::msg::DriverCommand>()
{
  return "py_bus_interfaces/msg/DriverCommand";
}

template<>
struct has_fixed_size<py_bus_interfaces::msg::DriverCommand>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<py_bus_interfaces::msg::DriverCommand>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<py_bus_interfaces::msg::DriverCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_COMMAND__TRAITS_HPP_
