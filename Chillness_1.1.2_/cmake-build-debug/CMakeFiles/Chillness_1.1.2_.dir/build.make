# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /snap/clion/139/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/139/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/egor/Repositories/Chillness/Chillness_1.1.2_

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/egor/Repositories/Chillness/Chillness_1.1.2_/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Chillness_1.1.2_.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Chillness_1.1.2_.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Chillness_1.1.2_.dir/flags.make

CMakeFiles/Chillness_1.1.2_.dir/main.cpp.o: CMakeFiles/Chillness_1.1.2_.dir/flags.make
CMakeFiles/Chillness_1.1.2_.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/Repositories/Chillness/Chillness_1.1.2_/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Chillness_1.1.2_.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Chillness_1.1.2_.dir/main.cpp.o -c /home/egor/Repositories/Chillness/Chillness_1.1.2_/main.cpp

CMakeFiles/Chillness_1.1.2_.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chillness_1.1.2_.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/egor/Repositories/Chillness/Chillness_1.1.2_/main.cpp > CMakeFiles/Chillness_1.1.2_.dir/main.cpp.i

CMakeFiles/Chillness_1.1.2_.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chillness_1.1.2_.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/egor/Repositories/Chillness/Chillness_1.1.2_/main.cpp -o CMakeFiles/Chillness_1.1.2_.dir/main.cpp.s

# Object files for target Chillness_1.1.2_
Chillness_1_1_2__OBJECTS = \
"CMakeFiles/Chillness_1.1.2_.dir/main.cpp.o"

# External object files for target Chillness_1.1.2_
Chillness_1_1_2__EXTERNAL_OBJECTS =

Chillness_1.1.2_: CMakeFiles/Chillness_1.1.2_.dir/main.cpp.o
Chillness_1.1.2_: CMakeFiles/Chillness_1.1.2_.dir/build.make
Chillness_1.1.2_: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
Chillness_1.1.2_: /usr/lib/x86_64-linux-gnu/libsfml-audio.so.2.5.1
Chillness_1.1.2_: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
Chillness_1.1.2_: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
Chillness_1.1.2_: CMakeFiles/Chillness_1.1.2_.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/egor/Repositories/Chillness/Chillness_1.1.2_/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Chillness_1.1.2_"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Chillness_1.1.2_.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Chillness_1.1.2_.dir/build: Chillness_1.1.2_

.PHONY : CMakeFiles/Chillness_1.1.2_.dir/build

CMakeFiles/Chillness_1.1.2_.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Chillness_1.1.2_.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Chillness_1.1.2_.dir/clean

CMakeFiles/Chillness_1.1.2_.dir/depend:
	cd /home/egor/Repositories/Chillness/Chillness_1.1.2_/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/egor/Repositories/Chillness/Chillness_1.1.2_ /home/egor/Repositories/Chillness/Chillness_1.1.2_ /home/egor/Repositories/Chillness/Chillness_1.1.2_/cmake-build-debug /home/egor/Repositories/Chillness/Chillness_1.1.2_/cmake-build-debug /home/egor/Repositories/Chillness/Chillness_1.1.2_/cmake-build-debug/CMakeFiles/Chillness_1.1.2_.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Chillness_1.1.2_.dir/depend

