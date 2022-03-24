cmake_minimum_required(VERSION 3.0)
project(my_robot_services)

find_package(catkin REQUIRED)
#find_package(catkin REQUIRED COMPONENTS                                                                                                                                  
#   roscpp                                                                                                                                                                 
#   rospy                                                                                                                                                                  
#   std_msgs                                                                                                                                                               
#   geometry_msgs
#   genmsg                                                                                                                                                                 
#   realtime_tools                                                                                                                                                         
#)
#
#add_service_files(
#    FILES
#    AddTwoInts.srv
#)
#
#generate_messages(
#   DEPENDENCIES
#   geometry_msgs
#   std_msgs
#)

catkin_package()

add_custom_target(my_robot_services
   ALL
   COMMAND cargo build --release -p my_robot_services --target-dir ${CMAKE_BINARY_DIR}/cargo
   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/cargo/release/my_robot_services ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/my_robot_services
   COMMENT "Building rosrust_package!!!"
)
