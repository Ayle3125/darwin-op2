# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ayle/sobeautifulyouare/all-build/Strategy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ayle/sobeautifulyouare/all-build/Strategy

# Include any dependencies generated for this target.
include CMakeFiles/strategy_robcup_penalty.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/strategy_robcup_penalty.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/strategy_robcup_penalty.dir/flags.make

CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.o: CMakeFiles/strategy_robcup_penalty.dir/flags.make
CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.o: /home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ayle/sobeautifulyouare/all-build/Strategy/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.o -c /home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp

CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp > CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.i

CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp -o CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.s

CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.o.requires:

.PHONY : CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.o.requires

CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.o.provides: CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.o.requires
	$(MAKE) -f CMakeFiles/strategy_robcup_penalty.dir/build.make CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.o.provides.build
.PHONY : CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.o.provides

CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.o.provides.build: CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.o


# Object files for target strategy_robcup_penalty
strategy_robcup_penalty_OBJECTS = \
"CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.o"

# External object files for target strategy_robcup_penalty
strategy_robcup_penalty_EXTERNAL_OBJECTS =

/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.o
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: CMakeFiles/strategy_robcup_penalty.dir/build.make
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_ts.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /home/ayle/sobeautifulyouare/bin/libvision_blob.so
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /home/ayle/sobeautifulyouare/bin/libvision_blob.so
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /home/ayle/sobeautifulyouare/bin/libvision_camera.so
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /home/ayle/sobeautifulyouare/bin/libvision_imgproc.so
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /home/ayle/sobeautifulyouare/bin/libmotion.so
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /home/ayle/sobeautifulyouare/bin/libcommunication.so
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /home/ayle/sobeautifulyouare/bin/libdarwin_framework.so
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /home/ayle/sobeautifulyouare/bin/libdarwin_linux.so
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.9
/home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so: CMakeFiles/strategy_robcup_penalty.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ayle/sobeautifulyouare/all-build/Strategy/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library /home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/strategy_robcup_penalty.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/strategy_robcup_penalty.dir/build: /home/ayle/sobeautifulyouare/bin/libstrategy_robcup_penalty.so

.PHONY : CMakeFiles/strategy_robcup_penalty.dir/build

CMakeFiles/strategy_robcup_penalty.dir/requires: CMakeFiles/strategy_robcup_penalty.dir/home/ayle/sobeautifulyouare/source/module/strategy/robcup_penalty/robcup_penalty.cpp.o.requires

.PHONY : CMakeFiles/strategy_robcup_penalty.dir/requires

CMakeFiles/strategy_robcup_penalty.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/strategy_robcup_penalty.dir/cmake_clean.cmake
.PHONY : CMakeFiles/strategy_robcup_penalty.dir/clean

CMakeFiles/strategy_robcup_penalty.dir/depend:
	cd /home/ayle/sobeautifulyouare/all-build/Strategy && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ayle/sobeautifulyouare/all-build/Strategy /home/ayle/sobeautifulyouare/all-build/Strategy /home/ayle/sobeautifulyouare/all-build/Strategy /home/ayle/sobeautifulyouare/all-build/Strategy /home/ayle/sobeautifulyouare/all-build/Strategy/CMakeFiles/strategy_robcup_penalty.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/strategy_robcup_penalty.dir/depend

