# generated from rosidl_generator_py/resource/_idl.py.em
# with input from rm_interfaces:msg/DebugArmor.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_DebugArmor(type):
    """Metaclass of message 'DebugArmor'."""

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
                'rm_interfaces.msg.DebugArmor')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__debug_armor
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__debug_armor
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__debug_armor
            cls._TYPE_SUPPORT = module.type_support_msg__msg__debug_armor
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__debug_armor

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class DebugArmor(metaclass=Metaclass_DebugArmor):
    """Message class 'DebugArmor'."""

    __slots__ = [
        '_center_x',
        '_type',
        '_light_ratio',
        '_center_distance',
        '_angle',
    ]

    _fields_and_field_types = {
        'center_x': 'int32',
        'type': 'string',
        'light_ratio': 'float',
        'center_distance': 'float',
        'angle': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.center_x = kwargs.get('center_x', int())
        self.type = kwargs.get('type', str())
        self.light_ratio = kwargs.get('light_ratio', float())
        self.center_distance = kwargs.get('center_distance', float())
        self.angle = kwargs.get('angle', float())

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
        if self.center_x != other.center_x:
            return False
        if self.type != other.type:
            return False
        if self.light_ratio != other.light_ratio:
            return False
        if self.center_distance != other.center_distance:
            return False
        if self.angle != other.angle:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def center_x(self):
        """Message field 'center_x'."""
        return self._center_x

    @center_x.setter
    def center_x(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'center_x' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'center_x' field must be an integer in [-2147483648, 2147483647]"
        self._center_x = value

    @builtins.property  # noqa: A003
    def type(self):  # noqa: A003
        """Message field 'type'."""
        return self._type

    @type.setter  # noqa: A003
    def type(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'type' field must be of type 'str'"
        self._type = value

    @builtins.property
    def light_ratio(self):
        """Message field 'light_ratio'."""
        return self._light_ratio

    @light_ratio.setter
    def light_ratio(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'light_ratio' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'light_ratio' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._light_ratio = value

    @builtins.property
    def center_distance(self):
        """Message field 'center_distance'."""
        return self._center_distance

    @center_distance.setter
    def center_distance(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'center_distance' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'center_distance' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._center_distance = value

    @builtins.property
    def angle(self):
        """Message field 'angle'."""
        return self._angle

    @angle.setter
    def angle(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'angle' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'angle' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._angle = value
