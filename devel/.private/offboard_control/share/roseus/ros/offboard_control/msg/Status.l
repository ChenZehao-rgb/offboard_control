;; Auto-generated. Do not edit!


(when (boundp 'offboard_control::Status)
  (if (not (find-package "OFFBOARD_CONTROL"))
    (make-package "OFFBOARD_CONTROL"))
  (shadow 'Status (find-package "OFFBOARD_CONTROL")))
(unless (find-package "OFFBOARD_CONTROL::STATUS")
  (make-package "OFFBOARD_CONTROL::STATUS"))

(in-package "ROS")
;;//! \htmlinclude Status.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass offboard_control::Status
  :super ros::object
  :slots (_state _uav2_position _uav2_orientation ))

(defmethod offboard_control::Status
  (:init
   (&key
    ((:state __state) "")
    ((:uav2_position __uav2_position) (instance geometry_msgs::Pose :init))
    ((:uav2_orientation __uav2_orientation) (instance geometry_msgs::Quaternion :init))
    )
   (send-super :init)
   (setq _state (string __state))
   (setq _uav2_position __uav2_position)
   (setq _uav2_orientation __uav2_orientation)
   self)
  (:state
   (&optional __state)
   (if __state (setq _state __state)) _state)
  (:uav2_position
   (&rest __uav2_position)
   (if (keywordp (car __uav2_position))
       (send* _uav2_position __uav2_position)
     (progn
       (if __uav2_position (setq _uav2_position (car __uav2_position)))
       _uav2_position)))
  (:uav2_orientation
   (&rest __uav2_orientation)
   (if (keywordp (car __uav2_orientation))
       (send* _uav2_orientation __uav2_orientation)
     (progn
       (if __uav2_orientation (setq _uav2_orientation (car __uav2_orientation)))
       _uav2_orientation)))
  (:serialization-length
   ()
   (+
    ;; string _state
    4 (length _state)
    ;; geometry_msgs/Pose _uav2_position
    (send _uav2_position :serialization-length)
    ;; geometry_msgs/Quaternion _uav2_orientation
    (send _uav2_orientation :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _state
       (write-long (length _state) s) (princ _state s)
     ;; geometry_msgs/Pose _uav2_position
       (send _uav2_position :serialize s)
     ;; geometry_msgs/Quaternion _uav2_orientation
       (send _uav2_orientation :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _state
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _state (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; geometry_msgs/Pose _uav2_position
     (send _uav2_position :deserialize buf ptr-) (incf ptr- (send _uav2_position :serialization-length))
   ;; geometry_msgs/Quaternion _uav2_orientation
     (send _uav2_orientation :deserialize buf ptr-) (incf ptr- (send _uav2_orientation :serialization-length))
   ;;
   self)
  )

(setf (get offboard_control::Status :md5sum-) "1da643e68400df1829ed9658c05293dc")
(setf (get offboard_control::Status :datatype-) "offboard_control/Status")
(setf (get offboard_control::Status :definition-)
      "string state
geometry_msgs/Pose uav2_position
geometry_msgs/Quaternion uav2_orientation
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

")



(provide :offboard_control/Status "1da643e68400df1829ed9658c05293dc")


