;; Auto-generated. Do not edit!


(when (boundp 'offboard_control::OffboardCtlType)
  (if (not (find-package "OFFBOARD_CONTROL"))
    (make-package "OFFBOARD_CONTROL"))
  (shadow 'OffboardCtlType (find-package "OFFBOARD_CONTROL")))
(unless (find-package "OFFBOARD_CONTROL::OFFBOARDCTLTYPE")
  (make-package "OFFBOARD_CONTROL::OFFBOARDCTLTYPE"))

(in-package "ROS")
;;//! \htmlinclude OffboardCtlType.msg.html


(intern "*GOTO_SETPOINT_STEP*" (find-package "OFFBOARD_CONTROL::OFFBOARDCTLTYPE"))
(shadow '*GOTO_SETPOINT_STEP* (find-package "OFFBOARD_CONTROL::OFFBOARDCTLTYPE"))
(defconstant offboard_control::OffboardCtlType::*GOTO_SETPOINT_STEP* 0)
(intern "*GOTO_SETPOINT_CLOSED_LOOP*" (find-package "OFFBOARD_CONTROL::OFFBOARDCTLTYPE"))
(shadow '*GOTO_SETPOINT_CLOSED_LOOP* (find-package "OFFBOARD_CONTROL::OFFBOARDCTLTYPE"))
(defconstant offboard_control::OffboardCtlType::*GOTO_SETPOINT_CLOSED_LOOP* 1)
(intern "*GOTO_SETPOINTS_SERIES*" (find-package "OFFBOARD_CONTROL::OFFBOARDCTLTYPE"))
(shadow '*GOTO_SETPOINTS_SERIES* (find-package "OFFBOARD_CONTROL::OFFBOARDCTLTYPE"))
(defconstant offboard_control::OffboardCtlType::*GOTO_SETPOINTS_SERIES* 2)

(defun offboard_control::OffboardCtlType-to-symbol (const)
  (cond
        ((= const 0) 'offboard_control::OffboardCtlType::*GOTO_SETPOINT_STEP*)
        ((= const 1) 'offboard_control::OffboardCtlType::*GOTO_SETPOINT_CLOSED_LOOP*)
        ((= const 2) 'offboard_control::OffboardCtlType::*GOTO_SETPOINTS_SERIES*)
        (t nil)))

(defclass offboard_control::OffboardCtlType
  :super ros::object
  :slots (_offb_ctrl_type ))

(defmethod offboard_control::OffboardCtlType
  (:init
   (&key
    ((:offb_ctrl_type __offb_ctrl_type) 0)
    )
   (send-super :init)
   (setq _offb_ctrl_type (round __offb_ctrl_type))
   self)
  (:offb_ctrl_type
   (&optional __offb_ctrl_type)
   (if __offb_ctrl_type (setq _offb_ctrl_type __offb_ctrl_type)) _offb_ctrl_type)
  (:serialization-length
   ()
   (+
    ;; uint8 _offb_ctrl_type
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _offb_ctrl_type
       (write-byte _offb_ctrl_type s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _offb_ctrl_type
     (setq _offb_ctrl_type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get offboard_control::OffboardCtlType :md5sum-) "640ad7cdefca8d4153a8d8cdc9622cb2")
(setf (get offboard_control::OffboardCtlType :datatype-) "offboard_control/OffboardCtlType")
(setf (get offboard_control::OffboardCtlType :definition-)
      "uint8 offb_ctrl_type

uint8 GOTO_SETPOINT_STEP = 0
uint8 GOTO_SETPOINT_CLOSED_LOOP = 1

uint8 GOTO_SETPOINTS_SERIES = 2
")



(provide :offboard_control/OffboardCtlType "640ad7cdefca8d4153a8d8cdc9622cb2")


