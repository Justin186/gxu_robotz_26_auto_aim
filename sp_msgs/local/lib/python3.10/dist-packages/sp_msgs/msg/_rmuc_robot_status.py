# generated from rosidl_generator_py/resource/_idl.py.em
# with input from sp_msgs:msg/RMUCRobotStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RMUCRobotStatus(type):
    """Metaclass of message 'RMUCRobotStatus'."""

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
                'sp_msgs.msg.RMUCRobotStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__rmuc_robot_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__rmuc_robot_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__rmuc_robot_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__rmuc_robot_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__rmuc_robot_status

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


class RMUCRobotStatus(metaclass=Metaclass_RMUCRobotStatus):
    """Message class 'RMUCRobotStatus'."""

    __slots__ = [
        '_header',
        '_current_hp',
        '_shooter_heat',
        '_ammo_allow',
        '_outpost_hp',
        '_base_hp',
        '_is_detect_enemy',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'current_hp': 'uint16',
        'shooter_heat': 'uint16',
        'ammo_allow': 'uint16',
        'outpost_hp': 'uint16',
        'base_hp': 'uint16',
        'is_detect_enemy': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.current_hp = kwargs.get('current_hp', int())
        self.shooter_heat = kwargs.get('shooter_heat', int())
        self.ammo_allow = kwargs.get('ammo_allow', int())
        self.outpost_hp = kwargs.get('outpost_hp', int())
        self.base_hp = kwargs.get('base_hp', int())
        self.is_detect_enemy = kwargs.get('is_detect_enemy', bool())

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
        if self.current_hp != other.current_hp:
            return False
        if self.shooter_heat != other.shooter_heat:
            return False
        if self.ammo_allow != other.ammo_allow:
            return False
        if self.outpost_hp != other.outpost_hp:
            return False
        if self.base_hp != other.base_hp:
            return False
        if self.is_detect_enemy != other.is_detect_enemy:
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
    def current_hp(self):
        """Message field 'current_hp'."""
        return self._current_hp

    @current_hp.setter
    def current_hp(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'current_hp' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'current_hp' field must be an unsigned integer in [0, 65535]"
        self._current_hp = value

    @builtins.property
    def shooter_heat(self):
        """Message field 'shooter_heat'."""
        return self._shooter_heat

    @shooter_heat.setter
    def shooter_heat(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'shooter_heat' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'shooter_heat' field must be an unsigned integer in [0, 65535]"
        self._shooter_heat = value

    @builtins.property
    def ammo_allow(self):
        """Message field 'ammo_allow'."""
        return self._ammo_allow

    @ammo_allow.setter
    def ammo_allow(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'ammo_allow' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'ammo_allow' field must be an unsigned integer in [0, 65535]"
        self._ammo_allow = value

    @builtins.property
    def outpost_hp(self):
        """Message field 'outpost_hp'."""
        return self._outpost_hp

    @outpost_hp.setter
    def outpost_hp(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'outpost_hp' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'outpost_hp' field must be an unsigned integer in [0, 65535]"
        self._outpost_hp = value

    @builtins.property
    def base_hp(self):
        """Message field 'base_hp'."""
        return self._base_hp

    @base_hp.setter
    def base_hp(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'base_hp' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'base_hp' field must be an unsigned integer in [0, 65535]"
        self._base_hp = value

    @builtins.property
    def is_detect_enemy(self):
        """Message field 'is_detect_enemy'."""
        return self._is_detect_enemy

    @is_detect_enemy.setter
    def is_detect_enemy(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_detect_enemy' field must be of type 'bool'"
        self._is_detect_enemy = value
