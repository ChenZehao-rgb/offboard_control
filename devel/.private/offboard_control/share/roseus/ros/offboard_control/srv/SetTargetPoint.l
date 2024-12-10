;; Auto-generated. Do not edit!


(when (boundp 'offboard_control::SetTargetPoint)
  (if (not (find-package "OFFBOARD_CONTROL"))
    (make-package "OFFBOARD_CONTROL"))
  (shadow 'SetTargetPoint (find-package "OFFBOARD_CONTROL")))
(unless (find-package "OFFBOARD_CONTROL::SETTARGETPOINT")
  (make-package "OFFBOARD_CONTROL::SETTARGETPOINT"))
(unless (find-package "OFFBOARD_CONTROL::SETTARGETPOINTREQUEST")
  (make-package "OFFBOARD_CONTROL::SETTARGETPOINTREQUEST"))
(unless (find-package "OFFBOARD_CONTROL::SETTARGETPOINTRESPONSE")
  (make-package "OFFBOARD_CONTROL::SETTARGETPOINTRESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))




(defclass offboard_control::SetTargetPointRequest
  :super ros::object
  :slots (_targetPoint ))

(defmethod offboard_control::SetTargetPointRequest
  (:init
   (&key
    ((:targetPoint __targetPoint) (instance geometry_msgs::PoseStamped :init))
    )
   (send-super :init)
   (setq _targetPoint __targetPoint)
   self)
  (:targetPoint
   (&rest __targetPoint)
   (if (keywordp (car __targetPoint))
       (send* _targetPoint __targetPoint)
     (progn
       (if __targetPoint (setq _targetPoint (car __targetPoint)))
       _targetPoint)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/PoseStamped _targetPoint
    (send _targetPoint :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/PoseStamped _targetPoint
       (send _targetPoint :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/PoseStamped _targetPoint
     (send _targetPoint :deserialize buf ptr-) (incf ptr- (send _targetPoint :serialization-length))
   ;;
   self)
  )

(defclass offboard_control::SetTargetPointResponse
  :super ros::object
  :slots (_success ))

(defmethod offboard_control::SetTargetPointResponse
  (:init
   (&key
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _success __success)
   self)
  (:success
   (&optional (__success :null))
   (if (not (eq __success :null)) (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass offboard_control::SetTargetPoint
  :super ros::object
  :slots ())

(setf (get offboard_control::SetTargetPoint :md5sum-) "51439c92d41e3c6de0a9c8267b7eef43")
(setf (get offboard_control::SetTargetPoint :datatype-) "offboard_control/SetTargetPoint")
(setf (get offboard_control::SetTargetPoint :request) offboard_control::SetTargetPointRequest)
(setf (get offboard_control::SetTargetPoint :response) offboard_control::SetTargetPointResponse)

(defmethod offboard_control::SetTargetPointRequest
  (:response () (instance offboard_control::SetTargetPointResponse :init)))

(setf (get offboard_control::SetTargetPointRequest :md5sum-) "51439c92d41e3c6de0a9c8267b7eef43")
(setf (get offboard_control::SetTargetPointRequest :datatype-) "offboard_control/SetTargetPointRequest")
(setf (get offboard_control::SetTargetPointRequest :definition-)
      "geometry_msgs/PoseStamped targetPoint

================================================================================
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
---
bool success
")

(setf (get offboard_control::SetTargetPointResponse :md5sum-) "51439c92d41e3c6de0a9c8267b7eef43")
(setf (get offboard_control::SetTargetPointResponse :datatype-) "offboard_control/SetTargetPointResponse")
(setf (get offboard_control::SetTargetPointResponse :definition-)
      "geometry_msgs/PoseStamped targetPoint

================================================================================
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
---
bool success
")



(provide :offboard_control/SetTargetPoint "51439c92d41e3c6de0a9c8267b7eef43")

