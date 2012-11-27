# Install script for directory: /home/cnhzcy14/CanFestival-3-71623bbf8093/src

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcanfestival.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcanfestival.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcanfestival.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/cnhzcy14/CanFestival-3-71623bbf8093/lib/libcanfestival.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcanfestival.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcanfestival.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcanfestival.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/canfestival" TYPE FILE FILES
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/CanFestival.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/CfLib.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/CfNode.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/CfNode_401.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/CfResult.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/CfSystem.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/HostNode.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/unix/applicfg.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/can.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/can_driver.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/unix/canfestival.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/config.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/data.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/dcf.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/def.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/emcy.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/lifegrd.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/lss.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/nmtMaster.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/nmtSlave.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/objacces.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/objdictdef.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/pdo.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/sdo.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/states.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/sync.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/sysdep.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/timer.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/timers_unix/timerscfg.h"
    "/home/cnhzcy14/CanFestival-3-71623bbf8093/include/timers_driver.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

