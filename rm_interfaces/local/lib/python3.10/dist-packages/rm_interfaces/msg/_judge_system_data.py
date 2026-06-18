# generated from rosidl_generator_py/resource/_idl.py.em
# with input from rm_interfaces:msg/JudgeSystemData.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_JudgeSystemData(type):
    """Metaclass of message 'JudgeSystemData'."""

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
                'rm_interfaces.msg.JudgeSystemData')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__judge_system_data
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__judge_system_data
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__judge_system_data
            cls._TYPE_SUPPORT = module.type_support_msg__msg__judge_system_data
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__judge_system_data

            from rm_interfaces.msg import OperatorCommand
            if OperatorCommand.__class__._TYPE_SUPPORT is None:
                OperatorCommand.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class JudgeSystemData(metaclass=Metaclass_JudgeSystemData):
    """Message class 'JudgeSystemData'."""

    __slots__ = [
        '_game_status',
        '_remaining_time',
        '_blood',
        '_outpost_hp',
        '_operator_command',
    ]

    _fields_and_field_types = {
        'game_status': 'uint8',
        'remaining_time': 'int16',
        'blood': 'int16',
        'outpost_hp': 'int16',
        'operator_command': 'rm_interfaces/OperatorCommand',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['rm_interfaces', 'msg'], 'OperatorCommand'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.game_status = kwargs.get('game_status', int())
        self.remaining_time = kwargs.get('remaining_time', int())
        self.blood = kwargs.get('blood', int())
        self.outpost_hp = kwargs.get('outpost_hp', int())
        from rm_interfaces.msg import OperatorCommand
        self.operator_command = kwargs.get('operator_command', OperatorCommand())

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
        if self.game_status != other.game_status:
            return False
        if self.remaining_time != other.remaining_time:
            return False
        if self.blood != other.blood:
            return False
        if self.outpost_hp != other.outpost_hp:
            return False
        if self.operator_command != other.operator_command:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def game_status(self):
        """Message field 'game_status'."""
        return self._game_status

    @game_status.setter
    def game_status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'game_status' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'game_status' field must be an unsigned integer in [0, 255]"
        self._game_status = value

    @builtins.property
    def remaining_time(self):
        """Message field 'remaining_time'."""
        return self._remaining_time

    @remaining_time.setter
    def remaining_time(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'remaining_time' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'remaining_time' field must be an integer in [-32768, 32767]"
        self._remaining_time = value

    @builtins.property
    def blood(self):
        """Message field 'blood'."""
        return self._blood

    @blood.setter
    def blood(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'blood' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'blood' field must be an integer in [-32768, 32767]"
        self._blood = value

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
            assert value >= -32768 and value < 32768, \
                "The 'outpost_hp' field must be an integer in [-32768, 32767]"
        self._outpost_hp = value

    @builtins.property
    def operator_command(self):
        """Message field 'operator_command'."""
        return self._operator_command

    @operator_command.setter
    def operator_command(self, value):
        if __debug__:
            from rm_interfaces.msg import OperatorCommand
            assert \
                isinstance(value, OperatorCommand), \
                "The 'operator_command' field must be a sub message of type 'OperatorCommand'"
        self._operator_command = value
