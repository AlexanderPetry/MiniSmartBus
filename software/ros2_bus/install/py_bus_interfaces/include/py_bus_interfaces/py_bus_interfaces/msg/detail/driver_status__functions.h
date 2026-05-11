// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from py_bus_interfaces:msg/DriverStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "py_bus_interfaces/msg/driver_status.h"


#ifndef PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_STATUS__FUNCTIONS_H_
#define PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_STATUS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "py_bus_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "py_bus_interfaces/msg/detail/driver_status__struct.h"

/// Initialize msg/DriverStatus message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * py_bus_interfaces__msg__DriverStatus
 * )) before or use
 * py_bus_interfaces__msg__DriverStatus__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
bool
py_bus_interfaces__msg__DriverStatus__init(py_bus_interfaces__msg__DriverStatus * msg);

/// Finalize msg/DriverStatus message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
void
py_bus_interfaces__msg__DriverStatus__fini(py_bus_interfaces__msg__DriverStatus * msg);

/// Create msg/DriverStatus message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * py_bus_interfaces__msg__DriverStatus__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
py_bus_interfaces__msg__DriverStatus *
py_bus_interfaces__msg__DriverStatus__create(void);

/// Destroy msg/DriverStatus message.
/**
 * It calls
 * py_bus_interfaces__msg__DriverStatus__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
void
py_bus_interfaces__msg__DriverStatus__destroy(py_bus_interfaces__msg__DriverStatus * msg);

/// Check for msg/DriverStatus message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
bool
py_bus_interfaces__msg__DriverStatus__are_equal(const py_bus_interfaces__msg__DriverStatus * lhs, const py_bus_interfaces__msg__DriverStatus * rhs);

/// Copy a msg/DriverStatus message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
bool
py_bus_interfaces__msg__DriverStatus__copy(
  const py_bus_interfaces__msg__DriverStatus * input,
  py_bus_interfaces__msg__DriverStatus * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
const rosidl_type_hash_t *
py_bus_interfaces__msg__DriverStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
const rosidl_runtime_c__type_description__TypeDescription *
py_bus_interfaces__msg__DriverStatus__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
const rosidl_runtime_c__type_description__TypeSource *
py_bus_interfaces__msg__DriverStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
const rosidl_runtime_c__type_description__TypeSource__Sequence *
py_bus_interfaces__msg__DriverStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/DriverStatus messages.
/**
 * It allocates the memory for the number of elements and calls
 * py_bus_interfaces__msg__DriverStatus__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
bool
py_bus_interfaces__msg__DriverStatus__Sequence__init(py_bus_interfaces__msg__DriverStatus__Sequence * array, size_t size);

/// Finalize array of msg/DriverStatus messages.
/**
 * It calls
 * py_bus_interfaces__msg__DriverStatus__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
void
py_bus_interfaces__msg__DriverStatus__Sequence__fini(py_bus_interfaces__msg__DriverStatus__Sequence * array);

/// Create array of msg/DriverStatus messages.
/**
 * It allocates the memory for the array and calls
 * py_bus_interfaces__msg__DriverStatus__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
py_bus_interfaces__msg__DriverStatus__Sequence *
py_bus_interfaces__msg__DriverStatus__Sequence__create(size_t size);

/// Destroy array of msg/DriverStatus messages.
/**
 * It calls
 * py_bus_interfaces__msg__DriverStatus__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
void
py_bus_interfaces__msg__DriverStatus__Sequence__destroy(py_bus_interfaces__msg__DriverStatus__Sequence * array);

/// Check for msg/DriverStatus message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
bool
py_bus_interfaces__msg__DriverStatus__Sequence__are_equal(const py_bus_interfaces__msg__DriverStatus__Sequence * lhs, const py_bus_interfaces__msg__DriverStatus__Sequence * rhs);

/// Copy an array of msg/DriverStatus messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_py_bus_interfaces
bool
py_bus_interfaces__msg__DriverStatus__Sequence__copy(
  const py_bus_interfaces__msg__DriverStatus__Sequence * input,
  py_bus_interfaces__msg__DriverStatus__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // PY_BUS_INTERFACES__MSG__DETAIL__DRIVER_STATUS__FUNCTIONS_H_
