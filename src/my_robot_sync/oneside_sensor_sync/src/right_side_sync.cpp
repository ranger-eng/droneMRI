#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "sensor_msgs/Image.h"
#include "my_robot_messages/RightSide.h"
#include "message_filters/subscriber.h"
#include "message_filters/time_synchronizer.h"
#include "message_filters/sync_policies/approximate_time.h"
#define IMU_BUF_LENGTH 10

using namespace std;

sensor_msgs::Imu average_imu_buffer(sensor_msgs::Imu *imu_msg) {
    sensor_msgs::Imu msg;
    for (int i=0; i<IMU_BUF_LENGTH; i++) {
        msg.orientation.x += imu_msg[i].orientation.x/IMU_BUF_LENGTH;
        msg.orientation.y += imu_msg[i].orientation.y/IMU_BUF_LENGTH;
        msg.orientation.z += imu_msg[i].orientation.z/IMU_BUF_LENGTH;
        msg.orientation.w += imu_msg[i].orientation.w/IMU_BUF_LENGTH;

        msg.angular_velocity.x += imu_msg[i].angular_velocity.x/IMU_BUF_LENGTH;
        msg.angular_velocity.y += imu_msg[i].angular_velocity.y/IMU_BUF_LENGTH;
        msg.angular_velocity.z += imu_msg[i].angular_velocity.z/IMU_BUF_LENGTH;

        msg.linear_acceleration.x += imu_msg[i].linear_acceleration.x/IMU_BUF_LENGTH;
        msg.linear_acceleration.y += imu_msg[i].linear_acceleration.y/IMU_BUF_LENGTH;
        msg.linear_acceleration.z += imu_msg[i].linear_acceleration.z/IMU_BUF_LENGTH;
    }
    return msg;
}

// Define buffer containing copies of the messages recieved in the callbacks
struct message_buffer_struct {
    sensor_msgs::Image                  cam_msg;
    int imu_r_index =                   0;
    sensor_msgs::Imu                    imu_r_msg[IMU_BUF_LENGTH];
};
message_buffer_struct                   msg_buf;
bool average_imus = false;

void callback_CAM_R(const sensor_msgs::ImageConstPtr &img_ptr) {
    // DO NOTHING
    cout << "img+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=" << endl;
}

void callback_IMU_R(const sensor_msgs::ImuConstPtr &imu_r_ptr) {
    // Store newest imu value in latest index of the circular buffer
    int i = msg_buf.imu_r_index;

    msg_buf.imu_r_msg[i%IMU_BUF_LENGTH] = *imu_r_ptr;
    msg_buf.imu_r_index += 1;
    cout << "imu+=+=" << endl;
}

void callback_SYNC(ros::Publisher& pub, const sensor_msgs::ImuConstPtr &imu_r_ptr, const sensor_msgs::ImageConstPtr &img_ptr) {
    my_robot_messages::RightSide msg;
    cout << "-------------Complete set---------------" << endl;
    
    // populate an aggregate message
    msg.header.stamp = ros::Time::now();
    msg.header.frame_id = "oneside message with IMU_L, IMU_LASER, CAM_L, and LASER.";
    //---
    msg.image_r = *img_ptr;
    if (average_imus) {
        msg.imu_r = average_imu_buffer(&msg_buf.imu_r_msg[0]);
    }
    else {
        msg.imu_r = *imu_r_ptr;
    }

    //cout << "IMU time stamp: " << msg.imu_l.header.stamp << " || " << "IMU LASER time stamp: " << msg.imu_laser.header.stamp << endl;
    //cout << "Laser time stamp: " << msg.laser << " || " << "Image time stamp: " << msg.image_l.header.stamp << endl;

    // publish message
    pub.publish(msg);
}

int main(int argc, char **argv) {
    int c;

    ros::init(argc, argv, "right_side_sync");
    ros::NodeHandle n;

    // parse input arguments
    // -m will average imu data
    while ((c = getopt(argc, argv, "m")) != -1) {
        switch (c) {
            case 'm':
                average_imus = true;
                break;
            case '?':
                if (isprint(optopt))
                    fprintf(stderr, "Unknown option '-%c'\n", optopt);
                    fprintf(stderr, "Usage: leftside_sensor_sync_node <-m:for averaging>\n");
                    return 1;
        }
    }

    // synced publisher. Published message is a complete set of the following sensor messages
    // my_robot_messages::LeftSide
    // Header header
    // ====
    // sensor_msgs/Image image_r
    // sensor_msgs/Imu imu_r
    ros::Publisher oneside_pub = n.advertise<my_robot_messages::RightSide>("RightSide_Pub", 1);

    // main_sync callback, callback_SYNC, gets executed when a complete set of these messages arrive
    // se  ApproximateTime policy for message_flters in ROS.
    message_filters::Subscriber<sensor_msgs::Imu> imu_r_sub(n, "/my_robot_driver/IMU_R/data", 1);
    message_filters::Subscriber<sensor_msgs::Image> img_sub(n, "/my_robot_driver/CAM_R/image_raw", 1);

    // subscribers that handle any preprocessing that needs to take place.
    // A reference to the message appears in the callback
    ros::Subscriber img_preprocess_sub = n.subscribe("/my_robot_driver/CAM_R/image_raw", 1, callback_CAM_R);
    ros::Subscriber imu_r_preprocess_sub = n.subscribe("/my_robot_driver/IMU_R/data", 5, callback_IMU_R);

    // Approximate time syncronozation takes in mag, imu, laser distance, and image_raw sensor messages and combines them
    // the slowest transmitting sensor dictates the transmission rate as async policy will wait for a complete set of all 4 sensors before transmitting one message.
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Imu, sensor_msgs::Image> MyAsyncPolicy_sync;
    message_filters::Synchronizer<MyAsyncPolicy_sync> main_sync(MyAsyncPolicy_sync(10), imu_r_sub, img_sub);
    main_sync.registerCallback(boost::bind(&callback_SYNC, boost::ref(oneside_pub), _1, _2));

    ros::spin();

    return 0;
}
