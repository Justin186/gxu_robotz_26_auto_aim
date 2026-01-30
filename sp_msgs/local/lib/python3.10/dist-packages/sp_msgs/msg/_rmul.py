# generated from rosidl_generator_py/resource/_idl.py.em
# with input from sp_msgs:msg/RMUL.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RMUL(type):
    """Metaclass of message 'RMUL'."""

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
                'sp_msgs.msg.RMUL')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__rmul
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__rmul
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__rmul
            cls._TYPE_SUPPORT = module.type_support_msg__msg__rmul
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__rmul

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


class RMUL(metaclass=Metaclass_RMUL):
    """Message class 'RMUL'."""

    __slots__ = [
        '_header',
        '_game_progress',
        '_stage_remain_time',
        '_cmd_type',
        '_emergency_stop',
        '_rfid_supply_arrived',
        '_rfid_control_arrived',
        '_stop_gimbal_scan',
        '_chassis_spin',
        '_x',
        '_y',
        '_current_hp',
        '_is_attacked',
        '_is_detect_enemy',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'game_progress': 'uint8',
        'stage_remain_time': 'uint16',
        'cmd_type': 'int32',
        'emergency_stop': 'boolean',
        'rfid_supply_arrived': 'boolean',
        'rfid_control_arrived': 'boolean',
        'stop_gimbal_scan': 'boolean',
        'chassis_spin': 'boolean',
        'x': 'float',
        'y': 'float',
        'current_hp': 'uint16',
        'is_attacked': 'uint8',
        'is_detect_enemy': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.game_progress = kwargs.get('game_progress', int())
        self.stage_remain_time = kwargs.get('stage_remain_time', int())
        self.cmd_type = kwargs.get('cmd_type', int())
        self.emergency_stop = kwargs.get('emergency_stop', bool())
        self.rfid_supply_arrived = kwargs.get('rfid_supply_arrived', bool())
        self.rfid_control_arrived = kwargs.get('rfid_control_arrived', bool())
        self.stop_gimbal_scan = kwargs.get('stop_gimbal_scan', bool())
        self.chassis_spin = kwargs.get('chassis_spin', bool())
        self.x = kwargs.get('x', float())
        self.y = kwargs.get('y', float())
        self.current_hp = kwargs.get('current_hp', int())
        self.is_attacked = kwargs.get('is_attacked', int())
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
        if self.game_progress != other.game_progress:
            return False
        if self.stage_remain_time != other.stage_remain_time:
            return False
        if self.cmd_type != other.cmd_type:
            return False
        if self.emergency_stop != other.emergency_stop:
            return False
        if self.rfid_supply_arrived != other.rfid_supply_arrived:
            return False
        if self.rfid_control_arrived != other.rfid_control_arrived:
            return False
        if self.stop_gimbal_scan != other.stop_gimbal_scan:
            return False
        if self.chassis_spin != other.chassis_spin:
            return False
        if self.x != other.x:
            return False
        if self.y != other.y:
            return False
        if self.current_hp != other.current_hp:
            return False
        if self.is_attacked != other.is_attacked:
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
    def game_progress(self):
        """Message field 'game_progress'."""
        return self._game_progress

    @game_progress.setter
    def game_progress(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'game_progress' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'game_progress' field must be an unsigned integer in [0, 255]"
        self._game_progress = value

    @builtins.property
    def stage_remain_time(self):
        """Message field 'stage_remain_time'."""
        return self._stage_remain_time

    @stage_remain_time.setter
    def stage_remain_time(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'stage_remain_time' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'stage_remain_time' field must be an unsigned integer in [0, 65535]"
        self._stage_remain_time = value

    @builtins.property
    def cmd_type(self):
        """Message field 'cmd_type'."""
        return self._cmd_type

    @cmd_type.setter
    def cmd_type(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'cmd_type' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'cmd_type' field must be an integer in [-2147483648, 2147483647]"
        self._cmd_type = value

    @builtins.property
    def emergency_stop(self):
        """Message field 'emergency_stop'."""
        return self._emergency_stop

    @emergency_stop.setter
    def emergency_stop(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'emergency_stop' field must be of type 'bool'"
        self._emergency_stop = value

    @builtins.property
    def rfid_supply_arrived(self):
        """Message field 'rfid_supply_arrived'."""
        return self._rfid_supply_arrived

    @rfid_supply_arrived.setter
    def rfid_supply_arrived(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'rfid_supply_arrived' field must be of type 'bool'"
        self._rfid_supply_arrived = value

    @builtins.property
    def rfid_control_arrived(self):
        """Message field 'rfid_control_arrived'."""
        return self._rfid_control_arrived

    @rfid_control_arrived.setter
    def rfid_control_arrived(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'rfid_control_arrived' field must be of type 'bool'"
        self._rfid_control_arrived = value

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

    @builtins.property
    def x(self):
        """Message field 'x'."""
        return self._x

    @x.setter
    def x(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'x' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'x' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._x = value

    @builtins.property
    def y(self):
        """Message field 'y'."""
        return self._y

    @y.setter
    def y(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'y' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'y' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._y = value

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
    def is_attacked(self):
        """Message field 'is_attacked'."""
        return self._is_attacked

    @is_attacked.setter
    def is_attacked(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'is_attacked' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'is_attacked' field must be an unsigned integer in [0, 255]"
        self._is_attacked = value

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
