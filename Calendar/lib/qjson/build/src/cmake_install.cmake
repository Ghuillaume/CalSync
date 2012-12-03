# Install script for directory: /home/guillaume/Bureau/CalSync/qjson/src

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
  FOREACH(file
      "$ENV{DESTDIR}/usr/local/lib/libqjson.so.0.7.1"
      "$ENV{DESTDIR}/usr/local/lib/libqjson.so.0"
      "$ENV{DESTDIR}/usr/local/lib/libqjson.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    ENDIF()
  ENDFOREACH()
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libqjson.so.0.7.1;/usr/local/lib/libqjson.so.0;/usr/local/lib/libqjson.so")
FILE(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES
    "/home/guillaume/Bureau/CalSync/qjson/build/lib/libqjson.so.0.7.1"
    "/home/guillaume/Bureau/CalSync/qjson/build/lib/libqjson.so.0"
    "/home/guillaume/Bureau/CalSync/qjson/build/lib/libqjson.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}/usr/local/lib/libqjson.so.0.7.1"
      "$ENV{DESTDIR}/usr/local/lib/libqjson.so.0"
      "$ENV{DESTDIR}/usr/local/lib/libqjson.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/qjson/parser.h;/usr/local/include/qjson/parserrunnable.h;/usr/local/include/qjson/qobjecthelper.h;/usr/local/include/qjson/serializer.h;/usr/local/include/qjson/serializerrunnable.h;/usr/local/include/qjson/qjson_export.h")
FILE(INSTALL DESTINATION "/usr/local/include/qjson" TYPE FILE FILES
    "/home/guillaume/Bureau/CalSync/qjson/src/parser.h"
    "/home/guillaume/Bureau/CalSync/qjson/src/parserrunnable.h"
    "/home/guillaume/Bureau/CalSync/qjson/src/qobjecthelper.h"
    "/home/guillaume/Bureau/CalSync/qjson/src/serializer.h"
    "/home/guillaume/Bureau/CalSync/qjson/src/serializerrunnable.h"
    "/home/guillaume/Bureau/CalSync/qjson/src/qjson_export.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

