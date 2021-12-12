// Generated by gencpp from file camera_control_msgs/GetCamPropertiesResponse.msg
// DO NOT EDIT!


#ifndef CAMERA_CONTROL_MSGS_MESSAGE_GETCAMPROPERTIESRESPONSE_H
#define CAMERA_CONTROL_MSGS_MESSAGE_GETCAMPROPERTIESRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace camera_control_msgs
{
template <class ContainerAllocator>
struct GetCamPropertiesResponse_
{
  typedef GetCamPropertiesResponse_<ContainerAllocator> Type;

  GetCamPropertiesResponse_()
    : success(false)
    , is_sleeping(false)
    , device_user_id()
    , min_binning_x(0)
    , max_binning_x(0)
    , current_binning_x(0)
    , min_binning_y(0)
    , max_binning_y(0)
    , current_binning_y(0)
    , max_framerate(0.0)
    , current_framerate(0.0)
    , min_exposure(0.0)
    , max_exposure(0.0)
    , current_exposure(0.0)
    , min_gain_in_cam_units(0.0)
    , max_gain_in_cam_units(0.0)
    , current_gain_in_cam_units(0.0)
    , min_gain(0.0)
    , max_gain(0.0)
    , current_gain(0.0)
    , min_gamma(0.0)
    , max_gamma(0.0)
    , current_gamma(0.0)
    , brightness_continuous(false)
    , gain_auto(false)
    , exposure_auto(false)  {
    }
  GetCamPropertiesResponse_(const ContainerAllocator& _alloc)
    : success(false)
    , is_sleeping(false)
    , device_user_id(_alloc)
    , min_binning_x(0)
    , max_binning_x(0)
    , current_binning_x(0)
    , min_binning_y(0)
    , max_binning_y(0)
    , current_binning_y(0)
    , max_framerate(0.0)
    , current_framerate(0.0)
    , min_exposure(0.0)
    , max_exposure(0.0)
    , current_exposure(0.0)
    , min_gain_in_cam_units(0.0)
    , max_gain_in_cam_units(0.0)
    , current_gain_in_cam_units(0.0)
    , min_gain(0.0)
    , max_gain(0.0)
    , current_gain(0.0)
    , min_gamma(0.0)
    , max_gamma(0.0)
    , current_gamma(0.0)
    , brightness_continuous(false)
    , gain_auto(false)
    , exposure_auto(false)  {
  (void)_alloc;
    }



   typedef uint8_t _success_type;
  _success_type success;

   typedef uint8_t _is_sleeping_type;
  _is_sleeping_type is_sleeping;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _device_user_id_type;
  _device_user_id_type device_user_id;

   typedef int32_t _min_binning_x_type;
  _min_binning_x_type min_binning_x;

   typedef int32_t _max_binning_x_type;
  _max_binning_x_type max_binning_x;

   typedef int32_t _current_binning_x_type;
  _current_binning_x_type current_binning_x;

   typedef int32_t _min_binning_y_type;
  _min_binning_y_type min_binning_y;

   typedef int32_t _max_binning_y_type;
  _max_binning_y_type max_binning_y;

   typedef int32_t _current_binning_y_type;
  _current_binning_y_type current_binning_y;

   typedef float _max_framerate_type;
  _max_framerate_type max_framerate;

   typedef float _current_framerate_type;
  _current_framerate_type current_framerate;

   typedef float _min_exposure_type;
  _min_exposure_type min_exposure;

   typedef float _max_exposure_type;
  _max_exposure_type max_exposure;

   typedef float _current_exposure_type;
  _current_exposure_type current_exposure;

   typedef float _min_gain_in_cam_units_type;
  _min_gain_in_cam_units_type min_gain_in_cam_units;

   typedef float _max_gain_in_cam_units_type;
  _max_gain_in_cam_units_type max_gain_in_cam_units;

   typedef float _current_gain_in_cam_units_type;
  _current_gain_in_cam_units_type current_gain_in_cam_units;

   typedef float _min_gain_type;
  _min_gain_type min_gain;

   typedef float _max_gain_type;
  _max_gain_type max_gain;

   typedef float _current_gain_type;
  _current_gain_type current_gain;

   typedef float _min_gamma_type;
  _min_gamma_type min_gamma;

   typedef float _max_gamma_type;
  _max_gamma_type max_gamma;

   typedef float _current_gamma_type;
  _current_gamma_type current_gamma;

   typedef uint8_t _brightness_continuous_type;
  _brightness_continuous_type brightness_continuous;

   typedef uint8_t _gain_auto_type;
  _gain_auto_type gain_auto;

   typedef uint8_t _exposure_auto_type;
  _exposure_auto_type exposure_auto;





  typedef boost::shared_ptr< ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator> const> ConstPtr;

}; // struct GetCamPropertiesResponse_

typedef ::camera_control_msgs::GetCamPropertiesResponse_<std::allocator<void> > GetCamPropertiesResponse;

typedef boost::shared_ptr< ::camera_control_msgs::GetCamPropertiesResponse > GetCamPropertiesResponsePtr;
typedef boost::shared_ptr< ::camera_control_msgs::GetCamPropertiesResponse const> GetCamPropertiesResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator1> & lhs, const ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator2> & rhs)
{
  return lhs.success == rhs.success &&
    lhs.is_sleeping == rhs.is_sleeping &&
    lhs.device_user_id == rhs.device_user_id &&
    lhs.min_binning_x == rhs.min_binning_x &&
    lhs.max_binning_x == rhs.max_binning_x &&
    lhs.current_binning_x == rhs.current_binning_x &&
    lhs.min_binning_y == rhs.min_binning_y &&
    lhs.max_binning_y == rhs.max_binning_y &&
    lhs.current_binning_y == rhs.current_binning_y &&
    lhs.max_framerate == rhs.max_framerate &&
    lhs.current_framerate == rhs.current_framerate &&
    lhs.min_exposure == rhs.min_exposure &&
    lhs.max_exposure == rhs.max_exposure &&
    lhs.current_exposure == rhs.current_exposure &&
    lhs.min_gain_in_cam_units == rhs.min_gain_in_cam_units &&
    lhs.max_gain_in_cam_units == rhs.max_gain_in_cam_units &&
    lhs.current_gain_in_cam_units == rhs.current_gain_in_cam_units &&
    lhs.min_gain == rhs.min_gain &&
    lhs.max_gain == rhs.max_gain &&
    lhs.current_gain == rhs.current_gain &&
    lhs.min_gamma == rhs.min_gamma &&
    lhs.max_gamma == rhs.max_gamma &&
    lhs.current_gamma == rhs.current_gamma &&
    lhs.brightness_continuous == rhs.brightness_continuous &&
    lhs.gain_auto == rhs.gain_auto &&
    lhs.exposure_auto == rhs.exposure_auto;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator1> & lhs, const ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace camera_control_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "14bd64331efb0f665787f525f453c05d";
  }

  static const char* value(const ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x14bd64331efb0f66ULL;
  static const uint64_t static_value2 = 0x5787f525f453c05dULL;
};

