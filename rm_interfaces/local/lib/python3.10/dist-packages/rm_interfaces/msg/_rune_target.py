# generated from rosidl_generator_py/resource/_idl.py.em
# with input from rm_interfaces:msg/RuneTarget.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RuneTarget(type):
    """Metaclass of message 'RuneTarget'."""

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
                'rm_interfaces.msg.RuneTarget')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__rune_target
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__rune_target
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__rune_target
            cls._TYPE_SUPPORT = module.type_support_msg__msg__rune_target
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__rune_target

            from rm_interfaces.msg import Point2d
            if Point2d.__class__._TYPE_SUPPORT is None:
                Point2d.__class__.__import_type_support__()

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


class RuneTarget(metaclass=Metaclass_RuneTarget):
    """Message class 'RuneTarget'."""

    __slots__ = [
        '_header',
        '_pts',
        '_is_lost',
        '_is_big_rune',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'pts': 'rm_interfaces/Point2d[5]',
        'is_lost': 'boolean',
        'is_big_rune': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.NamespacedType(['rm_interfaces', 'msg'], 'Point2d'), 5),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        from rm_interfaces.msg import Point2d
        self.pts = kwargs.get(
            'pts',
            [Point2d() for x in range(5)]
        )
        self.is_lost = kwargs.get('is_lost', bool())
        self.is_big_rune = kwargs.get('is_big_rune', bool())

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
        if self.pts != other.pts:
            return False
        if self.is_lost != other.is_lost:
            return False
        if self.is_big_rune != other.is_big_rune:
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
    def pts(self):
        """Message field 'pts'."""
        return self._pts

    @pts.setter
    def pts(self, value):
        if __debug__:
            from rm_interfaces.msg import Point2d
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 5 and
                 all(isinstance(v, Point2d) for v in value) and
                 True), \
                "The 'pts' field must be a set or sequence with length 5 and each value of type 'Point2d'"
        self._pts = value

    @builtins.property
    def is_lost(self):
        """Message field 'is_lost'."""
        return self._is_lost

    @is_lost.setter
    def is_lost(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_lost' field must be of type 'bool'"
        self._is_lost = value

    @builtins.property
    def is_big_rune(self):
        """Message field 'is_big_rune'."""
        return self._is_big_rune

    @is_big_rune.setter
    def is_big_rune(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_big_rune' field must be of type 'bool'"
        self._is_big_rune = value
