; Auto-generated. Do not edit!


(cl:in-package offboard_control-msg)


;//! \htmlinclude OffboardCtlType.msg.html

(cl:defclass <OffboardCtlType> (roslisp-msg-protocol:ros-message)
  ((offb_ctrl_type
    :reader offb_ctrl_type
    :initarg :offb_ctrl_type
    :type cl:fixnum
    :initform 0))
)

(cl:defclass OffboardCtlType (<OffboardCtlType>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <OffboardCtlType>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'OffboardCtlType)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-msg:<OffboardCtlType> is deprecated: use offboard_control-msg:OffboardCtlType instead.")))

(cl:ensure-generic-function 'offb_ctrl_type-val :lambda-list '(m))
(cl:defmethod offb_ctrl_type-val ((m <OffboardCtlType>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-msg:offb_ctrl_type-val is deprecated.  Use offboard_control-msg:offb_ctrl_type instead.")
  (offb_ctrl_type m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<OffboardCtlType>)))
    "Constants for message type '<OffboardCtlType>"
  '((:GOTO_SETPOINT_STEP . 0)
    (:GOTO_SETPOINT_CLOSED_LOOP . 1)
    (:GOTO_SETPOINTS_SERIES . 2))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'OffboardCtlType)))
    "Constants for message type 'OffboardCtlType"
  '((:GOTO_SETPOINT_STEP . 0)
    (:GOTO_SETPOINT_CLOSED_LOOP . 1)
    (:GOTO_SETPOINTS_SERIES . 2))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <OffboardCtlType>) ostream)
  "Serializes a message object of type '<OffboardCtlType>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'offb_ctrl_type)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <OffboardCtlType>) istream)
  "Deserializes a message object of type '<OffboardCtlType>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'offb_ctrl_type)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<OffboardCtlType>)))
  "Returns string type for a message object of type '<OffboardCtlType>"
  "offboard_control/OffboardCtlType")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'OffboardCtlType)))
  "Returns string type for a message object of type 'OffboardCtlType"
  "offboard_control/OffboardCtlType")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<OffboardCtlType>)))
  "Returns md5sum for a message object of type '<OffboardCtlType>"
  "640ad7cdefca8d4153a8d8cdc9622cb2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'OffboardCtlType)))
  "Returns md5sum for a message object of type 'OffboardCtlType"
  "640ad7cdefca8d4153a8d8cdc9622cb2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<OffboardCtlType>)))
  "Returns full string definition for message of type '<OffboardCtlType>"
  (cl:format cl:nil "uint8 offb_ctrl_type~%~%uint8 GOTO_SETPOINT_STEP = 0~%uint8 GOTO_SETPOINT_CLOSED_LOOP = 1~%~%uint8 GOTO_SETPOINTS_SERIES = 2~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'OffboardCtlType)))
  "Returns full string definition for message of type 'OffboardCtlType"
  (cl:format cl:nil "uint8 offb_ctrl_type~%~%uint8 GOTO_SETPOINT_STEP = 0~%uint8 GOTO_SETPOINT_CLOSED_LOOP = 1~%~%uint8 GOTO_SETPOINTS_SERIES = 2~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <OffboardCtlType>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <OffboardCtlType>))
  "Converts a ROS message object to a list"
  (cl:list 'OffboardCtlType
    (cl:cons ':offb_ctrl_type (offb_ctrl_type msg))
))
