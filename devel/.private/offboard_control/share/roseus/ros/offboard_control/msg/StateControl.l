;; Auto-generated. Do not edit!


(when (boundp 'offboard_control::StateControl)
  (if (not (find-package "OFFBOARD_CONTROL"))
    (make-package "OFFBOARD_CONTROL"))
  (shadow 'StateControl (find-package "OFFBOARD_CONTROL")))
(unless (find-package "OFFBOARD_CONTROL::STATECONTROL")
  (make-package "OFFBOARD_CONTROL::STATECONTROL"))

(in-package "ROS")
;;//! \htmlinclude StateControl.msg.html


(intern "*TAKEOFF*" (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(shadow '*TAKEOFF* (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(defconstant offboard_control::StateControl::*TAKEOFF* 0)
(intern "*ARRIVE_ONLINE_POINT*" (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(shadow '*ARRIVE_ONLINE_POINT* (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(defconstant offboard_control::StateControl::*ARRIVE_ONLINE_POINT* 1)
(intern "*AJUST_ATTITUDE*" (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(shadow '*AJUST_ATTITUDE* (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(defconstant offboard_control::StateControl::*AJUST_ATTITUDE* 2)
(intern "*ON_LINE*" (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(shadow '*ON_LINE* (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(defconstant offboard_control::StateControl::*ON_LINE* 3)
(intern "*FOLLOW_CABLE*" (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(shadow '*FOLLOW_CABLE* (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(defconstant offboard_control::StateControl::*FOLLOW_CABLE* 4)
(intern "*APPROACH_NODE*" (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(shadow '*APPROACH_NODE* (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(defconstant offboard_control::StateControl::*APPROACH_NODE* 5)
(intern "*CROSS_NODE*" (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(shadow '*CROSS_NODE* (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(defconstant offboard_control::StateControl::*CROSS_NODE* 6)
(intern "*LAND*" (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(shadow '*LAND* (find-package "OFFBOARD_CONTROL::STATECONTROL"))
(defconstant offboard_control::StateControl::*LAND* 7)

(defun offboard_control::StateControl-to-symbol (const)
  (cond
        ((= const 0) 'offboard_control::StateControl::*TAKEOFF*)
        ((= const 1) 'offboard_control::StateControl::*ARRIVE_ONLINE_POINT*)
        ((= const 2) 'offboard_control::StateControl::*AJUST_ATTITUDE*)
        ((= const 3) 'offboard_control::StateControl::*ON_LINE*)
        ((= const 4) 'offboard_control::StateControl::*FOLLOW_CABLE*)
        ((= const 5) 'offboard_control::StateControl::*APPROACH_NODE*)
        ((= const 6) 'offboard_control::StateControl::*CROSS_NODE*)
        ((= const 7) 'offboard_control::StateControl::*LAND*)
        (t nil)))

(defclass offboard_control::StateControl
  :super ros::object
  :slots (_state_ctrl_type ))

(defmethod offboard_control::StateControl
  (:init
   (&key
    ((:state_ctrl_type __state_ctrl_type) 0)
    )
   (send-super :init)
   (setq _state_ctrl_type (round __state_ctrl_type))
   self)
  (:state_ctrl_type
   (&optional __state_ctrl_type)
   (if __state_ctrl_type (setq _state_ctrl_type __state_ctrl_type)) _state_ctrl_type)
  (:serialization-length
   ()
   (+
    ;; uint8 _state_ctrl_type
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _state_ctrl_type
       (write-byte _state_ctrl_type s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _state_ctrl_type
     (setq _state_ctrl_type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get offboard_control::StateControl :md5sum-) "32bbda18dc61a12eea4cc4f9975ef333")
(setf (get offboard_control::StateControl :datatype-) "offboard_control/StateControl")
(setf (get offboard_control::StateControl :definition-)
      "uint8 state_ctrl_type
uint8 TAKEOFF = 0
uint8 ARRIVE_ONLINE_POINT = 1
uint8 AJUST_ATTITUDE = 2
uint8 ON_LINE = 3
uint8 FOLLOW_CABLE = 4
uint8 APPROACH_NODE = 5
uint8 CROSS_NODE = 6
uint8 LAND = 7
")



(provide :offboard_control/StateControl "32bbda18dc61a12eea4cc4f9975ef333")


