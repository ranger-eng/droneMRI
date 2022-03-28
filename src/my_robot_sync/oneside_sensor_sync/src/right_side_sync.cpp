#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "sensor_msgs/MagneticField.h"
#include "sensor_msgs/Image.h"
#include "my_robot_messages/Float32Stamped.h"
#include "my_robot_messages/RightSide.h"
#include "std_msgs/Float32.h"
#include "message_filters/subscriber.h"
#include "message_filters/time_synchronizer.h"
#include "message_filters/sync_policies/approximate_time.h"
#define BUFFER_LENGTH 100

using namespace message_filters;
using namespace std;

void callback(ros::Publisher& pub, const sensor_msgs::ImuConstPtr &imu_r_ptr, const sensor_msgs::ImageConstPtr &img_ptr) {
    
    my_robot_messages::RightSide msg;
    
    msg.header.stamp = ros::Time::now();
    msg.header.frame_id = "oneside message with IMU_L, IMU_LASER, CAM_L, and LASER.";
    //---
    msg.imu_r = *imu_r_ptr;
    msg.image_r = *img_ptr;

    cout << "IMU time stamp: " << msg.imu_r.header.stamp << endl;
    cout << "Image time stamp: " << msg.image_r.header.stamp << endl;

    pub.publish(msg);
}

int main(int argc, char **argv) {
    int c;
    bool this_is_right_side = false; // set up left side sync by default

    ros::init(argc, argv, "right_side_sync");
    ros::NodeHandle n;

    while ((c = getopt(argc, argv, "rl")) != -1) {
        switch (c) {
            // choose left or right side 
            case 'r':
                this_is_right_side = true;
                break;
            case 'l':
                this_is_right_side = false;
                break;
            case '?':
                if (isprint(optopt))
                    return 1;
        }
    }

    // publishers
    ros::Publisher oneside_pub = n.advertise<my_robot_messages::RightSide>("RightSide_Pub", 100);

    // subscribers
    message_filters::Subscriber<sensor_msgs::Imu> imu_r_sub(n, "/my_robot_driver/IMU_R/data", 1);
    message_filters::Subscriber<sensor_msgs::Image> img_sub(n, "/my_robot_driver/CAM_R/image_raw", 1);

    // Approximate time syncronozation takes in mag, imu, laser distance, and image_raw sensor messages and combines them
    // the slowest transmitting sensor dictates the transmission rate as async policy will wait for a complete set of all 4 sensors before transmitting one message.
    typedef sync_policies::ApproximateTime<sensor_msgs::Imu, sensor_msgs::Image> MyAsyncPolicy_sync;
    Synchronizer<MyAsyncPolicy_sync> main_sync(MyAsyncPolicy_sync(10), imu_r_sub, img_sub);
    main_sync.registerCallback(boost::bind(&callback, boost::ref(oneside_pub), _1, _2));

    ros::spin();

    return 0;
}
