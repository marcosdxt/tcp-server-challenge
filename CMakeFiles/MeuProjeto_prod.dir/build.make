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
CMAKE_SOURCE_DIR = /home/devel/qsp/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/devel/qsp/server

# Include any dependencies generated for this target.
include CMakeFiles/MeuProjeto_prod.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MeuProjeto_prod.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MeuProjeto_prod.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MeuProjeto_prod.dir/flags.make

CMakeFiles/MeuProjeto_prod.dir/src/main.cpp.o: CMakeFiles/MeuProjeto_prod.dir/flags.make
CMakeFiles/MeuProjeto_prod.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/MeuProjeto_prod.dir/src/main.cpp.o: CMakeFiles/MeuProjeto_prod.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/devel/qsp/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MeuProjeto_prod.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MeuProjeto_prod.dir/src/main.cpp.o -MF CMakeFiles/MeuProjeto_prod.dir/src/main.cpp.o.d -o CMakeFiles/MeuProjeto_prod.dir/src/main.cpp.o -c /home/devel/qsp/server/src/main.cpp

CMakeFiles/MeuProjeto_prod.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MeuProjeto_prod.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/devel/qsp/server/src/main.cpp > CMakeFiles/MeuProjeto_prod.dir/src/main.cpp.i

CMakeFiles/MeuProjeto_prod.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MeuProjeto_prod.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/devel/qsp/server/src/main.cpp -o CMakeFiles/MeuProjeto_prod.dir/src/main.cpp.s

# Object files for target MeuProjeto_prod
MeuProjeto_prod_OBJECTS = \
"CMakeFiles/MeuProjeto_prod.dir/src/main.cpp.o"

# External object files for target MeuProjeto_prod
MeuProjeto_prod_EXTERNAL_OBJECTS =

MeuProjeto_prod: CMakeFiles/MeuProjeto_prod.dir/src/main.cpp.o
MeuProjeto_prod: CMakeFiles/MeuProjeto_prod.dir/build.make
MeuProjeto_prod: CMakeFiles/MeuProjeto_prod.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/devel/qsp/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MeuProjeto_prod"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MeuProjeto_prod.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MeuProjeto_prod.dir/build: MeuProjeto_prod
.PHONY : CMakeFiles/MeuProjeto_prod.dir/build

CMakeFiles/MeuProjeto_prod.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MeuProjeto_prod.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MeuProjeto_prod.dir/clean

CMakeFiles/MeuProjeto_prod.dir/depend:
	cd /home/devel/qsp/server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/devel/qsp/server /home/devel/qsp/server /home/devel/qsp/server /home/devel/qsp/server /home/devel/qsp/server/CMakeFiles/MeuProjeto_prod.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MeuProjeto_prod.dir/depend

