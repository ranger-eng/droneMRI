#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "sensor_msgs/MagneticField.h"
#include "sensor_msgs/Image.h"
#include "distance_sensor/Float32Stamped.h"
#include "oneside_sensor_sync/Oneside.h"
#include "std_msgs/Float32.h"
#include "message_filters/subscriber.h"
#include "message_filters/time_synchronizer.h"
#include "message_filters/sync_policies/approximate_time.h"

using namespace message_filters;
using namespace std;

void callback(ros::Publisher& pub, const sensor_msgs::ImuConstPtr &imu, const sensor_msgs::MagneticFieldConstPtr &mag, const distance_sensor::Float32StampedConstPtr &laser, const sensor_msgs::ImageConstPtr &img) {
    
    oneside_sensor_sync::Oneside msg;
    msg.header.stamp = ros::Time::now();
    msg.header.frame_id = "oneside message with Imu, MagneticField, Image, and Laser Distance.";
    msg.laser = laser->data;
    
    msg.imu.header = imu->header;
    msg.imu.orientation = imu->orientation;
    msg.imu.orientation_covariance = imu->orientation_covariance;
    msg.imu.angular_velocity = imu->angular_velocity;
    msg.imu.angular_velocity_covariance = imu->angular_velocity_covariance;
    msg.imu.linear_acceleration = imu->linear_acceleration;
    msg.imu.linear_acceleration_covariance = imu->linear_acceleration_covariance;

    msg.mag.header = mag->header;
    msg.mag.magnetic_field = mag->magnetic_field;
    msg.mag.magnetic_field_covariance = mag->magnetic_field_covariance;

    msg.image.header = img->header;
    msg.image.height = img->height;
    msg.image.width = img->width;
    msg.image.encoding = img->encoding;
    msg.image.is_bigendian = img->is_bigendian;
    msg.image.step = img->step;
    msg.image.data = img->data;


    cout << "IMU time stamp: " << imu->header.stamp << " || " << "Magnetometer time stamp: " << mag->header.stamp << endl;
    cout << "Laser time stamp: " << laser->header.stamp << " || " << "Image time stamp: " << img->header.stamp << endl;

    pub.publish(msg);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "oneside_sensor_sync");
    ros::NodeHandle n;

    ros::Publisher oneside_pub = n.advertise<oneside_sensor_sync::Oneside>("oneside_syncd", 100);

    message_filters::Subscriber<sensor_msgs::Imu> imu_sub(n, "/IMU/imu/data", 1);
    message_filters::Subscriber<sensor_msgs::MagneticField> mag_sub(n, "/IMU/imu/mag", 1);
    message_filters::Subscriber<distance_sensor::Float32Stamped> laser_sub(n, "/Laser/distance", 1);
    message_filters::Subscriber<sensor_msgs::Image> img_sub(n, "/camera/left_camera/image_raw", 1);

    typedef sync_policies::ApproximateTime<sensor_msgs::Imu, sensor_msgs::MagneticField, distance_sensor::Float32Stamped, sensor_msgs::Image> MyAsyncPolicy;
    Synchronizer<MyAsyncPolicy> sync(MyAsyncPolicy(10), imu_sub, mag_sub, laser_sub, img_sub);
    
    sync.registerCallback(boost::bind(&callback, boost::ref(oneside_pub), _1, _2, _3, _4));

    ros::spin();

    return 0;
}
