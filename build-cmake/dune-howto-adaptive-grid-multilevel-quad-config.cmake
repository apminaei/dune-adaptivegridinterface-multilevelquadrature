if(NOT dune-howto-adaptive-grid-multilevel-quad_FOUND)
# Whether this module is installed or not
set(dune-howto-adaptive-grid-multilevel-quad_INSTALLED OFF)

# Settings specific to the module

# Package initialization
# Set prefix to source dir
set(PACKAGE_PREFIX_DIR /home/amir/Dune-projects/dune-howto-adaptive-grid-multilevel-quad)
macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

#report other information
set_and_check(dune-howto-adaptive-grid-multilevel-quad_PREFIX "${PACKAGE_PREFIX_DIR}")
set_and_check(dune-howto-adaptive-grid-multilevel-quad_INCLUDE_DIRS "/home/amir/Dune-projects/dune-howto-adaptive-grid-multilevel-quad")
set(dune-howto-adaptive-grid-multilevel-quad_CXX_FLAGS "-std=c++17 ")
set(dune-howto-adaptive-grid-multilevel-quad_CXX_FLAGS_DEBUG "-g")
set(dune-howto-adaptive-grid-multilevel-quad_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(dune-howto-adaptive-grid-multilevel-quad_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(dune-howto-adaptive-grid-multilevel-quad_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")
set(dune-howto-adaptive-grid-multilevel-quad_DEPENDS "dune-common;dune-geometry;dune-localfunctions;dune-uggrid;dune-grid;dune-istl;dune-typetree;dune-functions")
set(dune-howto-adaptive-grid-multilevel-quad_SUGGESTS "")
set(dune-howto-adaptive-grid-multilevel-quad_MODULE_PATH "/home/amir/Dune-projects/dune-howto-adaptive-grid-multilevel-quad/cmake/modules")
set(dune-howto-adaptive-grid-multilevel-quad_LIBRARIES "")

# Lines that are set by the CMake build system via the variable DUNE_CUSTOM_PKG_CONFIG_SECTION


#import the target
if(dune-howto-adaptive-grid-multilevel-quad_LIBRARIES)
  get_filename_component(_dir "${CMAKE_CURRENT_LIST_FILE}" PATH)
  include("${_dir}/dune-howto-adaptive-grid-multilevel-quad-targets.cmake")
endif()
endif()
