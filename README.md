# droneMRI
Please add the pylon-ros-camera driver before building this project.  
Follow instructions here: https://github.com/basler/pylon-ros-camera  
    note: both pylon-ros-camera, and dragandbot_commond  
    https://github.com/dragandbot/dragandbot_common  

ros noetic needs to be installed on your machine  
http://wiki.ros.org/noetic/Installation  

to build the project:  
>git clone git@github.com:ranger-eng/droneMRI.git  
>cd ./droneMRI  
>source /opt/ros/noetic/setup.zsh  
>catkin_make  

catkin_make may need to executed multiple times for the build to succeed. 
