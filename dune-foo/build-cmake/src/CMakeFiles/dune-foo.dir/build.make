# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/amir/Dune-projects/dune-foo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amir/Dune-projects/dune-foo/build-cmake

# Include any dependencies generated for this target.
include src/CMakeFiles/dune-foo.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/dune-foo.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/dune-foo.dir/flags.make

src/CMakeFiles/dune-foo.dir/dune-foo.cc.o: src/CMakeFiles/dune-foo.dir/flags.make
src/CMakeFiles/dune-foo.dir/dune-foo.cc.o: ../src/dune-foo.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amir/Dune-projects/dune-foo/build-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/dune-foo.dir/dune-foo.cc.o"
	cd /home/amir/Dune-projects/dune-foo/build-cmake/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dune-foo.dir/dune-foo.cc.o -c /home/amir/Dune-projects/dune-foo/src/dune-foo.cc

src/CMakeFiles/dune-foo.dir/dune-foo.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dune-foo.dir/dune-foo.cc.i"
	cd /home/amir/Dune-projects/dune-foo/build-cmake/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amir/Dune-projects/dune-foo/src/dune-foo.cc > CMakeFiles/dune-foo.dir/dune-foo.cc.i

src/CMakeFiles/dune-foo.dir/dune-foo.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dune-foo.dir/dune-foo.cc.s"
	cd /home/amir/Dune-projects/dune-foo/build-cmake/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amir/Dune-projects/dune-foo/src/dune-foo.cc -o CMakeFiles/dune-foo.dir/dune-foo.cc.s

src/CMakeFiles/dune-foo.dir/dune-foo.cc.o.requires:

.PHONY : src/CMakeFiles/dune-foo.dir/dune-foo.cc.o.requires

src/CMakeFiles/dune-foo.dir/dune-foo.cc.o.provides: src/CMakeFiles/dune-foo.dir/dune-foo.cc.o.requires
	$(MAKE) -f src/CMakeFiles/dune-foo.dir/build.make src/CMakeFiles/dune-foo.dir/dune-foo.cc.o.provides.build
.PHONY : src/CMakeFiles/dune-foo.dir/dune-foo.cc.o.provides

src/CMakeFiles/dune-foo.dir/dune-foo.cc.o.provides.build: src/CMakeFiles/dune-foo.dir/dune-foo.cc.o


# Object files for target dune-foo
dune__foo_OBJECTS = \
"CMakeFiles/dune-foo.dir/dune-foo.cc.o"

# External object files for target dune-foo
dune__foo_EXTERNAL_OBJECTS =

src/dune-foo: src/CMakeFiles/dune-foo.dir/dune-foo.cc.o
src/dune-foo: src/CMakeFiles/dune-foo.dir/build.make
src/dune-foo: /usr/local/lib/libdunealbertagrid_3d.a
src/dune-foo: /usr/local/lib/libdunealbertagrid_2d.a
src/dune-foo: /usr/local/lib/libdunealbertagrid_1d.a
src/dune-foo: /usr/local/lib/libdunegrid.a
src/dune-foo: /usr/local/lib/libdunegeometry.a
src/dune-foo: /usr/local/lib/libugS3.a
src/dune-foo: /usr/local/lib/libugS2.a
src/dune-foo: /usr/local/lib/libugL.a
src/dune-foo: /usr/local/lib/libdunecommon.a
src/dune-foo: /usr/local/lib/libdunegrid.a
src/dune-foo: /usr/local/lib/libdunegeometry.a
src/dune-foo: /usr/local/lib/libugS3.a
src/dune-foo: /usr/local/lib/libugS2.a
src/dune-foo: /usr/local/lib/libugL.a
src/dune-foo: /usr/local/lib/libdunecommon.a
src/dune-foo: /usr/lib/x86_64-linux-gnu/libldl.so
src/dune-foo: /usr/lib/x86_64-linux-gnu/libspqr.so
src/dune-foo: /usr/lib/x86_64-linux-gnu/libumfpack.so
src/dune-foo: /usr/lib/x86_64-linux-gnu/libcholmod.so
src/dune-foo: /usr/lib/x86_64-linux-gnu/libamd.so
src/dune-foo: /usr/lib/x86_64-linux-gnu/libcamd.so
src/dune-foo: /usr/lib/x86_64-linux-gnu/libcolamd.so
src/dune-foo: /usr/lib/x86_64-linux-gnu/libccolamd.so
src/dune-foo: /usr/lib/x86_64-linux-gnu/libsuitesparseconfig.so
src/dune-foo: /usr/lib/x86_64-linux-gnu/libsuperlu.so
src/dune-foo: /usr/lib/x86_64-linux-gnu/libblas.so
src/dune-foo: /usr/lib/x86_64-linux-gnu/liblapack.so
src/dune-foo: /usr/lib/x86_64-linux-gnu/libblas.so
src/dune-foo: /usr/lib/x86_64-linux-gnu/openmpi/lib/libmpi.so
src/dune-foo: /usr/local/lib/libdunealbertagrid_3d.a
src/dune-foo: /usr/local/lib/libdunealbertagrid_2d.a
src/dune-foo: /usr/local/lib/libdunealbertagrid_1d.a
src/dune-foo: /usr/local/lib/libdunegrid.a
src/dune-foo: /usr/local/lib/libdunegeometry.a
src/dune-foo: /usr/local/lib/libugS3.a
src/dune-foo: /usr/local/lib/libugS2.a
src/dune-foo: /usr/local/lib/libugL.a
src/dune-foo: /usr/local/lib/libdunecommon.a
src/dune-foo: /usr/lib/x86_64-linux-gnu/liblapack.so
src/dune-foo: /usr/lib/x86_64-linux-gnu/libblas.so
src/dune-foo: /usr/lib/x86_64-linux-gnu/openmpi/lib/libmpi.so
src/dune-foo: src/CMakeFiles/dune-foo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/amir/Dune-projects/dune-foo/build-cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable dune-foo"
	cd /home/amir/Dune-projects/dune-foo/build-cmake/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dune-foo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/dune-foo.dir/build: src/dune-foo

.PHONY : src/CMakeFiles/dune-foo.dir/build

src/CMakeFiles/dune-foo.dir/requires: src/CMakeFiles/dune-foo.dir/dune-foo.cc.o.requires

.PHONY : src/CMakeFiles/dune-foo.dir/requires

src/CMakeFiles/dune-foo.dir/clean:
	cd /home/amir/Dune-projects/dune-foo/build-cmake/src && $(CMAKE_COMMAND) -P CMakeFiles/dune-foo.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/dune-foo.dir/clean

src/CMakeFiles/dune-foo.dir/depend:
	cd /home/amir/Dune-projects/dune-foo/build-cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amir/Dune-projects/dune-foo /home/amir/Dune-projects/dune-foo/src /home/amir/Dune-projects/dune-foo/build-cmake /home/amir/Dune-projects/dune-foo/build-cmake/src /home/amir/Dune-projects/dune-foo/build-cmake/src/CMakeFiles/dune-foo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/dune-foo.dir/depend
