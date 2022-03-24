#!/usr/bin/env python
import rospy
from my_robot_messages.msg import LeftSide

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + "\tI heard %s", data.header.stamp)
    
def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('calibrate_main', anonymous=True)

    rospy.Subscriber("LeftSide_Pub", LeftSide, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()
