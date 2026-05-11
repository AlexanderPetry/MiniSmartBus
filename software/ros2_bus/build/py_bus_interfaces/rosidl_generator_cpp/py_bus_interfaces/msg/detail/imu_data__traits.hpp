// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from py_bus_interfaces:msg/ImuData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/imu_data.hpp"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__IMU_DATA__TRAITS_HPP_
#define PY_BUS_INTERFACES__MSG__DETAIL__IMU_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "py_bus_interfaces/msg/detail/imu_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace py_bus_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ImuData & msg,
  std::ostream & out)
{
  out << "{";
  // member: sample_id
  {
    out << "sample_id: ";
    rosidl_generator_traits::value_to_yaml(msg.sample_id, out);
    out << ", ";
  }

  // member: accel_x
  {
    out << "accel_x: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_x, out);
    out << ", ";
  }

  // member: accel_y
  {
    out << "accel_y: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_y, out);
    out << ", ";
  }

  // member: accel_z
  {
    out << "accel_z: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_z, out);
    out << ", ";
  }

  // member: temp
  {
    out << "temp: ";
    rosidl_generator_traits::value_to_yaml(msg.temp, out);
    out << ", ";
  }

  // member: gyro_x
  {
    out << "gyro_x: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_x, out);
    out << ", ";
  }

  // member: gyro_y
  {
    out << "gyro_y: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_y, out);
    out << ", ";
  }

  // member: gyro_z
  {
    out << "gyro_z: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_z, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ImuData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: sample_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sample_id: ";
    rosidl_generator_traits::value_to_yaml(msg.sample_id, out);
    out << "\n";
  }

  // member: accel_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accel_x: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_x, out);
    out << "\n";
  }

  // member: accel_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accel_y: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_y, out);
    out << "\n";
  }

  // member: accel_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accel_z: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_z, out);
    out << "\n";
  }

  // member: temp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "temp: ";
    rosidl_generator_traits::value_to_yaml(msg.temp, out);
    out << "\n";
  }

  // member: gyro_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_x: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_x, out);
    out << "\n";
  }

  // member: gyro_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_y: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_y, out);
    out << "\n";
  }

  // member: gyro_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gyro_z: ";
    rosidl_generator_traits::value_to_yaml(msg.gyro_z, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ImuData & msg, bool use_flow_style = false)
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
  const py_bus_interfaces::msg::ImuData & msg,
  std::ostream & out, size_t indentation = 0)
{
  py_bus_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use py_bus_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const py_bus_interfaces::msg::ImuData & msg)
{
  return py_bus_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<py_bus_interfaces::msg::ImuData>()
{
  return "py_bus_interfaces::msg::ImuData";
}

template<>
inline const char * name<py_bus_interfaces::msg::ImuData>()
{
  return "py_bus_interfaces/msg/ImuData";
}

template<>
struct has_fixed_size<py_bus_interfaces::msg::ImuData>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<py_bus_interfaces::msg::ImuData>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<py_bus_interfaces::msg::ImuData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__IMU_DATA__TRAITS_HPP_
