// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from py_bus_interfaces:msg/DriverCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/driver_command.hpp"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_COMMAND__STRUCT_HPP_
#define PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__py_bus_interfaces__msg__DriverCommand __attribute__((deprecated))
#else
# define DEPRECATED__py_bus_interfaces__msg__DriverCommand __declspec(deprecated)
#endif

namespace py_bus_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DriverCommand_
{
  using Type = DriverCommand_<ContainerAllocator>;

  explicit DriverCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->speed_kmh = 0.0f;
      this->steering_deg = 0.0f;
    }
  }

  explicit DriverCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->speed_kmh = 0.0f;
      this->steering_deg = 0.0f;
    }
  }

  // field types and members
  using _speed_kmh_type =
    float;
  _speed_kmh_type speed_kmh;
  using _steering_deg_type =
    float;
  _steering_deg_type steering_deg;

  // setters for named parameter idiom
  Type & set__speed_kmh(
    const float & _arg)
  {
    this->speed_kmh = _arg;
    return *this;
  }
  Type & set__steering_deg(
    const float & _arg)
  {
    this->steering_deg = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    py_bus_interfaces::msg::DriverCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const py_bus_interfaces::msg::DriverCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<py_bus_interfaces::msg::DriverCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<py_bus_interfaces::msg::DriverCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      py_bus_interfaces::msg::DriverCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<py_bus_interfaces::msg::DriverCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      py_bus_interfaces::msg::DriverCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<py_bus_interfaces::msg::DriverCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<py_bus_interfaces::msg::DriverCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<py_bus_interfaces::msg::DriverCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__py_bus_interfaces__msg__DriverCommand
    std::shared_ptr<py_bus_interfaces::msg::DriverCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__py_bus_interfaces__msg__DriverCommand
    std::shared_ptr<py_bus_interfaces::msg::DriverCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DriverCommand_ & other) const
  {
    if (this->speed_kmh != other.speed_kmh) {
      return false;
    }
    if (this->steering_deg != other.steering_deg) {
      return false;
    }
    return true;
  }
  bool operator!=(const DriverCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DriverCommand_

// alias to use template instance with default allocator
using DriverCommand =
  py_bus_interfaces::msg::DriverCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace py_bus_interfaces

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_COMMAND__STRUCT_HPP_
