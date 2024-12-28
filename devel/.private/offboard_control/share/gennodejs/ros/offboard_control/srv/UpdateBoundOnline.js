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

class UpdateBoundOnlineRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.velBound = null;
      this.accBound = null;
    }
    else {
      if (initObj.hasOwnProperty('velBound')) {
        this.velBound = initObj.velBound
      }
      else {
        this.velBound = new geometry_msgs.msg.Vector3();
      }
      if (initObj.hasOwnProperty('accBound')) {
        this.accBound = initObj.accBound
      }
      else {
        this.accBound = new geometry_msgs.msg.Vector3();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type UpdateBoundOnlineRequest
    // Serialize message field [velBound]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.velBound, buffer, bufferOffset);
    // Serialize message field [accBound]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.accBound, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type UpdateBoundOnlineRequest
    let len;
    let data = new UpdateBoundOnlineRequest(null);
    // Deserialize message field [velBound]
    data.velBound = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    // Deserialize message field [accBound]
    data.accBound = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 48;
  }

  static datatype() {
    // Returns string type for a service object
    return 'offboard_control/UpdateBoundOnlineRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c55196be5ab9eb3efa8c6c0801e7ab77';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Vector3 velBound
    geometry_msgs/Vector3 accBound
    
    ================================================================================
    MSG: geometry_msgs/Vector3
    # This represents a vector in free space. 
    # It is only meant to represent a direction. Therefore, it does not
    # make sense to apply a translation to it (e.g., when applying a 
    # generic rigid transformation to a Vector3, tf2 will only apply the
    # rotation). If you want your data to be translatable too, use the
    # geometry_msgs/Point message instead.
    
    float64 x
    float64 y
    float64 z
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new UpdateBoundOnlineRequest(null);
    if (msg.velBound !== undefined) {
      resolved.velBound = geometry_msgs.msg.Vector3.Resolve(msg.velBound)
    }
    else {
      resolved.velBound = new geometry_msgs.msg.Vector3()
    }

    if (msg.accBound !== undefined) {
      resolved.accBound = geometry_msgs.msg.Vector3.Resolve(msg.accBound)
    }
    else {
      resolved.accBound = new geometry_msgs.msg.Vector3()
    }

    return resolved;
    }
};

class UpdateBoundOnlineResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.success = null;
      this.isBoundUpdate = null;
    }
    else {
      if (initObj.hasOwnProperty('success')) {
        this.success = initObj.success
      }
      else {
        this.success = false;
      }
      if (initObj.hasOwnProperty('isBoundUpdate')) {
        this.isBoundUpdate = initObj.isBoundUpdate
      }
      else {
        this.isBoundUpdate = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type UpdateBoundOnlineResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    // Serialize message field [isBoundUpdate]
    bufferOffset = _serializer.bool(obj.isBoundUpdate, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type UpdateBoundOnlineResponse
    let len;
    let data = new UpdateBoundOnlineResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [isBoundUpdate]
    data.isBoundUpdate = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 2;
  }

  static datatype() {
    // Returns string type for a service object
    return 'offboard_control/UpdateBoundOnlineResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8c83de6d27285b4ae782a6260754280b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool success
    bool isBoundUpdate
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new UpdateBoundOnlineResponse(null);
    if (msg.success !== undefined) {
      resolved.success = msg.success;
    }
    else {
      resolved.success = false
    }

    if (msg.isBoundUpdate !== undefined) {
      resolved.isBoundUpdate = msg.isBoundUpdate;
    }
    else {
      resolved.isBoundUpdate = false
    }

    return resolved;
    }
};

module.exports = {
  Request: UpdateBoundOnlineRequest,
  Response: UpdateBoundOnlineResponse,
  md5sum() { return 'b63d0873a52c6e04efd40342ee8fed38'; },
  datatype() { return 'offboard_control/UpdateBoundOnline'; }
};
