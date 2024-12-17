; Auto-generated. Do not edit!


(cl:in-package offboard_control-srv)


;//! \htmlinclude SetUavTakeoffReady-request.msg.html

(cl:defclass <SetUavTakeoffReady-request> (roslisp-msg-protocol:ros-message)
  ((uavID
    :reader uavID
    :initarg :uavID
    :type cl:fixnum
    :initform 0))
)

(cl:defclass SetUavTakeoffReady-request (<SetUavTakeoffReady-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetUavTakeoffReady-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetUavTakeoffReady-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-srv:<SetUavTakeoffReady-request> is deprecated: use offboard_control-srv:SetUavTakeoffReady-request instead.")))

(cl:ensure-generic-function 'uavID-val :lambda-list '(m))
(cl:defmethod uavID-val ((m <SetUavTakeoffReady-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:uavID-val is deprecated.  Use offboard_control-srv:uavID instead.")
  (uavID m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetUavTakeoffReady-request>) ostream)
  "Serializes a message object of type '<SetUavTakeoffReady-request>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'uavID)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetUavTakeoffReady-request>) istream)
  "Deserializes a message object of type '<SetUavTakeoffReady-request>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'uavID)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetUavTakeoffReady-request>)))
  "Returns string type for a service object of type '<SetUavTakeoffReady-request>"
  "offboard_control/SetUavTakeoffReadyRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetUavTakeoffReady-request)))
  "Returns string type for a service object of type 'SetUavTakeoffReady-request"
  "offboard_control/SetUavTakeoffReadyRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetUavTakeoffReady-request>)))
  "Returns md5sum for a message object of type '<SetUavTakeoffReady-request>"
  "bfb94ba5582dfe70c8390e8d16832c2a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetUavTakeoffReady-request)))
  "Returns md5sum for a message object of type 'SetUavTakeoffReady-request"
  "bfb94ba5582dfe70c8390e8d16832c2a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetUavTakeoffReady-request>)))
  "Returns full string definition for message of type '<SetUavTakeoffReady-request>"
  (cl:format cl:nil "uint8 uavID~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetUavTakeoffReady-request)))
  "Returns full string definition for message of type 'SetUavTakeoffReady-request"
  (cl:format cl:nil "uint8 uavID~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetUavTakeoffReady-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetUavTakeoffReady-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetUavTakeoffReady-request
    (cl:cons ':uavID (uavID msg))
))
;//! \htmlinclude SetUavTakeoffReady-response.msg.html

(cl:defclass <SetUavTakeoffReady-response> (roslisp-msg-protocol:ros-message)
  ((offboard_enabled
    :reader offboard_enabled
    :initarg :offboard_enabled
    :type cl:boolean
    :initform cl:nil)
   (armed
    :reader armed
    :initarg :armed
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetUavTakeoffReady-response (<SetUavTakeoffReady-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetUavTakeoffReady-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetUavTakeoffReady-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-srv:<SetUavTakeoffReady-response> is deprecated: use offboard_control-srv:SetUavTakeoffReady-response instead.")))

(cl:ensure-generic-function 'offboard_enabled-val :lambda-list '(m))
(cl:defmethod offboard_enabled-val ((m <SetUavTakeoffReady-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:offboard_enabled-val is deprecated.  Use offboard_control-srv:offboard_enabled instead.")
  (offboard_enabled m))

(cl:ensure-generic-function 'armed-val :lambda-list '(m))
(cl:defmethod armed-val ((m <SetUavTakeoffReady-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:armed-val is deprecated.  Use offboard_control-srv:armed instead.")
  (armed m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetUavTakeoffReady-response>) ostream)
  "Serializes a message object of type '<SetUavTakeoffReady-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'offboard_enabled) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'armed) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetUavTakeoffReady-response>) istream)
  "Deserializes a message object of type '<SetUavTakeoffReady-response>"
    (cl:setf (cl:slot-value msg 'offboard_enabled) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'armed) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetUavTakeoffReady-response>)))
  "Returns string type for a service object of type '<SetUavTakeoffReady-response>"
  "offboard_control/SetUavTakeoffReadyResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetUavTakeoffReady-response)))
  "Returns string type for a service object of type 'SetUavTakeoffReady-response"
  "offboard_control/SetUavTakeoffReadyResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetUavTakeoffReady-response>)))
  "Returns md5sum for a message object of type '<SetUavTakeoffReady-response>"
  "bfb94ba5582dfe70c8390e8d16832c2a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetUavTakeoffReady-response)))
  "Returns md5sum for a message object of type 'SetUavTakeoffReady-response"
  "bfb94ba5582dfe70c8390e8d16832c2a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetUavTakeoffReady-response>)))
  "Returns full string definition for message of type '<SetUavTakeoffReady-response>"
  (cl:format cl:nil "bool offboard_enabled~%bool armed~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetUavTakeoffReady-response)))
  "Returns full string definition for message of type 'SetUavTakeoffReady-response"
  (cl:format cl:nil "bool offboard_enabled~%bool armed~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetUavTakeoffReady-response>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetUavTakeoffReady-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetUavTakeoffReady-response
    (cl:cons ':offboard_enabled (offboard_enabled msg))
    (cl:cons ':armed (armed msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetUavTakeoffReady)))
  'SetUavTakeoffReady-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetUavTakeoffReady)))
  'SetUavTakeoffReady-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetUavTakeoffReady)))
  "Returns string type for a service object of type '<SetUavTakeoffReady>"
  "offboard_control/SetUavTakeoffReady")