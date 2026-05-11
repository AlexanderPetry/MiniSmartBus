// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from py_bus_interfaces:msg/DriverStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/driver_status.hpp"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_STATUS__STRUCT_HPP_
#define PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__py_bus_interfaces__msg__DriverStatus __attribute__((deprecated))
#else
# define DEPRECATED__py_bus_interfaces__msg__DriverStatus __declspec(deprecated)
#endif

namespace py_bus_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DriverStatus_
{
  using Type = DriverStatus_<ContainerAllocator>;

  explicit DriverStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->source = "";
      this->rc_steering_us = 0l;
      this->rc_throttle_us = 0l;
      this->commanded_speed_kmh = 0.0f;
      this->commanded_steering_deg = 0.0f;
      this->applied_speed_kmh = 0.0f;
      this->applied_steering_deg = 0.0f;
      this->batt_voltage = 0.0f;
      this->batt_pct = 0.0f;
      this->raw_line = "";
    }
  }

  explicit DriverStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init),
    source(_alloc),
    raw_line(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->source = "";
      this->rc_steering_us = 0l;
      this->rc_throttle_us = 0l;
      this->commanded_speed_kmh = 0.0f;
      this->commanded_steering_deg = 0.0f;
      this->applied_speed_kmh = 0.0f;
      this->applied_steering_deg = 0.0f;
      this->batt_voltage = 0.0f;
      this->batt_pct = 0.0f;
      this->raw_line = "";
    }
  }

  // field types and members
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _source_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _source_type source;
  using _rc_steering_us_type =
    int32_t;
  _rc_steering_us_type rc_steering_us;
  using _rc_throttle_us_type =
    int32_t;
  _rc_throttle_us_type rc_throttle_us;
  using _commanded_speed_kmh_type =
    float;
  _commanded_speed_kmh_type commanded_speed_kmh;
  using _commanded_steering_deg_type =
    float;
  _commanded_steering_deg_type commanded_steering_deg;
  using _applied_speed_kmh_type =
    float;
  _applied_speed_kmh_type applied_speed_kmh;
  using _applied_steering_deg_type =
    float;
  _applied_steering_deg_type applied_steering_deg;
  using _batt_voltage_type =
    float;
  _batt_voltage_type batt_voltage;
  using _batt_pct_type =
    float;
  _batt_pct_type batt_pct;
  using _raw_line_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _raw_line_type raw_line;

  // setters for named parameter idiom
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__source(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->source = _arg;
    return *this;
  }
  Type & set__rc_steering_us(
    const int32_t & _arg)
  {
    this->rc_steering_us = _arg;
    return *this;
  }
  Type & set__rc_throttle_us(
    const int32_t & _arg)
  {
    this->rc_throttle_us = _arg;
    return *this;
  }
  Type & set__commanded_speed_kmh(
    const float & _arg)
  {
    this->commanded_speed_kmh = _arg;
    return *this;
  }
  Type & set__commanded_steering_deg(
    const float & _arg)
  {
    this->commanded_steering_deg = _arg;
    return *this;
  }
  Type & set__applied_speed_kmh(
    const float & _arg)
  {
    this->applied_speed_kmh = _arg;
    return *this;
  }
  Type & set__applied_steering_deg(
    const float & _arg)
  {
    this->applied_steering_deg = _arg;
    return *this;
  }
  Type & set__batt_voltage(
    const float & _arg)
  {
    this->batt_voltage = _arg;
    return *this;
  }
  Type & set__batt_pct(
    const float & _arg)
  {
    this->batt_pct = _arg;
    return *this;
  }
  Type & set__raw_line(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->raw_line = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    py_bus_interfaces::msg::DriverStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const py_bus_interfaces::msg::DriverStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<py_bus_interfaces::msg::DriverStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<py_bus_interfaces::msg::DriverStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      py_bus_interfaces::msg::DriverStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<py_bus_interfaces::msg::DriverStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      py_bus_interfaces::msg::DriverStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<py_bus_interfaces::msg::DriverStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<py_bus_interfaces::msg::DriverStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<py_bus_interfaces::msg::DriverStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__py_bus_interfaces__msg__DriverStatus
    std::shared_ptr<py_bus_interfaces::msg::DriverStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__py_bus_interfaces__msg__DriverStatus
    std::shared_ptr<py_bus_interfaces::msg::DriverStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DriverStatus_ & other) const
  {
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->source != other.source) {
      return false;
    }
    if (this->rc_steering_us != other.rc_steering_us) {
      return false;
    }
    if (this->rc_throttle_us != other.rc_throttle_us) {
      return false;
    }
    if (this->commanded_speed_kmh != other.commanded_speed_kmh) {
      return false;
    }
    if (this->commanded_steering_deg != other.commanded_steering_deg) {
      return false;
    }
    if (this->applied_speed_kmh != other.applied_speed_kmh) {
      return false;
    }
    if (this->applied_steering_deg != other.applied_steering_deg) {
      return false;
    }
    if (this->batt_voltage != other.batt_voltage) {
      return false;
    }
    if (this->batt_pct != other.batt_pct) {
      return false;
    }
    if (this->raw_line != other.raw_line) {
      return false;
    }
    return true;
  }
  bool operator!=(const DriverStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DriverStatus_

// alias to use template instance with default allocator
using DriverStatus =
  py_bus_interfaces::msg::DriverStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace py_bus_interfaces

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_STATUS__STRUCT_HPP_
