;; Auto-generated. Do not edit!


(when (boundp 'offboard_control::SetOffboardCtlType)
  (if (not (find-package "OFFBOARD_CONTROL"))
    (make-package "OFFBOARD_CONTROL"))
  (shadow 'SetOffboardCtlType (find-package "OFFBOARD_CONTROL")))
(unless (find-package "OFFBOARD_CONTROL::SETOFFBOARDCTLTYPE")
  (make-package "OFFBOARD_CONTROL::SETOFFBOARDCTLTYPE"))
(unless (find-package "OFFBOARD_CONTROL::SETOFFBOARDCTLTYPEREQUEST")
  (make-package "OFFBOARD_CONTROL::SETOFFBOARDCTLTYPEREQUEST"))
(unless (find-package "OFFBOARD_CONTROL::SETOFFBOARDCTLTYPERESPONSE")
  (make-package "OFFBOARD_CONTROL::SETOFFBOARDCTLTYPERESPONSE"))

(in-package "ROS")





(defclass offboard_control::SetOffboardCtlTypeRequest
  :super ros::object
  :slots (_offbCtlType ))

(defmethod offboard_control::SetOffboardCtlTypeRequest
  (:init
   (&key
    ((:offbCtlType __offbCtlType) 0)
    )
   (send-super :init)
   (setq _offbCtlType (round __offbCtlType))
   self)
  (:offbCtlType
   (&optional __offbCtlType)
   (if __offbCtlType (setq _offbCtlType __offbCtlType)) _offbCtlType)
  (:serialization-length
   ()
   (+
    ;; int32 _offbCtlType
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _offbCtlType
       (write-long _offbCtlType s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _offbCtlType
     (setq _offbCtlType (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass offboard_control::SetOffboardCtlTypeResponse
  :super ros::object
  :slots (_success ))

(defmethod offboard_control::SetOffboardCtlTypeResponse
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

(defclass offboard_control::SetOffboardCtlType
  :super ros::object
  :slots ())

(setf (get offboard_control::SetOffboardCtlType :md5sum-) "37b0bbed7a7478a029b22247760de72a")
(setf (get offboard_control::SetOffboardCtlType :datatype-) "offboard_control/SetOffboardCtlType")
(setf (get offboard_control::SetOffboardCtlType :request) offboard_control::SetOffboardCtlTypeRequest)
(setf (get offboard_control::SetOffboardCtlType :response) offboard_control::SetOffboardCtlTypeResponse)

(defmethod offboard_control::SetOffboardCtlTypeRequest
  (:response () (instance offboard_control::SetOffboardCtlTypeResponse :init)))

(setf (get offboard_control::SetOffboardCtlTypeRequest :md5sum-) "37b0bbed7a7478a029b22247760de72a")
(setf (get offboard_control::SetOffboardCtlTypeRequest :datatype-) "offboard_control/SetOffboardCtlTypeRequest")
(setf (get offboard_control::SetOffboardCtlTypeRequest :definition-)
      "int32 offbCtlType
---
bool success
")

(setf (get offboard_control::SetOffboardCtlTypeResponse :md5sum-) "37b0bbed7a7478a029b22247760de72a")
(setf (get offboard_control::SetOffboardCtlTypeResponse :datatype-) "offboard_control/SetOffboardCtlTypeResponse")
(setf (get offboard_control::SetOffboardCtlTypeResponse :definition-)
      "int32 offbCtlType
---
bool success
")



(provide :offboard_control/SetOffboardCtlType "37b0bbed7a7478a029b22247760de72a")


