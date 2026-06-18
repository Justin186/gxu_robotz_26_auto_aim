# generated from rosidl_generator_py/resource/_idl.py.em
# with input from rm_interfaces:srv/RunHandEyeCalibration.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RunHandEyeCalibration_Request(type):
    """Metaclass of message 'RunHandEyeCalibration_Request'."""

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
                'rm_interfaces.srv.RunHandEyeCalibration_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__run_hand_eye_calibration__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__run_hand_eye_calibration__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__run_hand_eye_calibration__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__run_hand_eye_calibration__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__run_hand_eye_calibration__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RunHandEyeCalibration_Request(metaclass=Metaclass_RunHandEyeCalibration_Request):
    """Message class 'RunHandEyeCalibration_Request'."""

    __slots__ = [
    ]

    _fields_and_field_types = {
    }

    SLOT_TYPES = (
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))

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
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)


# Import statements for member types

import builtins  # noqa: E402, I100

# already imported above
# import rosidl_parser.definition


class Metaclass_RunHandEyeCalibration_Response(type):
    """Metaclass of message 'RunHandEyeCalibration_Response'."""

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
                'rm_interfaces.srv.RunHandEyeCalibration_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__run_hand_eye_calibration__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__run_hand_eye_calibration__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__run_hand_eye_calibration__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__run_hand_eye_calibration__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__run_hand_eye_calibration__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RunHandEyeCalibration_Response(metaclass=Metaclass_RunHandEyeCalibration_Response):
    """Message class 'RunHandEyeCalibration_Response'."""

    __slots__ = [
        '_success',
        '_yaml_path',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'yaml_path': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.yaml_path = kwargs.get('yaml_path', str())

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
        if self.success != other.success:
            return False
        if self.yaml_path != other.yaml_path:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value

    @builtins.property
    def yaml_path(self):
        """Message field 'yaml_path'."""
        return self._yaml_path

    @yaml_path.setter
    def yaml_path(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'yaml_path' field must be of type 'str'"
        self._yaml_path = value


class Metaclass_RunHandEyeCalibration(type):
    """Metaclass of service 'RunHandEyeCalibration'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('rm_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'rm_interfaces.srv.RunHandEyeCalibration')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__run_hand_eye_calibration

            from rm_interfaces.srv import _run_hand_eye_calibration
            if _run_hand_eye_calibration.Metaclass_RunHandEyeCalibration_Request._TYPE_SUPPORT is None:
                _run_hand_eye_calibration.Metaclass_RunHandEyeCalibration_Request.__import_type_support__()
            if _run_hand_eye_calibration.Metaclass_RunHandEyeCalibration_Response._TYPE_SUPPORT is None:
                _run_hand_eye_calibration.Metaclass_RunHandEyeCalibration_Response.__import_type_support__()


class RunHandEyeCalibration(metaclass=Metaclass_RunHandEyeCalibration):
    from rm_interfaces.srv._run_hand_eye_calibration import RunHandEyeCalibration_Request as Request
    from rm_interfaces.srv._run_hand_eye_calibration import RunHandEyeCalibration_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
