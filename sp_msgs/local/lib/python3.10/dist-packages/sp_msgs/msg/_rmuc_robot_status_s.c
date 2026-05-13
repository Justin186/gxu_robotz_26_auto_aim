// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from sp_msgs:msg/RMUCRobotStatus.idl
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
#include "sp_msgs/msg/detail/rmuc_robot_status__struct.h"
#include "sp_msgs/msg/detail/rmuc_robot_status__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool sp_msgs__msg__rmuc_robot_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[47];
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
    assert(strncmp("sp_msgs.msg._rmuc_robot_status.RMUCRobotStatus", full_classname_dest, 46) == 0);
  }
  sp_msgs__msg__RMUCRobotStatus * ros_message = _ros_message;
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
  {  // current_hp
    PyObject * field = PyObject_GetAttrString(_pymsg, "current_hp");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->current_hp = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // shooter_heat
    PyObject * field = PyObject_GetAttrString(_pymsg, "shooter_heat");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->shooter_heat = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // ammo_allow
    PyObject * field = PyObject_GetAttrString(_pymsg, "ammo_allow");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->ammo_allow = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // outpost_hp
    PyObject * field = PyObject_GetAttrString(_pymsg, "outpost_hp");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->outpost_hp = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // base_hp
    PyObject * field = PyObject_GetAttrString(_pymsg, "base_hp");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->base_hp = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // enemy_outpost_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "enemy_outpost_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->enemy_outpost_status = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // is_detect_enemy
    PyObject * field = PyObject_GetAttrString(_pymsg, "is_detect_enemy");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->is_detect_enemy = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * sp_msgs__msg__rmuc_robot_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of RMUCRobotStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("sp_msgs.msg._rmuc_robot_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "RMUCRobotStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  sp_msgs__msg__RMUCRobotStatus * ros_message = (sp_msgs__msg__RMUCRobotStatus *)raw_ros_message;
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
  {  // current_hp
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->current_hp);
    {
      int rc = PyObject_SetAttrString(_pymessage, "current_hp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // shooter_heat
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->shooter_heat);
    {
      int rc = PyObject_SetAttrString(_pymessage, "shooter_heat", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ammo_allow
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->ammo_allow);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ammo_allow", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // outpost_hp
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->outpost_hp);
    {
      int rc = PyObject_SetAttrString(_pymessage, "outpost_hp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // base_hp
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->base_hp);
    {
      int rc = PyObject_SetAttrString(_pymessage, "base_hp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // enemy_outpost_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->enemy_outpost_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "enemy_outpost_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // is_detect_enemy
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->is_detect_enemy ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "is_detect_enemy", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
