// Auto-generated. Do not edit!

// (in-package offboard_control.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class OffboardCtlType {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.offb_ctrl_type = null;
    }
    else {
      if (initObj.hasOwnProperty('offb_ctrl_type')) {
        this.offb_ctrl_type = initObj.offb_ctrl_type
      }
      else {
        this.offb_ctrl_type = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type OffboardCtlType
    // Serialize message field [offb_ctrl_type]
    bufferOffset = _serializer.uint8(obj.offb_ctrl_type, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type OffboardCtlType
    let len;
    let data = new OffboardCtlType(null);
    // Deserialize message field [offb_ctrl_type]
    data.offb_ctrl_type = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a message object
    return 'offboard_control/OffboardCtlType';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '640ad7cdefca8d4153a8d8cdc9622cb2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 offb_ctrl_type
    
    uint8 GOTO_SETPOINT_STEP = 0
    uint8 GOTO_SETPOINT_CLOSED_LOOP = 1
    
    uint8 GOTO_SETPOINTS_SERIES = 2
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new OffboardCtlType(null);
    if (msg.offb_ctrl_type !== undefined) {
      resolved.offb_ctrl_type = msg.offb_ctrl_type;
    }
    else {
      resolved.offb_ctrl_type = 0
    }

    return resolved;
    }
};

// Constants for message
OffboardCtlType.Constants = {
  GOTO_SETPOINT_STEP: 0,
  GOTO_SETPOINT_CLOSED_LOOP: 1,
  GOTO_SETPOINTS_SERIES: 2,
}

module.exports = OffboardCtlType;
