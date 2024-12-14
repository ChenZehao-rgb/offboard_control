# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from offboard_control/isUavArrivedRequest.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import geometry_msgs.msg
import std_msgs.msg

class isUavArrivedRequest(genpy.Message):
  _md5sum = "fe78b9b615816ee275f9bae3c27a36c6"
  _type = "offboard_control/isUavArrivedRequest"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """geometry_msgs/PoseStamped targetPoint
uint8 uavID

================================================================================
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
"""
  __slots__ = ['targetPoint','uavID']
  _slot_types = ['geometry_msgs/PoseStamped','uint8']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       targetPoint,uavID

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(isUavArrivedRequest, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.targetPoint is None:
        self.targetPoint = geometry_msgs.msg.PoseStamped()
      if self.uavID is None:
        self.uavID = 0
    else:
      self.targetPoint = geometry_msgs.msg.PoseStamped()
      self.uavID = 0

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
      _x = self
      buff.write(_get_struct_3I().pack(_x.targetPoint.header.seq, _x.targetPoint.header.stamp.secs, _x.targetPoint.header.stamp.nsecs))
      _x = self.targetPoint.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self
      buff.write(_get_struct_7dB().pack(_x.targetPoint.pose.position.x, _x.targetPoint.pose.position.y, _x.targetPoint.pose.position.z, _x.targetPoint.pose.orientation.x, _x.targetPoint.pose.orientation.y, _x.targetPoint.pose.orientation.z, _x.targetPoint.pose.orientation.w, _x.uavID))
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
      if self.targetPoint is None:
        self.targetPoint = geometry_msgs.msg.PoseStamped()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.targetPoint.header.seq, _x.targetPoint.header.stamp.secs, _x.targetPoint.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.targetPoint.header.frame_id = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.targetPoint.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 57
      (_x.targetPoint.pose.position.x, _x.targetPoint.pose.position.y, _x.targetPoint.pose.position.z, _x.targetPoint.pose.orientation.x, _x.targetPoint.pose.orientation.y, _x.targetPoint.pose.orientation.z, _x.targetPoint.pose.orientation.w, _x.uavID,) = _get_struct_7dB().unpack(str[start:end])
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
      _x = self
      buff.write(_get_struct_3I().pack(_x.targetPoint.header.seq, _x.targetPoint.header.stamp.secs, _x.targetPoint.header.stamp.nsecs))
      _x = self.targetPoint.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self
      buff.write(_get_struct_7dB().pack(_x.targetPoint.pose.position.x, _x.targetPoint.pose.position.y, _x.targetPoint.pose.position.z, _x.targetPoint.pose.orientation.x, _x.targetPoint.pose.orientation.y, _x.targetPoint.pose.orientation.z, _x.targetPoint.pose.orientation.w, _x.uavID))
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
      if self.targetPoint is None:
        self.targetPoint = geometry_msgs.msg.PoseStamped()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.targetPoint.header.seq, _x.targetPoint.header.stamp.secs, _x.targetPoint.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.targetPoint.header.frame_id = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.targetPoint.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 57
      (_x.targetPoint.pose.position.x, _x.targetPoint.pose.position.y, _x.targetPoint.pose.position.z, _x.targetPoint.pose.orientation.x, _x.targetPoint.pose.orientation.y, _x.targetPoint.pose.orientation.z, _x.targetPoint.pose.orientation.w, _x.uavID,) = _get_struct_7dB().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_3I = None
def _get_struct_3I():
    global _struct_3I
    if _struct_3I is None:
        _struct_3I = struct.Struct("<3I")
    return _struct_3I
_struct_7dB = None
def _get_struct_7dB():
    global _struct_7dB
    if _struct_7dB is None:
        _struct_7dB = struct.Struct("<7dB")
    return _struct_7dB
# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from offboard_control/isUavArrivedResponse.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class isUavArrivedResponse(genpy.Message):
  _md5sum = "88de213cbe7d52dbd07f813d1b12f40a"
  _type = "offboard_control/isUavArrivedResponse"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """bool isArrived
"""
  __slots__ = ['isArrived']
  _slot_types = ['bool']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       isArrived

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(isUavArrivedResponse, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.isArrived is None:
        self.isArrived = False
    else:
      self.isArrived = False

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
      _x = self.isArrived
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
      (self.isArrived,) = _get_struct_B().unpack(str[start:end])
      self.isArrived = bool(self.isArrived)
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
      _x = self.isArrived
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
      (self.isArrived,) = _get_struct_B().unpack(str[start:end])
      self.isArrived = bool(self.isArrived)
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
class isUavArrived(object):
  _type          = 'offboard_control/isUavArrived'
  _md5sum = '260e64ccdbc79f78d3e3be5abe67c990'
  _request_class  = isUavArrivedRequest
  _response_class = isUavArrivedResponse
