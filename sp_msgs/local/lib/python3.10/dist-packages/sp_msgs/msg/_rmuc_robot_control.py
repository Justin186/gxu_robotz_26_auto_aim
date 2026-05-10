# generated from rosidl_generator_py/resource/_idl.py.em
# with input from sp_msgs:msg/RMUCRobotControl.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RMUCRobotControl(type):
    """Metaclass of message 'RMUCRobotControl'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('sp_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'sp_msgs.msg.RMUCRobotControl')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__rmuc_robot_control
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__rmuc_robot_control
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__rmuc_robot_control
            cls._TYPE_SUPPORT = module.type_support_msg__msg__rmuc_robot_control
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__rmuc_robot_control

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RMUCRobotControl(metaclass=Metaclass_RMUCRobotControl):
    """Message class 'RMUCRobotControl'."""

    __slots__ = [
        '_header',
        '_stop_gimbal_scan',
        '_chassis_spin',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'stop_gimbal_scan': 'boolean',
        'chassis_spin': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.stop_gimbal_scan = kwargs.get('stop_gimbal_scan', bool())
        self.chassis_spin = kwargs.get('chassis_spin', bool())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.stop_gimbal_scan != other.stop_gimbal_scan:
            return False
        if self.chassis_spin != other.chassis_spin:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def stop_gimbal_scan(self):
        """Message field 'stop_gimbal_scan'."""
        return self._stop_gimbal_scan

    @stop_gimbal_scan.setter
    def stop_gimbal_scan(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'stop_gimbal_scan' field must be of type 'bool'"
        self._stop_gimbal_scan = value

    @builtins.property
    def chassis_spin(self):
        """Message field 'chassis_spin'."""
        return self._chassis_spin

    @chassis_spin.setter
    def chassis_spin(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'chassis_spin' field must be of type 'bool'"
        self._chassis_spin = value
