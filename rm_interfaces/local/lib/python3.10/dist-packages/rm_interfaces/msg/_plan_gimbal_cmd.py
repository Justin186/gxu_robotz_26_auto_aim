# generated from rosidl_generator_py/resource/_idl.py.em
# with input from rm_interfaces:msg/PlanGimbalCmd.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_PlanGimbalCmd(type):
    """Metaclass of message 'PlanGimbalCmd'."""

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
            module = import_type_support('rm_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'rm_interfaces.msg.PlanGimbalCmd')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__plan_gimbal_cmd
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__plan_gimbal_cmd
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__plan_gimbal_cmd
            cls._TYPE_SUPPORT = module.type_support_msg__msg__plan_gimbal_cmd
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__plan_gimbal_cmd

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


class PlanGimbalCmd(metaclass=Metaclass_PlanGimbalCmd):
    """Message class 'PlanGimbalCmd'."""

    __slots__ = [
        '_header',
        '_ref_yaw',
        '_ref_yaw_vel',
        '_ref_yaw_acc',
        '_ref_pitch',
        '_ref_pitch_vel',
        '_ref_pitch_acc',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'ref_yaw': 'float',
        'ref_yaw_vel': 'float',
        'ref_yaw_acc': 'float',
        'ref_pitch': 'float',
        'ref_pitch_vel': 'float',
        'ref_pitch_acc': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.ref_yaw = kwargs.get('ref_yaw', float())
        self.ref_yaw_vel = kwargs.get('ref_yaw_vel', float())
        self.ref_yaw_acc = kwargs.get('ref_yaw_acc', float())
        self.ref_pitch = kwargs.get('ref_pitch', float())
        self.ref_pitch_vel = kwargs.get('ref_pitch_vel', float())
        self.ref_pitch_acc = kwargs.get('ref_pitch_acc', float())

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
        if self.ref_yaw != other.ref_yaw:
            return False
        if self.ref_yaw_vel != other.ref_yaw_vel:
            return False
        if self.ref_yaw_acc != other.ref_yaw_acc:
            return False
        if self.ref_pitch != other.ref_pitch:
            return False
        if self.ref_pitch_vel != other.ref_pitch_vel:
            return False
        if self.ref_pitch_acc != other.ref_pitch_acc:
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
    def ref_yaw(self):
        """Message field 'ref_yaw'."""
        return self._ref_yaw

    @ref_yaw.setter
    def ref_yaw(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ref_yaw' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'ref_yaw' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._ref_yaw = value

    @builtins.property
    def ref_yaw_vel(self):
        """Message field 'ref_yaw_vel'."""
        return self._ref_yaw_vel

    @ref_yaw_vel.setter
    def ref_yaw_vel(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ref_yaw_vel' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'ref_yaw_vel' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._ref_yaw_vel = value

    @builtins.property
    def ref_yaw_acc(self):
        """Message field 'ref_yaw_acc'."""
        return self._ref_yaw_acc

    @ref_yaw_acc.setter
    def ref_yaw_acc(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ref_yaw_acc' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'ref_yaw_acc' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._ref_yaw_acc = value

    @builtins.property
    def ref_pitch(self):
        """Message field 'ref_pitch'."""
        return self._ref_pitch

    @ref_pitch.setter
    def ref_pitch(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ref_pitch' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'ref_pitch' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._ref_pitch = value

    @builtins.property
    def ref_pitch_vel(self):
        """Message field 'ref_pitch_vel'."""
        return self._ref_pitch_vel

    @ref_pitch_vel.setter
    def ref_pitch_vel(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ref_pitch_vel' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'ref_pitch_vel' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._ref_pitch_vel = value

    @builtins.property
    def ref_pitch_acc(self):
        """Message field 'ref_pitch_acc'."""
        return self._ref_pitch_acc

    @ref_pitch_acc.setter
    def ref_pitch_acc(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'ref_pitch_acc' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'ref_pitch_acc' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._ref_pitch_acc = value
