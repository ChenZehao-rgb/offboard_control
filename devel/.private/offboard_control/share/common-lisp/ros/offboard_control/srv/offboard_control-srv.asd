
(cl:in-package :asdf)

(defsystem "offboard_control-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "SetOffboardCtlType" :depends-on ("_package_SetOffboardCtlType"))
    (:file "_package_SetOffboardCtlType" :depends-on ("_package"))
    (:file "SetPidGains" :depends-on ("_package_SetPidGains"))
    (:file "_package_SetPidGains" :depends-on ("_package"))
    (:file "SetTargetPoint" :depends-on ("_package_SetTargetPoint"))
    (:file "_package_SetTargetPoint" :depends-on ("_package"))
  ))