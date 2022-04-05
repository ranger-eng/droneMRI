#!/usr/bin/env python
import rospy
from my_robot_messages.msg import LeftSide
#from distance_sensor.msg import Float32stamped
from geometry_msgs.msg import Vector3Stamped , Vector3
import numpy as np


class Turret:

    def __init__(self):
       # rospy.Subscriber("LeftSide_Pub", LeftSide, self.callback)
        self.pub_msg = rospy.Publisher('Translation Vector', Vector3Stamped, queue_size=10)
        
        
    def callback(self,msg):
        pass
       # rospy.loginfo(rospy.get_caller_id() + "\tI heard %s", msg.header.stamp)
        
    

        # In ROS, nodes are uniquely named. If two nodes with the same
        # name are launched, the previous one is kicked off. The
        # anonymous=True flag means that rospy will choose a unique
        # name for our 'listener' node so that multiple listeners can
        # run simultaneously.
        

        

        # spin() simply keeps python from exiting until this node is stopped
        
if __name__ == '__main__':
    rospy.init_node('calibrate_main', anonymous=True)
    Turret()
    rospy.spin()