template<class ContainerAllocator>
struct DataType< ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "camera_control_msgs/GetCamPropertiesResponse";
  }

  static const char* value(const ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool success\n"
"\n"
"bool is_sleeping\n"
"\n"
"string device_user_id\n"
"\n"
"int32 min_binning_x\n"
"int32 max_binning_x\n"
"int32 current_binning_x\n"
"\n"
"int32 min_binning_y\n"
"int32 max_binning_y\n"
"int32 current_binning_y\n"
"\n"
"float32 max_framerate\n"
"float32 current_framerate\n"
"\n"
"float32 min_exposure\n"
"float32 max_exposure\n"
"float32 current_exposure\n"
"\n"
"float32 min_gain_in_cam_units\n"
"float32 max_gain_in_cam_units\n"
"float32 current_gain_in_cam_units\n"
"\n"
"float32 min_gain\n"
"float32 max_gain\n"
"float32 current_gain\n"
"\n"
"float32 min_gamma\n"
"float32 max_gamma\n"
"float32 current_gamma\n"
"\n"
"bool brightness_continuous\n"
"bool gain_auto\n"
"bool exposure_auto\n"
"\n"
;
  }

  static const char* value(const ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.success);
      stream.next(m.is_sleeping);
      stream.next(m.device_user_id);
      stream.next(m.min_binning_x);
      stream.next(m.max_binning_x);
      stream.next(m.current_binning_x);
      stream.next(m.min_binning_y);
      stream.next(m.max_binning_y);
      stream.next(m.current_binning_y);
      stream.next(m.max_framerate);
      stream.next(m.current_framerate);
      stream.next(m.min_exposure);
      stream.next(m.max_exposure);
      stream.next(m.current_exposure);
      stream.next(m.min_gain_in_cam_units);
      stream.next(m.max_gain_in_cam_units);
      stream.next(m.current_gain_in_cam_units);
      stream.next(m.min_gain);
      stream.next(m.max_gain);
      stream.next(m.current_gain);
      stream.next(m.min_gamma);
      stream.next(m.max_gamma);
      stream.next(m.current_gamma);
      stream.next(m.brightness_continuous);
      stream.next(m.gain_auto);
      stream.next(m.exposure_auto);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GetCamPropertiesResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::camera_control_msgs::GetCamPropertiesResponse_<ContainerAllocator>& v)
  {
    s << indent << "success: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.success);
    s << indent << "is_sleeping: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.is_sleeping);
    s << indent << "device_user_id: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.device_user_id);
    s << indent << "min_binning_x: ";
    Printer<int32_t>::stream(s, indent + "  ", v.min_binning_x);
    s << indent << "max_binning_x: ";
    Printer<int32_t>::stream(s, indent + "  ", v.max_binning_x);
    s << indent << "current_binning_x: ";
    Printer<int32_t>::stream(s, indent + "  ", v.current_binning_x);
    s << indent << "min_binning_y: ";
    Printer<int32_t>::stream(s, indent + "  ", v.min_binning_y);
    s << indent << "max_binning_y: ";
    Printer<int32_t>::stream(s, indent + "  ", v.max_binning_y);
    s << indent << "current_binning_y: ";
    Printer<int32_t>::stream(s, indent + "  ", v.current_binning_y);
    s << indent << "max_framerate: ";
    Printer<float>::stream(s, indent + "  ", v.max_framerate);
    s << indent << "current_framerate: ";
    Printer<float>::stream(s, indent + "  ", v.current_framerate);
    s << indent << "min_exposure: ";
    Printer<float>::stream(s, indent + "  ", v.min_exposure);
    s << indent << "max_exposure: ";
    Printer<float>::stream(s, indent + "  ", v.max_exposure);
    s << indent << "current_exposure: ";
    Printer<float>::stream(s, indent + "  ", v.current_exposure);
    s << indent << "min_gain_in_cam_units: ";
    Printer<float>::stream(s, indent + "  ", v.min_gain_in_cam_units);
    s << indent << "max_gain_in_cam_units: ";
    Printer<float>::stream(s, indent + "  ", v.max_gain_in_cam_units);
    s << indent << "current_gain_in_cam_units: ";
    Printer<float>::stream(s, indent + "  ", v.current_gain_in_cam_units);
    s << indent << "min_gain: ";
    Printer<float>::stream(s, indent + "  ", v.min_gain);
    s << indent << "max_gain: ";
    Printer<float>::stream(s, indent + "  ", v.max_gain);
    s << indent << "current_gain: ";
    Printer<float>::stream(s, indent + "  ", v.current_gain);
    s << indent << "min_gamma: ";
    Printer<float>::stream(s, indent + "  ", v.min_gamma);
    s << indent << "max_gamma: ";
    Printer<float>::stream(s, indent + "  ", v.max_gamma);
    s << indent << "current_gamma: ";
    Printer<float>::stream(s, indent + "  ", v.current_gamma);
    s << indent << "brightness_continuous: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.brightness_continuous);
    s << indent << "gain_auto: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.gain_auto);
    s << indent << "exposure_auto: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.exposure_auto);
  }
};

} // namespace message_operations
} // namespace ros

#endif // CAMERA_CONTROL_MSGS_MESSAGE_GETCAMPROPERTIESRESPONSE_H
