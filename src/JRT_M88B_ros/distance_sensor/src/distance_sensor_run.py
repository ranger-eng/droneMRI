#!/usr/bin/env python3
import rospy
from distance_sensor.msg import Float32Stamped
from sensor_serial import DistanceSensor
import os
import time

class DistanceNode:
    def __init__(self):
        self.pub = rospy.Publisher(OUT_TOPIC, Float32Stamped, queue_size=10)
        self.assert_port()  # make sure port is assigned
        self.sensor = DistanceSensor(port=rospy.get_param(PARAM_PORT))
        rospy.on_shutdown(self.sensor.clean)
        self.print_sensor_info()
        

    def assert_port(self):
        rate = rospy.Rate(.5)  # 2 hz
        while not rospy.has_param(PARAM_PORT):
            rospy.logwarn("Please assign a value to the port parameter")
            rate.sleep()

    def print_sensor_info(self):
        info = self.sensor.get_info()
        for key, val in info.items():
            line = "{}\t:\t{}".format(key, val)
            rospy.logwarn(line)

    def stream_distance(self):
        loop_rate = rospy.Rate(10)
        while True:
            tic = time.perf_counter_ns()/1000000000
            """loop_rate.sleep()"""
            msg = Float32Stamped()
            msg.data = self.sensor.read_once()
            msg.header.stamp = rospy.Time.now()
            self.pub.publish(msg)
            toc = time.perf_counter_ns()/1000000000
            dt = toc - tic
            Fs = 1/dt
            print("dt: ", dt, ", Fs: ", Fs)


if __name__ == '__main__':
    NODE_NAME = "distance_node"
    rospy.init_node(NODE_NAME)

    IN_TOPIC = "in_topic"
    OUT_TOPIC = "out_topic"

    PARAM_PORT = os.path.join(rospy.get_name(), "PORT")

    distance_node = DistanceNode()
    distance_node.stream_distance()
    rospy.spin()
