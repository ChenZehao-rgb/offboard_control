;; Auto-generated. Do not edit!


(when (boundp 'offboard_control::SetPidGains)
  (if (not (find-package "OFFBOARD_CONTROL"))
    (make-package "OFFBOARD_CONTROL"))
  (shadow 'SetPidGains (find-package "OFFBOARD_CONTROL")))
(unless (find-package "OFFBOARD_CONTROL::SETPIDGAINS")
  (make-package "OFFBOARD_CONTROL::SETPIDGAINS"))
(unless (find-package "OFFBOARD_CONTROL::SETPIDGAINSREQUEST")
  (make-package "OFFBOARD_CONTROL::SETPIDGAINSREQUEST"))
(unless (find-package "OFFBOARD_CONTROL::SETPIDGAINSRESPONSE")
  (make-package "OFFBOARD_CONTROL::SETPIDGAINSRESPONSE"))

(in-package "ROS")





(defclass offboard_control::SetPidGainsRequest
  :super ros::object
  :slots (_pid_axis _kp _ki _kd _i_max _i_min _vz_min _vz_max ))

(defmethod offboard_control::SetPidGainsRequest
  (:init
   (&key
    ((:pid_axis __pid_axis) 0)
    ((:kp __kp) 0.0)
    ((:ki __ki) 0.0)
    ((:kd __kd) 0.0)
    ((:i_max __i_max) 0.0)
    ((:i_min __i_min) 0.0)
    ((:vz_min __vz_min) 0.0)
    ((:vz_max __vz_max) 0.0)
    )
   (send-super :init)
   (setq _pid_axis (round __pid_axis))
   (setq _kp (float __kp))
   (setq _ki (float __ki))
   (setq _kd (float __kd))
   (setq _i_max (float __i_max))
   (setq _i_min (float __i_min))
   (setq _vz_min (float __vz_min))
   (setq _vz_max (float __vz_max))
   self)
  (:pid_axis
   (&optional __pid_axis)
   (if __pid_axis (setq _pid_axis __pid_axis)) _pid_axis)
  (:kp
   (&optional __kp)
   (if __kp (setq _kp __kp)) _kp)
  (:ki
   (&optional __ki)
   (if __ki (setq _ki __ki)) _ki)
  (:kd
   (&optional __kd)
   (if __kd (setq _kd __kd)) _kd)
  (:i_max
   (&optional __i_max)
   (if __i_max (setq _i_max __i_max)) _i_max)
  (:i_min
   (&optional __i_min)
   (if __i_min (setq _i_min __i_min)) _i_min)
  (:vz_min
   (&optional __vz_min)
   (if __vz_min (setq _vz_min __vz_min)) _vz_min)
  (:vz_max
   (&optional __vz_max)
   (if __vz_max (setq _vz_max __vz_max)) _vz_max)
  (:serialization-length
   ()
   (+
    ;; int32 _pid_axis
    4
    ;; float64 _kp
    8
    ;; float64 _ki
    8
    ;; float64 _kd
    8
    ;; float64 _i_max
    8
    ;; float64 _i_min
    8
    ;; float64 _vz_min
    8
    ;; float64 _vz_max
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _pid_axis
       (write-long _pid_axis s)
     ;; float64 _kp
       (sys::poke _kp (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _ki
       (sys::poke _ki (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _kd
       (sys::poke _kd (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _i_max
       (sys::poke _i_max (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _i_min
       (sys::poke _i_min (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _vz_min
       (sys::poke _vz_min (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _vz_max
       (sys::poke _vz_max (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _pid_axis
     (setq _pid_axis (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _kp
     (setq _kp (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _ki
     (setq _ki (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _kd
     (setq _kd (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _i_max
     (setq _i_max (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _i_min
     (setq _i_min (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _vz_min
     (setq _vz_min (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _vz_max
     (setq _vz_max (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass offboard_control::SetPidGainsResponse
  :super ros::object
  :slots (_success ))

(defmethod offboard_control::SetPidGainsResponse
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

(defclass offboard_control::SetPidGains
  :super ros::object
  :slots ())

(setf (get offboard_control::SetPidGains :md5sum-) "1855f912182466f5ec4438809773bb3c")
(setf (get offboard_control::SetPidGains :datatype-) "offboard_control/SetPidGains")
(setf (get offboard_control::SetPidGains :request) offboard_control::SetPidGainsRequest)
(setf (get offboard_control::SetPidGains :response) offboard_control::SetPidGainsResponse)

(defmethod offboard_control::SetPidGainsRequest
  (:response () (instance offboard_control::SetPidGainsResponse :init)))

(setf (get offboard_control::SetPidGainsRequest :md5sum-) "1855f912182466f5ec4438809773bb3c")
(setf (get offboard_control::SetPidGainsRequest :datatype-) "offboard_control/SetPidGainsRequest")
(setf (get offboard_control::SetPidGainsRequest :definition-)
      "int32 pid_axis
float64 kp
float64 ki
float64 kd
float64 i_max
float64 i_min
float64 vz_min
float64 vz_max
---
bool success
")

(setf (get offboard_control::SetPidGainsResponse :md5sum-) "1855f912182466f5ec4438809773bb3c")
(setf (get offboard_control::SetPidGainsResponse :datatype-) "offboard_control/SetPidGainsResponse")
(setf (get offboard_control::SetPidGainsResponse :definition-)
      "int32 pid_axis
float64 kp
float64 ki
float64 kd
float64 i_max
float64 i_min
float64 vz_min
float64 vz_max
---
bool success
")



(provide :offboard_control/SetPidGains "1855f912182466f5ec4438809773bb3c")


