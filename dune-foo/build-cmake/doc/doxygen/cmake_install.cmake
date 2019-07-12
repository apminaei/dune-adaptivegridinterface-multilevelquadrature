# Install script for directory: /home/amir/Dune-projects/dune-foo/doc/doxygen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND /usr/bin/cmake --build /home/amir/Dune-projects/dune-foo/build-cmake --target doxygen_dune-foo
        WORKING_DIRECTORY /home/amir/Dune-projects/dune-foo/build-cmake/doc/doxygen)
      file(GLOB doxygenfiles
        GLOB /home/amir/Dune-projects/dune-foo/build-cmake/doc/doxygen/html/*.html
        /home/amir/Dune-projects/dune-foo/build-cmake/doc/doxygen/html/*.js
        /home/amir/Dune-projects/dune-foo/build-cmake/doc/doxygen/html/*.png
        /home/amir/Dune-projects/dune-foo/build-cmake/doc/doxygen/html/*.css
        /home/amir/Dune-projects/dune-foo/build-cmake/doc/doxygen/html/*.gif)
      set(doxygenfiles "${doxygenfiles}")
      foreach(_file ${doxygenfiles})
         get_filename_component(_basename ${_file} NAME)
         LIST(APPEND CMAKE_INSTALL_MANIFEST_FILES /usr/local/share/doc/dune-foo/doxygen/${_basename})
       endforeach()
       file(INSTALL ${doxygenfiles} DESTINATION /usr/local/share/doc/dune-foo/doxygen)
       message(STATUS "Installed doxygen into /usr/local/share/doc/dune-foo/doxygen")
endif()

