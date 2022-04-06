#!/usr/bin/env python3
import rospy
from cv_bridge import CvBridge
import cv2
from sensor_msgs.msg import Image
#from distance_sensor.msg import Float32stamped
#from geometry_msgs.msg import Vector3Stamped , Vector3
import numpy as np


class ImageSaver:

    def __init__(self):
        self.bridge = CvBridge()
        imgL = rospy.wait_for_message("/my_robot_driver/CAM_L/image_raw", Image)# self.callbackL)
        imgR = rospy.wait_for_message("/my_robot_driver/CAM_R/image_raw", Image)#, self.callbackR)
        
        
   # def callbackL(self,msg):
        cv_imgL = self.bridge.imgmsg_to_cv2(imgL,"bayer_rggb8")
        timeL = imgL.header.stamp.secs
        nameL = '/home/acer/bagfiles/Left_'+str(timeL)+'.png'
        grayL = cv2.cvtColor(cv_imgL, cv2.COLOR_BayerBG2GRAY)
        cv2.imwrite(nameL,grayL)
        rospy.loginfo('Successfully saved Left Image')


    #def callbackR(self,msg):
        cv_imgR = self.bridge.imgmsg_to_cv2(imgR,"bayer_rggb8")
        timeR = imgR.header.stamp.secs
        nameR = '/home/acer/bagfiles/Right_'+str(timeR)+'.png'
        grayR = cv2.cvtColor(cv_imgR, cv2.COLOR_BayerBG2GRAY)
        cv2.imwrite(nameR,grayR)
        rospy.loginfo('Successfully saved Right Image')
    
       # rospy.loginfo(rospy.get_caller_id() + "\tI heard %s", msg.header.stamp)
        
    

        # In ROS, nodes are uniquely named. If two nodes with the same
        # name are launched, the previous one is kicked off. The
        # anonymous=True flag means that rospy will choose a unique
        # name for our 'listener' node so that multiple listeners can
        # run simultaneously.
        

        

        # spin() simply keeps python from exiting until this node is stopped
        
if __name__ == '__main__':
    rospy.init_node('Image_Saver', anonymous=True)
    ImageSaver()
   # rospy.spin()
