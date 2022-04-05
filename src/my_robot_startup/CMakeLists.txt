cmake_minimum_required(VERSION 3.0.2)
project(my_robot_startup)

################################################
## Declare ROS messages, services and actions ##
################################################

###################################
## catkin specific configuration ##
###################################

catkin_package()

###########
## Build ##
###########

#############
## Install ##
#############
catkin_install_python(PROGRAMS 
    test/my_robot_sync_rightside_unittest.py
    DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
    test/my_robot_sync_leftside_unittest.py
    DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

#############
## Testing ##
#############

