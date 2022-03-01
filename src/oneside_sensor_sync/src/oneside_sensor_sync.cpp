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
#define BUFFER_LENGTH 100

using namespace message_filters;
using namespace std;

struct buff_struct {
    int buffer_indx = 0;
    float orientation[3][BUFFER_LENGTH] = {0};
    float angular_velocity[3][BUFFER_LENGTH] = {0};
    float linear_acceleration[3][BUFFER_LENGTH] = {0};

    float magnetic_field[3][BUFFER_LENGTH] = {0};
};

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


    // cout << "IMU time stamp: " << imu->header.stamp << " || " << "Magnetometer time stamp: " << mag->header.stamp << endl;
    // cout << "Laser time stamp: " << laser->header.stamp << " || " << "Image time stamp: " << img->header.stamp << endl;

    pub.publish(msg);
}

void callback_avg(ros::Publisher& imu_pub, ros::Publisher& mag_pub, struct buff_struct& buff, const sensor_msgs::ImuConstPtr &imu, const sensor_msgs::MagneticFieldConstPtr &mag) {
    int indx = buff.buffer_indx;
    float imu_orientation_avg[3] = {0.0};
    float imu_angular_velocity_avg[3] = {0.0};
    float imu_linear_acceleration_avg[3] = {0.0};
    float mag_magnetic_field_avg[3] = {0.0};
    sensor_msgs::Imu imu_msg;
    sensor_msgs::MagneticField mag_msg;

    // pull current value
    buff.orientation[0][indx] = imu->orientation.x; buff.angular_velocity[0][indx] = imu->angular_velocity.x; buff.linear_acceleration[0][indx] = imu->linear_acceleration.x;
    buff.orientation[1][indx] = imu->orientation.y; buff.angular_velocity[1][indx] = imu->angular_velocity.y; buff.linear_acceleration[1][indx] = imu->linear_acceleration.y;
    buff.orientation[2][indx] = imu->orientation.z; buff.angular_velocity[2][indx] = imu->angular_velocity.z; buff.linear_acceleration[2][indx] = imu->linear_acceleration.z;
    buff.magnetic_field[0][indx] = mag->magnetic_field.x; buff.magnetic_field[1][indx] = mag->magnetic_field.y; buff.magnetic_field[2][indx] = mag->magnetic_field.z;
   
    // average the whole buffer, for x y and z
    for (int j=0; j<3; j++) {
        for (int i=0; i<BUFFER_LENGTH; i++) {
            imu_orientation_avg[j] = imu_orientation_avg[j] + buff.orientation[j][i]/BUFFER_LENGTH;
            imu_angular_velocity_avg[j] = imu_angular_velocity_avg[j] + buff.angular_velocity[j][i]/BUFFER_LENGTH;
            imu_linear_acceleration_avg[j] = imu_linear_acceleration_avg[j] + buff.linear_acceleration[j][i]/BUFFER_LENGTH;
            mag_magnetic_field_avg[j] = mag_magnetic_field_avg[j] + buff.magnetic_field[j][i]/BUFFER_LENGTH;
        }
    }

    for (int j=0; j<3; j++) {
        cout << "Avg " << imu_orientation_avg[j] << " || " << "Raw " << imu->orientation.x << endl;
    }
    
    // populate a new message with the averaged values an publish
    imu_msg.header = imu->header;
    imu_msg.orientation.x = imu_orientation_avg[0]; imu_msg.orientation.y = imu_orientation_avg[1]; imu_msg.orientation.z = imu_orientation_avg[2]; 
    imu_msg.orientation_covariance = imu->orientation_covariance;
    imu_msg.angular_velocity.x = imu_angular_velocity_avg[0]; imu_msg.angular_velocity.y = imu_angular_velocity_avg[1]; imu_msg.angular_velocity.z = imu_angular_velocity_avg[2]; 
    imu_msg.angular_velocity_covariance = imu->angular_velocity_covariance;
    imu_msg.linear_acceleration.x = imu_linear_acceleration_avg[0]; imu_msg.linear_acceleration.y = imu_linear_acceleration_avg[1]; imu_msg.linear_acceleration.z = imu_linear_acceleration_avg[2]; 
    imu_msg.linear_acceleration_covariance = imu->linear_acceleration_covariance;

    mag_msg.header = mag->header;
    mag_msg.magnetic_field.x = mag_magnetic_field_avg[0]; mag_msg.magnetic_field.y = mag_magnetic_field_avg[1]; mag_msg.magnetic_field.z = mag_magnetic_field_avg[2];
    mag_msg.magnetic_field_covariance = mag->magnetic_field_covariance;

    mag_pub.publish(mag_msg);
    imu_pub.publish(imu_msg);

    // increment buff_index counter, mod BUFFER_LENGTH so the buffer is circular
    buff.buffer_indx = (buff.buffer_indx + 1)%BUFFER_LENGTH;
}

int main(int argc, char **argv) {
    struct buff_struct buff;

    ros::init(argc, argv, "oneside_sensor_sync");
    ros::NodeHandle n;

    ros::Publisher oneside_pub = n.advertise<oneside_sensor_sync::Oneside>("oneside_syncd", 100);
    ros::Publisher imu_avg_pub = n.advertise<sensor_msgs::Imu>("oneside_syncd/imu_avg", 100);
    ros::Publisher mag_avg_pub = n.advertise<sensor_msgs::MagneticField>("oneside_syncd/mag_avg", 100);

    message_filters::Subscriber<sensor_msgs::Imu> imu_sub(n, "/IMU/imu/data", 1);
    message_filters::Subscriber<sensor_msgs::MagneticField> mag_sub(n, "/IMU/imu/mag", 1);
    message_filters::Subscriber<distance_sensor::Float32Stamped> laser_sub(n, "/Laser/distance", 1);
    message_filters::Subscriber<sensor_msgs::Image> img_sub(n, "/camera/left_camera/image_raw", 1);

    // a callback for averaging imu and mag data
    typedef sync_policies::ApproximateTime<sensor_msgs::Imu, sensor_msgs::MagneticField> MyAsyncPolicy_avg;
    Synchronizer<MyAsyncPolicy_avg> sync_avg(MyAsyncPolicy_avg(10), imu_sub, mag_sub);
    
    sync_avg.registerCallback(boost::bind(&callback_avg, boost::ref(imu_avg_pub), boost::ref(mag_avg_pub), boost::ref(buff), _1, _2));
    
    // Approximate time syncronozation takes in mag, imu, laser distance, and image_raw sensor messages and combines them
    // the slowest transmitting sensor dictates the transmission rate as async policy will wait for a complete set of all 4 sensors before transmitting one message.
    typedef sync_policies::ApproximateTime<sensor_msgs::Imu, sensor_msgs::MagneticField, distance_sensor::Float32Stamped, sensor_msgs::Image> MyAsyncPolicy;
    Synchronizer<MyAsyncPolicy> sync(MyAsyncPolicy(10), imu_sub, mag_sub, laser_sub, img_sub);
    
    sync.registerCallback(boost::bind(&callback, boost::ref(oneside_pub), _1, _2, _3, _4));

    ros::spin();

    return 0;
}
