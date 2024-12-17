;; Auto-generated. Do not edit!


(when (boundp 'offboard_control::SetUavTakeoffReady)
  (if (not (find-package "OFFBOARD_CONTROL"))
    (make-package "OFFBOARD_CONTROL"))
  (shadow 'SetUavTakeoffReady (find-package "OFFBOARD_CONTROL")))
(unless (find-package "OFFBOARD_CONTROL::SETUAVTAKEOFFREADY")
  (make-package "OFFBOARD_CONTROL::SETUAVTAKEOFFREADY"))
(unless (find-package "OFFBOARD_CONTROL::SETUAVTAKEOFFREADYREQUEST")
  (make-package "OFFBOARD_CONTROL::SETUAVTAKEOFFREADYREQUEST"))
(unless (find-package "OFFBOARD_CONTROL::SETUAVTAKEOFFREADYRESPONSE")
  (make-package "OFFBOARD_CONTROL::SETUAVTAKEOFFREADYRESPONSE"))

(in-package "ROS")





(defclass offboard_control::SetUavTakeoffReadyRequest
  :super ros::object
  :slots (_uavID ))

(defmethod offboard_control::SetUavTakeoffReadyRequest
  (:init
   (&key
    ((:uavID __uavID) 0)
    )
   (send-super :init)
   (setq _uavID (round __uavID))
   self)
  (:uavID
   (&optional __uavID)
   (if __uavID (setq _uavID __uavID)) _uavID)
  (:serialization-length
   ()
   (+
    ;; uint8 _uavID
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _uavID
       (write-byte _uavID s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _uavID
     (setq _uavID (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(defclass offboard_control::SetUavTakeoffReadyResponse
  :super ros::object
  :slots (_offboard_enabled _armed ))

(defmethod offboard_control::SetUavTakeoffReadyResponse
  (:init
   (&key
    ((:offboard_enabled __offboard_enabled) nil)
    ((:armed __armed) nil)
    )
   (send-super :init)
   (setq _offboard_enabled __offboard_enabled)
   (setq _armed __armed)
   self)
  (:offboard_enabled
   (&optional (__offboard_enabled :null))
   (if (not (eq __offboard_enabled :null)) (setq _offboard_enabled __offboard_enabled)) _offboard_enabled)
  (:armed
   (&optional (__armed :null))
   (if (not (eq __armed :null)) (setq _armed __armed)) _armed)
  (:serialization-length
   ()
   (+
    ;; bool _offboard_enabled
    1
    ;; bool _armed
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _offboard_enabled
       (if _offboard_enabled (write-byte -1 s) (write-byte 0 s))
     ;; bool _armed
       (if _armed (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _offboard_enabled
     (setq _offboard_enabled (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _armed
     (setq _armed (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass offboard_control::SetUavTakeoffReady
  :super ros::object
  :slots ())

(setf (get offboard_control::SetUavTakeoffReady :md5sum-) "bfb94ba5582dfe70c8390e8d16832c2a")
(setf (get offboard_control::SetUavTakeoffReady :datatype-) "offboard_control/SetUavTakeoffReady")
(setf (get offboard_control::SetUavTakeoffReady :request) offboard_control::SetUavTakeoffReadyRequest)
(setf (get offboard_control::SetUavTakeoffReady :response) offboard_control::SetUavTakeoffReadyResponse)

(defmethod offboard_control::SetUavTakeoffReadyRequest
  (:response () (instance offboard_control::SetUavTakeoffReadyResponse :init)))

(setf (get offboard_control::SetUavTakeoffReadyRequest :md5sum-) "bfb94ba5582dfe70c8390e8d16832c2a")
(setf (get offboard_control::SetUavTakeoffReadyRequest :datatype-) "offboard_control/SetUavTakeoffReadyRequest")
(setf (get offboard_control::SetUavTakeoffReadyRequest :definition-)
      "uint8 uavID
---
bool offboard_enabled
bool armed
")

(setf (get offboard_control::SetUavTakeoffReadyResponse :md5sum-) "bfb94ba5582dfe70c8390e8d16832c2a")
(setf (get offboard_control::SetUavTakeoffReadyResponse :datatype-) "offboard_control/SetUavTakeoffReadyResponse")
(setf (get offboard_control::SetUavTakeoffReadyResponse :definition-)
      "uint8 uavID
---
bool offboard_enabled
bool armed
")



(provide :offboard_control/SetUavTakeoffReady "bfb94ba5582dfe70c8390e8d16832c2a")


