; Auto-generated. Do not edit!


(cl:in-package offboard_control-srv)


;//! \htmlinclude GenTrajOnline-request.msg.html

(cl:defclass <GenTrajOnline-request> (roslisp-msg-protocol:ros-message)
  ((targPoint
    :reader targPoint
    :initarg :targPoint
    :type mavros_msgs-msg:PositionTarget
    :initform (cl:make-instance 'mavros_msgs-msg:PositionTarget))
   (pose
    :reader pose
    :initarg :pose
    :type geometry_msgs-msg:PoseStamped
    :initform (cl:make-instance 'geometry_msgs-msg:PoseStamped))
   (twist
    :reader twist
    :initarg :twist
    :type geometry_msgs-msg:TwistStamped
    :initform (cl:make-instance 'geometry_msgs-msg:TwistStamped))
   (acc
    :reader acc
    :initarg :acc
    :type geometry_msgs-msg:AccelWithCovarianceStamped
    :initform (cl:make-instance 'geometry_msgs-msg:AccelWithCovarianceStamped))
   (isUpdateState
    :reader isUpdateState
    :initarg :isUpdateState
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GenTrajOnline-request (<GenTrajOnline-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GenTrajOnline-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GenTrajOnline-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-srv:<GenTrajOnline-request> is deprecated: use offboard_control-srv:GenTrajOnline-request instead.")))

(cl:ensure-generic-function 'targPoint-val :lambda-list '(m))
(cl:defmethod targPoint-val ((m <GenTrajOnline-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:targPoint-val is deprecated.  Use offboard_control-srv:targPoint instead.")
  (targPoint m))

(cl:ensure-generic-function 'pose-val :lambda-list '(m))
(cl:defmethod pose-val ((m <GenTrajOnline-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:pose-val is deprecated.  Use offboard_control-srv:pose instead.")
  (pose m))

(cl:ensure-generic-function 'twist-val :lambda-list '(m))
(cl:defmethod twist-val ((m <GenTrajOnline-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:twist-val is deprecated.  Use offboard_control-srv:twist instead.")
  (twist m))

(cl:ensure-generic-function 'acc-val :lambda-list '(m))
(cl:defmethod acc-val ((m <GenTrajOnline-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:acc-val is deprecated.  Use offboard_control-srv:acc instead.")
  (acc m))

(cl:ensure-generic-function 'isUpdateState-val :lambda-list '(m))
(cl:defmethod isUpdateState-val ((m <GenTrajOnline-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:isUpdateState-val is deprecated.  Use offboard_control-srv:isUpdateState instead.")
  (isUpdateState m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GenTrajOnline-request>) ostream)
  "Serializes a message object of type '<GenTrajOnline-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'targPoint) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'twist) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'acc) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'isUpdateState) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GenTrajOnline-request>) istream)
  "Deserializes a message object of type '<GenTrajOnline-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'targPoint) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'twist) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'acc) istream)
    (cl:setf (cl:slot-value msg 'isUpdateState) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GenTrajOnline-request>)))
  "Returns string type for a service object of type '<GenTrajOnline-request>"
  "offboard_control/GenTrajOnlineRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GenTrajOnline-request)))
  "Returns string type for a service object of type 'GenTrajOnline-request"
  "offboard_control/GenTrajOnlineRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GenTrajOnline-request>)))
  "Returns md5sum for a message object of type '<GenTrajOnline-request>"
  "4d549d1dedf81e3210ca57165d54ba1c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GenTrajOnline-request)))
  "Returns md5sum for a message object of type 'GenTrajOnline-request"
  "4d549d1dedf81e3210ca57165d54ba1c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GenTrajOnline-request>)))
  "Returns full string definition for message of type '<GenTrajOnline-request>"
  (cl:format cl:nil "mavros_msgs/PositionTarget targPoint~%geometry_msgs/PoseStamped pose~%geometry_msgs/TwistStamped twist~%geometry_msgs/AccelWithCovarianceStamped acc~%bool isUpdateState~%~%================================================================================~%MSG: mavros_msgs/PositionTarget~%# Message for SET_POSITION_TARGET_LOCAL_NED~%#~%# Some complex system requires all feautures that mavlink~%# message provide. See issue #402.~%~%std_msgs/Header header~%~%uint8 coordinate_frame~%uint8 FRAME_LOCAL_NED = 1~%uint8 FRAME_LOCAL_OFFSET_NED = 7~%uint8 FRAME_BODY_NED = 8~%uint8 FRAME_BODY_OFFSET_NED = 9~%~%uint16 type_mask~%uint16 IGNORE_PX = 1	# Position ignore flags~%uint16 IGNORE_PY = 2~%uint16 IGNORE_PZ = 4~%uint16 IGNORE_VX = 8	# Velocity vector ignore flags~%uint16 IGNORE_VY = 16~%uint16 IGNORE_VZ = 32~%uint16 IGNORE_AFX = 64	# Acceleration/Force vector ignore flags~%uint16 IGNORE_AFY = 128~%uint16 IGNORE_AFZ = 256~%uint16 FORCE = 512	# Force in af vector flag~%uint16 IGNORE_YAW = 1024~%uint16 IGNORE_YAW_RATE = 2048~%~%geometry_msgs/Point position~%geometry_msgs/Vector3 velocity~%geometry_msgs/Vector3 acceleration_or_force~%float32 yaw~%float32 yaw_rate~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: geometry_msgs/TwistStamped~%# A twist with reference coordinate frame and timestamp~%Header header~%Twist twist~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/AccelWithCovarianceStamped~%# This represents an estimated accel with reference coordinate frame and timestamp.~%Header header~%AccelWithCovariance accel~%~%================================================================================~%MSG: geometry_msgs/AccelWithCovariance~%# This expresses acceleration in free space with uncertainty.~%~%Accel accel~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Accel~%# This expresses acceleration in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GenTrajOnline-request)))
  "Returns full string definition for message of type 'GenTrajOnline-request"
  (cl:format cl:nil "mavros_msgs/PositionTarget targPoint~%geometry_msgs/PoseStamped pose~%geometry_msgs/TwistStamped twist~%geometry_msgs/AccelWithCovarianceStamped acc~%bool isUpdateState~%~%================================================================================~%MSG: mavros_msgs/PositionTarget~%# Message for SET_POSITION_TARGET_LOCAL_NED~%#~%# Some complex system requires all feautures that mavlink~%# message provide. See issue #402.~%~%std_msgs/Header header~%~%uint8 coordinate_frame~%uint8 FRAME_LOCAL_NED = 1~%uint8 FRAME_LOCAL_OFFSET_NED = 7~%uint8 FRAME_BODY_NED = 8~%uint8 FRAME_BODY_OFFSET_NED = 9~%~%uint16 type_mask~%uint16 IGNORE_PX = 1	# Position ignore flags~%uint16 IGNORE_PY = 2~%uint16 IGNORE_PZ = 4~%uint16 IGNORE_VX = 8	# Velocity vector ignore flags~%uint16 IGNORE_VY = 16~%uint16 IGNORE_VZ = 32~%uint16 IGNORE_AFX = 64	# Acceleration/Force vector ignore flags~%uint16 IGNORE_AFY = 128~%uint16 IGNORE_AFZ = 256~%uint16 FORCE = 512	# Force in af vector flag~%uint16 IGNORE_YAW = 1024~%uint16 IGNORE_YAW_RATE = 2048~%~%geometry_msgs/Point position~%geometry_msgs/Vector3 velocity~%geometry_msgs/Vector3 acceleration_or_force~%float32 yaw~%float32 yaw_rate~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: geometry_msgs/TwistStamped~%# A twist with reference coordinate frame and timestamp~%Header header~%Twist twist~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/AccelWithCovarianceStamped~%# This represents an estimated accel with reference coordinate frame and timestamp.~%Header header~%AccelWithCovariance accel~%~%================================================================================~%MSG: geometry_msgs/AccelWithCovariance~%# This expresses acceleration in free space with uncertainty.~%~%Accel accel~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Accel~%# This expresses acceleration in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GenTrajOnline-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'targPoint))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'twist))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'acc))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GenTrajOnline-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GenTrajOnline-request
    (cl:cons ':targPoint (targPoint msg))
    (cl:cons ':pose (pose msg))
    (cl:cons ':twist (twist msg))
    (cl:cons ':acc (acc msg))
    (cl:cons ':isUpdateState (isUpdateState msg))
))
;//! \htmlinclude GenTrajOnline-response.msg.html

(cl:defclass <GenTrajOnline-response> (roslisp-msg-protocol:ros-message)
  ((setPointRaw
    :reader setPointRaw
    :initarg :setPointRaw
    :type mavros_msgs-msg:PositionTarget
    :initform (cl:make-instance 'mavros_msgs-msg:PositionTarget))
   (success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GenTrajOnline-response (<GenTrajOnline-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GenTrajOnline-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GenTrajOnline-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-srv:<GenTrajOnline-response> is deprecated: use offboard_control-srv:GenTrajOnline-response instead.")))

(cl:ensure-generic-function 'setPointRaw-val :lambda-list '(m))
(cl:defmethod setPointRaw-val ((m <GenTrajOnline-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:setPointRaw-val is deprecated.  Use offboard_control-srv:setPointRaw instead.")
  (setPointRaw m))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <GenTrajOnline-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:success-val is deprecated.  Use offboard_control-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GenTrajOnline-response>) ostream)
  "Serializes a message object of type '<GenTrajOnline-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'setPointRaw) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GenTrajOnline-response>) istream)
  "Deserializes a message object of type '<GenTrajOnline-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'setPointRaw) istream)
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GenTrajOnline-response>)))
  "Returns string type for a service object of type '<GenTrajOnline-response>"
  "offboard_control/GenTrajOnlineResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GenTrajOnline-response)))
  "Returns string type for a service object of type 'GenTrajOnline-response"
  "offboard_control/GenTrajOnlineResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GenTrajOnline-response>)))
  "Returns md5sum for a message object of type '<GenTrajOnline-response>"
  "4d549d1dedf81e3210ca57165d54ba1c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GenTrajOnline-response)))
  "Returns md5sum for a message object of type 'GenTrajOnline-response"
  "4d549d1dedf81e3210ca57165d54ba1c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GenTrajOnline-response>)))
  "Returns full string definition for message of type '<GenTrajOnline-response>"
  (cl:format cl:nil "mavros_msgs/PositionTarget setPointRaw~%bool success~%~%================================================================================~%MSG: mavros_msgs/PositionTarget~%# Message for SET_POSITION_TARGET_LOCAL_NED~%#~%# Some complex system requires all feautures that mavlink~%# message provide. See issue #402.~%~%std_msgs/Header header~%~%uint8 coordinate_frame~%uint8 FRAME_LOCAL_NED = 1~%uint8 FRAME_LOCAL_OFFSET_NED = 7~%uint8 FRAME_BODY_NED = 8~%uint8 FRAME_BODY_OFFSET_NED = 9~%~%uint16 type_mask~%uint16 IGNORE_PX = 1	# Position ignore flags~%uint16 IGNORE_PY = 2~%uint16 IGNORE_PZ = 4~%uint16 IGNORE_VX = 8	# Velocity vector ignore flags~%uint16 IGNORE_VY = 16~%uint16 IGNORE_VZ = 32~%uint16 IGNORE_AFX = 64	# Acceleration/Force vector ignore flags~%uint16 IGNORE_AFY = 128~%uint16 IGNORE_AFZ = 256~%uint16 FORCE = 512	# Force in af vector flag~%uint16 IGNORE_YAW = 1024~%uint16 IGNORE_YAW_RATE = 2048~%~%geometry_msgs/Point position~%geometry_msgs/Vector3 velocity~%geometry_msgs/Vector3 acceleration_or_force~%float32 yaw~%float32 yaw_rate~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GenTrajOnline-response)))
  "Returns full string definition for message of type 'GenTrajOnline-response"
  (cl:format cl:nil "mavros_msgs/PositionTarget setPointRaw~%bool success~%~%================================================================================~%MSG: mavros_msgs/PositionTarget~%# Message for SET_POSITION_TARGET_LOCAL_NED~%#~%# Some complex system requires all feautures that mavlink~%# message provide. See issue #402.~%~%std_msgs/Header header~%~%uint8 coordinate_frame~%uint8 FRAME_LOCAL_NED = 1~%uint8 FRAME_LOCAL_OFFSET_NED = 7~%uint8 FRAME_BODY_NED = 8~%uint8 FRAME_BODY_OFFSET_NED = 9~%~%uint16 type_mask~%uint16 IGNORE_PX = 1	# Position ignore flags~%uint16 IGNORE_PY = 2~%uint16 IGNORE_PZ = 4~%uint16 IGNORE_VX = 8	# Velocity vector ignore flags~%uint16 IGNORE_VY = 16~%uint16 IGNORE_VZ = 32~%uint16 IGNORE_AFX = 64	# Acceleration/Force vector ignore flags~%uint16 IGNORE_AFY = 128~%uint16 IGNORE_AFZ = 256~%uint16 FORCE = 512	# Force in af vector flag~%uint16 IGNORE_YAW = 1024~%uint16 IGNORE_YAW_RATE = 2048~%~%geometry_msgs/Point position~%geometry_msgs/Vector3 velocity~%geometry_msgs/Vector3 acceleration_or_force~%float32 yaw~%float32 yaw_rate~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GenTrajOnline-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'setPointRaw))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GenTrajOnline-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GenTrajOnline-response
    (cl:cons ':setPointRaw (setPointRaw msg))
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GenTrajOnline)))
  'GenTrajOnline-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GenTrajOnline)))
  'GenTrajOnline-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GenTrajOnline)))
  "Returns string type for a service object of type '<GenTrajOnline>"
  "offboard_control/GenTrajOnline")