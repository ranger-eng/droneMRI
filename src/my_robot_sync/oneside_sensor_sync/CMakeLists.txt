cmake_minimum_required(VERSION 3.0.2)
project(oneside_sensor_sync)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  message_filters
)

################################################
## Declare ROS messages, services and actions ##
################################################


###################################
## catkin specific configuration ##
###################################

catkin_package(
    DEPENDS
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  # includes custom messages from message generator
  ${CMAKE_BINARY_DIR}/../devel/include/
)

add_executable(${PROJECT_NAME}_node src/oneside_sensor_sync.cpp)

target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
)

#############
## Install ##
#############

#############
## Testing ##
#############

