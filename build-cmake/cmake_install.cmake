# Install script for directory: /home/amir/Dune-projects/dune-howto-adaptive-grid-multilevel-quad

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
  set(CMAKE_MODULE_PATH /home/amir/Dune-projects/dune-howto-adaptive-grid-multilevel-quad/cmake/modules;/usr/local/share/dune/cmake/modules;/usr/local/share/dune/cmake/modules;/usr/local/share/dune/cmake/modules;/usr/local/share/dune/cmake/modules;/usr/local/share/dune/cmake/modules;/usr/local/share/dune/cmake/modules;/usr/local/share/dune/cmake/modules;/usr/local/share/dune/cmake/modules)
              set(DUNE_PYTHON_WHEELHOUSE /usr/local/share/dune/wheelhouse)
              include(DuneExecuteProcess)
              dune_execute_process(COMMAND "/usr/bin/cmake" --build . --target install_python --config $<CONFIG>)
              
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/dunecontrol/dune-howto-adaptive-grid-multilevel-quad" TYPE FILE FILES "/home/amir/Dune-projects/dune-howto-adaptive-grid-multilevel-quad/dune.module")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/dune-howto-adaptive-grid-multilevel-quad" TYPE FILE FILES
    "/home/amir/Dune-projects/dune-howto-adaptive-grid-multilevel-quad/build-cmake/cmake/pkg/dune-howto-adaptive-grid-multilevel-quad-config.cmake"
    "/home/amir/Dune-projects/dune-howto-adaptive-grid-multilevel-quad/build-cmake/dune-howto-adaptive-grid-multilevel-quad-config-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/dune-howto-adaptive-grid-multilevel-quad" TYPE FILE FILES "/home/amir/Dune-projects/dune-howto-adaptive-grid-multilevel-quad/config.h.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/amir/Dune-projects/dune-howto-adaptive-grid-multilevel-quad/build-cmake/dune-howto-adaptive-grid-multilevel-quad.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/amir/Dune-projects/dune-howto-adaptive-grid-multilevel-quad/build-cmake/src/cmake_install.cmake")
  include("/home/amir/Dune-projects/dune-howto-adaptive-grid-multilevel-quad/build-cmake/dune/cmake_install.cmake")
  include("/home/amir/Dune-projects/dune-howto-adaptive-grid-multilevel-quad/build-cmake/doc/cmake_install.cmake")
  include("/home/amir/Dune-projects/dune-howto-adaptive-grid-multilevel-quad/build-cmake/cmake/modules/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/amir/Dune-projects/dune-howto-adaptive-grid-multilevel-quad/build-cmake/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
