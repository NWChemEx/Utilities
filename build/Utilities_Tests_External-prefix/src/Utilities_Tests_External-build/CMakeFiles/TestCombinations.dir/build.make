# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.9.3_1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.9.3_1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/Working/Utilities/Utilities_Test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/Working/Utilities/build/Utilities_Tests_External-prefix/src/Utilities_Tests_External-build

# Include any dependencies generated for this target.
include CMakeFiles/TestCombinations.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TestCombinations.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TestCombinations.dir/flags.make

CMakeFiles/TestCombinations.dir/TestCombinations.cpp.o: CMakeFiles/TestCombinations.dir/flags.make
CMakeFiles/TestCombinations.dir/TestCombinations.cpp.o: /Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/Working/Utilities/Utilities_Test/TestCombinations.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/Working/Utilities/build/Utilities_Tests_External-prefix/src/Utilities_Tests_External-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TestCombinations.dir/TestCombinations.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TestCombinations.dir/TestCombinations.cpp.o -c /Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/Working/Utilities/Utilities_Test/TestCombinations.cpp

CMakeFiles/TestCombinations.dir/TestCombinations.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestCombinations.dir/TestCombinations.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/Working/Utilities/Utilities_Test/TestCombinations.cpp > CMakeFiles/TestCombinations.dir/TestCombinations.cpp.i

CMakeFiles/TestCombinations.dir/TestCombinations.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestCombinations.dir/TestCombinations.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/Working/Utilities/Utilities_Test/TestCombinations.cpp -o CMakeFiles/TestCombinations.dir/TestCombinations.cpp.s

CMakeFiles/TestCombinations.dir/TestCombinations.cpp.o.requires:

.PHONY : CMakeFiles/TestCombinations.dir/TestCombinations.cpp.o.requires

CMakeFiles/TestCombinations.dir/TestCombinations.cpp.o.provides: CMakeFiles/TestCombinations.dir/TestCombinations.cpp.o.requires
	$(MAKE) -f CMakeFiles/TestCombinations.dir/build.make CMakeFiles/TestCombinations.dir/TestCombinations.cpp.o.provides.build
.PHONY : CMakeFiles/TestCombinations.dir/TestCombinations.cpp.o.provides

CMakeFiles/TestCombinations.dir/TestCombinations.cpp.o.provides.build: CMakeFiles/TestCombinations.dir/TestCombinations.cpp.o


# Object files for target TestCombinations
TestCombinations_OBJECTS = \
"CMakeFiles/TestCombinations.dir/TestCombinations.cpp.o"

# External object files for target TestCombinations
TestCombinations_EXTERNAL_OBJECTS =

TestCombinations: CMakeFiles/TestCombinations.dir/TestCombinations.cpp.o
TestCombinations: CMakeFiles/TestCombinations.dir/build.make
TestCombinations: /Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/NWChemEx/lib/libcatch.dylib
TestCombinations: /Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/Working/Utilities/build/stage/Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/NWChemEx/lib/Utilities/libUtilities.dylib
TestCombinations: CMakeFiles/TestCombinations.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/Working/Utilities/build/Utilities_Tests_External-prefix/src/Utilities_Tests_External-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TestCombinations"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestCombinations.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TestCombinations.dir/build: TestCombinations

.PHONY : CMakeFiles/TestCombinations.dir/build

CMakeFiles/TestCombinations.dir/requires: CMakeFiles/TestCombinations.dir/TestCombinations.cpp.o.requires

.PHONY : CMakeFiles/TestCombinations.dir/requires

CMakeFiles/TestCombinations.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TestCombinations.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TestCombinations.dir/clean

CMakeFiles/TestCombinations.dir/depend:
	cd /Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/Working/Utilities/build/Utilities_Tests_External-prefix/src/Utilities_Tests_External-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/Working/Utilities/Utilities_Test /Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/Working/Utilities/Utilities_Test /Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/Working/Utilities/build/Utilities_Tests_External-prefix/src/Utilities_Tests_External-build /Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/Working/Utilities/build/Utilities_Tests_External-prefix/src/Utilities_Tests_External-build /Users/wadejong/Desktop/NWChemEx_Project/NWChemEx-Project/Working/Utilities/build/Utilities_Tests_External-prefix/src/Utilities_Tests_External-build/CMakeFiles/TestCombinations.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TestCombinations.dir/depend

