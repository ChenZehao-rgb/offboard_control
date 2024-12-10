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

class SetOffboardCtlTypeRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.offbCtlType = null;
    }
    else {
      if (initObj.hasOwnProperty('offbCtlType')) {
        this.offbCtlType = initObj.offbCtlType
      }
      else {
        this.offbCtlType = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetOffboardCtlTypeRequest
    // Serialize message field [offbCtlType]
    bufferOffset = _serializer.int32(obj.offbCtlType, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetOffboardCtlTypeRequest
    let len;
    let data = new SetOffboardCtlTypeRequest(null);
    // Deserialize message field [offbCtlType]
    data.offbCtlType = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'offboard_control/SetOffboardCtlTypeRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c3d42780a828cad348444e814dd3f03f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 offbCtlType
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetOffboardCtlTypeRequest(null);
    if (msg.offbCtlType !== undefined) {
      resolved.offbCtlType = msg.offbCtlType;
    }
    else {
      resolved.offbCtlType = 0
    }

    return resolved;
    }
};

class SetOffboardCtlTypeResponse {
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
    // Serializes a message object of type SetOffboardCtlTypeResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetOffboardCtlTypeResponse
    let len;
    let data = new SetOffboardCtlTypeResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'offboard_control/SetOffboardCtlTypeResponse';
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
    const resolved = new SetOffboardCtlTypeResponse(null);
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
  Request: SetOffboardCtlTypeRequest,
  Response: SetOffboardCtlTypeResponse,
  md5sum() { return '37b0bbed7a7478a029b22247760de72a'; },
  datatype() { return 'offboard_control/SetOffboardCtlType'; }
};
