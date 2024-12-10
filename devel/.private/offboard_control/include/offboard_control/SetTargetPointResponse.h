// Generated by gencpp from file offboard_control/SetTargetPointResponse.msg
// DO NOT EDIT!


#ifndef OFFBOARD_CONTROL_MESSAGE_SETTARGETPOINTRESPONSE_H
#define OFFBOARD_CONTROL_MESSAGE_SETTARGETPOINTRESPONSE_H


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
struct SetTargetPointResponse_
{
  typedef SetTargetPointResponse_<ContainerAllocator> Type;

  SetTargetPointResponse_()
    : success(false)  {
    }
  SetTargetPointResponse_(const ContainerAllocator& _alloc)
    : success(false)  {
  (void)_alloc;
    }



   typedef uint8_t _success_type;
  _success_type success;





  typedef boost::shared_ptr< ::offboard_control::SetTargetPointResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::offboard_control::SetTargetPointResponse_<ContainerAllocator> const> ConstPtr;

}; // struct SetTargetPointResponse_

typedef ::offboard_control::SetTargetPointResponse_<std::allocator<void> > SetTargetPointResponse;

typedef boost::shared_ptr< ::offboard_control::SetTargetPointResponse > SetTargetPointResponsePtr;
typedef boost::shared_ptr< ::offboard_control::SetTargetPointResponse const> SetTargetPointResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::offboard_control::SetTargetPointResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::offboard_control::SetTargetPointResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::offboard_control::SetTargetPointResponse_<ContainerAllocator1> & lhs, const ::offboard_control::SetTargetPointResponse_<ContainerAllocator2> & rhs)
{
  return lhs.success == rhs.success;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::offboard_control::SetTargetPointResponse_<ContainerAllocator1> & lhs, const ::offboard_control::SetTargetPointResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace offboard_control

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::offboard_control::SetTargetPointResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::offboard_control::SetTargetPointResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::offboard_control::SetTargetPointResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::offboard_control::SetTargetPointResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::offboard_control::SetTargetPointResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::offboard_control::SetTargetPointResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::offboard_control::SetTargetPointResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "358e233cde0c8a8bcfea4ce193f8fc15";
  }

  static const char* value(const ::offboard_control::SetTargetPointResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x358e233cde0c8a8bULL;
  static const uint64_t static_value2 = 0xcfea4ce193f8fc15ULL;
};

template<class ContainerAllocator>
struct DataType< ::offboard_control::SetTargetPointResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "offboard_control/SetTargetPointResponse";
  }

  static const char* value(const ::offboard_control::SetTargetPointResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::offboard_control::SetTargetPointResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool success\n"
;
  }

  static const char* value(const ::offboard_control::SetTargetPointResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::offboard_control::SetTargetPointResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.success);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SetTargetPointResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::offboard_control::SetTargetPointResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::offboard_control::SetTargetPointResponse_<ContainerAllocator>& v)
  {
    s << indent << "success: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.success);
  }
};

} // namespace message_operations
} // namespace ros

#endif // OFFBOARD_CONTROL_MESSAGE_SETTARGETPOINTRESPONSE_H