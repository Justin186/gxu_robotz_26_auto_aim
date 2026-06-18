# generated from rosidl_generator_py/resource/_idl.py.em
# with input from rm_interfaces:msg/SerialReceiveData.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SerialReceiveData(type):
    """Metaclass of message 'SerialReceiveData'."""

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
                'rm_interfaces.msg.SerialReceiveData')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__serial_receive_data
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__serial_receive_data
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__serial_receive_data
            cls._TYPE_SUPPORT = module.type_support_msg__msg__serial_receive_data
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__serial_receive_data

            from rm_interfaces.msg import JudgeSystemData
            if JudgeSystemData.__class__._TYPE_SUPPORT is None:
                JudgeSystemData.__class__.__import_type_support__()

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


class SerialReceiveData(metaclass=Metaclass_SerialReceiveData):
    """Message class 'SerialReceiveData'."""

    __slots__ = [
        '_header',
        '_mode',
        '_bullet_speed',
        '_roll',
        '_yaw',
        '_pitch',
        '_judge_system_data',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'mode': 'uint8',
        'bullet_speed': 'float',
        'roll': 'float',
        'yaw': 'float',
        'pitch': 'float',
        'judge_system_data': 'rm_interfaces/JudgeSystemData',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['rm_interfaces', 'msg'], 'JudgeSystemData'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.mode = kwargs.get('mode', int())
        self.bullet_speed = kwargs.get('bullet_speed', float())
        self.roll = kwargs.get('roll', float())
        self.yaw = kwargs.get('yaw', float())
        self.pitch = kwargs.get('pitch', float())
        from rm_interfaces.msg import JudgeSystemData
        self.judge_system_data = kwargs.get('judge_system_data', JudgeSystemData())

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
        if self.mode != other.mode:
            return False
        if self.bullet_speed != other.bullet_speed:
            return False
        if self.roll != other.roll:
            return False
        if self.yaw != other.yaw:
            return False
        if self.pitch != other.pitch:
            return False
        if self.judge_system_data != other.judge_system_data:
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
    def mode(self):
        """Message field 'mode'."""
        return self._mode

    @mode.setter
    def mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'mode' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'mode' field must be an unsigned integer in [0, 255]"
        self._mode = value

    @builtins.property
    def bullet_speed(self):
        """Message field 'bullet_speed'."""
        return self._bullet_speed

    @bullet_speed.setter
    def bullet_speed(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'bullet_speed' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'bullet_speed' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._bullet_speed = value

    @builtins.property
    def roll(self):
        """Message field 'roll'."""
        return self._roll

    @roll.setter
    def roll(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'roll' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'roll' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._roll = value

    @builtins.property
    def yaw(self):
        """Message field 'yaw'."""
        return self._yaw

    @yaw.setter
    def yaw(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'yaw' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'yaw' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._yaw = value

    @builtins.property
    def pitch(self):
        """Message field 'pitch'."""
        return self._pitch

    @pitch.setter
    def pitch(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pitch' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pitch' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pitch = value

    @builtins.property
    def judge_system_data(self):
        """Message field 'judge_system_data'."""
        return self._judge_system_data

    @judge_system_data.setter
    def judge_system_data(self, value):
        if __debug__:
            from rm_interfaces.msg import JudgeSystemData
            assert \
                isinstance(value, JudgeSystemData), \
                "The 'judge_system_data' field must be a sub message of type 'JudgeSystemData'"
        self._judge_system_data = value
