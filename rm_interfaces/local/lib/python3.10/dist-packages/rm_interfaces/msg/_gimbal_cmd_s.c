// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from rm_interfaces:msg/GimbalCmd.idl
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
#include "rm_interfaces/msg/detail/gimbal_cmd__struct.h"
#include "rm_interfaces/msg/detail/gimbal_cmd__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool rm_interfaces__msg__gimbal_cmd__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[40];
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
    assert(strncmp("rm_interfaces.msg._gimbal_cmd.GimbalCmd", full_classname_dest, 39) == 0);
  }
  rm_interfaces__msg__GimbalCmd * ros_message = _ros_message;
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
  {  // pitch
    PyObject * field = PyObject_GetAttrString(_pymsg, "pitch");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->pitch = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // yaw
    PyObject * field = PyObject_GetAttrString(_pymsg, "yaw");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->yaw = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // yaw_diff
    PyObject * field = PyObject_GetAttrString(_pymsg, "yaw_diff");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->yaw_diff = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // pitch_diff
    PyObject * field = PyObject_GetAttrString(_pymsg, "pitch_diff");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->pitch_diff = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // distance
    PyObject * field = PyObject_GetAttrString(_pymsg, "distance");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->distance = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // fire_advice
    PyObject * field = PyObject_GetAttrString(_pymsg, "fire_advice");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->fire_advice = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * rm_interfaces__msg__gimbal_cmd__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GimbalCmd */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("rm_interfaces.msg._gimbal_cmd");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GimbalCmd");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  rm_interfaces__msg__GimbalCmd * ros_message = (rm_interfaces__msg__GimbalCmd *)raw_ros_message;
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
  {  // pitch
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->pitch);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pitch", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // yaw
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->yaw);
    {
      int rc = PyObject_SetAttrString(_pymessage, "yaw", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // yaw_diff
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->yaw_diff);
    {
      int rc = PyObject_SetAttrString(_pymessage, "yaw_diff", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pitch_diff
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->pitch_diff);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pitch_diff", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // distance
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->distance);
    {
      int rc = PyObject_SetAttrString(_pymessage, "distance", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // fire_advice
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->fire_advice ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "fire_advice", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
