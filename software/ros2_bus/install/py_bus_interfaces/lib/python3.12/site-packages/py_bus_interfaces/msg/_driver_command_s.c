// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from py_bus_interfaces:msg/DriverCommand.idl
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
#include "py_bus_interfaces/msg/detail/driver_command__struct.h"
#include "py_bus_interfaces/msg/detail/driver_command__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool py_bus_interfaces__msg__driver_command__convert_from_py(PyObject * _pymsg, void * _ros_message)
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
    assert(strncmp("py_bus_interfaces.msg._driver_command", (char *)PyUnicode_1BYTE_DATA(module_attr), 37) == 0);
    assert(strncmp("DriverCommand", (char *)PyUnicode_1BYTE_DATA(name_attr), 13) == 0);

    Py_DECREF(module_attr);
    Py_DECREF(name_attr);
    Py_DECREF(class_attr);
  }
  py_bus_interfaces__msg__DriverCommand * ros_message = _ros_message;
  {  // speed_kmh
    PyObject * field = PyObject_GetAttrString(_pymsg, "speed_kmh");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->speed_kmh = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // steering_deg
    PyObject * field = PyObject_GetAttrString(_pymsg, "steering_deg");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->steering_deg = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * py_bus_interfaces__msg__driver_command__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of DriverCommand */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("py_bus_interfaces.msg._driver_command");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "DriverCommand");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  py_bus_interfaces__msg__DriverCommand * ros_message = (py_bus_interfaces__msg__DriverCommand *)raw_ros_message;
  {  // speed_kmh
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->speed_kmh);
    {
      int rc = PyObject_SetAttrString(_pymessage, "speed_kmh", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // steering_deg
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->steering_deg);
    {
      int rc = PyObject_SetAttrString(_pymessage, "steering_deg", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
