; Auto-generated. Do not edit!


(cl:in-package offboard_control-msg)


;//! \htmlinclude Status.msg.html

(cl:defclass <Status> (roslisp-msg-protocol:ros-message)
  ((state
    :reader state
    :initarg :state
    :type cl:string
    :initform "")
   (uav1_position
    :reader uav1_position
    :initarg :uav1_position
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (uav1_orientation
    :reader uav1_orientation
    :initarg :uav1_orientation
    :type geometry_msgs-msg:Quaternion
    :initform (cl:make-instance 'geometry_msgs-msg:Quaternion))
   (uav2_position
    :reader uav2_position
    :initarg :uav2_position
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (uav2_orientation
    :reader uav2_orientation
    :initarg :uav2_orientation
    :type geometry_msgs-msg:Quaternion
    :initform (cl:make-instance 'geometry_msgs-msg:Quaternion)))
)

(cl:defclass Status (<Status>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Status>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Status)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-msg:<Status> is deprecated: use offboard_control-msg:Status instead.")))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-msg:state-val is deprecated.  Use offboard_control-msg:state instead.")
  (state m))

(cl:ensure-generic-function 'uav1_position-val :lambda-list '(m))
(cl:defmethod uav1_position-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-msg:uav1_position-val is deprecated.  Use offboard_control-msg:uav1_position instead.")
  (uav1_position m))

(cl:ensure-generic-function 'uav1_orientation-val :lambda-list '(m))
(cl:defmethod uav1_orientation-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-msg:uav1_orientation-val is deprecated.  Use offboard_control-msg:uav1_orientation instead.")
  (uav1_orientation m))

(cl:ensure-generic-function 'uav2_position-val :lambda-list '(m))
(cl:defmethod uav2_position-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-msg:uav2_position-val is deprecated.  Use offboard_control-msg:uav2_position instead.")
  (uav2_position m))

(cl:ensure-generic-function 'uav2_orientation-val :lambda-list '(m))
(cl:defmethod uav2_orientation-val ((m <Status>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-msg:uav2_orientation-val is deprecated.  Use offboard_control-msg:uav2_orientation instead.")
  (uav2_orientation m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Status>) ostream)
  "Serializes a message object of type '<Status>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'state))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'uav1_position) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'uav1_orientation) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'uav2_position) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'uav2_orientation) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Status>) istream)
  "Deserializes a message object of type '<Status>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'state) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'state) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'uav1_position) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'uav1_orientation) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'uav2_position) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'uav2_orientation) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Status>)))
  "Returns string type for a message object of type '<Status>"
  "offboard_control/Status")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Status)))
  "Returns string type for a message object of type 'Status"
  "offboard_control/Status")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Status>)))
  "Returns md5sum for a message object of type '<Status>"
  "a0c7abb5783c6834587efbd77de4a4a3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Status)))
  "Returns md5sum for a message object of type 'Status"
  "a0c7abb5783c6834587efbd77de4a4a3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Status>)))
  "Returns full string definition for message of type '<Status>"
  (cl:format cl:nil "string state~%geometry_msgs/Pose uav1_position~%geometry_msgs/Quaternion uav1_orientation~%geometry_msgs/Pose uav2_position~%geometry_msgs/Quaternion uav2_orientation~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Status)))
  "Returns full string definition for message of type 'Status"
  (cl:format cl:nil "string state~%geometry_msgs/Pose uav1_position~%geometry_msgs/Quaternion uav1_orientation~%geometry_msgs/Pose uav2_position~%geometry_msgs/Quaternion uav2_orientation~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Status>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'state))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'uav1_position))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'uav1_orientation))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'uav2_position))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'uav2_orientation))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Status>))
  "Converts a ROS message object to a list"
  (cl:list 'Status
    (cl:cons ':state (state msg))
    (cl:cons ':uav1_position (uav1_position msg))
    (cl:cons ':uav1_orientation (uav1_orientation msg))
    (cl:cons ':uav2_position (uav2_position msg))
    (cl:cons ':uav2_orientation (uav2_orientation msg))
))
