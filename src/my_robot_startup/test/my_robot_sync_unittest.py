#!/usr/bin/env python3
PKG = 'my_robot_startup'
import roslib; roslib.load_manifest(PKG)  # This line is not needed with Catkin.
import rospy
from my_robot_messages.msg import LeftSide

import sys
import unittest

class MyRobotSyncLeft(unittest.TestCase):
    def test_imu_l_topic_from_bagfile_exists(self): # only functions with 'test_'-prefix will be run!
        topics = rospy.get_published_topics()
        topic_exists = 0
        for i in topics:
            if '/my_robot_driver/IMU_L/data' in i:
                topic_exists = 1
        self.assertEquals(topic_exists, 1, "1!=1")
    
    def test_imu_laser_topic_from_bagfile_exists(self): # only functions with 'test_'-prefix will be run!
        topics = rospy.get_published_topics()
        topic_exists = 0
        for i in topics:
            if '/my_robot_driver/IMU_LASER/data' in i:
                topic_exists = 1
        self.assertEquals(topic_exists, 1, "1!=1")

    def test_distance_topic_from_bagfile_exists(self): # only functions with 'test_'-prefix will be run!
        topics = rospy.get_published_topics()
        topic_exists = 0
        for i in topics:
            if '/my_robot_driver/DISTANCE' in i:
                topic_exists = 1
        self.assertEquals(topic_exists, 1, "1!=1")

    def test_image_topic_from_bagfile_exists(self): # only functions with 'test_'-prefix will be run!
        topics = rospy.get_published_topics()
        topic_exists = 0
        for i in topics:
            if '/my_robot_driver/CAM_L/image_raw' in i:
                topic_exists = 1
        self.assertEquals(topic_exists, 1, "1!=1")

    def msg_cb(self, msg):
        self.success = True

    def test_leftside_sub(self):
        rospy.init_node('random_sub')
        self.success = False
        rospy.sleep(rospy.Duration.from_sec(0.5))
        rospy.Subscriber("LeftSide_Pub", LeftSide, self.msg_cb)
        rospy.sleep(rospy.Duration.from_sec(0.5))
        self.assertEqual(self.success, True)


if __name__ == '__main__':
    import rostest
    rostest.rosrun(PKG, 'testmy_robot_sync_leftside', MyRobotSyncLeft)
