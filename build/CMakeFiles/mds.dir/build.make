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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/project/sliceapi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/project/sliceapi/build

# Include any dependencies generated for this target.
include CMakeFiles/mds.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mds.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mds.dir/flags.make

CMakeFiles/mds.dir/source/interface.cpp.o: CMakeFiles/mds.dir/flags.make
CMakeFiles/mds.dir/source/interface.cpp.o: ../source/interface.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/project/sliceapi/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mds.dir/source/interface.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mds.dir/source/interface.cpp.o -c /root/project/sliceapi/source/interface.cpp

CMakeFiles/mds.dir/source/interface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mds.dir/source/interface.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/project/sliceapi/source/interface.cpp > CMakeFiles/mds.dir/source/interface.cpp.i

CMakeFiles/mds.dir/source/interface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mds.dir/source/interface.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/project/sliceapi/source/interface.cpp -o CMakeFiles/mds.dir/source/interface.cpp.s

CMakeFiles/mds.dir/source/interface.cpp.o.requires:
.PHONY : CMakeFiles/mds.dir/source/interface.cpp.o.requires

CMakeFiles/mds.dir/source/interface.cpp.o.provides: CMakeFiles/mds.dir/source/interface.cpp.o.requires
	$(MAKE) -f CMakeFiles/mds.dir/build.make CMakeFiles/mds.dir/source/interface.cpp.o.provides.build
.PHONY : CMakeFiles/mds.dir/source/interface.cpp.o.provides

CMakeFiles/mds.dir/source/interface.cpp.o.provides.build: CMakeFiles/mds.dir/source/interface.cpp.o

CMakeFiles/mds.dir/source/ComDocIO.cpp.o: CMakeFiles/mds.dir/flags.make
CMakeFiles/mds.dir/source/ComDocIO.cpp.o: ../source/ComDocIO.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/project/sliceapi/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mds.dir/source/ComDocIO.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mds.dir/source/ComDocIO.cpp.o -c /root/project/sliceapi/source/ComDocIO.cpp

CMakeFiles/mds.dir/source/ComDocIO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mds.dir/source/ComDocIO.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/project/sliceapi/source/ComDocIO.cpp > CMakeFiles/mds.dir/source/ComDocIO.cpp.i

CMakeFiles/mds.dir/source/ComDocIO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mds.dir/source/ComDocIO.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/project/sliceapi/source/ComDocIO.cpp -o CMakeFiles/mds.dir/source/ComDocIO.cpp.s

CMakeFiles/mds.dir/source/ComDocIO.cpp.o.requires:
.PHONY : CMakeFiles/mds.dir/source/ComDocIO.cpp.o.requires

CMakeFiles/mds.dir/source/ComDocIO.cpp.o.provides: CMakeFiles/mds.dir/source/ComDocIO.cpp.o.requires
	$(MAKE) -f CMakeFiles/mds.dir/build.make CMakeFiles/mds.dir/source/ComDocIO.cpp.o.provides.build
.PHONY : CMakeFiles/mds.dir/source/ComDocIO.cpp.o.provides

CMakeFiles/mds.dir/source/ComDocIO.cpp.o.provides.build: CMakeFiles/mds.dir/source/ComDocIO.cpp.o

CMakeFiles/mds.dir/source/JavaApi.cpp.o: CMakeFiles/mds.dir/flags.make
CMakeFiles/mds.dir/source/JavaApi.cpp.o: ../source/JavaApi.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/project/sliceapi/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mds.dir/source/JavaApi.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mds.dir/source/JavaApi.cpp.o -c /root/project/sliceapi/source/JavaApi.cpp

CMakeFiles/mds.dir/source/JavaApi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mds.dir/source/JavaApi.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/project/sliceapi/source/JavaApi.cpp > CMakeFiles/mds.dir/source/JavaApi.cpp.i

CMakeFiles/mds.dir/source/JavaApi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mds.dir/source/JavaApi.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/project/sliceapi/source/JavaApi.cpp -o CMakeFiles/mds.dir/source/JavaApi.cpp.s

