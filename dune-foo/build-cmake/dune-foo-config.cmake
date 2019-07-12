if(NOT dune-foo_FOUND)
# Whether this module is installed or not
set(dune-foo_INSTALLED OFF)

# Settings specific to the module

# Package initialization
# Set prefix to source dir
set(PACKAGE_PREFIX_DIR /home/amir/Dune-projects/dune-foo)
macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

#report other information
set_and_check(dune-foo_PREFIX "${PACKAGE_PREFIX_DIR}")
set_and_check(dune-foo_INCLUDE_DIRS "/home/amir/Dune-projects/dune-foo")
set(dune-foo_CXX_FLAGS " -std=c++14 ")
set(dune-foo_CXX_FLAGS_DEBUG "-g")
set(dune-foo_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(dune-foo_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(dune-foo_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")
set(dune-foo_DEPENDS "dune-common;dune-geometry;dune-localfunctions;dune-uggrid;dune-grid;dune-typetree;dune-istl;dune-functions")
set(dune-foo_SUGGESTS "")
set(dune-foo_MODULE_PATH "/home/amir/Dune-projects/dune-foo/cmake/modules")
set(dune-foo_LIBRARIES "")

# Lines that are set by the CMake build system via the variable DUNE_CUSTOM_PKG_CONFIG_SECTION


#import the target
if(dune-foo_LIBRARIES)
  get_filename_component(_dir "${CMAKE_CURRENT_LIST_FILE}" PATH)
  include("${_dir}/dune-foo-targets.cmake")
endif()
endif()
