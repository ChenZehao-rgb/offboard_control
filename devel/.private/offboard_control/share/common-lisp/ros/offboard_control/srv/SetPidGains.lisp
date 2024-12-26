; Auto-generated. Do not edit!


(cl:in-package offboard_control-srv)


;//! \htmlinclude SetPidGains-request.msg.html

(cl:defclass <SetPidGains-request> (roslisp-msg-protocol:ros-message)
  ((pid_axis
    :reader pid_axis
    :initarg :pid_axis
    :type cl:integer
    :initform 0)
   (kp
    :reader kp
    :initarg :kp
    :type cl:float
    :initform 0.0)
   (ki
    :reader ki
    :initarg :ki
    :type cl:float
    :initform 0.0)
   (kd
    :reader kd
    :initarg :kd
    :type cl:float
    :initform 0.0)
   (i_max
    :reader i_max
    :initarg :i_max
    :type cl:float
    :initform 0.0)
   (i_min
    :reader i_min
    :initarg :i_min
    :type cl:float
    :initform 0.0)
   (vz_min
    :reader vz_min
    :initarg :vz_min
    :type cl:float
    :initform 0.0)
   (vz_max
    :reader vz_max
    :initarg :vz_max
    :type cl:float
    :initform 0.0))
)

(cl:defclass SetPidGains-request (<SetPidGains-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetPidGains-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetPidGains-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-srv:<SetPidGains-request> is deprecated: use offboard_control-srv:SetPidGains-request instead.")))

(cl:ensure-generic-function 'pid_axis-val :lambda-list '(m))
(cl:defmethod pid_axis-val ((m <SetPidGains-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:pid_axis-val is deprecated.  Use offboard_control-srv:pid_axis instead.")
  (pid_axis m))

(cl:ensure-generic-function 'kp-val :lambda-list '(m))
(cl:defmethod kp-val ((m <SetPidGains-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:kp-val is deprecated.  Use offboard_control-srv:kp instead.")
  (kp m))

(cl:ensure-generic-function 'ki-val :lambda-list '(m))
(cl:defmethod ki-val ((m <SetPidGains-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:ki-val is deprecated.  Use offboard_control-srv:ki instead.")
  (ki m))

(cl:ensure-generic-function 'kd-val :lambda-list '(m))
(cl:defmethod kd-val ((m <SetPidGains-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:kd-val is deprecated.  Use offboard_control-srv:kd instead.")
  (kd m))

(cl:ensure-generic-function 'i_max-val :lambda-list '(m))
(cl:defmethod i_max-val ((m <SetPidGains-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:i_max-val is deprecated.  Use offboard_control-srv:i_max instead.")
  (i_max m))

(cl:ensure-generic-function 'i_min-val :lambda-list '(m))
(cl:defmethod i_min-val ((m <SetPidGains-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:i_min-val is deprecated.  Use offboard_control-srv:i_min instead.")
  (i_min m))

(cl:ensure-generic-function 'vz_min-val :lambda-list '(m))
(cl:defmethod vz_min-val ((m <SetPidGains-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:vz_min-val is deprecated.  Use offboard_control-srv:vz_min instead.")
  (vz_min m))

(cl:ensure-generic-function 'vz_max-val :lambda-list '(m))
(cl:defmethod vz_max-val ((m <SetPidGains-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:vz_max-val is deprecated.  Use offboard_control-srv:vz_max instead.")
  (vz_max m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetPidGains-request>) ostream)
  "Serializes a message object of type '<SetPidGains-request>"
  (cl:let* ((signed (cl:slot-value msg 'pid_axis)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'kp))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'ki))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'kd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'i_max))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'i_min))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'vz_min))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'vz_max))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetPidGains-request>) istream)
  "Deserializes a message object of type '<SetPidGains-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'pid_axis) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'kp) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ki) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'kd) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'i_max) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'i_min) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vz_min) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vz_max) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetPidGains-request>)))
  "Returns string type for a service object of type '<SetPidGains-request>"
  "offboard_control/SetPidGainsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetPidGains-request)))
  "Returns string type for a service object of type 'SetPidGains-request"
  "offboard_control/SetPidGainsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetPidGains-request>)))
  "Returns md5sum for a message object of type '<SetPidGains-request>"
  "1855f912182466f5ec4438809773bb3c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetPidGains-request)))
  "Returns md5sum for a message object of type 'SetPidGains-request"
  "1855f912182466f5ec4438809773bb3c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetPidGains-request>)))
  "Returns full string definition for message of type '<SetPidGains-request>"
  (cl:format cl:nil "int32 pid_axis~%float64 kp~%float64 ki~%float64 kd~%float64 i_max~%float64 i_min~%float64 vz_min~%float64 vz_max~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetPidGains-request)))
  "Returns full string definition for message of type 'SetPidGains-request"
  (cl:format cl:nil "int32 pid_axis~%float64 kp~%float64 ki~%float64 kd~%float64 i_max~%float64 i_min~%float64 vz_min~%float64 vz_max~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetPidGains-request>))
  (cl:+ 0
     4
     8
     8
     8
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetPidGains-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetPidGains-request
    (cl:cons ':pid_axis (pid_axis msg))
    (cl:cons ':kp (kp msg))
    (cl:cons ':ki (ki msg))
    (cl:cons ':kd (kd msg))
    (cl:cons ':i_max (i_max msg))
    (cl:cons ':i_min (i_min msg))
    (cl:cons ':vz_min (vz_min msg))
    (cl:cons ':vz_max (vz_max msg))
))
;//! \htmlinclude SetPidGains-response.msg.html

(cl:defclass <SetPidGains-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetPidGains-response (<SetPidGains-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetPidGains-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetPidGains-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-srv:<SetPidGains-response> is deprecated: use offboard_control-srv:SetPidGains-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetPidGains-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:success-val is deprecated.  Use offboard_control-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetPidGains-response>) ostream)
  "Serializes a message object of type '<SetPidGains-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetPidGains-response>) istream)
  "Deserializes a message object of type '<SetPidGains-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetPidGains-response>)))
  "Returns string type for a service object of type '<SetPidGains-response>"
  "offboard_control/SetPidGainsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetPidGains-response)))
  "Returns string type for a service object of type 'SetPidGains-response"
  "offboard_control/SetPidGainsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetPidGains-response>)))
  "Returns md5sum for a message object of type '<SetPidGains-response>"
  "1855f912182466f5ec4438809773bb3c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetPidGains-response)))
  "Returns md5sum for a message object of type 'SetPidGains-response"
  "1855f912182466f5ec4438809773bb3c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetPidGains-response>)))
  "Returns full string definition for message of type '<SetPidGains-response>"
  (cl:format cl:nil "bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetPidGains-response)))
  "Returns full string definition for message of type 'SetPidGains-response"
  (cl:format cl:nil "bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetPidGains-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetPidGains-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetPidGains-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetPidGains)))
  'SetPidGains-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetPidGains)))
  'SetPidGains-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetPidGains)))
  "Returns string type for a service object of type '<SetPidGains>"
  "offboard_control/SetPidGains")