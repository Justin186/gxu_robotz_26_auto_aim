# generated from rosidl_generator_py/resource/_idl.py.em
# with input from rm_interfaces:msg/Measurement.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Measurement(type):
    """Metaclass of message 'Measurement'."""

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
                'rm_interfaces.msg.Measurement')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__measurement
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__measurement
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__measurement
            cls._TYPE_SUPPORT = module.type_support_msg__msg__measurement
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__measurement

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Measurement(metaclass=Metaclass_Measurement):
    """Message class 'Measurement'."""

    __slots__ = [
        '_x1',
        '_y1',
        '_z1',
        '_yaw1',
        '_x2',
        '_y2',
        '_z2',
        '_yaw2',
    ]

    _fields_and_field_types = {
        'x1': 'double',
        'y1': 'double',
        'z1': 'double',
        'yaw1': 'double',
        'x2': 'double',
        'y2': 'double',
        'z2': 'double',
        'yaw2': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.x1 = kwargs.get('x1', float())
        self.y1 = kwargs.get('y1', float())
        self.z1 = kwargs.get('z1', float())
        self.yaw1 = kwargs.get('yaw1', float())
        self.x2 = kwargs.get('x2', float())
        self.y2 = kwargs.get('y2', float())
        self.z2 = kwargs.get('z2', float())
        self.yaw2 = kwargs.get('yaw2', float())

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
        if self.x1 != other.x1:
            return False
        if self.y1 != other.y1:
            return False
        if self.z1 != other.z1:
            return False
        if self.yaw1 != other.yaw1:
            return False
        if self.x2 != other.x2:
            return False
        if self.y2 != other.y2:
            return False
        if self.z2 != other.z2:
            return False
        if self.yaw2 != other.yaw2:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def x1(self):
        """Message field 'x1'."""
        return self._x1

    @x1.setter
    def x1(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'x1' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'x1' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._x1 = value

    @builtins.property
    def y1(self):
        """Message field 'y1'."""
        return self._y1

    @y1.setter
    def y1(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'y1' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'y1' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._y1 = value

    @builtins.property
    def z1(self):
        """Message field 'z1'."""
        return self._z1

    @z1.setter
    def z1(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'z1' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'z1' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._z1 = value

    @builtins.property
    def yaw1(self):
        """Message field 'yaw1'."""
        return self._yaw1

    @yaw1.setter
    def yaw1(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'yaw1' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'yaw1' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._yaw1 = value

    @builtins.property
    def x2(self):
        """Message field 'x2'."""
        return self._x2

    @x2.setter
    def x2(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'x2' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'x2' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._x2 = value

    @builtins.property
    def y2(self):
        """Message field 'y2'."""
        return self._y2

    @y2.setter
    def y2(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'y2' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'y2' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._y2 = value

    @builtins.property
    def z2(self):
        """Message field 'z2'."""
        return self._z2

    @z2.setter
    def z2(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'z2' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'z2' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._z2 = value

    @builtins.property
    def yaw2(self):
        """Message field 'yaw2'."""
        return self._yaw2

    @yaw2.setter
    def yaw2(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'yaw2' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'yaw2' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._yaw2 = value
