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
CMAKE_SOURCE_DIR = /home/ayle/code/git/soccer/sobeautifulyouare/all-build/Communication

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ayle/code/git/soccer/sobeautifulyouare/all-build/Communication

# Include any dependencies generated for this target.
include CMakeFiles/communication.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/communication.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/communication.dir/flags.make

CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.o: CMakeFiles/communication.dir/flags.make
CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.o: /home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ayle/code/git/soccer/sobeautifulyouare/all-build/Communication/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.o -c /home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp

CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp > CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.i

CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp -o CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.s

CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.o.requires:

.PHONY : CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.o.requires

CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.o.provides: CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.o.requires
	$(MAKE) -f CMakeFiles/communication.dir/build.make CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.o.provides.build
.PHONY : CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.o.provides

CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.o.provides.build: CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.o


# Object files for target communication
communication_OBJECTS = \
"CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.o"

# External object files for target communication
communication_EXTERNAL_OBJECTS =

/home/ayle/code/git/soccer/sobeautifulyouare/bin/libcommunication.so: CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.o
/home/ayle/code/git/soccer/sobeautifulyouare/bin/libcommunication.so: CMakeFiles/communication.dir/build.make
/home/ayle/code/git/soccer/sobeautifulyouare/bin/libcommunication.so: CMakeFiles/communication.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ayle/code/git/soccer/sobeautifulyouare/all-build/Communication/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library /home/ayle/code/git/soccer/sobeautifulyouare/bin/libcommunication.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/communication.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/communication.dir/build: /home/ayle/code/git/soccer/sobeautifulyouare/bin/libcommunication.so

.PHONY : CMakeFiles/communication.dir/build

CMakeFiles/communication.dir/requires: CMakeFiles/communication.dir/home/ayle/code/git/soccer/sobeautifulyouare/source/module/communication/communication.cpp.o.requires

.PHONY : CMakeFiles/communication.dir/requires

CMakeFiles/communication.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/communication.dir/cmake_clean.cmake
.PHONY : CMakeFiles/communication.dir/clean

CMakeFiles/communication.dir/depend:
	cd /home/ayle/code/git/soccer/sobeautifulyouare/all-build/Communication && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ayle/code/git/soccer/sobeautifulyouare/all-build/Communication /home/ayle/code/git/soccer/sobeautifulyouare/all-build/Communication /home/ayle/code/git/soccer/sobeautifulyouare/all-build/Communication /home/ayle/code/git/soccer/sobeautifulyouare/all-build/Communication /home/ayle/code/git/soccer/sobeautifulyouare/all-build/Communication/CMakeFiles/communication.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/communication.dir/depend

