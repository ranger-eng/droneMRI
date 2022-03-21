#!/usr/bin/env python3

from pynput import keyboard
from std_msgs.msg import String
import rospy

class Key:
    def __init__(self):
        self.pub_key = rospy.Publisher('/keyboard_event',String, queue_size=10)
    
    def on_press(self,k):
        self.pub_key.publish(k)
        rospy.loginfo('sending {}'.format(k))

    


if __name__=='__main__':
    rospy.init_node('keyboard_control')
    key = Key()
    listener = keyboard.Listener(on_press=key.on_press)
    listener.start()

    rospy.spin()
