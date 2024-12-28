// Generated by gencpp from file offboard_control/GenTrajOnlineRequest.msg
// DO NOT EDIT!


#ifndef OFFBOARD_CONTROL_MESSAGE_GENTRAJONLINEREQUEST_H
#define OFFBOARD_CONTROL_MESSAGE_GENTRAJONLINEREQUEST_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <mavros_msgs/PositionTarget.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/AccelWithCovarianceStamped.h>

namespace offboard_control
{
template <class ContainerAllocator>
struct GenTrajOnlineRequest_
{
  typedef GenTrajOnlineRequest_<ContainerAllocator> Type;

  GenTrajOnlineRequest_()
    : targPoint()
    , pose()
    , twist()
    , acc()
    , isUpdateState(false)  {
    }
  GenTrajOnlineRequest_(const ContainerAllocator& _alloc)
    : targPoint(_alloc)
    , pose(_alloc)
    , twist(_alloc)
    , acc(_alloc)
    , isUpdateState(false)  {
  (void)_alloc;
    }



   typedef  ::mavros_msgs::PositionTarget_<ContainerAllocator>  _targPoint_type;
  _targPoint_type targPoint;

   typedef  ::geometry_msgs::PoseStamped_<ContainerAllocator>  _pose_type;
  _pose_type pose;

   typedef  ::geometry_msgs::TwistStamped_<ContainerAllocator>  _twist_type;
  _twist_type twist;

   typedef  ::geometry_msgs::AccelWithCovarianceStamped_<ContainerAllocator>  _acc_type;
  _acc_type acc;

   typedef uint8_t _isUpdateState_type;
  _isUpdateState_type isUpdateState;





  typedef boost::shared_ptr< ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator> const> ConstPtr;

}; // struct GenTrajOnlineRequest_

typedef ::offboard_control::GenTrajOnlineRequest_<std::allocator<void> > GenTrajOnlineRequest;

typedef boost::shared_ptr< ::offboard_control::GenTrajOnlineRequest > GenTrajOnlineRequestPtr;
typedef boost::shared_ptr< ::offboard_control::GenTrajOnlineRequest const> GenTrajOnlineRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator1> & lhs, const ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator2> & rhs)
{
  return lhs.targPoint == rhs.targPoint &&
    lhs.pose == rhs.pose &&
    lhs.twist == rhs.twist &&
    lhs.acc == rhs.acc &&
    lhs.isUpdateState == rhs.isUpdateState;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator1> & lhs, const ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace offboard_control

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "69caf5ed1b7124486d92a1d48a43b7ae";
  }

  static const char* value(const ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x69caf5ed1b712448ULL;
  static const uint64_t static_value2 = 0x6d92a1d48a43b7aeULL;
};

