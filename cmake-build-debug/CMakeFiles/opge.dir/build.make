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
CMAKE_SOURCE_DIR = /home/alex/CLionProjects/opge

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/CLionProjects/opge/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/opge.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/opge.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/opge.dir/flags.make

CMakeFiles/opge.dir/main.cpp.o: CMakeFiles/opge.dir/flags.make
CMakeFiles/opge.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/CLionProjects/opge/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/opge.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opge.dir/main.cpp.o -c /home/alex/CLionProjects/opge/main.cpp

CMakeFiles/opge.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opge.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/CLionProjects/opge/main.cpp > CMakeFiles/opge.dir/main.cpp.i

CMakeFiles/opge.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opge.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/CLionProjects/opge/main.cpp -o CMakeFiles/opge.dir/main.cpp.s

# Object files for target opge
opge_OBJECTS = \
"CMakeFiles/opge.dir/main.cpp.o"

# External object files for target opge
opge_EXTERNAL_OBJECTS =

opge: CMakeFiles/opge.dir/main.cpp.o
opge: CMakeFiles/opge.dir/build.make
opge: CMakeFiles/opge.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/CLionProjects/opge/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable opge"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/opge.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/opge.dir/build: opge

.PHONY : CMakeFiles/opge.dir/build

CMakeFiles/opge.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/opge.dir/cmake_clean.cmake
.PHONY : CMakeFiles/opge.dir/clean

CMakeFiles/opge.dir/depend:
	cd /home/alex/CLionProjects/opge/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/CLionProjects/opge /home/alex/CLionProjects/opge /home/alex/CLionProjects/opge/cmake-build-debug /home/alex/CLionProjects/opge/cmake-build-debug /home/alex/CLionProjects/opge/cmake-build-debug/CMakeFiles/opge.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/opge.dir/depend

