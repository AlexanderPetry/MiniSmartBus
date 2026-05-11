// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from py_bus_interfaces:msg/UwbData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/uwb_data.hpp"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__UWB_DATA__BUILDER_HPP_
#define PY_BUS_INTERFACES__MSG__DETAIL__UWB_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "py_bus_interfaces/msg/detail/uwb_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace py_bus_interfaces
{

namespace msg
{

namespace builder
{

class Init_UwbData_ts
{
public:
  explicit Init_UwbData_ts(::py_bus_interfaces::msg::UwbData & msg)
  : msg_(msg)
  {}
  ::py_bus_interfaces::msg::UwbData ts(::py_bus_interfaces::msg::UwbData::_ts_type arg)
  {
    msg_.ts = std::move(arg);
    return std::move(msg_);
  }

private:
  ::py_bus_interfaces::msg::UwbData msg_;
};

class Init_UwbData_y
{
public:
  explicit Init_UwbData_y(::py_bus_interfaces::msg::UwbData & msg)
  : msg_(msg)
  {}
  Init_UwbData_ts y(::py_bus_interfaces::msg::UwbData::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_UwbData_ts(msg_);
  }

private:
  ::py_bus_interfaces::msg::UwbData msg_;
};

class Init_UwbData_x
{
public:
  Init_UwbData_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_UwbData_y x(::py_bus_interfaces::msg::UwbData::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_UwbData_y(msg_);
  }

private:
  ::py_bus_interfaces::msg::UwbData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::py_bus_interfaces::msg::UwbData>()
{
  return py_bus_interfaces::msg::builder::Init_UwbData_x();
}

}  // namespace py_bus_interfaces

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__UWB_DATA__BUILDER_HPP_
