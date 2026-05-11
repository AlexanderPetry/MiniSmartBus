# generated from rosidl_generator_py/resource/_idl.py.em
# with input from py_bus_interfaces:msg/DriverStatus.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_DriverStatus(type):
    """Metaclass of message 'DriverStatus'."""

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
            module = import_type_support('py_bus_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'py_bus_interfaces.msg.DriverStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__driver_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__driver_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__driver_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__driver_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__driver_status

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class DriverStatus(metaclass=Metaclass_DriverStatus):
    """Message class 'DriverStatus'."""

    __slots__ = [
        '_stamp',
        '_source',
        '_rc_steering_us',
        '_rc_throttle_us',
        '_commanded_speed_kmh',
        '_commanded_steering_deg',
        '_applied_speed_kmh',
        '_applied_steering_deg',
        '_batt_voltage',
        '_batt_pct',
        '_raw_line',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'stamp': 'builtin_interfaces/Time',
        'source': 'string',
        'rc_steering_us': 'int32',
        'rc_throttle_us': 'int32',
        'commanded_speed_kmh': 'float',
        'commanded_steering_deg': 'float',
        'applied_speed_kmh': 'float',
        'applied_steering_deg': 'float',
        'batt_voltage': 'float',
        'batt_pct': 'float',
        'raw_line': 'string',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from builtin_interfaces.msg import Time
        self.stamp = kwargs.get('stamp', Time())
        self.source = kwargs.get('source', str())
        self.rc_steering_us = kwargs.get('rc_steering_us', int())
        self.rc_throttle_us = kwargs.get('rc_throttle_us', int())
        self.commanded_speed_kmh = kwargs.get('commanded_speed_kmh', float())
        self.commanded_steering_deg = kwargs.get('commanded_steering_deg', float())
        self.applied_speed_kmh = kwargs.get('applied_speed_kmh', float())
        self.applied_steering_deg = kwargs.get('applied_steering_deg', float())
        self.batt_voltage = kwargs.get('batt_voltage', float())
        self.batt_pct = kwargs.get('batt_pct', float())
        self.raw_line = kwargs.get('raw_line', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
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
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.stamp != other.stamp:
            return False
        if self.source != other.source:
            return False
        if self.rc_steering_us != other.rc_steering_us:
            return False
        if self.rc_throttle_us != other.rc_throttle_us:
            return False
        if self.commanded_speed_kmh != other.commanded_speed_kmh:
            return False
        if self.commanded_steering_deg != other.commanded_steering_deg:
            return False
        if self.applied_speed_kmh != other.applied_speed_kmh:
            return False
        if self.applied_steering_deg != other.applied_steering_deg:
            return False
        if self.batt_voltage != other.batt_voltage:
            return False
        if self.batt_pct != other.batt_pct:
            return False
        if self.raw_line != other.raw_line:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def stamp(self):
        """Message field 'stamp'."""
        return self._stamp

    @stamp.setter
    def stamp(self, value):
        if self._check_fields:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'stamp' field must be a sub message of type 'Time'"
        self._stamp = value

    @builtins.property
    def source(self):
        """Message field 'source'."""
        return self._source

    @source.setter
    def source(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'source' field must be of type 'str'"
        self._source = value

    @builtins.property
    def rc_steering_us(self):
        """Message field 'rc_steering_us'."""
        return self._rc_steering_us

    @rc_steering_us.setter
    def rc_steering_us(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'rc_steering_us' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'rc_steering_us' field must be an integer in [-2147483648, 2147483647]"
        self._rc_steering_us = value

    @builtins.property
    def rc_throttle_us(self):
        """Message field 'rc_throttle_us'."""
        return self._rc_throttle_us

    @rc_throttle_us.setter
    def rc_throttle_us(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'rc_throttle_us' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'rc_throttle_us' field must be an integer in [-2147483648, 2147483647]"
        self._rc_throttle_us = value

    @builtins.property
    def commanded_speed_kmh(self):
        """Message field 'commanded_speed_kmh'."""
        return self._commanded_speed_kmh

    @commanded_speed_kmh.setter
    def commanded_speed_kmh(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'commanded_speed_kmh' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'commanded_speed_kmh' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._commanded_speed_kmh = value

    @builtins.property
    def commanded_steering_deg(self):
        """Message field 'commanded_steering_deg'."""
        return self._commanded_steering_deg

    @commanded_steering_deg.setter
    def commanded_steering_deg(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'commanded_steering_deg' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'commanded_steering_deg' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._commanded_steering_deg = value

    @builtins.property
    def applied_speed_kmh(self):
        """Message field 'applied_speed_kmh'."""
        return self._applied_speed_kmh

    @applied_speed_kmh.setter
    def applied_speed_kmh(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'applied_speed_kmh' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'applied_speed_kmh' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._applied_speed_kmh = value

    @builtins.property
    def applied_steering_deg(self):
        """Message field 'applied_steering_deg'."""
        return self._applied_steering_deg

    @applied_steering_deg.setter
    def applied_steering_deg(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'applied_steering_deg' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'applied_steering_deg' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._applied_steering_deg = value

    @builtins.property
    def batt_voltage(self):
        """Message field 'batt_voltage'."""
        return self._batt_voltage

    @batt_voltage.setter
    def batt_voltage(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'batt_voltage' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'batt_voltage' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._batt_voltage = value

    @builtins.property
    def batt_pct(self):
        """Message field 'batt_pct'."""
        return self._batt_pct

    @batt_pct.setter
    def batt_pct(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'batt_pct' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'batt_pct' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._batt_pct = value

    @builtins.property
    def raw_line(self):
        """Message field 'raw_line'."""
        return self._raw_line

    @raw_line.setter
    def raw_line(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'raw_line' field must be of type 'str'"
        self._raw_line = value
