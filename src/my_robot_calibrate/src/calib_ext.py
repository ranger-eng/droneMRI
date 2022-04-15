#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import Imu
from geometry_msgs.msg import Quaternion
import numpy as np
from distance_sensor.msg import Float32Stamped

class Extrinsic_Calibrator:

    def __init__(self):
        self.distance_sub = rospy.Subscriber()
        self.Left_sub = rospy.Subscriber()
        self.Right_sub = rospy.Subscriber()
        self.

    def S(angle):
        SIN = np.sin(angle)
        return SIN

    def DH(d,theta,r,alpha):

        T = np.array([[np.cos(theta), np.sin][][][]])