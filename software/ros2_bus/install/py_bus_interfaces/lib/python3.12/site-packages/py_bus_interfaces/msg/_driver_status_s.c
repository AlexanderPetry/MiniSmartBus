// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from py_bus_interfaces:msg/DriverStatus.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "py_bus_interfaces/msg/detail/driver_status__struct.h"
#include "py_bus_interfaces/msg/detail/driver_status__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool builtin_interfaces__msg__time__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * builtin_interfaces__msg__time__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool py_bus_interfaces__msg__driver_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
    if (class_attr == NULL) {
      return false;
    }
    PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
    if (name_attr == NULL) {
      Py_DECREF(class_attr);
      return false;
    }
    PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
    if (module_attr == NULL) {
      Py_DECREF(name_attr);
      Py_DECREF(class_attr);
      return false;
    }

    // PyUnicode_1BYTE_DATA is just a cast
    assert(strncmp("py_bus_interfaces.msg._driver_status", (char *)PyUnicode_1BYTE_DATA(module_attr), 36) == 0);
    assert(strncmp("DriverStatus", (char *)PyUnicode_1BYTE_DATA(name_attr), 12) == 0);

    Py_DECREF(module_attr);
    Py_DECREF(name_attr);
    Py_DECREF(class_attr);
  }
  py_bus_interfaces__msg__DriverStatus * ros_message = _ros_message;
  {  // stamp
    PyObject * field = PyObject_GetAttrString(_pymsg, "stamp");
    if (!field) {
      return false;
    }
    if (!builtin_interfaces__msg__time__convert_from_py(field, &ros_message->stamp)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // source
    PyObject * field = PyObject_GetAttrString(_pymsg, "source");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->source, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // rc_steering_us
    PyObject * field = PyObject_GetAttrString(_pymsg, "rc_steering_us");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->rc_steering_us = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // rc_throttle_us
    PyObject * field = PyObject_GetAttrString(_pymsg, "rc_throttle_us");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->rc_throttle_us = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // commanded_speed_kmh
    PyObject * field = PyObject_GetAttrString(_pymsg, "commanded_speed_kmh");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->commanded_speed_kmh = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // commanded_steering_deg
    PyObject * field = PyObject_GetAttrString(_pymsg, "commanded_steering_deg");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->commanded_steering_deg = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // applied_speed_kmh
    PyObject * field = PyObject_GetAttrString(_pymsg, "applied_speed_kmh");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->applied_speed_kmh = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // applied_steering_deg
    PyObject * field = PyObject_GetAttrString(_pymsg, "applied_steering_deg");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->applied_steering_deg = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // batt_voltage
    PyObject * field = PyObject_GetAttrString(_pymsg, "batt_voltage");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->batt_voltage = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // batt_pct
    PyObject * field = PyObject_GetAttrString(_pymsg, "batt_pct");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->batt_pct = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // raw_line
    PyObject * field = PyObject_GetAttrString(_pymsg, "raw_line");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->raw_line, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * py_bus_interfaces__msg__driver_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of DriverStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("py_bus_interfaces.msg._driver_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "DriverStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  py_bus_interfaces__msg__DriverStatus * ros_message = (py_bus_interfaces__msg__DriverStatus *)raw_ros_message;
  {  // stamp
    PyObject * field = NULL;
    field = builtin_interfaces__msg__time__convert_to_py(&ros_message->stamp);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "stamp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // source
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->source.data,
      strlen(ros_message->source.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "source", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rc_steering_us
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->rc_steering_us);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rc_steering_us", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rc_throttle_us
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->rc_throttle_us);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rc_throttle_us", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // commanded_speed_kmh
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->commanded_speed_kmh);
    {
      int rc = PyObject_SetAttrString(_pymessage, "commanded_speed_kmh", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // commanded_steering_deg
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->commanded_steering_deg);
    {
      int rc = PyObject_SetAttrString(_pymessage, "commanded_steering_deg", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // applied_speed_kmh
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->applied_speed_kmh);
    {
      int rc = PyObject_SetAttrString(_pymessage, "applied_speed_kmh", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // applied_steering_deg
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->applied_steering_deg);
    {
      int rc = PyObject_SetAttrString(_pymessage, "applied_steering_deg", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // batt_voltage
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->batt_voltage);
    {
      int rc = PyObject_SetAttrString(_pymessage, "batt_voltage", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // batt_pct
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->batt_pct);
    {
      int rc = PyObject_SetAttrString(_pymessage, "batt_pct", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // raw_line
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->raw_line.data,
      strlen(ros_message->raw_line.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "raw_line", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
