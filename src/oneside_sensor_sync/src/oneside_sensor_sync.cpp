#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "sensor_msgs/MagneticField.h"
#include "sensor_msgs/Image.h"
#include "distance_sensor/Float32Stamped.h"
#include "std_msgs/Float32.h"
#include "message_filters/subscriber.h"
#include "message_filters/time_synchronizer.h"
#include "message_filters/sync_policies/approximate_time.h"

using namespace sensor_msgs;
using namespace distance_sensor;
using namespace message_filters;
using namespace std;

void callback(const ImuConstPtr &imu, const MagneticFieldConstPtr &mag, const Float32StampedConstPtr &laser, const ImageConstPtr &img) {
    cout << "IMU time stamp: " << imu->header.stamp << " || " << "Magnetometer time stamp: " << mag->header.stamp << endl;
    cout << "Laser time stamp: " << laser->header.stamp << " || " << "Image time stamp: " << img->header.stamp << endl;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "oneside_sensor_sync");
    ros::NodeHandle n;

    message_filters::Subscriber<Imu> imu_sub(n, "/IMU/imu/data", 1);
    message_filters::Subscriber<MagneticField> mag_sub(n, "/IMU/imu/mag", 1);
    message_filters::Subscriber<Float32Stamped> laser_sub(n, "/Laser/distance", 1);
    message_filters::Subscriber<Image> img_sub(n, "/camera/left_camera/image_raw", 1);

    typedef sync_policies::ApproximateTime<Imu, MagneticField, Float32Stamped, Image> MyAsyncPolicy;
    Synchronizer<MyAsyncPolicy> sync(MyAsyncPolicy(10), imu_sub, mag_sub, laser_sub, img_sub);
    sync.registerCallback(boost::bind(&callback, _1, _2, _3, _4));

    ros::spin();

    return 0;
}
