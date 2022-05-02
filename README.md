# droneMRI
Please add the pylon-ros-camera driver before building this project.  
Follow instructions here: https://github.com/basler/pylon-ros-camera  
    note: both pylon-ros-camera, and dragandbot_commond  
    https://github.com/dragandbot/dragandbot_common  

The distance sensor node is dependant on pyserial. Install using   
pip3 install pyserial  

The services for this project are written in Rust. Please follow the steps below to install Rust on the machine:   
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
rustup update

ros noetic needs to be installed on your machine  
http://wiki.ros.org/noetic/Installation  

to build the project:  
>git clone git@github.com:ranger-eng/droneMRI.git  
>cd ./droneMRI  
>source /opt/ros/noetic/setup.zsh  
>catkin_make  

catkin_make may need to executed multiple times for the build to succeed. 
