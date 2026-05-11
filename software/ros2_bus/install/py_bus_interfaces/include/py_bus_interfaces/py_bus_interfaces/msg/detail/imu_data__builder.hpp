// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from py_bus_interfaces:msg/ImuData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/imu_data.hpp"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__IMU_DATA__BUILDER_HPP_
#define PY_BUS_INTERFACES__MSG__DETAIL__IMU_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "py_bus_interfaces/msg/detail/imu_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace py_bus_interfaces
{

namespace msg
{

namespace builder
{

class Init_ImuData_gyro_z
{
public:
  explicit Init_ImuData_gyro_z(::py_bus_interfaces::msg::ImuData & msg)
  : msg_(msg)
  {}
  ::py_bus_interfaces::msg::ImuData gyro_z(::py_bus_interfaces::msg::ImuData::_gyro_z_type arg)
  {
    msg_.gyro_z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::py_bus_interfaces::msg::ImuData msg_;
};

class Init_ImuData_gyro_y
{
public:
  explicit Init_ImuData_gyro_y(::py_bus_interfaces::msg::ImuData & msg)
  : msg_(msg)
  {}
  Init_ImuData_gyro_z gyro_y(::py_bus_interfaces::msg::ImuData::_gyro_y_type arg)
  {
    msg_.gyro_y = std::move(arg);
    return Init_ImuData_gyro_z(msg_);
  }

private:
  ::py_bus_interfaces::msg::ImuData msg_;
};

class Init_ImuData_gyro_x
{
public:
  explicit Init_ImuData_gyro_x(::py_bus_interfaces::msg::ImuData & msg)
  : msg_(msg)
  {}
  Init_ImuData_gyro_y gyro_x(::py_bus_interfaces::msg::ImuData::_gyro_x_type arg)
  {
    msg_.gyro_x = std::move(arg);
    return Init_ImuData_gyro_y(msg_);
  }

private:
  ::py_bus_interfaces::msg::ImuData msg_;
};

class Init_ImuData_temp
{
public:
  explicit Init_ImuData_temp(::py_bus_interfaces::msg::ImuData & msg)
  : msg_(msg)
  {}
  Init_ImuData_gyro_x temp(::py_bus_interfaces::msg::ImuData::_temp_type arg)
  {
    msg_.temp = std::move(arg);
    return Init_ImuData_gyro_x(msg_);
  }

private:
  ::py_bus_interfaces::msg::ImuData msg_;
};

class Init_ImuData_accel_z
{
public:
  explicit Init_ImuData_accel_z(::py_bus_interfaces::msg::ImuData & msg)
  : msg_(msg)
  {}
  Init_ImuData_temp accel_z(::py_bus_interfaces::msg::ImuData::_accel_z_type arg)
  {
    msg_.accel_z = std::move(arg);
    return Init_ImuData_temp(msg_);
  }

private:
  ::py_bus_interfaces::msg::ImuData msg_;
};

class Init_ImuData_accel_y
{
public:
  explicit Init_ImuData_accel_y(::py_bus_interfaces::msg::ImuData & msg)
  : msg_(msg)
  {}
  Init_ImuData_accel_z accel_y(::py_bus_interfaces::msg::ImuData::_accel_y_type arg)
  {
    msg_.accel_y = std::move(arg);
    return Init_ImuData_accel_z(msg_);
  }

private:
  ::py_bus_interfaces::msg::ImuData msg_;
};

class Init_ImuData_accel_x
{
public:
  explicit Init_ImuData_accel_x(::py_bus_interfaces::msg::ImuData & msg)
  : msg_(msg)
  {}
  Init_ImuData_accel_y accel_x(::py_bus_interfaces::msg::ImuData::_accel_x_type arg)
  {
    msg_.accel_x = std::move(arg);
    return Init_ImuData_accel_y(msg_);
  }

private:
  ::py_bus_interfaces::msg::ImuData msg_;
};

class Init_ImuData_sample_id
{
public:
  Init_ImuData_sample_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ImuData_accel_x sample_id(::py_bus_interfaces::msg::ImuData::_sample_id_type arg)
  {
    msg_.sample_id = std::move(arg);
    return Init_ImuData_accel_x(msg_);
  }

private:
  ::py_bus_interfaces::msg::ImuData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::py_bus_interfaces::msg::ImuData>()
{
  return py_bus_interfaces::msg::builder::Init_ImuData_sample_id();
}

}  // namespace py_bus_interfaces

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__IMU_DATA__BUILDER_HPP_
