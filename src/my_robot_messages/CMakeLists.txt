cmake_minimum_required(VERSION 3.0.2)
project(my_robot_messages)

find_package(catkin REQUIRED COMPONENTS
    std_msgs
    sensor_msgs
    message_generation
)

################################################
## Declare ROS messages, services and actions ##
################################################

add_message_files(
    FILES
    Float32Stamped.msg
    LeftSide.msg
    RightSide.msg
)

generate_messages(
    DEPENDENCIES
    sensor_msgs
    std_msgs
)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################


###################################
## catkin specific configuration ##
###################################

catkin_package(
    DEPENDS message_runtime
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
    ${catkin_INCLUDE_DIRS}
)

#############
## Install ##
#############

#############
## Testing ##
#############
