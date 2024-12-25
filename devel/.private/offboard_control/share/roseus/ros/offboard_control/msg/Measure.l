;; Auto-generated. Do not edit!


(when (boundp 'offboard_control::Measure)
  (if (not (find-package "OFFBOARD_CONTROL"))
    (make-package "OFFBOARD_CONTROL"))
  (shadow 'Measure (find-package "OFFBOARD_CONTROL")))
(unless (find-package "OFFBOARD_CONTROL::MEASURE")
  (make-package "OFFBOARD_CONTROL::MEASURE"))

(in-package "ROS")
;;//! \htmlinclude Measure.msg.html


(defclass offboard_control::Measure
  :super ros::object
  :slots (_is_valid _x _z ))

(defmethod offboard_control::Measure
  (:init
   (&key
    ((:is_valid __is_valid) nil)
    ((:x __x) 0.0)
    ((:z __z) 0.0)
    )
   (send-super :init)
   (setq _is_valid __is_valid)
   (setq _x (float __x))
   (setq _z (float __z))
   self)
  (:is_valid
   (&optional (__is_valid :null))
   (if (not (eq __is_valid :null)) (setq _is_valid __is_valid)) _is_valid)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:z
   (&optional __z)
   (if __z (setq _z __z)) _z)
  (:serialization-length
   ()
   (+
    ;; bool _is_valid
    1
    ;; float64 _x
    8
    ;; float64 _z
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _is_valid
       (if _is_valid (write-byte -1 s) (write-byte 0 s))
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _z
       (sys::poke _z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _is_valid
     (setq _is_valid (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _z
     (setq _z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get offboard_control::Measure :md5sum-) "038007aa6658d27492f7f0c6eeb28f91")
(setf (get offboard_control::Measure :datatype-) "offboard_control/Measure")
(setf (get offboard_control::Measure :definition-)
      "bool is_valid
float64 x
float64 z
")



(provide :offboard_control/Measure "038007aa6658d27492f7f0c6eeb28f91")


