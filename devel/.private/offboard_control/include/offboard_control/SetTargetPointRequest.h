// Generated by gencpp from file offboard_control/SetTargetPointRequest.msg
// DO NOT EDIT!


#ifndef OFFBOARD_CONTROL_MESSAGE_SETTARGETPOINTREQUEST_H
#define OFFBOARD_CONTROL_MESSAGE_SETTARGETPOINTREQUEST_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/PositionTarget.h>

namespace offboard_control
{
template <class ContainerAllocator>
struct SetTargetPointRequest_
{
  typedef SetTargetPointRequest_<ContainerAllocator> Type;

  SetTargetPointRequest_()
    : targetPoint()
    , targetPointRaw()
    , uavID(0)  {
    }
  SetTargetPointRequest_(const ContainerAllocator& _alloc)
    : targetPoint(_alloc)
    , targetPointRaw(_alloc)
    , uavID(0)  {
  (void)_alloc;
    }



   typedef  ::geometry_msgs::PoseStamped_<ContainerAllocator>  _targetPoint_type;
  _targetPoint_type targetPoint;

   typedef  ::mavros_msgs::PositionTarget_<ContainerAllocator>  _targetPointRaw_type;
  _targetPointRaw_type targetPointRaw;

   typedef uint8_t _uavID_type;
  _uavID_type uavID;





  typedef boost::shared_ptr< ::offboard_control::SetTargetPointRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::offboard_control::SetTargetPointRequest_<ContainerAllocator> const> ConstPtr;

}; // struct SetTargetPointRequest_

typedef ::offboard_control::SetTargetPointRequest_<std::allocator<void> > SetTargetPointRequest;

typedef boost::shared_ptr< ::offboard_control::SetTargetPointRequest > SetTargetPointRequestPtr;
typedef boost::shared_ptr< ::offboard_control::SetTargetPointRequest const> SetTargetPointRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::offboard_control::SetTargetPointRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::offboard_control::SetTargetPointRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::offboard_control::SetTargetPointRequest_<ContainerAllocator1> & lhs, const ::offboard_control::SetTargetPointRequest_<ContainerAllocator2> & rhs)
{
  return lhs.targetPoint == rhs.targetPoint &&
    lhs.targetPointRaw == rhs.targetPointRaw &&
    lhs.uavID == rhs.uavID;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::offboard_control::SetTargetPointRequest_<ContainerAllocator1> & lhs, const ::offboard_control::SetTargetPointRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace offboard_control

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::offboard_control::SetTargetPointRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::offboard_control::SetTargetPointRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::offboard_control::SetTargetPointRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::offboard_control::SetTargetPointRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::offboard_control::SetTargetPointRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::offboard_control::SetTargetPointRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::offboard_control::SetTargetPointRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "72cfe09baead49e371d1147e57883723";
  }

  static const char* value(const ::offboard_control::SetTargetPointRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x72cfe09baead49e3ULL;
  static const uint64_t static_value2 = 0x71d1147e57883723ULL;
};

template<class ContainerAllocator>
struct DataType< ::offboard_control::SetTargetPointRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "offboard_control/SetTargetPointRequest";
  }

  static const char* value(const ::offboard_control::SetTargetPointRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::offboard_control::SetTargetPointRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "geometry_msgs/PoseStamped targetPoint\n"
"mavros_msgs/PositionTarget targetPointRaw\n"
"uint8 uavID\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/PoseStamped\n"
"# A Pose with reference coordinate frame and timestamp\n"
"Header header\n"
"Pose pose\n"
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
"MSG: geometry_msgs/Pose\n"
"# A representation of pose in free space, composed of position and orientation. \n"
"Point position\n"
"Quaternion orientation\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
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
;
  }

  static const char* value(const ::offboard_control::SetTargetPointRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::offboard_control::SetTargetPointRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.targetPoint);
      stream.next(m.targetPointRaw);
      stream.next(m.uavID);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SetTargetPointRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::offboard_control::SetTargetPointRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::offboard_control::SetTargetPointRequest_<ContainerAllocator>& v)
  {
    s << indent << "targetPoint: ";
    s << std::endl;
    Printer< ::geometry_msgs::PoseStamped_<ContainerAllocator> >::stream(s, indent + "  ", v.targetPoint);
    s << indent << "targetPointRaw: ";
    s << std::endl;
    Printer< ::mavros_msgs::PositionTarget_<ContainerAllocator> >::stream(s, indent + "  ", v.targetPointRaw);
    s << indent << "uavID: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.uavID);
  }
};

} // namespace message_operations
} // namespace ros

#endif // OFFBOARD_CONTROL_MESSAGE_SETTARGETPOINTREQUEST_H
