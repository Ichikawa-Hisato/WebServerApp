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
CMAKE_SOURCE_DIR = /home/user/project/WebServerApp/develop/src/sample/http_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/project/WebServerApp/develop/src/sample/http_server/build

# Include any dependencies generated for this target.
include CMakeFiles/sampleApp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sampleApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sampleApp.dir/flags.make

CMakeFiles/sampleApp.dir/sampleApp.cpp.o: CMakeFiles/sampleApp.dir/flags.make
CMakeFiles/sampleApp.dir/sampleApp.cpp.o: ../sampleApp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/project/WebServerApp/develop/src/sample/http_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sampleApp.dir/sampleApp.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sampleApp.dir/sampleApp.cpp.o -c /home/user/project/WebServerApp/develop/src/sample/http_server/sampleApp.cpp

CMakeFiles/sampleApp.dir/sampleApp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sampleApp.dir/sampleApp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/project/WebServerApp/develop/src/sample/http_server/sampleApp.cpp > CMakeFiles/sampleApp.dir/sampleApp.cpp.i

CMakeFiles/sampleApp.dir/sampleApp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sampleApp.dir/sampleApp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/project/WebServerApp/develop/src/sample/http_server/sampleApp.cpp -o CMakeFiles/sampleApp.dir/sampleApp.cpp.s

# Object files for target sampleApp
sampleApp_OBJECTS = \
"CMakeFiles/sampleApp.dir/sampleApp.cpp.o"

# External object files for target sampleApp
sampleApp_EXTERNAL_OBJECTS =

sampleApp: CMakeFiles/sampleApp.dir/sampleApp.cpp.o
sampleApp: CMakeFiles/sampleApp.dir/build.make
sampleApp: CMakeFiles/sampleApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/project/WebServerApp/develop/src/sample/http_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sampleApp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sampleApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sampleApp.dir/build: sampleApp

.PHONY : CMakeFiles/sampleApp.dir/build

CMakeFiles/sampleApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sampleApp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sampleApp.dir/clean

CMakeFiles/sampleApp.dir/depend:
	cd /home/user/project/WebServerApp/develop/src/sample/http_server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/project/WebServerApp/develop/src/sample/http_server /home/user/project/WebServerApp/develop/src/sample/http_server /home/user/project/WebServerApp/develop/src/sample/http_server/build /home/user/project/WebServerApp/develop/src/sample/http_server/build /home/user/project/WebServerApp/develop/src/sample/http_server/build/CMakeFiles/sampleApp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sampleApp.dir/depend

