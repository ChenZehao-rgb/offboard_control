# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from offboard_control/StateControl.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class StateControl(genpy.Message):
  _md5sum = "32bbda18dc61a12eea4cc4f9975ef333"
  _type = "offboard_control/StateControl"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """uint8 state_ctrl_type
uint8 TAKEOFF = 0
uint8 ARRIVE_ONLINE_POINT = 1
uint8 AJUST_ATTITUDE = 2
uint8 ON_LINE = 3
uint8 FOLLOW_CABLE = 4
uint8 APPROACH_NODE = 5
uint8 CROSS_NODE = 6
uint8 LAND = 7"""
  # Pseudo-constants
  TAKEOFF = 0
  ARRIVE_ONLINE_POINT = 1
  AJUST_ATTITUDE = 2
  ON_LINE = 3
  FOLLOW_CABLE = 4
  APPROACH_NODE = 5
  CROSS_NODE = 6
  LAND = 7

  __slots__ = ['state_ctrl_type']
  _slot_types = ['uint8']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       state_ctrl_type

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(StateControl, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.state_ctrl_type is None:
        self.state_ctrl_type = 0
    else:
      self.state_ctrl_type = 0

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self.state_ctrl_type
      buff.write(_get_struct_B().pack(_x))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      start = end
      end += 1
      (self.state_ctrl_type,) = _get_struct_B().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self.state_ctrl_type
      buff.write(_get_struct_B().pack(_x))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      start = end
      end += 1
      (self.state_ctrl_type,) = _get_struct_B().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_B = None
def _get_struct_B():
    global _struct_B
    if _struct_B is None:
        _struct_B = struct.Struct("<B")
    return _struct_B