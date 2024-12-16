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
(if (not (find-package "MAVROS_MSGS"))
  (ros::roseus-add-msgs "mavros_msgs"))




(defclass offboard_control::SetTargetPointRequest
  :super ros::object
  :slots (_targetPoint _targetPointRaw _uavID ))

(defmethod offboard_control::SetTargetPointRequest
  (:init
   (&key
    ((:targetPoint __targetPoint) (instance geometry_msgs::PoseStamped :init))
    ((:targetPointRaw __targetPointRaw) (instance mavros_msgs::PositionTarget :init))
    ((:uavID __uavID) 0)
    )
   (send-super :init)
   (setq _targetPoint __targetPoint)
   (setq _targetPointRaw __targetPointRaw)
   (setq _uavID (round __uavID))
   self)
  (:targetPoint
   (&rest __targetPoint)
   (if (keywordp (car __targetPoint))
       (send* _targetPoint __targetPoint)
     (progn
       (if __targetPoint (setq _targetPoint (car __targetPoint)))
       _targetPoint)))
  (:targetPointRaw
   (&rest __targetPointRaw)
   (if (keywordp (car __targetPointRaw))
       (send* _targetPointRaw __targetPointRaw)
     (progn
       (if __targetPointRaw (setq _targetPointRaw (car __targetPointRaw)))
       _targetPointRaw)))
  (:uavID
   (&optional __uavID)
   (if __uavID (setq _uavID __uavID)) _uavID)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/PoseStamped _targetPoint
    (send _targetPoint :serialization-length)
    ;; mavros_msgs/PositionTarget _targetPointRaw
    (send _targetPointRaw :serialization-length)
    ;; uint8 _uavID
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/PoseStamped _targetPoint
       (send _targetPoint :serialize s)
     ;; mavros_msgs/PositionTarget _targetPointRaw
       (send _targetPointRaw :serialize s)
     ;; uint8 _uavID
       (write-byte _uavID s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/PoseStamped _targetPoint
     (send _targetPoint :deserialize buf ptr-) (incf ptr- (send _targetPoint :serialization-length))
   ;; mavros_msgs/PositionTarget _targetPointRaw
     (send _targetPointRaw :deserialize buf ptr-) (incf ptr- (send _targetPointRaw :serialization-length))
   ;; uint8 _uavID
     (setq _uavID (sys::peek buf ptr- :char)) (incf ptr- 1)
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

(setf (get offboard_control::SetTargetPoint :md5sum-) "fcd605373e89b0a0850fa783080be9b9")
(setf (get offboard_control::SetTargetPoint :datatype-) "offboard_control/SetTargetPoint")
(setf (get offboard_control::SetTargetPoint :request) offboard_control::SetTargetPointRequest)
(setf (get offboard_control::SetTargetPoint :response) offboard_control::SetTargetPointResponse)

(defmethod offboard_control::SetTargetPointRequest
  (:response () (instance offboard_control::SetTargetPointResponse :init)))

(setf (get offboard_control::SetTargetPointRequest :md5sum-) "fcd605373e89b0a0850fa783080be9b9")
(setf (get offboard_control::SetTargetPointRequest :datatype-) "offboard_control/SetTargetPointRequest")
(setf (get offboard_control::SetTargetPointRequest :definition-)
      "geometry_msgs/PoseStamped targetPoint
mavros_msgs/PositionTarget targetPointRaw
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

================================================================================
MSG: mavros_msgs/PositionTarget
# Message for SET_POSITION_TARGET_LOCAL_NED
#
# Some complex system requires all feautures that mavlink
# message provide. See issue #402.

std_msgs/Header header

uint8 coordinate_frame
uint8 FRAME_LOCAL_NED = 1
uint8 FRAME_LOCAL_OFFSET_NED = 7
uint8 FRAME_BODY_NED = 8
uint8 FRAME_BODY_OFFSET_NED = 9

uint16 type_mask
uint16 IGNORE_PX = 1	# Position ignore flags
uint16 IGNORE_PY = 2
uint16 IGNORE_PZ = 4
uint16 IGNORE_VX = 8	# Velocity vector ignore flags
uint16 IGNORE_VY = 16
uint16 IGNORE_VZ = 32
uint16 IGNORE_AFX = 64	# Acceleration/Force vector ignore flags
uint16 IGNORE_AFY = 128
uint16 IGNORE_AFZ = 256
uint16 FORCE = 512	# Force in af vector flag
uint16 IGNORE_YAW = 1024
uint16 IGNORE_YAW_RATE = 2048

geometry_msgs/Point position
geometry_msgs/Vector3 velocity
geometry_msgs/Vector3 acceleration_or_force
float32 yaw
float32 yaw_rate

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
---
bool success
")

(setf (get offboard_control::SetTargetPointResponse :md5sum-) "fcd605373e89b0a0850fa783080be9b9")
(setf (get offboard_control::SetTargetPointResponse :datatype-) "offboard_control/SetTargetPointResponse")
(setf (get offboard_control::SetTargetPointResponse :definition-)
      "geometry_msgs/PoseStamped targetPoint
mavros_msgs/PositionTarget targetPointRaw
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

================================================================================
MSG: mavros_msgs/PositionTarget
# Message for SET_POSITION_TARGET_LOCAL_NED
#
# Some complex system requires all feautures that mavlink
# message provide. See issue #402.

std_msgs/Header header

uint8 coordinate_frame
uint8 FRAME_LOCAL_NED = 1
uint8 FRAME_LOCAL_OFFSET_NED = 7
uint8 FRAME_BODY_NED = 8
uint8 FRAME_BODY_OFFSET_NED = 9

uint16 type_mask
uint16 IGNORE_PX = 1	# Position ignore flags
uint16 IGNORE_PY = 2
uint16 IGNORE_PZ = 4
uint16 IGNORE_VX = 8	# Velocity vector ignore flags
uint16 IGNORE_VY = 16
uint16 IGNORE_VZ = 32
uint16 IGNORE_AFX = 64	# Acceleration/Force vector ignore flags
uint16 IGNORE_AFY = 128
uint16 IGNORE_AFZ = 256
uint16 FORCE = 512	# Force in af vector flag
uint16 IGNORE_YAW = 1024
uint16 IGNORE_YAW_RATE = 2048

geometry_msgs/Point position
geometry_msgs/Vector3 velocity
geometry_msgs/Vector3 acceleration_or_force
float32 yaw
float32 yaw_rate

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
---
bool success
")



(provide :offboard_control/SetTargetPoint "fcd605373e89b0a0850fa783080be9b9")


