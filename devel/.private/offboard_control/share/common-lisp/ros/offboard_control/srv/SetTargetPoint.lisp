; Auto-generated. Do not edit!


(cl:in-package offboard_control-srv)


;//! \htmlinclude SetTargetPoint-request.msg.html

(cl:defclass <SetTargetPoint-request> (roslisp-msg-protocol:ros-message)
  ((targetPoint
    :reader targetPoint
    :initarg :targetPoint
    :type geometry_msgs-msg:PoseStamped
    :initform (cl:make-instance 'geometry_msgs-msg:PoseStamped))
   (targetPointRaw
    :reader targetPointRaw
    :initarg :targetPointRaw
    :type mavros_msgs-msg:PositionTarget
    :initform (cl:make-instance 'mavros_msgs-msg:PositionTarget))
   (uavID
    :reader uavID
    :initarg :uavID
    :type cl:fixnum
    :initform 0))
)

(cl:defclass SetTargetPoint-request (<SetTargetPoint-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetTargetPoint-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetTargetPoint-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-srv:<SetTargetPoint-request> is deprecated: use offboard_control-srv:SetTargetPoint-request instead.")))

(cl:ensure-generic-function 'targetPoint-val :lambda-list '(m))
(cl:defmethod targetPoint-val ((m <SetTargetPoint-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:targetPoint-val is deprecated.  Use offboard_control-srv:targetPoint instead.")
  (targetPoint m))

(cl:ensure-generic-function 'targetPointRaw-val :lambda-list '(m))
(cl:defmethod targetPointRaw-val ((m <SetTargetPoint-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:targetPointRaw-val is deprecated.  Use offboard_control-srv:targetPointRaw instead.")
  (targetPointRaw m))

(cl:ensure-generic-function 'uavID-val :lambda-list '(m))
(cl:defmethod uavID-val ((m <SetTargetPoint-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:uavID-val is deprecated.  Use offboard_control-srv:uavID instead.")
  (uavID m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetTargetPoint-request>) ostream)
  "Serializes a message object of type '<SetTargetPoint-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'targetPoint) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'targetPointRaw) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'uavID)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetTargetPoint-request>) istream)
  "Deserializes a message object of type '<SetTargetPoint-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'targetPoint) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'targetPointRaw) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'uavID)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetTargetPoint-request>)))
  "Returns string type for a service object of type '<SetTargetPoint-request>"
  "offboard_control/SetTargetPointRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetTargetPoint-request)))
  "Returns string type for a service object of type 'SetTargetPoint-request"
  "offboard_control/SetTargetPointRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetTargetPoint-request>)))
  "Returns md5sum for a message object of type '<SetTargetPoint-request>"
  "fcd605373e89b0a0850fa783080be9b9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetTargetPoint-request)))
  "Returns md5sum for a message object of type 'SetTargetPoint-request"
  "fcd605373e89b0a0850fa783080be9b9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetTargetPoint-request>)))
  "Returns full string definition for message of type '<SetTargetPoint-request>"
  (cl:format cl:nil "geometry_msgs/PoseStamped targetPoint~%mavros_msgs/PositionTarget targetPointRaw~%uint8 uavID~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: mavros_msgs/PositionTarget~%# Message for SET_POSITION_TARGET_LOCAL_NED~%#~%# Some complex system requires all feautures that mavlink~%# message provide. See issue #402.~%~%std_msgs/Header header~%~%uint8 coordinate_frame~%uint8 FRAME_LOCAL_NED = 1~%uint8 FRAME_LOCAL_OFFSET_NED = 7~%uint8 FRAME_BODY_NED = 8~%uint8 FRAME_BODY_OFFSET_NED = 9~%~%uint16 type_mask~%uint16 IGNORE_PX = 1	# Position ignore flags~%uint16 IGNORE_PY = 2~%uint16 IGNORE_PZ = 4~%uint16 IGNORE_VX = 8	# Velocity vector ignore flags~%uint16 IGNORE_VY = 16~%uint16 IGNORE_VZ = 32~%uint16 IGNORE_AFX = 64	# Acceleration/Force vector ignore flags~%uint16 IGNORE_AFY = 128~%uint16 IGNORE_AFZ = 256~%uint16 FORCE = 512	# Force in af vector flag~%uint16 IGNORE_YAW = 1024~%uint16 IGNORE_YAW_RATE = 2048~%~%geometry_msgs/Point position~%geometry_msgs/Vector3 velocity~%geometry_msgs/Vector3 acceleration_or_force~%float32 yaw~%float32 yaw_rate~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetTargetPoint-request)))
  "Returns full string definition for message of type 'SetTargetPoint-request"
  (cl:format cl:nil "geometry_msgs/PoseStamped targetPoint~%mavros_msgs/PositionTarget targetPointRaw~%uint8 uavID~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: mavros_msgs/PositionTarget~%# Message for SET_POSITION_TARGET_LOCAL_NED~%#~%# Some complex system requires all feautures that mavlink~%# message provide. See issue #402.~%~%std_msgs/Header header~%~%uint8 coordinate_frame~%uint8 FRAME_LOCAL_NED = 1~%uint8 FRAME_LOCAL_OFFSET_NED = 7~%uint8 FRAME_BODY_NED = 8~%uint8 FRAME_BODY_OFFSET_NED = 9~%~%uint16 type_mask~%uint16 IGNORE_PX = 1	# Position ignore flags~%uint16 IGNORE_PY = 2~%uint16 IGNORE_PZ = 4~%uint16 IGNORE_VX = 8	# Velocity vector ignore flags~%uint16 IGNORE_VY = 16~%uint16 IGNORE_VZ = 32~%uint16 IGNORE_AFX = 64	# Acceleration/Force vector ignore flags~%uint16 IGNORE_AFY = 128~%uint16 IGNORE_AFZ = 256~%uint16 FORCE = 512	# Force in af vector flag~%uint16 IGNORE_YAW = 1024~%uint16 IGNORE_YAW_RATE = 2048~%~%geometry_msgs/Point position~%geometry_msgs/Vector3 velocity~%geometry_msgs/Vector3 acceleration_or_force~%float32 yaw~%float32 yaw_rate~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetTargetPoint-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'targetPoint))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'targetPointRaw))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetTargetPoint-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetTargetPoint-request
    (cl:cons ':targetPoint (targetPoint msg))
    (cl:cons ':targetPointRaw (targetPointRaw msg))
    (cl:cons ':uavID (uavID msg))
))
;//! \htmlinclude SetTargetPoint-response.msg.html

(cl:defclass <SetTargetPoint-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetTargetPoint-response (<SetTargetPoint-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetTargetPoint-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetTargetPoint-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-srv:<SetTargetPoint-response> is deprecated: use offboard_control-srv:SetTargetPoint-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetTargetPoint-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:success-val is deprecated.  Use offboard_control-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetTargetPoint-response>) ostream)
  "Serializes a message object of type '<SetTargetPoint-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetTargetPoint-response>) istream)
  "Deserializes a message object of type '<SetTargetPoint-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetTargetPoint-response>)))
  "Returns string type for a service object of type '<SetTargetPoint-response>"
  "offboard_control/SetTargetPointResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetTargetPoint-response)))
  "Returns string type for a service object of type 'SetTargetPoint-response"
  "offboard_control/SetTargetPointResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetTargetPoint-response>)))
  "Returns md5sum for a message object of type '<SetTargetPoint-response>"
  "fcd605373e89b0a0850fa783080be9b9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetTargetPoint-response)))
  "Returns md5sum for a message object of type 'SetTargetPoint-response"
  "fcd605373e89b0a0850fa783080be9b9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetTargetPoint-response>)))
  "Returns full string definition for message of type '<SetTargetPoint-response>"
  (cl:format cl:nil "bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetTargetPoint-response)))
  "Returns full string definition for message of type 'SetTargetPoint-response"
  (cl:format cl:nil "bool success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetTargetPoint-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetTargetPoint-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetTargetPoint-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetTargetPoint)))
  'SetTargetPoint-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetTargetPoint)))
  'SetTargetPoint-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetTargetPoint)))
  "Returns string type for a service object of type '<SetTargetPoint>"
  "offboard_control/SetTargetPoint")