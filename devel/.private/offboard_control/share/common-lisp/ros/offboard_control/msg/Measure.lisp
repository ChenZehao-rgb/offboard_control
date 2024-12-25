; Auto-generated. Do not edit!


(cl:in-package offboard_control-msg)


;//! \htmlinclude Measure.msg.html

(cl:defclass <Measure> (roslisp-msg-protocol:ros-message)
  ((is_valid
    :reader is_valid
    :initarg :is_valid
    :type cl:boolean
    :initform cl:nil)
   (x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (z
    :reader z
    :initarg :z
    :type cl:float
    :initform 0.0))
)

(cl:defclass Measure (<Measure>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Measure>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Measure)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-msg:<Measure> is deprecated: use offboard_control-msg:Measure instead.")))

(cl:ensure-generic-function 'is_valid-val :lambda-list '(m))
(cl:defmethod is_valid-val ((m <Measure>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-msg:is_valid-val is deprecated.  Use offboard_control-msg:is_valid instead.")
  (is_valid m))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <Measure>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-msg:x-val is deprecated.  Use offboard_control-msg:x instead.")
  (x m))

(cl:ensure-generic-function 'z-val :lambda-list '(m))
(cl:defmethod z-val ((m <Measure>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-msg:z-val is deprecated.  Use offboard_control-msg:z instead.")
  (z m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Measure>) ostream)
  "Serializes a message object of type '<Measure>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_valid) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Measure>) istream)
  "Deserializes a message object of type '<Measure>"
    (cl:setf (cl:slot-value msg 'is_valid) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'z) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Measure>)))
  "Returns string type for a message object of type '<Measure>"
  "offboard_control/Measure")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Measure)))
  "Returns string type for a message object of type 'Measure"
  "offboard_control/Measure")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Measure>)))
  "Returns md5sum for a message object of type '<Measure>"
  "038007aa6658d27492f7f0c6eeb28f91")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Measure)))
  "Returns md5sum for a message object of type 'Measure"
  "038007aa6658d27492f7f0c6eeb28f91")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Measure>)))
  "Returns full string definition for message of type '<Measure>"
  (cl:format cl:nil "bool is_valid~%float64 x~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Measure)))
  "Returns full string definition for message of type 'Measure"
  (cl:format cl:nil "bool is_valid~%float64 x~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Measure>))
  (cl:+ 0
     1
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Measure>))
  "Converts a ROS message object to a list"
  (cl:list 'Measure
    (cl:cons ':is_valid (is_valid msg))
    (cl:cons ':x (x msg))
    (cl:cons ':z (z msg))
))
