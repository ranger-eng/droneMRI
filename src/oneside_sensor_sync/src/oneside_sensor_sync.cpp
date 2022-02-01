#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "sensor_msgs/MagneticField.h"
#include "std_msgs/Float32.h"
#include "message_filters/subscriber.h"
#include "message_filters/time_synchronizer.h"
#include "message_filters/sync_policies/approximate_time.h"

using namespace sensor_msgs;
using namespace message_filters;
using namespace std;

void callback(const ImuConstPtr &imu, const MagneticFieldConstPtr &mag) {
    cout << "IMU time stamp: " << imu->header.stamp << " || " << "Magnetometer time stamp: " << mag->header.stamp << endl;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "oneside_sensor_sync");
    ros::NodeHandle n;

    message_filters::Subscriber<Imu> imu_sub(n, "/IMU/imu/data", 1);
    message_filters::Subscriber<MagneticField> mag_sub(n, "/IMU/imu/mag", 1);

    typedef sync_policies::ApproximateTime<Imu, MagneticField> MyAsyncPolicy;
    Synchronizer<MyAsyncPolicy> sync(MyAsyncPolicy(10), imu_sub, mag_sub);
    sync.registerCallback(boost::bind(&callback, _1, _2));

    ros::spin();

    return 0;
}
