# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.o: /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.o   -c /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.c

CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.c > CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.i

CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.c -o CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.s

CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.o.requires:
.PHONY : CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.o.requires

CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.o.provides: CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.o.provides.build
.PHONY : CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.o.provides

CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.o.provides.build: CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.o

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/bin/server: CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.o
/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/bin/server: CMakeFiles/server.dir/build.make
/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/bin/server: /usr/lib64/libSDLmain.a
/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/bin/server: /usr/lib64/libSDL.so
/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/bin/server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/bin/server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/bin/server
.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/requires: CMakeFiles/server.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/server.o.requires
.PHONY : CMakeFiles/server.dir/requires

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

