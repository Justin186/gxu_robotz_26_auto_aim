// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from sp_msgs:msg/RMUCRobotControl.idl
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
#include "sp_msgs/msg/detail/rmuc_robot_control__struct.h"
#include "sp_msgs/msg/detail/rmuc_robot_control__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool sp_msgs__msg__rmuc_robot_control__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[49];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("sp_msgs.msg._rmuc_robot_control.RMUCRobotControl", full_classname_dest, 48) == 0);
  }
  sp_msgs__msg__RMUCRobotControl * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // stop_gimbal_scan
    PyObject * field = PyObject_GetAttrString(_pymsg, "stop_gimbal_scan");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->stop_gimbal_scan = (Py_True == field);
    Py_DECREF(field);
  }
  {  // chassis_spin
    PyObject * field = PyObject_GetAttrString(_pymsg, "chassis_spin");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->chassis_spin = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * sp_msgs__msg__rmuc_robot_control__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of RMUCRobotControl */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("sp_msgs.msg._rmuc_robot_control");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "RMUCRobotControl");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  sp_msgs__msg__RMUCRobotControl * ros_message = (sp_msgs__msg__RMUCRobotControl *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "header", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // stop_gimbal_scan
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->stop_gimbal_scan ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "stop_gimbal_scan", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // chassis_spin
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->chassis_spin ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "chassis_spin", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
