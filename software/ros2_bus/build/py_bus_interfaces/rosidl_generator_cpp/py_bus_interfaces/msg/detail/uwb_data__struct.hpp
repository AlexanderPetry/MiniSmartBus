// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from py_bus_interfaces:msg/UwbData.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/uwb_data.hpp"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__UWB_DATA__STRUCT_HPP_
#define PY_BUS_INTERFACES__MSG__DETAIL__UWB_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__py_bus_interfaces__msg__UwbData __attribute__((deprecated))
#else
# define DEPRECATED__py_bus_interfaces__msg__UwbData __declspec(deprecated)
#endif

namespace py_bus_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct UwbData_
{
  using Type = UwbData_<ContainerAllocator>;

  explicit UwbData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0.0f;
      this->y = 0.0f;
      this->ts = 0.0;
    }
  }

  explicit UwbData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0.0f;
      this->y = 0.0f;
      this->ts = 0.0;
    }
  }

  // field types and members
  using _x_type =
    float;
  _x_type x;
  using _y_type =
    float;
  _y_type y;
  using _ts_type =
    double;
  _ts_type ts;

  // setters for named parameter idiom
  Type & set__x(
    const float & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const float & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__ts(
    const double & _arg)
  {
    this->ts = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    py_bus_interfaces::msg::UwbData_<ContainerAllocator> *;
  using ConstRawPtr =
    const py_bus_interfaces::msg::UwbData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<py_bus_interfaces::msg::UwbData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<py_bus_interfaces::msg::UwbData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      py_bus_interfaces::msg::UwbData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<py_bus_interfaces::msg::UwbData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      py_bus_interfaces::msg::UwbData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<py_bus_interfaces::msg::UwbData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<py_bus_interfaces::msg::UwbData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<py_bus_interfaces::msg::UwbData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__py_bus_interfaces__msg__UwbData
    std::shared_ptr<py_bus_interfaces::msg::UwbData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__py_bus_interfaces__msg__UwbData
    std::shared_ptr<py_bus_interfaces::msg::UwbData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const UwbData_ & other) const
  {
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->ts != other.ts) {
      return false;
    }
    return true;
  }
  bool operator!=(const UwbData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct UwbData_

// alias to use template instance with default allocator
using UwbData =
  py_bus_interfaces::msg::UwbData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace py_bus_interfaces

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__UWB_DATA__STRUCT_HPP_
