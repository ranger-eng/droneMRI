#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "sensor_msgs/MagneticField.h"
#include "std_msgs/Float32.h"
#include "message_filters/subscriber.h"
#include "message_filters/time_synchronizer.h"
#include "message_filters/sync_policies/approximate_time.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "oneside_sensor_sync");
    ros::NodeHandle n;

    message_filters::Subscriber<sensor_msgs::Imu> imu_sub(n, "data", 1);

    return 0;
}
