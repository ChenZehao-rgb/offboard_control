;; Auto-generated. Do not edit!


(when (boundp 'offboard_control::GenTrajOnline)
  (if (not (find-package "OFFBOARD_CONTROL"))
    (make-package "OFFBOARD_CONTROL"))
  (shadow 'GenTrajOnline (find-package "OFFBOARD_CONTROL")))
(unless (find-package "OFFBOARD_CONTROL::GENTRAJONLINE")
  (make-package "OFFBOARD_CONTROL::GENTRAJONLINE"))
(unless (find-package "OFFBOARD_CONTROL::GENTRAJONLINEREQUEST")
  (make-package "OFFBOARD_CONTROL::GENTRAJONLINEREQUEST"))
(unless (find-package "OFFBOARD_CONTROL::GENTRAJONLINERESPONSE")
  (make-package "OFFBOARD_CONTROL::GENTRAJONLINERESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "MAVROS_MSGS"))
  (ros::roseus-add-msgs "mavros_msgs"))


(if (not (find-package "MAVROS_MSGS"))
  (ros::roseus-add-msgs "mavros_msgs"))


(defclass offboard_control::GenTrajOnlineRequest
  :super ros::object
  :slots (_targPoint _pose _twist _acc _isUpdateState ))

(defmethod offboard_control::GenTrajOnlineRequest
  (:init
   (&key
    ((:targPoint __targPoint) (instance mavros_msgs::PositionTarget :init))
    ((:pose __pose) (instance geometry_msgs::PoseStamped :init))
    ((:twist __twist) (instance geometry_msgs::TwistStamped :init))
    ((:acc __acc) (instance geometry_msgs::AccelWithCovarianceStamped :init))
    ((:isUpdateState __isUpdateState) nil)
    )
   (send-super :init)
   (setq _targPoint __targPoint)
   (setq _pose __pose)
   (setq _twist __twist)
   (setq _acc __acc)
   (setq _isUpdateState __isUpdateState)
   self)
  (:targPoint
   (&rest __targPoint)
   (if (keywordp (car __targPoint))
       (send* _targPoint __targPoint)
     (progn
       (if __targPoint (setq _targPoint (car __targPoint)))
       _targPoint)))
  (:pose
   (&rest __pose)
   (if (keywordp (car __pose))
       (send* _pose __pose)
     (progn
       (if __pose (setq _pose (car __pose)))
       _pose)))
  (:twist
   (&rest __twist)
   (if (keywordp (car __twist))
       (send* _twist __twist)
     (progn
       (if __twist (setq _twist (car __twist)))
       _twist)))
  (:acc
   (&rest __acc)
   (if (keywordp (car __acc))
       (send* _acc __acc)
     (progn
       (if __acc (setq _acc (car __acc)))
       _acc)))
  (:isUpdateState
   (&optional (__isUpdateState :null))
   (if (not (eq __isUpdateState :null)) (setq _isUpdateState __isUpdateState)) _isUpdateState)
  (:serialization-length
   ()
   (+
    ;; mavros_msgs/PositionTarget _targPoint
    (send _targPoint :serialization-length)
    ;; geometry_msgs/PoseStamped _pose
    (send _pose :serialization-length)
    ;; geometry_msgs/TwistStamped _twist
    (send _twist :serialization-length)
    ;; geometry_msgs/AccelWithCovarianceStamped _acc
    (send _acc :serialization-length)
    ;; bool _isUpdateState
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; mavros_msgs/PositionTarget _targPoint
       (send _targPoint :serialize s)
     ;; geometry_msgs/PoseStamped _pose
       (send _pose :serialize s)
     ;; geometry_msgs/TwistStamped _twist
       (send _twist :serialize s)
     ;; geometry_msgs/AccelWithCovarianceStamped _acc
       (send _acc :serialize s)
     ;; bool _isUpdateState
       (if _isUpdateState (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; mavros_msgs/PositionTarget _targPoint
     (send _targPoint :deserialize buf ptr-) (incf ptr- (send _targPoint :serialization-length))
   ;; geometry_msgs/PoseStamped _pose
     (send _pose :deserialize buf ptr-) (incf ptr- (send _pose :serialization-length))
   ;; geometry_msgs/TwistStamped _twist
     (send _twist :deserialize buf ptr-) (incf ptr- (send _twist :serialization-length))
   ;; geometry_msgs/AccelWithCovarianceStamped _acc
     (send _acc :deserialize buf ptr-) (incf ptr- (send _acc :serialization-length))
   ;; bool _isUpdateState
     (setq _isUpdateState (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass offboard_control::GenTrajOnlineResponse
  :super ros::object
  :slots (_setPointRaw _success ))

(defmethod offboard_control::GenTrajOnlineResponse
  (:init
   (&key
    ((:setPointRaw __setPointRaw) (instance mavros_msgs::PositionTarget :init))
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _setPointRaw __setPointRaw)
   (setq _success __success)
   self)
  (:setPointRaw
   (&rest __setPointRaw)
   (if (keywordp (car __setPointRaw))
       (send* _setPointRaw __setPointRaw)
     (progn
       (if __setPointRaw (setq _setPointRaw (car __setPointRaw)))
       _setPointRaw)))
  (:success
   (&optional (__success :null))
   (if (not (eq __success :null)) (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; mavros_msgs/PositionTarget _setPointRaw
    (send _setPointRaw :serialization-length)
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; mavros_msgs/PositionTarget _setPointRaw
       (send _setPointRaw :serialize s)
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; mavros_msgs/PositionTarget _setPointRaw
     (send _setPointRaw :deserialize buf ptr-) (incf ptr- (send _setPointRaw :serialization-length))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass offboard_control::GenTrajOnline
  :super ros::object
  :slots ())

(setf (get offboard_control::GenTrajOnline :md5sum-) "4d549d1dedf81e3210ca57165d54ba1c")
(setf (get offboard_control::GenTrajOnline :datatype-) "offboard_control/GenTrajOnline")
(setf (get offboard_control::GenTrajOnline :request) offboard_control::GenTrajOnlineRequest)
(setf (get offboard_control::GenTrajOnline :response) offboard_control::GenTrajOnlineResponse)

(defmethod offboard_control::GenTrajOnlineRequest
  (:response () (instance offboard_control::GenTrajOnlineResponse :init)))

(setf (get offboard_control::GenTrajOnlineRequest :md5sum-) "4d549d1dedf81e3210ca57165d54ba1c")
(setf (get offboard_control::GenTrajOnlineRequest :datatype-) "offboard_control/GenTrajOnlineRequest")
(setf (get offboard_control::GenTrajOnlineRequest :definition-)
      "mavros_msgs/PositionTarget targPoint
geometry_msgs/PoseStamped pose
geometry_msgs/TwistStamped twist
geometry_msgs/AccelWithCovarianceStamped acc
bool isUpdateState

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
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

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
float64 z
================================================================================
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

================================================================================
MSG: geometry_msgs/TwistStamped
# A twist with reference coordinate frame and timestamp
Header header
Twist twist

================================================================================
MSG: geometry_msgs/Twist
# This expresses velocity in free space broken into its linear and angular parts.
Vector3  linear
Vector3  angular

================================================================================
MSG: geometry_msgs/AccelWithCovarianceStamped
# This represents an estimated accel with reference coordinate frame and timestamp.
Header header
AccelWithCovariance accel

================================================================================
MSG: geometry_msgs/AccelWithCovariance
# This expresses acceleration in free space with uncertainty.

Accel accel

# Row-major representation of the 6x6 covariance matrix
# The orientation parameters use a fixed-axis representation.
# In order, the parameters are:
# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)
float64[36] covariance

================================================================================
MSG: geometry_msgs/Accel
# This expresses acceleration in free space broken into its linear and angular parts.
Vector3  linear
Vector3  angular
---
mavros_msgs/PositionTarget setPointRaw
bool success

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
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

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
")

(setf (get offboard_control::GenTrajOnlineResponse :md5sum-) "4d549d1dedf81e3210ca57165d54ba1c")
(setf (get offboard_control::GenTrajOnlineResponse :datatype-) "offboard_control/GenTrajOnlineResponse")
(setf (get offboard_control::GenTrajOnlineResponse :definition-)
      "mavros_msgs/PositionTarget targPoint
geometry_msgs/PoseStamped pose
geometry_msgs/TwistStamped twist
geometry_msgs/AccelWithCovarianceStamped acc
bool isUpdateState

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
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

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
float64 z
================================================================================
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

================================================================================
MSG: geometry_msgs/TwistStamped
# A twist with reference coordinate frame and timestamp
Header header
Twist twist

================================================================================
MSG: geometry_msgs/Twist
# This expresses velocity in free space broken into its linear and angular parts.
Vector3  linear
Vector3  angular

================================================================================
MSG: geometry_msgs/AccelWithCovarianceStamped
# This represents an estimated accel with reference coordinate frame and timestamp.
Header header
AccelWithCovariance accel

================================================================================
MSG: geometry_msgs/AccelWithCovariance
# This expresses acceleration in free space with uncertainty.

Accel accel

# Row-major representation of the 6x6 covariance matrix
# The orientation parameters use a fixed-axis representation.
# In order, the parameters are:
# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)
float64[36] covariance

================================================================================
MSG: geometry_msgs/Accel
# This expresses acceleration in free space broken into its linear and angular parts.
Vector3  linear
Vector3  angular
---
mavros_msgs/PositionTarget setPointRaw
bool success

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
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

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
")



(provide :offboard_control/GenTrajOnline "4d549d1dedf81e3210ca57165d54ba1c")


