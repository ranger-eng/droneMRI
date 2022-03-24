cmake_minimum_required(VERSION 3.0.2)
project(my_robot_calibrate)

find_package(catkin REQUIRED COMPONENTS
  sensor_msgs
  std_msgs
  rospy
)

################################################
## Declare ROS messages, services and actions ##
################################################

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

###################################
## catkin specific configuration ##
###################################
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES my_robot_calibrate
#  CATKIN_DEPENDS dependencies roscpp rospy
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${CMAKE_BINARY_DIR}/../devel/include/
)

#############
## Install ##
#############
catkin_install_python(PROGRAMS src/calibrate_main.py
    DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

#############
## Testing ##
#############