CMakeFiles/mds.dir/source/JavaApi.cpp.o.requires:
.PHONY : CMakeFiles/mds.dir/source/JavaApi.cpp.o.requires

CMakeFiles/mds.dir/source/JavaApi.cpp.o.provides: CMakeFiles/mds.dir/source/JavaApi.cpp.o.requires
	$(MAKE) -f CMakeFiles/mds.dir/build.make CMakeFiles/mds.dir/source/JavaApi.cpp.o.provides.build
.PHONY : CMakeFiles/mds.dir/source/JavaApi.cpp.o.provides

CMakeFiles/mds.dir/source/JavaApi.cpp.o.provides.build: CMakeFiles/mds.dir/source/JavaApi.cpp.o

CMakeFiles/mds.dir/source/export.cpp.o: CMakeFiles/mds.dir/flags.make
CMakeFiles/mds.dir/source/export.cpp.o: ../source/export.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/project/sliceapi/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mds.dir/source/export.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mds.dir/source/export.cpp.o -c /root/project/sliceapi/source/export.cpp

CMakeFiles/mds.dir/source/export.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mds.dir/source/export.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/project/sliceapi/source/export.cpp > CMakeFiles/mds.dir/source/export.cpp.i

CMakeFiles/mds.dir/source/export.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mds.dir/source/export.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/project/sliceapi/source/export.cpp -o CMakeFiles/mds.dir/source/export.cpp.s

CMakeFiles/mds.dir/source/export.cpp.o.requires:
.PHONY : CMakeFiles/mds.dir/source/export.cpp.o.requires

CMakeFiles/mds.dir/source/export.cpp.o.provides: CMakeFiles/mds.dir/source/export.cpp.o.requires
	$(MAKE) -f CMakeFiles/mds.dir/build.make CMakeFiles/mds.dir/source/export.cpp.o.provides.build
.PHONY : CMakeFiles/mds.dir/source/export.cpp.o.provides

CMakeFiles/mds.dir/source/export.cpp.o.provides.build: CMakeFiles/mds.dir/source/export.cpp.o

# Object files for target mds
mds_OBJECTS = \
"CMakeFiles/mds.dir/source/interface.cpp.o" \
"CMakeFiles/mds.dir/source/ComDocIO.cpp.o" \
"CMakeFiles/mds.dir/source/JavaApi.cpp.o" \
"CMakeFiles/mds.dir/source/export.cpp.o"

# External object files for target mds
mds_EXTERNAL_OBJECTS =

libmds.so: CMakeFiles/mds.dir/source/interface.cpp.o
libmds.so: CMakeFiles/mds.dir/source/ComDocIO.cpp.o
libmds.so: CMakeFiles/mds.dir/source/JavaApi.cpp.o
libmds.so: CMakeFiles/mds.dir/source/export.cpp.o
libmds.so: CMakeFiles/mds.dir/build.make
libmds.so: CMakeFiles/mds.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libmds.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mds.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mds.dir/build: libmds.so
.PHONY : CMakeFiles/mds.dir/build

CMakeFiles/mds.dir/requires: CMakeFiles/mds.dir/source/interface.cpp.o.requires
CMakeFiles/mds.dir/requires: CMakeFiles/mds.dir/source/ComDocIO.cpp.o.requires
CMakeFiles/mds.dir/requires: CMakeFiles/mds.dir/source/JavaApi.cpp.o.requires
CMakeFiles/mds.dir/requires: CMakeFiles/mds.dir/source/export.cpp.o.requires
.PHONY : CMakeFiles/mds.dir/requires

CMakeFiles/mds.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mds.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mds.dir/clean

CMakeFiles/mds.dir/depend:
	cd /root/project/sliceapi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/project/sliceapi /root/project/sliceapi /root/project/sliceapi/build /root/project/sliceapi/build /root/project/sliceapi/build/CMakeFiles/mds.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mds.dir/depend

