# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspaces/cs225/cs225git/lab_heaps

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/cs225/cs225git/lab_heaps/build

# Include any dependencies generated for this target.
include CMakeFiles/heaps.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/heaps.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/heaps.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/heaps.dir/flags.make

CMakeFiles/heaps.dir/entry/heaps.cpp.o: CMakeFiles/heaps.dir/flags.make
CMakeFiles/heaps.dir/entry/heaps.cpp.o: ../entry/heaps.cpp
CMakeFiles/heaps.dir/entry/heaps.cpp.o: CMakeFiles/heaps.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/cs225/cs225git/lab_heaps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/heaps.dir/entry/heaps.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/heaps.dir/entry/heaps.cpp.o -MF CMakeFiles/heaps.dir/entry/heaps.cpp.o.d -o CMakeFiles/heaps.dir/entry/heaps.cpp.o -c /workspaces/cs225/cs225git/lab_heaps/entry/heaps.cpp

CMakeFiles/heaps.dir/entry/heaps.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/heaps.dir/entry/heaps.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/cs225/cs225git/lab_heaps/entry/heaps.cpp > CMakeFiles/heaps.dir/entry/heaps.cpp.i

CMakeFiles/heaps.dir/entry/heaps.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/heaps.dir/entry/heaps.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/cs225/cs225git/lab_heaps/entry/heaps.cpp -o CMakeFiles/heaps.dir/entry/heaps.cpp.s

# Object files for target heaps
heaps_OBJECTS = \
"CMakeFiles/heaps.dir/entry/heaps.cpp.o"

# External object files for target heaps
heaps_EXTERNAL_OBJECTS =

heaps: CMakeFiles/heaps.dir/entry/heaps.cpp.o
heaps: CMakeFiles/heaps.dir/build.make
heaps: src/libsrc.a
heaps: lib/libcs225.a
heaps: lib/liblodepng.a
heaps: CMakeFiles/heaps.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/cs225/cs225git/lab_heaps/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable heaps"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/heaps.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/heaps.dir/build: heaps
.PHONY : CMakeFiles/heaps.dir/build

CMakeFiles/heaps.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/heaps.dir/cmake_clean.cmake
.PHONY : CMakeFiles/heaps.dir/clean

CMakeFiles/heaps.dir/depend:
	cd /workspaces/cs225/cs225git/lab_heaps/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/cs225/cs225git/lab_heaps /workspaces/cs225/cs225git/lab_heaps /workspaces/cs225/cs225git/lab_heaps/build /workspaces/cs225/cs225git/lab_heaps/build /workspaces/cs225/cs225git/lab_heaps/build/CMakeFiles/heaps.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/heaps.dir/depend