template<class ContainerAllocator>
struct DataType< ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "offboard_control/GenTrajOnlineRequest";
  }

  static const char* value(const ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mavros_msgs/PositionTarget targPoint\n"
"geometry_msgs/PoseStamped pose\n"
"geometry_msgs/TwistStamped twist\n"
"geometry_msgs/AccelWithCovarianceStamped acc\n"
"bool isUpdateState\n"
"\n"
"================================================================================\n"
"MSG: mavros_msgs/PositionTarget\n"
"# Message for SET_POSITION_TARGET_LOCAL_NED\n"
"#\n"
"# Some complex system requires all feautures that mavlink\n"
"# message provide. See issue #402.\n"
"\n"
"std_msgs/Header header\n"
"\n"
"uint8 coordinate_frame\n"
"uint8 FRAME_LOCAL_NED = 1\n"
"uint8 FRAME_LOCAL_OFFSET_NED = 7\n"
"uint8 FRAME_BODY_NED = 8\n"
"uint8 FRAME_BODY_OFFSET_NED = 9\n"
"\n"
"uint16 type_mask\n"
"uint16 IGNORE_PX = 1	# Position ignore flags\n"
"uint16 IGNORE_PY = 2\n"
"uint16 IGNORE_PZ = 4\n"
"uint16 IGNORE_VX = 8	# Velocity vector ignore flags\n"
"uint16 IGNORE_VY = 16\n"
"uint16 IGNORE_VZ = 32\n"
"uint16 IGNORE_AFX = 64	# Acceleration/Force vector ignore flags\n"
"uint16 IGNORE_AFY = 128\n"
"uint16 IGNORE_AFZ = 256\n"
"uint16 FORCE = 512	# Force in af vector flag\n"
"uint16 IGNORE_YAW = 1024\n"
"uint16 IGNORE_YAW_RATE = 2048\n"
"\n"
"geometry_msgs/Point position\n"
"geometry_msgs/Vector3 velocity\n"
"geometry_msgs/Vector3 acceleration_or_force\n"
"float32 yaw\n"
"float32 yaw_rate\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Vector3\n"
"# This represents a vector in free space. \n"
"# It is only meant to represent a direction. Therefore, it does not\n"
"# make sense to apply a translation to it (e.g., when applying a \n"
"# generic rigid transformation to a Vector3, tf2 will only apply the\n"
"# rotation). If you want your data to be translatable too, use the\n"
"# geometry_msgs/Point message instead.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"================================================================================\n"
"MSG: geometry_msgs/PoseStamped\n"
"# A Pose with reference coordinate frame and timestamp\n"
"Header header\n"
"Pose pose\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Pose\n"
"# A representation of pose in free space, composed of position and orientation. \n"
"Point position\n"
"Quaternion orientation\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Quaternion\n"
"# This represents an orientation in free space in quaternion form.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"float64 w\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/TwistStamped\n"
"# A twist with reference coordinate frame and timestamp\n"
"Header header\n"
"Twist twist\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Twist\n"
"# This expresses velocity in free space broken into its linear and angular parts.\n"
"Vector3  linear\n"
"Vector3  angular\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/AccelWithCovarianceStamped\n"
"# This represents an estimated accel with reference coordinate frame and timestamp.\n"
"Header header\n"
"AccelWithCovariance accel\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/AccelWithCovariance\n"
"# This expresses acceleration in free space with uncertainty.\n"
"\n"
"Accel accel\n"
"\n"
"# Row-major representation of the 6x6 covariance matrix\n"
"# The orientation parameters use a fixed-axis representation.\n"
"# In order, the parameters are:\n"
"# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)\n"
"float64[36] covariance\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Accel\n"
"# This expresses acceleration in free space broken into its linear and angular parts.\n"
"Vector3  linear\n"
"Vector3  angular\n"
;
  }

  static const char* value(const ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.targPoint);
      stream.next(m.pose);
      stream.next(m.twist);
      stream.next(m.acc);
      stream.next(m.isUpdateState);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GenTrajOnlineRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::offboard_control::GenTrajOnlineRequest_<ContainerAllocator>& v)
  {
    s << indent << "targPoint: ";
    s << std::endl;
    Printer< ::mavros_msgs::PositionTarget_<ContainerAllocator> >::stream(s, indent + "  ", v.targPoint);
    s << indent << "pose: ";
    s << std::endl;
    Printer< ::geometry_msgs::PoseStamped_<ContainerAllocator> >::stream(s, indent + "  ", v.pose);
    s << indent << "twist: ";
    s << std::endl;
    Printer< ::geometry_msgs::TwistStamped_<ContainerAllocator> >::stream(s, indent + "  ", v.twist);
    s << indent << "acc: ";
    s << std::endl;
    Printer< ::geometry_msgs::AccelWithCovarianceStamped_<ContainerAllocator> >::stream(s, indent + "  ", v.acc);
    s << indent << "isUpdateState: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.isUpdateState);
  }
};

} // namespace message_operations
} // namespace ros

#endif // OFFBOARD_CONTROL_MESSAGE_GENTRAJONLINEREQUEST_H
