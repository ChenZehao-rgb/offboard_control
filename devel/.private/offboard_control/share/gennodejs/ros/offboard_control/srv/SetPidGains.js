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

class SetPidGainsRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.pid_axis = null;
      this.kp = null;
      this.ki = null;
      this.kd = null;
      this.i_max = null;
      this.i_min = null;
      this.vz_min = null;
      this.vz_max = null;
    }
    else {
      if (initObj.hasOwnProperty('pid_axis')) {
        this.pid_axis = initObj.pid_axis
      }
      else {
        this.pid_axis = 0;
      }
      if (initObj.hasOwnProperty('kp')) {
        this.kp = initObj.kp
      }
      else {
        this.kp = 0.0;
      }
      if (initObj.hasOwnProperty('ki')) {
        this.ki = initObj.ki
      }
      else {
        this.ki = 0.0;
      }
      if (initObj.hasOwnProperty('kd')) {
        this.kd = initObj.kd
      }
      else {
        this.kd = 0.0;
      }
      if (initObj.hasOwnProperty('i_max')) {
        this.i_max = initObj.i_max
      }
      else {
        this.i_max = 0.0;
      }
      if (initObj.hasOwnProperty('i_min')) {
        this.i_min = initObj.i_min
      }
      else {
        this.i_min = 0.0;
      }
      if (initObj.hasOwnProperty('vz_min')) {
        this.vz_min = initObj.vz_min
      }
      else {
        this.vz_min = 0.0;
      }
      if (initObj.hasOwnProperty('vz_max')) {
        this.vz_max = initObj.vz_max
      }
      else {
        this.vz_max = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SetPidGainsRequest
    // Serialize message field [pid_axis]
    bufferOffset = _serializer.int32(obj.pid_axis, buffer, bufferOffset);
    // Serialize message field [kp]
    bufferOffset = _serializer.float64(obj.kp, buffer, bufferOffset);
    // Serialize message field [ki]
    bufferOffset = _serializer.float64(obj.ki, buffer, bufferOffset);
    // Serialize message field [kd]
    bufferOffset = _serializer.float64(obj.kd, buffer, bufferOffset);
    // Serialize message field [i_max]
    bufferOffset = _serializer.float64(obj.i_max, buffer, bufferOffset);
    // Serialize message field [i_min]
    bufferOffset = _serializer.float64(obj.i_min, buffer, bufferOffset);
    // Serialize message field [vz_min]
    bufferOffset = _serializer.float64(obj.vz_min, buffer, bufferOffset);
    // Serialize message field [vz_max]
    bufferOffset = _serializer.float64(obj.vz_max, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetPidGainsRequest
    let len;
    let data = new SetPidGainsRequest(null);
    // Deserialize message field [pid_axis]
    data.pid_axis = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [kp]
    data.kp = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [ki]
    data.ki = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [kd]
    data.kd = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [i_max]
    data.i_max = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [i_min]
    data.i_min = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [vz_min]
    data.vz_min = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [vz_max]
    data.vz_max = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 60;
  }

  static datatype() {
    // Returns string type for a service object
    return 'offboard_control/SetPidGainsRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '87e160b42ecf66d2bbfac1a23360455c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 pid_axis
    float64 kp
    float64 ki
    float64 kd
    float64 i_max
    float64 i_min
    float64 vz_min
    float64 vz_max
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SetPidGainsRequest(null);
    if (msg.pid_axis !== undefined) {
      resolved.pid_axis = msg.pid_axis;
    }
    else {
      resolved.pid_axis = 0
    }

    if (msg.kp !== undefined) {
      resolved.kp = msg.kp;
    }
    else {
      resolved.kp = 0.0
    }

    if (msg.ki !== undefined) {
      resolved.ki = msg.ki;
    }
    else {
      resolved.ki = 0.0
    }

    if (msg.kd !== undefined) {
      resolved.kd = msg.kd;
    }
    else {
      resolved.kd = 0.0
    }

    if (msg.i_max !== undefined) {
      resolved.i_max = msg.i_max;
    }
    else {
      resolved.i_max = 0.0
    }

    if (msg.i_min !== undefined) {
      resolved.i_min = msg.i_min;
    }
    else {
      resolved.i_min = 0.0
    }

    if (msg.vz_min !== undefined) {
      resolved.vz_min = msg.vz_min;
    }
    else {
      resolved.vz_min = 0.0
    }

    if (msg.vz_max !== undefined) {
      resolved.vz_max = msg.vz_max;
    }
    else {
      resolved.vz_max = 0.0
    }

    return resolved;
    }
};

class SetPidGainsResponse {
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
    // Serializes a message object of type SetPidGainsResponse
    // Serialize message field [success]
    bufferOffset = _serializer.bool(obj.success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SetPidGainsResponse
    let len;
    let data = new SetPidGainsResponse(null);
    // Deserialize message field [success]
    data.success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'offboard_control/SetPidGainsResponse';
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
    const resolved = new SetPidGainsResponse(null);
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
  Request: SetPidGainsRequest,
  Response: SetPidGainsResponse,
  md5sum() { return '1855f912182466f5ec4438809773bb3c'; },
  datatype() { return 'offboard_control/SetPidGains'; }
};
