
(cl:in-package :asdf)

(defsystem "offboard_control-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "OffboardCtlType" :depends-on ("_package_OffboardCtlType"))
    (:file "_package_OffboardCtlType" :depends-on ("_package"))
    (:file "StateControl" :depends-on ("_package_StateControl"))
    (:file "_package_StateControl" :depends-on ("_package"))
  ))