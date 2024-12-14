// Auto-generated. Do not edit!

// (in-package offboard_control.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------


//-----------------------------------------------------------

class SetTargetPointRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.targetPoint = null;
      this.uavID = null;
    }
    else {
      if (initObj.hasOwnProperty('targetPoint')) {
        this.targetPoint = initObj.targetPoint
      }
      else {
        this.targetPoint = new geometry_msgs.msg.PoseStamped();
      }
      if (initObj.hasOwnProperty('uavID')) {
        this.uavID = initObj.uavID
      }
      else {
        this.uavID = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetTargetPointRequest
    // Serialize message field [targetPoint]
    bufferOffset = geometry_msgs.msg.PoseStamped.serialize(obj.targetPoint, buffer, bufferOffset);
    // Serialize message field [uavID]
    bufferOffset = _serializer.uint8(obj.uavID, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetTargetPointRequest
    let len;
    let data = new SetTargetPointRequest(null);
    // Deserialize message field [targetPoint]
    data.targetPoint = geometry_msgs.msg.PoseStamped.deserialize(buffer, bufferOffset);
    // Deserialize message field [uavID]
    data.uavID = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += geometry_msgs.msg.PoseStamped.getMessageSize(object.targetPoint);
    return length + 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'offboard_control/SetTargetPointRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'fe78b9b615816ee275f9bae3c27a36c6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/PoseStamped targetPoint
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetTargetPointRequest(null);
    if (msg.targetPoint !== undefined) {
      resolved.targetPoint = geometry_msgs.msg.PoseStamped.Resolve(msg.targetPoint)
    }
    else {
      resolved.targetPoint = new geometry_msgs.msg.PoseStamped()
    }

    if (msg.uavID !== undefined) {
      resolved.uavID = msg.uavID;
    }
    else {
      resolved.uavID = 0
    }

    return resolved;
    }
};

class SetTargetPointResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.success = null;
    }
    else {
      if (initObj.hasOwnProperty('success')) {
        this.success = initObj.success
      }
      else {
        this.success = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetTargetPointResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetTargetPointResponse
    let len;
    let data = new SetTargetPointResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'offboard_control/SetTargetPointResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '358e233cde0c8a8bcfea4ce193f8fc15';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool success
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetTargetPointResponse(null);
    if (msg.success !== undefined) {
      resolved.success = msg.success;
    }
    else {
      resolved.success = false
    }

    return resolved;
    }
};

module.exports = {
  Request: SetTargetPointRequest,
  Response: SetTargetPointResponse,
  md5sum() { return '9a658aee9c9634e4e1d337a3edbe9137'; },
  datatype() { return 'offboard_control/SetTargetPoint'; }
};
