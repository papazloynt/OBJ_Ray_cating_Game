# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/151/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/151/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/chastikov/techno_park/AIAP/Ray cast"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/chastikov/techno_park/AIAP/Ray cast/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/images.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/images.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/images.dir/flags.make

CMakeFiles/images.dir/src/gui.cpp.o: CMakeFiles/images.dir/flags.make
CMakeFiles/images.dir/src/gui.cpp.o: ../src/gui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/chastikov/techno_park/AIAP/Ray cast/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/images.dir/src/gui.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/images.dir/src/gui.cpp.o -c "/home/chastikov/techno_park/AIAP/Ray cast/src/gui.cpp"

CMakeFiles/images.dir/src/gui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/images.dir/src/gui.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/chastikov/techno_park/AIAP/Ray cast/src/gui.cpp" > CMakeFiles/images.dir/src/gui.cpp.i

CMakeFiles/images.dir/src/gui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/images.dir/src/gui.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/chastikov/techno_park/AIAP/Ray cast/src/gui.cpp" -o CMakeFiles/images.dir/src/gui.cpp.s

# Object files for target images
images_OBJECTS = \
"CMakeFiles/images.dir/src/gui.cpp.o"

# External object files for target images
images_EXTERNAL_OBJECTS =

images: CMakeFiles/images.dir/src/gui.cpp.o
images: CMakeFiles/images.dir/build.make
images: libray_cast.a
images: CMakeFiles/images.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/chastikov/techno_park/AIAP/Ray cast/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable images"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/images.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/images.dir/build: images

.PHONY : CMakeFiles/images.dir/build

CMakeFiles/images.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/images.dir/cmake_clean.cmake
.PHONY : CMakeFiles/images.dir/clean

CMakeFiles/images.dir/depend:
	cd "/home/chastikov/techno_park/AIAP/Ray cast/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/chastikov/techno_park/AIAP/Ray cast" "/home/chastikov/techno_park/AIAP/Ray cast" "/home/chastikov/techno_park/AIAP/Ray cast/cmake-build-debug" "/home/chastikov/techno_park/AIAP/Ray cast/cmake-build-debug" "/home/chastikov/techno_park/AIAP/Ray cast/cmake-build-debug/CMakeFiles/images.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/images.dir/depend

