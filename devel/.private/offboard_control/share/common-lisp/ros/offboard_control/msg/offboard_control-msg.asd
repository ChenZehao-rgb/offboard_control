
(cl:in-package :asdf)

(defsystem "offboard_control-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "Measure" :depends-on ("_package_Measure"))
    (:file "_package_Measure" :depends-on ("_package"))
    (:file "OffboardCtlType" :depends-on ("_package_OffboardCtlType"))
    (:file "_package_OffboardCtlType" :depends-on ("_package"))
    (:file "StateControl" :depends-on ("_package_StateControl"))
    (:file "_package_StateControl" :depends-on ("_package"))
    (:file "Status" :depends-on ("_package_Status"))
    (:file "_package_Status" :depends-on ("_package"))
  ))