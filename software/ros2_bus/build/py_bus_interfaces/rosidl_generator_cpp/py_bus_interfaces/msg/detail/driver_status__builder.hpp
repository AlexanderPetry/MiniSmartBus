// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from py_bus_interfaces:msg/DriverStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/driver_status.hpp"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_STATUS__BUILDER_HPP_
#define PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "py_bus_interfaces/msg/detail/driver_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace py_bus_interfaces
{

namespace msg
{

namespace builder
{

class Init_DriverStatus_raw_line
{
public:
  explicit Init_DriverStatus_raw_line(::py_bus_interfaces::msg::DriverStatus & msg)
  : msg_(msg)
  {}
  ::py_bus_interfaces::msg::DriverStatus raw_line(::py_bus_interfaces::msg::DriverStatus::_raw_line_type arg)
  {
    msg_.raw_line = std::move(arg);
    return std::move(msg_);
  }

private:
  ::py_bus_interfaces::msg::DriverStatus msg_;
};

class Init_DriverStatus_batt_pct
{
public:
  explicit Init_DriverStatus_batt_pct(::py_bus_interfaces::msg::DriverStatus & msg)
  : msg_(msg)
  {}
  Init_DriverStatus_raw_line batt_pct(::py_bus_interfaces::msg::DriverStatus::_batt_pct_type arg)
  {
    msg_.batt_pct = std::move(arg);
    return Init_DriverStatus_raw_line(msg_);
  }

private:
  ::py_bus_interfaces::msg::DriverStatus msg_;
};

class Init_DriverStatus_batt_voltage
{
public:
  explicit Init_DriverStatus_batt_voltage(::py_bus_interfaces::msg::DriverStatus & msg)
  : msg_(msg)
  {}
  Init_DriverStatus_batt_pct batt_voltage(::py_bus_interfaces::msg::DriverStatus::_batt_voltage_type arg)
  {
    msg_.batt_voltage = std::move(arg);
    return Init_DriverStatus_batt_pct(msg_);
  }

private:
  ::py_bus_interfaces::msg::DriverStatus msg_;
};

class Init_DriverStatus_applied_steering_deg
{
public:
  explicit Init_DriverStatus_applied_steering_deg(::py_bus_interfaces::msg::DriverStatus & msg)
  : msg_(msg)
  {}
  Init_DriverStatus_batt_voltage applied_steering_deg(::py_bus_interfaces::msg::DriverStatus::_applied_steering_deg_type arg)
  {
    msg_.applied_steering_deg = std::move(arg);
    return Init_DriverStatus_batt_voltage(msg_);
  }

private:
  ::py_bus_interfaces::msg::DriverStatus msg_;
};

class Init_DriverStatus_applied_speed_kmh
{
public:
  explicit Init_DriverStatus_applied_speed_kmh(::py_bus_interfaces::msg::DriverStatus & msg)
  : msg_(msg)
  {}
  Init_DriverStatus_applied_steering_deg applied_speed_kmh(::py_bus_interfaces::msg::DriverStatus::_applied_speed_kmh_type arg)
  {
    msg_.applied_speed_kmh = std::move(arg);
    return Init_DriverStatus_applied_steering_deg(msg_);
  }

private:
  ::py_bus_interfaces::msg::DriverStatus msg_;
};

class Init_DriverStatus_commanded_steering_deg
{
public:
  explicit Init_DriverStatus_commanded_steering_deg(::py_bus_interfaces::msg::DriverStatus & msg)
  : msg_(msg)
  {}
  Init_DriverStatus_applied_speed_kmh commanded_steering_deg(::py_bus_interfaces::msg::DriverStatus::_commanded_steering_deg_type arg)
  {
    msg_.commanded_steering_deg = std::move(arg);
    return Init_DriverStatus_applied_speed_kmh(msg_);
  }

private:
  ::py_bus_interfaces::msg::DriverStatus msg_;
};

class Init_DriverStatus_commanded_speed_kmh
{
public:
  explicit Init_DriverStatus_commanded_speed_kmh(::py_bus_interfaces::msg::DriverStatus & msg)
  : msg_(msg)
  {}
  Init_DriverStatus_commanded_steering_deg commanded_speed_kmh(::py_bus_interfaces::msg::DriverStatus::_commanded_speed_kmh_type arg)
  {
    msg_.commanded_speed_kmh = std::move(arg);
    return Init_DriverStatus_commanded_steering_deg(msg_);
  }

private:
  ::py_bus_interfaces::msg::DriverStatus msg_;
};

class Init_DriverStatus_rc_throttle_us
{
public:
  explicit Init_DriverStatus_rc_throttle_us(::py_bus_interfaces::msg::DriverStatus & msg)
  : msg_(msg)
  {}
  Init_DriverStatus_commanded_speed_kmh rc_throttle_us(::py_bus_interfaces::msg::DriverStatus::_rc_throttle_us_type arg)
  {
    msg_.rc_throttle_us = std::move(arg);
    return Init_DriverStatus_commanded_speed_kmh(msg_);
  }

private:
  ::py_bus_interfaces::msg::DriverStatus msg_;
};

class Init_DriverStatus_rc_steering_us
{
public:
  explicit Init_DriverStatus_rc_steering_us(::py_bus_interfaces::msg::DriverStatus & msg)
  : msg_(msg)
  {}
  Init_DriverStatus_rc_throttle_us rc_steering_us(::py_bus_interfaces::msg::DriverStatus::_rc_steering_us_type arg)
  {
    msg_.rc_steering_us = std::move(arg);
    return Init_DriverStatus_rc_throttle_us(msg_);
  }

private:
  ::py_bus_interfaces::msg::DriverStatus msg_;
};

class Init_DriverStatus_source
{
public:
  explicit Init_DriverStatus_source(::py_bus_interfaces::msg::DriverStatus & msg)
  : msg_(msg)
  {}
  Init_DriverStatus_rc_steering_us source(::py_bus_interfaces::msg::DriverStatus::_source_type arg)
  {
    msg_.source = std::move(arg);
    return Init_DriverStatus_rc_steering_us(msg_);
  }

private:
  ::py_bus_interfaces::msg::DriverStatus msg_;
};

class Init_DriverStatus_stamp
{
public:
  Init_DriverStatus_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DriverStatus_source stamp(::py_bus_interfaces::msg::DriverStatus::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_DriverStatus_source(msg_);
  }

private:
  ::py_bus_interfaces::msg::DriverStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::py_bus_interfaces::msg::DriverStatus>()
{
  return py_bus_interfaces::msg::builder::Init_DriverStatus_stamp();
}

}  // namespace py_bus_interfaces

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_STATUS__BUILDER_HPP_
