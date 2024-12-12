; Auto-generated. Do not edit!


(cl:in-package offboard_control-msg)


;//! \htmlinclude StateControl.msg.html

(cl:defclass <StateControl> (roslisp-msg-protocol:ros-message)
  ((state_ctrl_type
    :reader state_ctrl_type
    :initarg :state_ctrl_type
    :type cl:fixnum
    :initform 0))
)

(cl:defclass StateControl (<StateControl>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StateControl>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StateControl)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-msg:<StateControl> is deprecated: use offboard_control-msg:StateControl instead.")))

(cl:ensure-generic-function 'state_ctrl_type-val :lambda-list '(m))
(cl:defmethod state_ctrl_type-val ((m <StateControl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-msg:state_ctrl_type-val is deprecated.  Use offboard_control-msg:state_ctrl_type instead.")
  (state_ctrl_type m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<StateControl>)))
    "Constants for message type '<StateControl>"
  '((:TAKEOFF . 0)
    (:ARRIVE_ONLINE_POINT . 1)
    (:AJUST_ATTITUDE . 2)
    (:ON_LINE . 3)
    (:FOLLOW_CABLE . 4)
    (:APPROACH_NODE . 5)
    (:CROSS_NODE . 6)
    (:LAND . 7))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'StateControl)))
    "Constants for message type 'StateControl"
  '((:TAKEOFF . 0)
    (:ARRIVE_ONLINE_POINT . 1)
    (:AJUST_ATTITUDE . 2)
    (:ON_LINE . 3)
    (:FOLLOW_CABLE . 4)
    (:APPROACH_NODE . 5)
    (:CROSS_NODE . 6)
    (:LAND . 7))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StateControl>) ostream)
  "Serializes a message object of type '<StateControl>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state_ctrl_type)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StateControl>) istream)
  "Deserializes a message object of type '<StateControl>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state_ctrl_type)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StateControl>)))
  "Returns string type for a message object of type '<StateControl>"
  "offboard_control/StateControl")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StateControl)))
  "Returns string type for a message object of type 'StateControl"
  "offboard_control/StateControl")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StateControl>)))
  "Returns md5sum for a message object of type '<StateControl>"
  "32bbda18dc61a12eea4cc4f9975ef333")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StateControl)))
  "Returns md5sum for a message object of type 'StateControl"
  "32bbda18dc61a12eea4cc4f9975ef333")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StateControl>)))
  "Returns full string definition for message of type '<StateControl>"
  (cl:format cl:nil "uint8 state_ctrl_type~%uint8 TAKEOFF = 0~%uint8 ARRIVE_ONLINE_POINT = 1~%uint8 AJUST_ATTITUDE = 2~%uint8 ON_LINE = 3~%uint8 FOLLOW_CABLE = 4~%uint8 APPROACH_NODE = 5~%uint8 CROSS_NODE = 6~%uint8 LAND = 7~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StateControl)))
  "Returns full string definition for message of type 'StateControl"
  (cl:format cl:nil "uint8 state_ctrl_type~%uint8 TAKEOFF = 0~%uint8 ARRIVE_ONLINE_POINT = 1~%uint8 AJUST_ATTITUDE = 2~%uint8 ON_LINE = 3~%uint8 FOLLOW_CABLE = 4~%uint8 APPROACH_NODE = 5~%uint8 CROSS_NODE = 6~%uint8 LAND = 7~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StateControl>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StateControl>))
  "Converts a ROS message object to a list"
  (cl:list 'StateControl
    (cl:cons ':state_ctrl_type (state_ctrl_type msg))
))
