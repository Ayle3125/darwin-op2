# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/abraham/abraham/soccer/sobeautifulyouare/all-build/Strategy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/abraham/abraham/soccer/sobeautifulyouare/all-build/Strategy

# Include any dependencies generated for this target.
include CMakeFiles/strategy_marathon.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/strategy_marathon.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/strategy_marathon.dir/flags.make

CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.o: CMakeFiles/strategy_marathon.dir/flags.make
CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.o: /home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/abraham/abraham/soccer/sobeautifulyouare/all-build/Strategy/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.o -c /home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp

CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp > CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.i

CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp -o CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.s

CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.o.requires:
.PHONY : CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.o.requires

CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.o.provides: CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.o.requires
	$(MAKE) -f CMakeFiles/strategy_marathon.dir/build.make CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.o.provides.build
.PHONY : CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.o.provides

CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.o.provides.build: CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.o

# Object files for target strategy_marathon
strategy_marathon_OBJECTS = \
"CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.o"

# External object files for target strategy_marathon
strategy_marathon_EXTERNAL_OBJECTS =

/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.o
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: CMakeFiles/strategy_marathon.dir/build.make
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_calib3d.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_contrib.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_core.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_features2d.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_flann.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_gpu.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_highgui.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_imgproc.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_legacy.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_ml.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_nonfree.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_objdetect.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_photo.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_stitching.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_ts.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_video.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /usr/local/opencv/release/lib/libopencv_videostab.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /home/abraham/abraham/soccer/sobeautifulyouare/bin/libvision_blob.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /home/abraham/abraham/soccer/sobeautifulyouare/bin/libvision_blob.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /home/abraham/abraham/soccer/sobeautifulyouare/bin/libvision_camera.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /home/abraham/abraham/soccer/sobeautifulyouare/bin/libvision_imgproc.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /home/abraham/abraham/soccer/sobeautifulyouare/bin/libmotion.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /home/abraham/abraham/soccer/sobeautifulyouare/bin/libcommunication.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /home/abraham/abraham/soccer/sobeautifulyouare/bin/libdarwin_framework.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: /home/abraham/abraham/soccer/sobeautifulyouare/bin/libdarwin_linux.so
/home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so: CMakeFiles/strategy_marathon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library /home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/strategy_marathon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/strategy_marathon.dir/build: /home/abraham/abraham/soccer/sobeautifulyouare/bin/libstrategy_marathon.so
.PHONY : CMakeFiles/strategy_marathon.dir/build

CMakeFiles/strategy_marathon.dir/requires: CMakeFiles/strategy_marathon.dir/home/abraham/abraham/soccer/sobeautifulyouare/source/module/strategy/marathon/marathon.cpp.o.requires
.PHONY : CMakeFiles/strategy_marathon.dir/requires

CMakeFiles/strategy_marathon.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/strategy_marathon.dir/cmake_clean.cmake
.PHONY : CMakeFiles/strategy_marathon.dir/clean

CMakeFiles/strategy_marathon.dir/depend:
	cd /home/abraham/abraham/soccer/sobeautifulyouare/all-build/Strategy && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/abraham/abraham/soccer/sobeautifulyouare/all-build/Strategy /home/abraham/abraham/soccer/sobeautifulyouare/all-build/Strategy /home/abraham/abraham/soccer/sobeautifulyouare/all-build/Strategy /home/abraham/abraham/soccer/sobeautifulyouare/all-build/Strategy /home/abraham/abraham/soccer/sobeautifulyouare/all-build/Strategy/CMakeFiles/strategy_marathon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/strategy_marathon.dir/depend

