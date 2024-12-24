// Auto-generated. Do not edit!

// (in-package offboard_control.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class Status {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.state = null;
      this.uav1_position = null;
      this.uav1_orientation = null;
      this.uav2_position = null;
      this.uav2_orientation = null;
    }
    else {
      if (initObj.hasOwnProperty('state')) {
        this.state = initObj.state
      }
      else {
        this.state = '';
      }
      if (initObj.hasOwnProperty('uav1_position')) {
        this.uav1_position = initObj.uav1_position
      }
      else {
        this.uav1_position = new geometry_msgs.msg.Pose();
      }
      if (initObj.hasOwnProperty('uav1_orientation')) {
        this.uav1_orientation = initObj.uav1_orientation
      }
      else {
        this.uav1_orientation = new geometry_msgs.msg.Quaternion();
      }
      if (initObj.hasOwnProperty('uav2_position')) {
        this.uav2_position = initObj.uav2_position
      }
      else {
        this.uav2_position = new geometry_msgs.msg.Pose();
      }
      if (initObj.hasOwnProperty('uav2_orientation')) {
        this.uav2_orientation = initObj.uav2_orientation
      }
      else {
        this.uav2_orientation = new geometry_msgs.msg.Quaternion();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Status
    // Serialize message field [state]
    bufferOffset = _serializer.string(obj.state, buffer, bufferOffset);
    // Serialize message field [uav1_position]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.uav1_position, buffer, bufferOffset);
    // Serialize message field [uav1_orientation]
    bufferOffset = geometry_msgs.msg.Quaternion.serialize(obj.uav1_orientation, buffer, bufferOffset);
    // Serialize message field [uav2_position]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.uav2_position, buffer, bufferOffset);
    // Serialize message field [uav2_orientation]
    bufferOffset = geometry_msgs.msg.Quaternion.serialize(obj.uav2_orientation, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Status
    let len;
    let data = new Status(null);
    // Deserialize message field [state]
    data.state = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [uav1_position]
    data.uav1_position = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    // Deserialize message field [uav1_orientation]
    data.uav1_orientation = geometry_msgs.msg.Quaternion.deserialize(buffer, bufferOffset);
    // Deserialize message field [uav2_position]
    data.uav2_position = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    // Deserialize message field [uav2_orientation]
    data.uav2_orientation = geometry_msgs.msg.Quaternion.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.state);
    return length + 180;
  }

  static datatype() {
    // Returns string type for a message object
    return 'offboard_control/Status';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a0c7abb5783c6834587efbd77de4a4a3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string state
    geometry_msgs/Pose uav1_position
    geometry_msgs/Quaternion uav1_orientation
    geometry_msgs/Pose uav2_position
    geometry_msgs/Quaternion uav2_orientation
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
    const resolved = new Status(null);
    if (msg.state !== undefined) {
      resolved.state = msg.state;
    }
    else {
      resolved.state = ''
    }

    if (msg.uav1_position !== undefined) {
      resolved.uav1_position = geometry_msgs.msg.Pose.Resolve(msg.uav1_position)
    }
    else {
      resolved.uav1_position = new geometry_msgs.msg.Pose()
    }

    if (msg.uav1_orientation !== undefined) {
      resolved.uav1_orientation = geometry_msgs.msg.Quaternion.Resolve(msg.uav1_orientation)
    }
    else {
      resolved.uav1_orientation = new geometry_msgs.msg.Quaternion()
    }

    if (msg.uav2_position !== undefined) {
      resolved.uav2_position = geometry_msgs.msg.Pose.Resolve(msg.uav2_position)
    }
    else {
      resolved.uav2_position = new geometry_msgs.msg.Pose()
    }

    if (msg.uav2_orientation !== undefined) {
      resolved.uav2_orientation = geometry_msgs.msg.Quaternion.Resolve(msg.uav2_orientation)
    }
    else {
      resolved.uav2_orientation = new geometry_msgs.msg.Quaternion()
    }

    return resolved;
    }
};

module.exports = Status;
