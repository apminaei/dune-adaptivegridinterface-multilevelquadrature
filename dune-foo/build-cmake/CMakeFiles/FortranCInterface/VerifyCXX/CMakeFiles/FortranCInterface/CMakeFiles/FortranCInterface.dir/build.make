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
CMAKE_SOURCE_DIR = /usr/share/cmake-3.10/Modules/FortranCInterface

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amir/dune-project/dune-foo/build-cmake/CMakeFiles/FortranCInterface/VerifyCXX/CMakeFiles/FortranCInterface

# Include any dependencies generated for this target.
include CMakeFiles/FortranCInterface.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FortranCInterface.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FortranCInterface.dir/flags.make

CMakeFiles/FortranCInterface.dir/main.F.o: CMakeFiles/FortranCInterface.dir/flags.make
CMakeFiles/FortranCInterface.dir/main.F.o: /usr/share/cmake-3.10/Modules/FortranCInterface/main.F
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/amir/dune-project/dune-foo/build-cmake/CMakeFiles/FortranCInterface/VerifyCXX/CMakeFiles/FortranCInterface/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building Fortran object CMakeFiles/FortranCInterface.dir/main.F.o"
	/usr/bin/gfortran $(Fortran_DEFINES) -DCALL_MOD $(Fortran_INCLUDES) $(Fortran_FLAGS) -c /usr/share/cmake-3.10/Modules/FortranCInterface/main.F -o CMakeFiles/FortranCInterface.dir/main.F.o

CMakeFiles/FortranCInterface.dir/main.F.i: cmake_force
	@echo "Preprocessing Fortran source to CMakeFiles/FortranCInterface.dir/main.F.i"
	/usr/bin/gfortran $(Fortran_DEFINES) -DCALL_MOD $(Fortran_INCLUDES) $(Fortran_FLAGS) -E /usr/share/cmake-3.10/Modules/FortranCInterface/main.F > CMakeFiles/FortranCInterface.dir/main.F.i

CMakeFiles/FortranCInterface.dir/main.F.s: cmake_force
	@echo "Compiling Fortran source to assembly CMakeFiles/FortranCInterface.dir/main.F.s"
	/usr/bin/gfortran $(Fortran_DEFINES) -DCALL_MOD $(Fortran_INCLUDES) $(Fortran_FLAGS) -S /usr/share/cmake-3.10/Modules/FortranCInterface/main.F -o CMakeFiles/FortranCInterface.dir/main.F.s

CMakeFiles/FortranCInterface.dir/main.F.o.requires:

.PHONY : CMakeFiles/FortranCInterface.dir/main.F.o.requires

CMakeFiles/FortranCInterface.dir/main.F.o.provides: CMakeFiles/FortranCInterface.dir/main.F.o.requires
	$(MAKE) -f CMakeFiles/FortranCInterface.dir/build.make CMakeFiles/FortranCInterface.dir/main.F.o.provides.build
.PHONY : CMakeFiles/FortranCInterface.dir/main.F.o.provides

CMakeFiles/FortranCInterface.dir/main.F.o.provides.build: CMakeFiles/FortranCInterface.dir/main.F.o


CMakeFiles/FortranCInterface.dir/call_sub.f.o: CMakeFiles/FortranCInterface.dir/flags.make
CMakeFiles/FortranCInterface.dir/call_sub.f.o: /usr/share/cmake-3.10/Modules/FortranCInterface/call_sub.f
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/amir/dune-project/dune-foo/build-cmake/CMakeFiles/FortranCInterface/VerifyCXX/CMakeFiles/FortranCInterface/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building Fortran object CMakeFiles/FortranCInterface.dir/call_sub.f.o"
	/usr/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -c /usr/share/cmake-3.10/Modules/FortranCInterface/call_sub.f -o CMakeFiles/FortranCInterface.dir/call_sub.f.o

CMakeFiles/FortranCInterface.dir/call_sub.f.i: cmake_force
	@echo "Preprocessing Fortran source to CMakeFiles/FortranCInterface.dir/call_sub.f.i"
	/usr/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -E /usr/share/cmake-3.10/Modules/FortranCInterface/call_sub.f > CMakeFiles/FortranCInterface.dir/call_sub.f.i

CMakeFiles/FortranCInterface.dir/call_sub.f.s: cmake_force
	@echo "Compiling Fortran source to assembly CMakeFiles/FortranCInterface.dir/call_sub.f.s"
	/usr/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -S /usr/share/cmake-3.10/Modules/FortranCInterface/call_sub.f -o CMakeFiles/FortranCInterface.dir/call_sub.f.s

CMakeFiles/FortranCInterface.dir/call_sub.f.o.requires:

.PHONY : CMakeFiles/FortranCInterface.dir/call_sub.f.o.requires

CMakeFiles/FortranCInterface.dir/call_sub.f.o.provides: CMakeFiles/FortranCInterface.dir/call_sub.f.o.requires
	$(MAKE) -f CMakeFiles/FortranCInterface.dir/build.make CMakeFiles/FortranCInterface.dir/call_sub.f.o.provides.build
.PHONY : CMakeFiles/FortranCInterface.dir/call_sub.f.o.provides

