// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from sp_msgs:msg/RMUL.idl
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
#include "sp_msgs/msg/detail/rmul__struct.h"
#include "sp_msgs/msg/detail/rmul__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool sp_msgs__msg__rmul__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[23];
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
    assert(strncmp("sp_msgs.msg._rmul.RMUL", full_classname_dest, 22) == 0);
  }
  sp_msgs__msg__RMUL * ros_message = _ros_message;
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
  {  // game_progress
    PyObject * field = PyObject_GetAttrString(_pymsg, "game_progress");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->game_progress = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // stage_remain_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "stage_remain_time");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->stage_remain_time = (uint16_t)PyLong_AsUnsignedLong(field);
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
  {  // is_attacked
    PyObject * field = PyObject_GetAttrString(_pymsg, "is_attacked");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->is_attacked = (uint8_t)PyLong_AsUnsignedLong(field);
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
  {  // rfid_supply_arrived
    PyObject * field = PyObject_GetAttrString(_pymsg, "rfid_supply_arrived");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->rfid_supply_arrived = (Py_True == field);
    Py_DECREF(field);
  }
  {  // rfid_control_arrived
    PyObject * field = PyObject_GetAttrString(_pymsg, "rfid_control_arrived");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->rfid_control_arrived = (Py_True == field);
    Py_DECREF(field);
  }
  {  // cmd_type
    PyObject * field = PyObject_GetAttrString(_pymsg, "cmd_type");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->cmd_type = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // emergency_stop
    PyObject * field = PyObject_GetAttrString(_pymsg, "emergency_stop");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->emergency_stop = (Py_True == field);
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
  {  // x
    PyObject * field = PyObject_GetAttrString(_pymsg, "x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->x = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // y
    PyObject * field = PyObject_GetAttrString(_pymsg, "y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->y = (float)PyFloat_AS_DOUBLE(field);
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
  {  // is_at_nav_goal
    PyObject * field = PyObject_GetAttrString(_pymsg, "is_at_nav_goal");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->is_at_nav_goal = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * sp_msgs__msg__rmul__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of RMUL */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("sp_msgs.msg._rmul");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "RMUL");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  sp_msgs__msg__RMUL * ros_message = (sp_msgs__msg__RMUL *)raw_ros_message;
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
  {  // game_progress
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->game_progress);
    {
      int rc = PyObject_SetAttrString(_pymessage, "game_progress", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // stage_remain_time
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->stage_remain_time);
    {
      int rc = PyObject_SetAttrString(_pymessage, "stage_remain_time", field);
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
  {  // is_attacked
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->is_attacked);
    {
      int rc = PyObject_SetAttrString(_pymessage, "is_attacked", field);
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
  {  // rfid_supply_arrived
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->rfid_supply_arrived ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rfid_supply_arrived", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rfid_control_arrived
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->rfid_control_arrived ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rfid_control_arrived", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // cmd_type
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->cmd_type);
    {
      int rc = PyObject_SetAttrString(_pymessage, "cmd_type", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // emergency_stop
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->emergency_stop ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "emergency_stop", field);
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
  {  // x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "y", field);
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
  {  // is_at_nav_goal
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->is_at_nav_goal ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "is_at_nav_goal", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
