;; Auto-generated. Do not edit!


(when (boundp 'offboard_control::isUavArrived)
  (if (not (find-package "OFFBOARD_CONTROL"))
    (make-package "OFFBOARD_CONTROL"))
  (shadow 'isUavArrived (find-package "OFFBOARD_CONTROL")))
(unless (find-package "OFFBOARD_CONTROL::ISUAVARRIVED")
  (make-package "OFFBOARD_CONTROL::ISUAVARRIVED"))
(unless (find-package "OFFBOARD_CONTROL::ISUAVARRIVEDREQUEST")
  (make-package "OFFBOARD_CONTROL::ISUAVARRIVEDREQUEST"))
(unless (find-package "OFFBOARD_CONTROL::ISUAVARRIVEDRESPONSE")
  (make-package "OFFBOARD_CONTROL::ISUAVARRIVEDRESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))




(defclass offboard_control::isUavArrivedRequest
  :super ros::object
  :slots (_targetPoint _uavID ))

(defmethod offboard_control::isUavArrivedRequest
  (:init
   (&key
    ((:targetPoint __targetPoint) (instance geometry_msgs::PoseStamped :init))
    ((:uavID __uavID) 0)
    )
   (send-super :init)
   (setq _targetPoint __targetPoint)
   (setq _uavID (round __uavID))
   self)
  (:targetPoint
   (&rest __targetPoint)
   (if (keywordp (car __targetPoint))
       (send* _targetPoint __targetPoint)
     (progn
       (if __targetPoint (setq _targetPoint (car __targetPoint)))
       _targetPoint)))
  (:uavID
   (&optional __uavID)
   (if __uavID (setq _uavID __uavID)) _uavID)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/PoseStamped _targetPoint
    (send _targetPoint :serialization-length)
    ;; uint8 _uavID
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/PoseStamped _targetPoint
       (send _targetPoint :serialize s)
     ;; uint8 _uavID
       (write-byte _uavID s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/PoseStamped _targetPoint
     (send _targetPoint :deserialize buf ptr-) (incf ptr- (send _targetPoint :serialization-length))
   ;; uint8 _uavID
     (setq _uavID (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(defclass offboard_control::isUavArrivedResponse
  :super ros::object
  :slots (_isArrived ))

(defmethod offboard_control::isUavArrivedResponse
  (:init
   (&key
    ((:isArrived __isArrived) nil)
    )
   (send-super :init)
   (setq _isArrived __isArrived)
   self)
  (:isArrived
   (&optional (__isArrived :null))
   (if (not (eq __isArrived :null)) (setq _isArrived __isArrived)) _isArrived)
  (:serialization-length
   ()
   (+
    ;; bool _isArrived
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _isArrived
       (if _isArrived (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _isArrived
     (setq _isArrived (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass offboard_control::isUavArrived
  :super ros::object
  :slots ())

(setf (get offboard_control::isUavArrived :md5sum-) "260e64ccdbc79f78d3e3be5abe67c990")
(setf (get offboard_control::isUavArrived :datatype-) "offboard_control/isUavArrived")
(setf (get offboard_control::isUavArrived :request) offboard_control::isUavArrivedRequest)
(setf (get offboard_control::isUavArrived :response) offboard_control::isUavArrivedResponse)

(defmethod offboard_control::isUavArrivedRequest
  (:response () (instance offboard_control::isUavArrivedResponse :init)))

(setf (get offboard_control::isUavArrivedRequest :md5sum-) "260e64ccdbc79f78d3e3be5abe67c990")
(setf (get offboard_control::isUavArrivedRequest :datatype-) "offboard_control/isUavArrivedRequest")
(setf (get offboard_control::isUavArrivedRequest :definition-)
      "geometry_msgs/PoseStamped targetPoint
uint8 uavID

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
bool isArrived
")

(setf (get offboard_control::isUavArrivedResponse :md5sum-) "260e64ccdbc79f78d3e3be5abe67c990")
(setf (get offboard_control::isUavArrivedResponse :datatype-) "offboard_control/isUavArrivedResponse")
(setf (get offboard_control::isUavArrivedResponse :definition-)
      "geometry_msgs/PoseStamped targetPoint
uint8 uavID

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
bool isArrived
")



(provide :offboard_control/isUavArrived "260e64ccdbc79f78d3e3be5abe67c990")


