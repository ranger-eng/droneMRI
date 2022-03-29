#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "sensor_msgs/MagneticField.h"
#include "sensor_msgs/Image.h"
#include "my_robot_messages/Float32Stamped.h"
#include "my_robot_messages/LeftSide.h"
#include "std_msgs/Float32.h"
#include "message_filters/subscriber.h"
#include "message_filters/time_synchronizer.h"
#include "message_filters/sync_policies/approximate_time.h"
#define BUFFER_LENGTH 100

using namespace std;

my_robot_messages::Float32Stamped laser_msg;
void laserCallback(const my_robot_messages::Float32Stamped &laser_ptr) {
    laser_msg.header = laser_ptr.header;
    laser_msg.data = laser_ptr.data;
    cout << laser_ptr.data << endl;
}

void callback(ros::Publisher& pub, const sensor_msgs::ImuConstPtr &imu_l_ptr, const sensor_msgs::ImuConstPtr &imu_laser_ptr, const sensor_msgs::ImageConstPtr &img_ptr) {
    
    my_robot_messages::LeftSide msg;
    
    msg.header.stamp = ros::Time::now();
    msg.header.frame_id = "oneside message with IMU_L, IMU_LASER, CAM_L, and LASER.";
    //---
    msg.laser = laser_msg.data;
    msg.imu_l = *imu_l_ptr;
    msg.imu_laser = *imu_laser_ptr;
    msg.image_l = *img_ptr;

    cout << "IMU time stamp: " << msg.imu_l.header.stamp << " || " << "IMU LASER time stamp: " << msg.imu_laser.header.stamp << endl;
    cout << "Laser time stamp: " << msg.laser << " || " << "Image time stamp: " << msg.image_l.header.stamp << endl;

    pub.publish(msg);
}

int main(int argc, char **argv) {
    bool mean_option = false;
    int c;

    ros::init(argc, argv, "oneside_sensor_sync");
    ros::NodeHandle n;

    while ((c = getopt(argc, argv, "m")) != -1) {
        switch (c) {
            // choose if the one sided sync is averaged or not 
            case 'm':
                mean_option = true;
                break;
            case '?':
                if (isprint(optopt))
                    fprintf(stderr, "Unknown option '-%c'\n", optopt);
                    fprintf(stderr, "Usage: oneside_sensor_sync <-m:for averaging>\n");
                    return 1;
        }
    }

    // publishers
    ros::Publisher oneside_pub = n.advertise<my_robot_messages::LeftSide>("LeftSide_Pub", 100);

    // subscribers
    message_filters::Subscriber<sensor_msgs::Imu> imu_l_sub(n, "/my_robot_driver/IMU_L/data", 1);
    message_filters::Subscriber<sensor_msgs::Imu> imu_laser_sub(n, "/my_robot_driver/IMU_LASER/data", 1);
    message_filters::Subscriber<sensor_msgs::Image> img_sub(n, "/my_robot_driver/CAM_L/image_raw", 1);

    ros::Subscriber laser_sub = n.subscribe("/my_robot_driver/DISTANCE", 1000, laserCallback);

    // Approximate time syncronozation takes in mag, imu, laser distance, and image_raw sensor messages and combines them
    // the slowest transmitting sensor dictates the transmission rate as async policy will wait for a complete set of all 4 sensors before transmitting one message.
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Imu, sensor_msgs::Imu, sensor_msgs::Image> MyAsyncPolicy_sync;
    message_filters::Synchronizer<MyAsyncPolicy_sync> main_sync(MyAsyncPolicy_sync(10), imu_l_sub, imu_laser_sub, img_sub);
    main_sync.registerCallback(boost::bind(&callback, boost::ref(oneside_pub), _1, _2, _3));


    ros::spin();

    return 0;
}
