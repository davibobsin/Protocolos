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
include CMakeFiles/grafico.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/grafico.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/grafico.dir/flags.make

CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.o: CMakeFiles/grafico.dir/flags.make
CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.o: /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.o   -c /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.c

CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.c > CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.i

CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.c -o CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.s

CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.o.requires:
.PHONY : CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.o.requires

CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.o.provides: CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.o.requires
	$(MAKE) -f CMakeFiles/grafico.dir/build.make CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.o.provides.build
.PHONY : CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.o.provides

CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.o.provides.build: CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.o

# Object files for target grafico
grafico_OBJECTS = \
"CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.o"

# External object files for target grafico
grafico_EXTERNAL_OBJECTS =

/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/bin/grafico: CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.o
/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/bin/grafico: CMakeFiles/grafico.dir/build.make
/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/bin/grafico: libbib_graf.a
/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/bin/grafico: /usr/lib64/libSDLmain.a
/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/bin/grafico: /usr/lib64/libSDL.so
/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/bin/grafico: CMakeFiles/grafico.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/bin/grafico"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/grafico.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/grafico.dir/build: /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/bin/grafico
.PHONY : CMakeFiles/grafico.dir/build

CMakeFiles/grafico.dir/requires: CMakeFiles/grafico.dir/home/users/eng10048_3/Documents/PROTO_2018/Protocolos/src/grafico.o.requires
.PHONY : CMakeFiles/grafico.dir/requires

CMakeFiles/grafico.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/grafico.dir/cmake_clean.cmake
.PHONY : CMakeFiles/grafico.dir/clean

CMakeFiles/grafico.dir/depend:
	cd /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build /home/users/eng10048_3/Documents/PROTO_2018/Protocolos/build/CMakeFiles/grafico.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/grafico.dir/depend
