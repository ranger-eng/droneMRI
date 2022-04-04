#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "sensor_msgs/Image.h"
#include "my_robot_messages/Float32Stamped.h"
#include "my_robot_messages/LeftSide.h"
#include "std_msgs/Float32.h"
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
    my_robot_messages::Float32Stamped   laser_msg;
    int imu_l_index =                   0;
    int imu_laser_index =               0;
    sensor_msgs::Imu                    imu_l_msg[IMU_BUF_LENGTH];
    sensor_msgs::Imu                    imu_laser_msg[IMU_BUF_LENGTH];
};
message_buffer_struct                   msg_buf;

void callback_CAM_L(const sensor_msgs::ImageConstPtr &img_ptr) {
    // DO NOTHING
    cout << "img+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=" << endl;
}

void callback_DISTANCE(const my_robot_messages::Float32StampedConstPtr &laser_ptr) {
    // Store newest laser value in msg_buf
    msg_buf.laser_msg = *laser_ptr;
    cout << "laser+=+=+=+=+=+=+=+" << endl;
}

void callback_IMU_L(const sensor_msgs::ImuConstPtr &imu_l_ptr) {
    // Store newest imu value in latest index of the circular buffer
    int i = msg_buf.imu_l_index;

    msg_buf.imu_l_msg[i%IMU_BUF_LENGTH] = *imu_l_ptr;
    msg_buf.imu_l_index += 1;
    cout << "imu+=+=" << endl;
}

void callback_IMU_LASER(const sensor_msgs::ImuConstPtr &imu_laser_ptr) {
    // Store newest imu value in latest index of the circular buffer
    int i = msg_buf.imu_laser_index;

    msg_buf.imu_laser_msg[i%IMU_BUF_LENGTH] = *imu_laser_ptr;
    msg_buf.imu_laser_index += 1;
    cout << "imu+=" << endl;
}

void callback_SYNC(ros::Publisher& pub, const sensor_msgs::ImuConstPtr &imu_l_ptr, const sensor_msgs::ImuConstPtr &imu_laser_ptr, const sensor_msgs::ImageConstPtr &img_ptr) {
    my_robot_messages::LeftSide msg;
    cout << "-------------Complete set---------------" << endl;
    
    msg.header.stamp = ros::Time::now();
    msg.header.frame_id = "oneside message with IMU_L, IMU_LASER, CAM_L, and LASER.";
    //---
    msg.laser = msg_buf.laser_msg.data;
    msg.image_l = *img_ptr;
    // msg.imu_l = msg_buf.imu_l_msg[0];
    // msg.imu_laser = msg_buf.imu_laser_msg[0];
    msg.imu_l = average_imu_buffer(&msg_buf.imu_l_msg[0]);
    msg.imu_laser = average_imu_buffer(&msg_buf.imu_laser_msg[0]);

    //cout << "IMU time stamp: " << msg.imu_l.header.stamp << " || " << "IMU LASER time stamp: " << msg.imu_laser.header.stamp << endl;
    //cout << "Laser time stamp: " << msg.laser << " || " << "Image time stamp: " << msg.image_l.header.stamp << endl;

    pub.publish(msg);
}


int main(int argc, char **argv) {
    bool mean_option = false;
    int c;

    ros::init(argc, argv, "left_side_sync");
    ros::NodeHandle n;

    // parse input arguments
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

    // synced publisher. Published message is a complete set of the following sensor messages
    // my_robot_messages::LeftSide
    // Header header
    // ====
    // sensor_msgs/Image image_l
    // float32 laser
    // sensor_msgs/Imu imu_l
    // sensor_msgs/Imu imu_laser
    ros::Publisher oneside_pub = n.advertise<my_robot_messages::LeftSide>("LeftSide_Pub", 1);

    // main_sync callback, callback_SYNC, gets executed when a complete set of these messages arrive
    // se  ApproximateTime policy for message_flters in ROS.
    message_filters::Subscriber<sensor_msgs::Imu> imu_l_sub(n, "/my_robot_driver/IMU_L/data", 1);
    message_filters::Subscriber<sensor_msgs::Imu> imu_laser_sub(n, "/my_robot_driver/IMU_LASER/data", 1);
    message_filters::Subscriber<sensor_msgs::Image> img_sub(n, "/my_robot_driver/CAM_L/image_raw", 1);

    // subscribers that handle any preprocessing that needs to take place.
    // A reference to the message appears in the callback
    ros::Subscriber img_preprocess_sub = n.subscribe("/my_robot_driver/CAM_L/image_raw", 1, callback_CAM_L);
    ros::Subscriber laser_preprocess_sub = n.subscribe("/my_robot_driver/DISTANCE", 1, callback_DISTANCE);
    ros::Subscriber imu_l_preprocess_sub = n.subscribe("/my_robot_driver/IMU_L/data", 5, callback_IMU_L);
    ros::Subscriber imu_laser_preprocess_sub = n.subscribe("/my_robot_driver/IMU_LASER/data", 5, callback_IMU_LASER);

    // Approximate time syncronozation takes in mag, imu, laser distance, and image_raw sensor messages and combines them
    // the slowest transmitting sensor dictates the transmission rate as async policy will wait for a complete set of all 4 sensors before transmitting one message.
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Imu, sensor_msgs::Imu, sensor_msgs::Image> MyAsyncPolicy_sync;
    message_filters::Synchronizer<MyAsyncPolicy_sync> main_sync(MyAsyncPolicy_sync(10), imu_l_sub, imu_laser_sub, img_sub);
    main_sync.registerCallback(boost::bind(&callback_SYNC, boost::ref(oneside_pub), _1, _2, _3));


    ros::spin();

    return 0;
}
