; Auto-generated. Do not edit!


(cl:in-package offboard_control-srv)


;//! \htmlinclude SetOffboardCtlType-request.msg.html

(cl:defclass <SetOffboardCtlType-request> (roslisp-msg-protocol:ros-message)
  ((offbCtlType
    :reader offbCtlType
    :initarg :offbCtlType
    :type cl:integer
    :initform 0))
)

(cl:defclass SetOffboardCtlType-request (<SetOffboardCtlType-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetOffboardCtlType-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetOffboardCtlType-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-srv:<SetOffboardCtlType-request> is deprecated: use offboard_control-srv:SetOffboardCtlType-request instead.")))

(cl:ensure-generic-function 'offbCtlType-val :lambda-list '(m))
(cl:defmethod offbCtlType-val ((m <SetOffboardCtlType-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:offbCtlType-val is deprecated.  Use offboard_control-srv:offbCtlType instead.")
  (offbCtlType m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetOffboardCtlType-request>) ostream)
  "Serializes a message object of type '<SetOffboardCtlType-request>"
  (cl:let* ((signed (cl:slot-value msg 'offbCtlType)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetOffboardCtlType-request>) istream)
  "Deserializes a message object of type '<SetOffboardCtlType-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'offbCtlType) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetOffboardCtlType-request>)))
  "Returns string type for a service object of type '<SetOffboardCtlType-request>"
  "offboard_control/SetOffboardCtlTypeRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetOffboardCtlType-request)))
  "Returns string type for a service object of type 'SetOffboardCtlType-request"
  "offboard_control/SetOffboardCtlTypeRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetOffboardCtlType-request>)))
  "Returns md5sum for a message object of type '<SetOffboardCtlType-request>"
  "37b0bbed7a7478a029b22247760de72a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetOffboardCtlType-request)))
  "Returns md5sum for a message object of type 'SetOffboardCtlType-request"
  "37b0bbed7a7478a029b22247760de72a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetOffboardCtlType-request>)))
  "Returns full string definition for message of type '<SetOffboardCtlType-request>"
  (cl:format cl:nil "int32 offbCtlType~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetOffboardCtlType-request)))
  "Returns full string definition for message of type 'SetOffboardCtlType-request"
  (cl:format cl:nil "int32 offbCtlType~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetOffboardCtlType-request>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetOffboardCtlType-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetOffboardCtlType-request
    (cl:cons ':offbCtlType (offbCtlType msg))
))
;//! \htmlinclude SetOffboardCtlType-response.msg.html

(cl:defclass <SetOffboardCtlType-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetOffboardCtlType-response (<SetOffboardCtlType-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetOffboardCtlType-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetOffboardCtlType-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-srv:<SetOffboardCtlType-response> is deprecated: use offboard_control-srv:SetOffboardCtlType-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetOffboardCtlType-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:success-val is deprecated.  Use offboard_control-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetOffboardCtlType-response>) ostream)
  "Serializes a message object of type '<SetOffboardCtlType-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetOffboardCtlType-response>) istream)
  "Deserializes a message object of type '<SetOffboardCtlType-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetOffboardCtlType-response>)))
  "Returns string type for a service object of type '<SetOffboardCtlType-response>"
  "offboard_control/SetOffboardCtlTypeResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetOffboardCtlType-response)))
  "Returns string type for a service object of type 'SetOffboardCtlType-response"
  "offboard_control/SetOffboardCtlTypeResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetOffboardCtlType-response>)))
  "Returns md5sum for a message object of type '<SetOffboardCtlType-response>"
  "37b0bbed7a7478a029b22247760de72a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetOffboardCtlType-response)))
  "Returns md5sum for a message object of type 'SetOffboardCtlType-response"
  "37b0bbed7a7478a029b22247760de72a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetOffboardCtlType-response>)))
  "Returns full string definition for message of type '<SetOffboardCtlType-response>"
  (cl:format cl:nil "bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetOffboardCtlType-response)))
  "Returns full string definition for message of type 'SetOffboardCtlType-response"
  (cl:format cl:nil "bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetOffboardCtlType-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetOffboardCtlType-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetOffboardCtlType-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetOffboardCtlType)))
  'SetOffboardCtlType-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetOffboardCtlType)))
  'SetOffboardCtlType-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetOffboardCtlType)))
  "Returns string type for a service object of type '<SetOffboardCtlType>"
  "offboard_control/SetOffboardCtlType")