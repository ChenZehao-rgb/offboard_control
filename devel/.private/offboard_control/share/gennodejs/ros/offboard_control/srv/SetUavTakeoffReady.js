// Auto-generated. Do not edit!

// (in-package offboard_control.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class SetUavTakeoffReadyRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.uavID = null;
    }
    else {
      if (initObj.hasOwnProperty('uavID')) {
        this.uavID = initObj.uavID
      }
      else {
        this.uavID = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetUavTakeoffReadyRequest
    // Serialize message field [uavID]
    bufferOffset = _serializer.uint8(obj.uavID, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetUavTakeoffReadyRequest
    let len;
    let data = new SetUavTakeoffReadyRequest(null);
    // Deserialize message field [uavID]
    data.uavID = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'offboard_control/SetUavTakeoffReadyRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '69ae467ce8ff6cb85ca62e798d7a5406';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 uavID
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetUavTakeoffReadyRequest(null);
    if (msg.uavID !== undefined) {
      resolved.uavID = msg.uavID;
    }
    else {
      resolved.uavID = 0
    }

    return resolved;
    }
};

class SetUavTakeoffReadyResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.offboard_enabled = null;
      this.armed = null;
    }
    else {
      if (initObj.hasOwnProperty('offboard_enabled')) {
        this.offboard_enabled = initObj.offboard_enabled
      }
      else {
        this.offboard_enabled = false;
      }
      if (initObj.hasOwnProperty('armed')) {
        this.armed = initObj.armed
      }
      else {
        this.armed = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetUavTakeoffReadyResponse
    // Serialize message field [offboard_enabled]
    bufferOffset = _serializer.bool(obj.offboard_enabled, buffer, bufferOffset);
    // Serialize message field [armed]
    bufferOffset = _serializer.bool(obj.armed, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetUavTakeoffReadyResponse
    let len;
    let data = new SetUavTakeoffReadyResponse(null);
    // Deserialize message field [offboard_enabled]
    data.offboard_enabled = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [armed]
    data.armed = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 2;
  }

  static datatype() {
    // Returns string type for a service object
    return 'offboard_control/SetUavTakeoffReadyResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '358fed19915ac0f7266841f0ce120de4';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool offboard_enabled
    bool armed
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetUavTakeoffReadyResponse(null);
    if (msg.offboard_enabled !== undefined) {
      resolved.offboard_enabled = msg.offboard_enabled;
    }
    else {
      resolved.offboard_enabled = false
    }

    if (msg.armed !== undefined) {
      resolved.armed = msg.armed;
    }
    else {
      resolved.armed = false
    }

    return resolved;
    }
};

module.exports = {
  Request: SetUavTakeoffReadyRequest,
  Response: SetUavTakeoffReadyResponse,
  md5sum() { return 'bfb94ba5582dfe70c8390e8d16832c2a'; },
  datatype() { return 'offboard_control/SetUavTakeoffReady'; }
};
