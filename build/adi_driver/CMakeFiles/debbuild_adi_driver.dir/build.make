# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pibot/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pibot/catkin_ws/build

# Utility rule file for debbuild_adi_driver.

# Include the progress variables for this target.
include adi_driver/CMakeFiles/debbuild_adi_driver.dir/progress.make

adi_driver/CMakeFiles/debbuild_adi_driver:
	cd /home/pibot/catkin_ws/src/adi_driver && bloom-generate rosdebian --os-name ubuntu --os-version xenial --ros-distro kinetic
	cd /home/pibot/catkin_ws/src/adi_driver && fakeroot debian/rules binary
	cd /home/pibot/catkin_ws/src/adi_driver && find debian obj-x86_64-linux-gnu -type f -not -name postinst -print0 | xargs -0 rm --
	cd /home/pibot/catkin_ws/src/adi_driver && find debian obj-x86_64-linux-gnu -type d -empty -delete

debbuild_adi_driver: adi_driver/CMakeFiles/debbuild_adi_driver
debbuild_adi_driver: adi_driver/CMakeFiles/debbuild_adi_driver.dir/build.make

.PHONY : debbuild_adi_driver

# Rule to build all files generated by this target.
adi_driver/CMakeFiles/debbuild_adi_driver.dir/build: debbuild_adi_driver

.PHONY : adi_driver/CMakeFiles/debbuild_adi_driver.dir/build

adi_driver/CMakeFiles/debbuild_adi_driver.dir/clean:
	cd /home/pibot/catkin_ws/build/adi_driver && $(CMAKE_COMMAND) -P CMakeFiles/debbuild_adi_driver.dir/cmake_clean.cmake
.PHONY : adi_driver/CMakeFiles/debbuild_adi_driver.dir/clean

adi_driver/CMakeFiles/debbuild_adi_driver.dir/depend:
	cd /home/pibot/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pibot/catkin_ws/src /home/pibot/catkin_ws/src/adi_driver /home/pibot/catkin_ws/build /home/pibot/catkin_ws/build/adi_driver /home/pibot/catkin_ws/build/adi_driver/CMakeFiles/debbuild_adi_driver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : adi_driver/CMakeFiles/debbuild_adi_driver.dir/depend

