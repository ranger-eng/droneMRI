#!/usr/bin/env python3
import rospy
import cv2 as cv
from cv_bridge import CvBridge
from sensor_msgs.msg import Imu, Image
from geometry_msgs.msg import Vector3
from std_msgs.msg import Float32, String
import numpy as np


import os

directory = "/home/pibot/Desktop"
class Merger:
    def __init__(self):
        self.bridge = CvBridge()
        rospy.Subscriber('/IMU/imu/data', Imu, self.imu_cb)
        rospy.Subscriber('/camera/left_camera/image_raw', Image, self.camera_cb)
        rospy.Subscriber('/rpy_angles', Vector3,  self.angles_cb)
        rospy.Subscriber('/Laser/distance', Float32, self.laser_cb)
        rospy.Subscriber('/keyboard_event', String, self.key_cb)
        self.IMU = 0
        self.counter = 0
        self.dist = 0


    def imu_cb(self,msg):
        # self.IMU.secs = msg.header.stamp.secs
        # self.IMU.nsecs = msg.header.stamp.nsecs
        # self.IMU.x = msg.orientation.x
        # self.IMU.y = msg.orientation.y
        # self.IMU.z = msg.orientation.z
        # self.IMU.w = msg.orientation.w
        pass


    def camera_cb(self,msg):
        rospy.loginfo_once('connected to camera')
        
        self.cv_image = self.bridge.imgmsg_to_cv2(msg, "mono8")
        cv.imshow('View',self.cv_image)



        pass
    def angles_cb(self,msg):
        self.angles = np.array((msg.x,msg.y,msg.z))
        pass
    def laser_cb(self,msg):
        self.dist = msg.data
        pass
    def key_cb(self,msg):
        if msg.data == 's':
            image = 'left{0}.png'.format(self.counter)
            name = 'output{0}'.format(self.counter) + '.txt'
            os.chdir(directory)
            cv.imwrite(image,self.cv_image)
            with open(name) as f:
                f.write(self.dist , self.angles)
            rospy.loginfo('saved!')




if __name__=='__main__':
    rospy.init_node('merger')
    M = Merger()   
        
    rospy.spin()


