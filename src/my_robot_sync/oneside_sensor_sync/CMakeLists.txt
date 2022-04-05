cmake_minimum_required(VERSION 3.0.2)
project(my_robot_sync)

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

add_executable(left_side_sync_node src/left_side_sync.cpp)
add_executable(right_side_sync_node src/right_side_sync.cpp)

target_link_libraries(left_side_sync_node
   ${catkin_LIBRARIES}
)

target_link_libraries(right_side_sync_node
   ${catkin_LIBRARIES}
)

#############
## Install ##
#############

#############
## Testing ##
#############

