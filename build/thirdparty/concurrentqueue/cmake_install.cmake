# Install script for directory: /home/clown911026/cs/project/ThreadPool/thirdparty/concurrentqueue

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/concurrentqueue/concurrentqueueTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/concurrentqueue/concurrentqueueTargets.cmake"
         "/home/clown911026/cs/project/ThreadPool/build/thirdparty/concurrentqueue/CMakeFiles/Export/lib/cmake/concurrentqueue/concurrentqueueTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/concurrentqueue/concurrentqueueTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/concurrentqueue/concurrentqueueTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/concurrentqueue" TYPE FILE FILES "/home/clown911026/cs/project/ThreadPool/build/thirdparty/concurrentqueue/CMakeFiles/Export/lib/cmake/concurrentqueue/concurrentqueueTargets.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/concurrentqueue" TYPE FILE FILES
    "/home/clown911026/cs/project/ThreadPool/build/thirdparty/concurrentqueue/concurrentqueueConfig.cmake"
    "/home/clown911026/cs/project/ThreadPool/build/thirdparty/concurrentqueue/concurrentqueueConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/concurrentqueue/moodycamel" TYPE FILE FILES
    "/home/clown911026/cs/project/ThreadPool/thirdparty/concurrentqueue/blockingconcurrentqueue.h"
    "/home/clown911026/cs/project/ThreadPool/thirdparty/concurrentqueue/concurrentqueue.h"
    "/home/clown911026/cs/project/ThreadPool/thirdparty/concurrentqueue/lightweightsemaphore.h"
    "/home/clown911026/cs/project/ThreadPool/thirdparty/concurrentqueue/LICENSE.md"
    )
endif()

