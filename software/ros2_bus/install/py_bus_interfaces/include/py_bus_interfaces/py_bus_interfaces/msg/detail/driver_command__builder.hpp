// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from py_bus_interfaces:msg/DriverCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/driver_command.hpp"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_COMMAND__BUILDER_HPP_
#define PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "py_bus_interfaces/msg/detail/driver_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace py_bus_interfaces
{

namespace msg
{

namespace builder
{

class Init_DriverCommand_steering_deg
{
public:
  explicit Init_DriverCommand_steering_deg(::py_bus_interfaces::msg::DriverCommand & msg)
  : msg_(msg)
  {}
  ::py_bus_interfaces::msg::DriverCommand steering_deg(::py_bus_interfaces::msg::DriverCommand::_steering_deg_type arg)
  {
    msg_.steering_deg = std::move(arg);
    return std::move(msg_);
  }

private:
  ::py_bus_interfaces::msg::DriverCommand msg_;
};

class Init_DriverCommand_speed_kmh
{
public:
  Init_DriverCommand_speed_kmh()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DriverCommand_steering_deg speed_kmh(::py_bus_interfaces::msg::DriverCommand::_speed_kmh_type arg)
  {
    msg_.speed_kmh = std::move(arg);
    return Init_DriverCommand_steering_deg(msg_);
  }

private:
  ::py_bus_interfaces::msg::DriverCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::py_bus_interfaces::msg::DriverCommand>()
{
  return py_bus_interfaces::msg::builder::Init_DriverCommand_speed_kmh();
}

}  // namespace py_bus_interfaces

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_COMMAND__BUILDER_HPP_
