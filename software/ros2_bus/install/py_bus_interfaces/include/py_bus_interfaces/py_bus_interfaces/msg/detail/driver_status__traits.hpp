// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from py_bus_interfaces:msg/DriverStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/driver_status.hpp"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_STATUS__TRAITS_HPP_
#define PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "py_bus_interfaces/msg/detail/driver_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace py_bus_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const DriverStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: source
  {
    out << "source: ";
    rosidl_generator_traits::value_to_yaml(msg.source, out);
    out << ", ";
  }

  // member: rc_steering_us
  {
    out << "rc_steering_us: ";
    rosidl_generator_traits::value_to_yaml(msg.rc_steering_us, out);
    out << ", ";
  }

  // member: rc_throttle_us
  {
    out << "rc_throttle_us: ";
    rosidl_generator_traits::value_to_yaml(msg.rc_throttle_us, out);
    out << ", ";
  }

  // member: commanded_speed_kmh
  {
    out << "commanded_speed_kmh: ";
    rosidl_generator_traits::value_to_yaml(msg.commanded_speed_kmh, out);
    out << ", ";
  }

  // member: commanded_steering_deg
  {
    out << "commanded_steering_deg: ";
    rosidl_generator_traits::value_to_yaml(msg.commanded_steering_deg, out);
    out << ", ";
  }

  // member: applied_speed_kmh
  {
    out << "applied_speed_kmh: ";
    rosidl_generator_traits::value_to_yaml(msg.applied_speed_kmh, out);
    out << ", ";
  }

  // member: applied_steering_deg
  {
    out << "applied_steering_deg: ";
    rosidl_generator_traits::value_to_yaml(msg.applied_steering_deg, out);
    out << ", ";
  }

  // member: batt_voltage
  {
    out << "batt_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.batt_voltage, out);
    out << ", ";
  }

  // member: batt_pct
  {
    out << "batt_pct: ";
    rosidl_generator_traits::value_to_yaml(msg.batt_pct, out);
    out << ", ";
  }

  // member: raw_line
  {
    out << "raw_line: ";
    rosidl_generator_traits::value_to_yaml(msg.raw_line, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DriverStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }

  // member: source
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "source: ";
    rosidl_generator_traits::value_to_yaml(msg.source, out);
    out << "\n";
  }

  // member: rc_steering_us
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rc_steering_us: ";
    rosidl_generator_traits::value_to_yaml(msg.rc_steering_us, out);
    out << "\n";
  }

  // member: rc_throttle_us
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rc_throttle_us: ";
    rosidl_generator_traits::value_to_yaml(msg.rc_throttle_us, out);
    out << "\n";
  }

  // member: commanded_speed_kmh
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "commanded_speed_kmh: ";
    rosidl_generator_traits::value_to_yaml(msg.commanded_speed_kmh, out);
    out << "\n";
  }

  // member: commanded_steering_deg
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "commanded_steering_deg: ";
    rosidl_generator_traits::value_to_yaml(msg.commanded_steering_deg, out);
    out << "\n";
  }

  // member: applied_speed_kmh
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "applied_speed_kmh: ";
    rosidl_generator_traits::value_to_yaml(msg.applied_speed_kmh, out);
    out << "\n";
  }

  // member: applied_steering_deg
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "applied_steering_deg: ";
    rosidl_generator_traits::value_to_yaml(msg.applied_steering_deg, out);
    out << "\n";
  }

  // member: batt_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "batt_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.batt_voltage, out);
    out << "\n";
  }

  // member: batt_pct
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "batt_pct: ";
    rosidl_generator_traits::value_to_yaml(msg.batt_pct, out);
    out << "\n";
  }

  // member: raw_line
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "raw_line: ";
    rosidl_generator_traits::value_to_yaml(msg.raw_line, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DriverStatus & msg, bool use_flow_style = false)
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
  const py_bus_interfaces::msg::DriverStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  py_bus_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use py_bus_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const py_bus_interfaces::msg::DriverStatus & msg)
{
  return py_bus_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<py_bus_interfaces::msg::DriverStatus>()
{
  return "py_bus_interfaces::msg::DriverStatus";
}

template<>
inline const char * name<py_bus_interfaces::msg::DriverStatus>()
{
  return "py_bus_interfaces/msg/DriverStatus";
}

template<>
struct has_fixed_size<py_bus_interfaces::msg::DriverStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<py_bus_interfaces::msg::DriverStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<py_bus_interfaces::msg::DriverStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_STATUS__TRAITS_HPP_
