// Generated by gencpp from file offboard_control/SetPidGainsRequest.msg
// DO NOT EDIT!


#ifndef OFFBOARD_CONTROL_MESSAGE_SETPIDGAINSREQUEST_H
#define OFFBOARD_CONTROL_MESSAGE_SETPIDGAINSREQUEST_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace offboard_control
{
template <class ContainerAllocator>
struct SetPidGainsRequest_
{
  typedef SetPidGainsRequest_<ContainerAllocator> Type;

  SetPidGainsRequest_()
    : pid_axis(0)
    , kp(0.0)
    , ki(0.0)
    , kd(0.0)
    , i_max(0.0)
    , i_min(0.0)  {
    }
  SetPidGainsRequest_(const ContainerAllocator& _alloc)
    : pid_axis(0)
    , kp(0.0)
    , ki(0.0)
    , kd(0.0)
    , i_max(0.0)
    , i_min(0.0)  {
  (void)_alloc;
    }



   typedef int32_t _pid_axis_type;
  _pid_axis_type pid_axis;

   typedef double _kp_type;
  _kp_type kp;

   typedef double _ki_type;
  _ki_type ki;

   typedef double _kd_type;
  _kd_type kd;

   typedef double _i_max_type;
  _i_max_type i_max;

   typedef double _i_min_type;
  _i_min_type i_min;





  typedef boost::shared_ptr< ::offboard_control::SetPidGainsRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::offboard_control::SetPidGainsRequest_<ContainerAllocator> const> ConstPtr;

}; // struct SetPidGainsRequest_

typedef ::offboard_control::SetPidGainsRequest_<std::allocator<void> > SetPidGainsRequest;

typedef boost::shared_ptr< ::offboard_control::SetPidGainsRequest > SetPidGainsRequestPtr;
typedef boost::shared_ptr< ::offboard_control::SetPidGainsRequest const> SetPidGainsRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::offboard_control::SetPidGainsRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::offboard_control::SetPidGainsRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::offboard_control::SetPidGainsRequest_<ContainerAllocator1> & lhs, const ::offboard_control::SetPidGainsRequest_<ContainerAllocator2> & rhs)
{
  return lhs.pid_axis == rhs.pid_axis &&
    lhs.kp == rhs.kp &&
    lhs.ki == rhs.ki &&
    lhs.kd == rhs.kd &&
    lhs.i_max == rhs.i_max &&
    lhs.i_min == rhs.i_min;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::offboard_control::SetPidGainsRequest_<ContainerAllocator1> & lhs, const ::offboard_control::SetPidGainsRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace offboard_control

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::offboard_control::SetPidGainsRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::offboard_control::SetPidGainsRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::offboard_control::SetPidGainsRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::offboard_control::SetPidGainsRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::offboard_control::SetPidGainsRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::offboard_control::SetPidGainsRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::offboard_control::SetPidGainsRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "eaeeb6b42b420e9ea4d5e6ebab58fdef";
  }

  static const char* value(const ::offboard_control::SetPidGainsRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xeaeeb6b42b420e9eULL;
  static const uint64_t static_value2 = 0xa4d5e6ebab58fdefULL;
};

template<class ContainerAllocator>
struct DataType< ::offboard_control::SetPidGainsRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "offboard_control/SetPidGainsRequest";
  }

  static const char* value(const ::offboard_control::SetPidGainsRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::offboard_control::SetPidGainsRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 pid_axis\n"
"float64 kp\n"
"float64 ki\n"
"float64 kd\n"
"float64 i_max\n"
"float64 i_min\n"
;
  }

  static const char* value(const ::offboard_control::SetPidGainsRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::offboard_control::SetPidGainsRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.pid_axis);
      stream.next(m.kp);
      stream.next(m.ki);
      stream.next(m.kd);
      stream.next(m.i_max);
      stream.next(m.i_min);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SetPidGainsRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::offboard_control::SetPidGainsRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::offboard_control::SetPidGainsRequest_<ContainerAllocator>& v)
  {
    s << indent << "pid_axis: ";
    Printer<int32_t>::stream(s, indent + "  ", v.pid_axis);
    s << indent << "kp: ";
    Printer<double>::stream(s, indent + "  ", v.kp);
    s << indent << "ki: ";
    Printer<double>::stream(s, indent + "  ", v.ki);
    s << indent << "kd: ";
    Printer<double>::stream(s, indent + "  ", v.kd);
    s << indent << "i_max: ";
    Printer<double>::stream(s, indent + "  ", v.i_max);
    s << indent << "i_min: ";
    Printer<double>::stream(s, indent + "  ", v.i_min);
  }
};

} // namespace message_operations
} // namespace ros

#endif // OFFBOARD_CONTROL_MESSAGE_SETPIDGAINSREQUEST_H