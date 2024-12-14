; Auto-generated. Do not edit!


(cl:in-package offboard_control-srv)


;//! \htmlinclude isUavArrived-request.msg.html

(cl:defclass <isUavArrived-request> (roslisp-msg-protocol:ros-message)
  ((targetPoint
    :reader targetPoint
    :initarg :targetPoint
    :type geometry_msgs-msg:PoseStamped
    :initform (cl:make-instance 'geometry_msgs-msg:PoseStamped))
   (uavID
    :reader uavID
    :initarg :uavID
    :type cl:fixnum
    :initform 0))
)

(cl:defclass isUavArrived-request (<isUavArrived-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <isUavArrived-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'isUavArrived-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-srv:<isUavArrived-request> is deprecated: use offboard_control-srv:isUavArrived-request instead.")))

(cl:ensure-generic-function 'targetPoint-val :lambda-list '(m))
(cl:defmethod targetPoint-val ((m <isUavArrived-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:targetPoint-val is deprecated.  Use offboard_control-srv:targetPoint instead.")
  (targetPoint m))

(cl:ensure-generic-function 'uavID-val :lambda-list '(m))
(cl:defmethod uavID-val ((m <isUavArrived-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:uavID-val is deprecated.  Use offboard_control-srv:uavID instead.")
  (uavID m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <isUavArrived-request>) ostream)
  "Serializes a message object of type '<isUavArrived-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'targetPoint) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'uavID)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <isUavArrived-request>) istream)
  "Deserializes a message object of type '<isUavArrived-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'targetPoint) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'uavID)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<isUavArrived-request>)))
  "Returns string type for a service object of type '<isUavArrived-request>"
  "offboard_control/isUavArrivedRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'isUavArrived-request)))
  "Returns string type for a service object of type 'isUavArrived-request"
  "offboard_control/isUavArrivedRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<isUavArrived-request>)))
  "Returns md5sum for a message object of type '<isUavArrived-request>"
  "260e64ccdbc79f78d3e3be5abe67c990")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'isUavArrived-request)))
  "Returns md5sum for a message object of type 'isUavArrived-request"
  "260e64ccdbc79f78d3e3be5abe67c990")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<isUavArrived-request>)))
  "Returns full string definition for message of type '<isUavArrived-request>"
  (cl:format cl:nil "geometry_msgs/PoseStamped targetPoint~%uint8 uavID~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'isUavArrived-request)))
  "Returns full string definition for message of type 'isUavArrived-request"
  (cl:format cl:nil "geometry_msgs/PoseStamped targetPoint~%uint8 uavID~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <isUavArrived-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'targetPoint))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <isUavArrived-request>))
  "Converts a ROS message object to a list"
  (cl:list 'isUavArrived-request
    (cl:cons ':targetPoint (targetPoint msg))
    (cl:cons ':uavID (uavID msg))
))
;//! \htmlinclude isUavArrived-response.msg.html

(cl:defclass <isUavArrived-response> (roslisp-msg-protocol:ros-message)
  ((isArrived
    :reader isArrived
    :initarg :isArrived
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass isUavArrived-response (<isUavArrived-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <isUavArrived-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'isUavArrived-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-srv:<isUavArrived-response> is deprecated: use offboard_control-srv:isUavArrived-response instead.")))

(cl:ensure-generic-function 'isArrived-val :lambda-list '(m))
(cl:defmethod isArrived-val ((m <isUavArrived-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:isArrived-val is deprecated.  Use offboard_control-srv:isArrived instead.")
  (isArrived m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <isUavArrived-response>) ostream)
  "Serializes a message object of type '<isUavArrived-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'isArrived) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <isUavArrived-response>) istream)
  "Deserializes a message object of type '<isUavArrived-response>"
    (cl:setf (cl:slot-value msg 'isArrived) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<isUavArrived-response>)))
  "Returns string type for a service object of type '<isUavArrived-response>"
  "offboard_control/isUavArrivedResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'isUavArrived-response)))
  "Returns string type for a service object of type 'isUavArrived-response"
  "offboard_control/isUavArrivedResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<isUavArrived-response>)))
  "Returns md5sum for a message object of type '<isUavArrived-response>"
  "260e64ccdbc79f78d3e3be5abe67c990")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'isUavArrived-response)))
  "Returns md5sum for a message object of type 'isUavArrived-response"
  "260e64ccdbc79f78d3e3be5abe67c990")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<isUavArrived-response>)))
  "Returns full string definition for message of type '<isUavArrived-response>"
  (cl:format cl:nil "bool isArrived~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'isUavArrived-response)))
  "Returns full string definition for message of type 'isUavArrived-response"
  (cl:format cl:nil "bool isArrived~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <isUavArrived-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <isUavArrived-response>))
  "Converts a ROS message object to a list"
  (cl:list 'isUavArrived-response
    (cl:cons ':isArrived (isArrived msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'isUavArrived)))
  'isUavArrived-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'isUavArrived)))
  'isUavArrived-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'isUavArrived)))
  "Returns string type for a service object of type '<isUavArrived>"
  "offboard_control/isUavArrived")