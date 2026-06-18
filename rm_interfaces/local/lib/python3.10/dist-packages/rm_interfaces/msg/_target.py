# generated from rosidl_generator_py/resource/_idl.py.em
# with input from rm_interfaces:msg/Target.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Target(type):
    """Metaclass of message 'Target'."""

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
                'rm_interfaces.msg.Target')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__target
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__target
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__target
            cls._TYPE_SUPPORT = module.type_support_msg__msg__target
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__target

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

            from geometry_msgs.msg import Vector3
            if Vector3.__class__._TYPE_SUPPORT is None:
                Vector3.__class__.__import_type_support__()

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


class Target(metaclass=Metaclass_Target):
    """Message class 'Target'."""

    __slots__ = [
        '_header',
        '_tracking',
        '_id',
        '_armors_num',
        '_position',
        '_velocity',
        '_yaw',
        '_v_yaw',
        '_radius_1',
        '_radius_2',
        '_d_za',
        '_d_zc',
        '_yaw_diff',
        '_position_diff',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'tracking': 'boolean',
        'id': 'string',
        'armors_num': 'int32',
        'position': 'geometry_msgs/Point',
        'velocity': 'geometry_msgs/Vector3',
        'yaw': 'double',
        'v_yaw': 'double',
        'radius_1': 'double',
        'radius_2': 'double',
        'd_za': 'double',
        'd_zc': 'double',
        'yaw_diff': 'double',
        'position_diff': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
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
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.tracking = kwargs.get('tracking', bool())
        self.id = kwargs.get('id', str())
        self.armors_num = kwargs.get('armors_num', int())
        from geometry_msgs.msg import Point
        self.position = kwargs.get('position', Point())
        from geometry_msgs.msg import Vector3
        self.velocity = kwargs.get('velocity', Vector3())
        self.yaw = kwargs.get('yaw', float())
        self.v_yaw = kwargs.get('v_yaw', float())
        self.radius_1 = kwargs.get('radius_1', float())
        self.radius_2 = kwargs.get('radius_2', float())
        self.d_za = kwargs.get('d_za', float())
        self.d_zc = kwargs.get('d_zc', float())
        self.yaw_diff = kwargs.get('yaw_diff', float())
        self.position_diff = kwargs.get('position_diff', float())

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
        if self.tracking != other.tracking:
            return False
        if self.id != other.id:
            return False
        if self.armors_num != other.armors_num:
            return False
        if self.position != other.position:
            return False
        if self.velocity != other.velocity:
            return False
        if self.yaw != other.yaw:
            return False
        if self.v_yaw != other.v_yaw:
            return False
        if self.radius_1 != other.radius_1:
            return False
        if self.radius_2 != other.radius_2:
            return False
        if self.d_za != other.d_za:
            return False
        if self.d_zc != other.d_zc:
            return False
        if self.yaw_diff != other.yaw_diff:
            return False
        if self.position_diff != other.position_diff:
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
    def tracking(self):
        """Message field 'tracking'."""
        return self._tracking

    @tracking.setter
    def tracking(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'tracking' field must be of type 'bool'"
        self._tracking = value

    @builtins.property  # noqa: A003
    def id(self):  # noqa: A003
        """Message field 'id'."""
        return self._id

    @id.setter  # noqa: A003
    def id(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'id' field must be of type 'str'"
        self._id = value

    @builtins.property
    def armors_num(self):
        """Message field 'armors_num'."""
        return self._armors_num

    @armors_num.setter
    def armors_num(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'armors_num' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'armors_num' field must be an integer in [-2147483648, 2147483647]"
        self._armors_num = value

    @builtins.property
    def position(self):
        """Message field 'position'."""
        return self._position

    @position.setter
    def position(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'position' field must be a sub message of type 'Point'"
        self._position = value

    @builtins.property
    def velocity(self):
        """Message field 'velocity'."""
        return self._velocity

    @velocity.setter
    def velocity(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'velocity' field must be a sub message of type 'Vector3'"
        self._velocity = value

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
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'yaw' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._yaw = value

    @builtins.property
    def v_yaw(self):
        """Message field 'v_yaw'."""
        return self._v_yaw

    @v_yaw.setter
    def v_yaw(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'v_yaw' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'v_yaw' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._v_yaw = value

    @builtins.property
    def radius_1(self):
        """Message field 'radius_1'."""
        return self._radius_1

    @radius_1.setter
    def radius_1(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'radius_1' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'radius_1' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._radius_1 = value

    @builtins.property
    def radius_2(self):
        """Message field 'radius_2'."""
        return self._radius_2

    @radius_2.setter
    def radius_2(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'radius_2' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'radius_2' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._radius_2 = value

    @builtins.property
    def d_za(self):
        """Message field 'd_za'."""
        return self._d_za

    @d_za.setter
    def d_za(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'd_za' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'd_za' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._d_za = value

    @builtins.property
    def d_zc(self):
        """Message field 'd_zc'."""
        return self._d_zc

    @d_zc.setter
    def d_zc(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'd_zc' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'd_zc' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._d_zc = value

    @builtins.property
    def yaw_diff(self):
        """Message field 'yaw_diff'."""
        return self._yaw_diff

    @yaw_diff.setter
    def yaw_diff(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'yaw_diff' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'yaw_diff' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._yaw_diff = value

    @builtins.property
    def position_diff(self):
        """Message field 'position_diff'."""
        return self._position_diff

    @position_diff.setter
    def position_diff(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'position_diff' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'position_diff' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._position_diff = value