CMakeFiles/FortranCInterface.dir/call_sub.f.o.provides.build: CMakeFiles/FortranCInterface.dir/call_sub.f.o


CMakeFiles/FortranCInterface.dir/call_mod.f90.o: CMakeFiles/FortranCInterface.dir/flags.make
CMakeFiles/FortranCInterface.dir/call_mod.f90.o: /usr/share/cmake-3.10/Modules/FortranCInterface/call_mod.f90
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/amir/dune-project/dune-foo/build-cmake/CMakeFiles/FortranCInterface/VerifyCXX/CMakeFiles/FortranCInterface/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building Fortran object CMakeFiles/FortranCInterface.dir/call_mod.f90.o"
	/usr/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -c /usr/share/cmake-3.10/Modules/FortranCInterface/call_mod.f90 -o CMakeFiles/FortranCInterface.dir/call_mod.f90.o

CMakeFiles/FortranCInterface.dir/call_mod.f90.i: cmake_force
	@echo "Preprocessing Fortran source to CMakeFiles/FortranCInterface.dir/call_mod.f90.i"
	/usr/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -E /usr/share/cmake-3.10/Modules/FortranCInterface/call_mod.f90 > CMakeFiles/FortranCInterface.dir/call_mod.f90.i

CMakeFiles/FortranCInterface.dir/call_mod.f90.s: cmake_force
	@echo "Compiling Fortran source to assembly CMakeFiles/FortranCInterface.dir/call_mod.f90.s"
	/usr/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -S /usr/share/cmake-3.10/Modules/FortranCInterface/call_mod.f90 -o CMakeFiles/FortranCInterface.dir/call_mod.f90.s

CMakeFiles/FortranCInterface.dir/call_mod.f90.o.requires:

.PHONY : CMakeFiles/FortranCInterface.dir/call_mod.f90.o.requires

CMakeFiles/FortranCInterface.dir/call_mod.f90.o.provides: CMakeFiles/FortranCInterface.dir/call_mod.f90.o.requires
	$(MAKE) -f CMakeFiles/FortranCInterface.dir/build.make CMakeFiles/FortranCInterface.dir/call_mod.f90.o.provides.build
.PHONY : CMakeFiles/FortranCInterface.dir/call_mod.f90.o.provides

CMakeFiles/FortranCInterface.dir/call_mod.f90.o.provides.build: CMakeFiles/FortranCInterface.dir/call_mod.f90.o


# Object files for target FortranCInterface
FortranCInterface_OBJECTS = \
"CMakeFiles/FortranCInterface.dir/main.F.o" \
"CMakeFiles/FortranCInterface.dir/call_sub.f.o" \
"CMakeFiles/FortranCInterface.dir/call_mod.f90.o"

# External object files for target FortranCInterface
FortranCInterface_EXTERNAL_OBJECTS =

FortranCInterface: CMakeFiles/FortranCInterface.dir/main.F.o
FortranCInterface: CMakeFiles/FortranCInterface.dir/call_sub.f.o
FortranCInterface: CMakeFiles/FortranCInterface.dir/call_mod.f90.o
FortranCInterface: CMakeFiles/FortranCInterface.dir/build.make
FortranCInterface: libsymbols.a
FortranCInterface: libmyfort.a
FortranCInterface: CMakeFiles/FortranCInterface.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/amir/dune-project/dune-foo/build-cmake/CMakeFiles/FortranCInterface/VerifyCXX/CMakeFiles/FortranCInterface/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking Fortran executable FortranCInterface"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FortranCInterface.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FortranCInterface.dir/build: FortranCInterface

.PHONY : CMakeFiles/FortranCInterface.dir/build

CMakeFiles/FortranCInterface.dir/requires: CMakeFiles/FortranCInterface.dir/main.F.o.requires
CMakeFiles/FortranCInterface.dir/requires: CMakeFiles/FortranCInterface.dir/call_sub.f.o.requires
CMakeFiles/FortranCInterface.dir/requires: CMakeFiles/FortranCInterface.dir/call_mod.f90.o.requires

.PHONY : CMakeFiles/FortranCInterface.dir/requires

CMakeFiles/FortranCInterface.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FortranCInterface.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FortranCInterface.dir/clean

CMakeFiles/FortranCInterface.dir/depend:
	cd /home/amir/dune-project/dune-foo/build-cmake/CMakeFiles/FortranCInterface/VerifyCXX/CMakeFiles/FortranCInterface && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usr/share/cmake-3.10/Modules/FortranCInterface /usr/share/cmake-3.10/Modules/FortranCInterface /home/amir/dune-project/dune-foo/build-cmake/CMakeFiles/FortranCInterface/VerifyCXX/CMakeFiles/FortranCInterface /home/amir/dune-project/dune-foo/build-cmake/CMakeFiles/FortranCInterface/VerifyCXX/CMakeFiles/FortranCInterface /home/amir/dune-project/dune-foo/build-cmake/CMakeFiles/FortranCInterface/VerifyCXX/CMakeFiles/FortranCInterface/CMakeFiles/FortranCInterface.dir/DependInfo.cmake
.PHONY : CMakeFiles/FortranCInterface.dir/depend

