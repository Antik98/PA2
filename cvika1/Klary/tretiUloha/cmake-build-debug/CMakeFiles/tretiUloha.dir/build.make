# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/David/Documents/PA2/cvika1/tretiUloha

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/David/Documents/PA2/cvika1/tretiUloha/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/tretiUloha.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tretiUloha.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tretiUloha.dir/flags.make

CMakeFiles/tretiUloha.dir/main.cpp.o: CMakeFiles/tretiUloha.dir/flags.make
CMakeFiles/tretiUloha.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/David/Documents/PA2/cvika1/tretiUloha/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tretiUloha.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tretiUloha.dir/main.cpp.o -c /Users/David/Documents/PA2/cvika1/tretiUloha/main.cpp

CMakeFiles/tretiUloha.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tretiUloha.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/David/Documents/PA2/cvika1/tretiUloha/main.cpp > CMakeFiles/tretiUloha.dir/main.cpp.i

CMakeFiles/tretiUloha.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tretiUloha.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/David/Documents/PA2/cvika1/tretiUloha/main.cpp -o CMakeFiles/tretiUloha.dir/main.cpp.s

# Object files for target tretiUloha
tretiUloha_OBJECTS = \
"CMakeFiles/tretiUloha.dir/main.cpp.o"

# External object files for target tretiUloha
tretiUloha_EXTERNAL_OBJECTS =

tretiUloha: CMakeFiles/tretiUloha.dir/main.cpp.o
tretiUloha: CMakeFiles/tretiUloha.dir/build.make
tretiUloha: CMakeFiles/tretiUloha.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/David/Documents/PA2/cvika1/tretiUloha/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tretiUloha"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tretiUloha.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tretiUloha.dir/build: tretiUloha

.PHONY : CMakeFiles/tretiUloha.dir/build

CMakeFiles/tretiUloha.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tretiUloha.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tretiUloha.dir/clean

CMakeFiles/tretiUloha.dir/depend:
	cd /Users/David/Documents/PA2/cvika1/tretiUloha/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/David/Documents/PA2/cvika1/tretiUloha /Users/David/Documents/PA2/cvika1/tretiUloha /Users/David/Documents/PA2/cvika1/tretiUloha/cmake-build-debug /Users/David/Documents/PA2/cvika1/tretiUloha/cmake-build-debug /Users/David/Documents/PA2/cvika1/tretiUloha/cmake-build-debug/CMakeFiles/tretiUloha.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tretiUloha.dir/depend

