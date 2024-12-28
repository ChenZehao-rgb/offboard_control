; Auto-generated. Do not edit!


(cl:in-package offboard_control-srv)


;//! \htmlinclude UpdateBoundOnline-request.msg.html

(cl:defclass <UpdateBoundOnline-request> (roslisp-msg-protocol:ros-message)
  ((velBound
    :reader velBound
    :initarg :velBound
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (accBound
    :reader accBound
    :initarg :accBound
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass UpdateBoundOnline-request (<UpdateBoundOnline-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <UpdateBoundOnline-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'UpdateBoundOnline-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-srv:<UpdateBoundOnline-request> is deprecated: use offboard_control-srv:UpdateBoundOnline-request instead.")))

(cl:ensure-generic-function 'velBound-val :lambda-list '(m))
(cl:defmethod velBound-val ((m <UpdateBoundOnline-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:velBound-val is deprecated.  Use offboard_control-srv:velBound instead.")
  (velBound m))

(cl:ensure-generic-function 'accBound-val :lambda-list '(m))
(cl:defmethod accBound-val ((m <UpdateBoundOnline-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:accBound-val is deprecated.  Use offboard_control-srv:accBound instead.")
  (accBound m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <UpdateBoundOnline-request>) ostream)
  "Serializes a message object of type '<UpdateBoundOnline-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'velBound) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'accBound) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <UpdateBoundOnline-request>) istream)
  "Deserializes a message object of type '<UpdateBoundOnline-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'velBound) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'accBound) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<UpdateBoundOnline-request>)))
  "Returns string type for a service object of type '<UpdateBoundOnline-request>"
  "offboard_control/UpdateBoundOnlineRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'UpdateBoundOnline-request)))
  "Returns string type for a service object of type 'UpdateBoundOnline-request"
  "offboard_control/UpdateBoundOnlineRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<UpdateBoundOnline-request>)))
  "Returns md5sum for a message object of type '<UpdateBoundOnline-request>"
  "b63d0873a52c6e04efd40342ee8fed38")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'UpdateBoundOnline-request)))
  "Returns md5sum for a message object of type 'UpdateBoundOnline-request"
  "b63d0873a52c6e04efd40342ee8fed38")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<UpdateBoundOnline-request>)))
  "Returns full string definition for message of type '<UpdateBoundOnline-request>"
  (cl:format cl:nil "geometry_msgs/Vector3 velBound~%geometry_msgs/Vector3 accBound~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'UpdateBoundOnline-request)))
  "Returns full string definition for message of type 'UpdateBoundOnline-request"
  (cl:format cl:nil "geometry_msgs/Vector3 velBound~%geometry_msgs/Vector3 accBound~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <UpdateBoundOnline-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'velBound))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'accBound))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <UpdateBoundOnline-request>))
  "Converts a ROS message object to a list"
  (cl:list 'UpdateBoundOnline-request
    (cl:cons ':velBound (velBound msg))
    (cl:cons ':accBound (accBound msg))
))
;//! \htmlinclude UpdateBoundOnline-response.msg.html

(cl:defclass <UpdateBoundOnline-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil)
   (isBoundUpdate
    :reader isBoundUpdate
    :initarg :isBoundUpdate
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass UpdateBoundOnline-response (<UpdateBoundOnline-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <UpdateBoundOnline-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'UpdateBoundOnline-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name offboard_control-srv:<UpdateBoundOnline-response> is deprecated: use offboard_control-srv:UpdateBoundOnline-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <UpdateBoundOnline-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:success-val is deprecated.  Use offboard_control-srv:success instead.")
  (success m))

(cl:ensure-generic-function 'isBoundUpdate-val :lambda-list '(m))
(cl:defmethod isBoundUpdate-val ((m <UpdateBoundOnline-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader offboard_control-srv:isBoundUpdate-val is deprecated.  Use offboard_control-srv:isBoundUpdate instead.")
  (isBoundUpdate m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <UpdateBoundOnline-response>) ostream)
  "Serializes a message object of type '<UpdateBoundOnline-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'isBoundUpdate) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <UpdateBoundOnline-response>) istream)
  "Deserializes a message object of type '<UpdateBoundOnline-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'isBoundUpdate) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<UpdateBoundOnline-response>)))
  "Returns string type for a service object of type '<UpdateBoundOnline-response>"
  "offboard_control/UpdateBoundOnlineResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'UpdateBoundOnline-response)))
  "Returns string type for a service object of type 'UpdateBoundOnline-response"
  "offboard_control/UpdateBoundOnlineResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<UpdateBoundOnline-response>)))
  "Returns md5sum for a message object of type '<UpdateBoundOnline-response>"
  "b63d0873a52c6e04efd40342ee8fed38")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'UpdateBoundOnline-response)))
  "Returns md5sum for a message object of type 'UpdateBoundOnline-response"
  "b63d0873a52c6e04efd40342ee8fed38")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<UpdateBoundOnline-response>)))
  "Returns full string definition for message of type '<UpdateBoundOnline-response>"
  (cl:format cl:nil "bool success~%bool isBoundUpdate~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'UpdateBoundOnline-response)))
  "Returns full string definition for message of type 'UpdateBoundOnline-response"
  (cl:format cl:nil "bool success~%bool isBoundUpdate~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <UpdateBoundOnline-response>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <UpdateBoundOnline-response>))
  "Converts a ROS message object to a list"
  (cl:list 'UpdateBoundOnline-response
    (cl:cons ':success (success msg))
    (cl:cons ':isBoundUpdate (isBoundUpdate msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'UpdateBoundOnline)))
  'UpdateBoundOnline-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'UpdateBoundOnline)))
  'UpdateBoundOnline-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'UpdateBoundOnline)))
  "Returns string type for a service object of type '<UpdateBoundOnline>"
  "offboard_control/UpdateBoundOnline")