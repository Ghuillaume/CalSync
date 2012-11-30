#----------------------------------------------------------------
# Generated CMake target import file for configuration "".
#----------------------------------------------------------------

# Commands may need to know the format version.
SET(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "qjson" for configuration ""
SET_PROPERTY(TARGET qjson APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
SET_TARGET_PROPERTIES(qjson PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "Qt4::QtCore"
  IMPORTED_LOCATION_NOCONFIG "/usr/local/lib/libqjson.so.0.7.1"
  IMPORTED_SONAME_NOCONFIG "libqjson.so.0"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS qjson )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_qjson "/usr/local/lib/libqjson.so.0.7.1" )

# Loop over all imported files and verify that they actually exist
FOREACH(target ${_IMPORT_CHECK_TARGETS} )
  FOREACH(file ${_IMPORT_CHECK_FILES_FOR_${target}} )
    IF(NOT EXISTS "${file}" )
      MESSAGE(FATAL_ERROR "The imported target \"${target}\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    ENDIF()
  ENDFOREACH()
  UNSET(_IMPORT_CHECK_FILES_FOR_${target})
ENDFOREACH()
UNSET(_IMPORT_CHECK_TARGETS)

# Commands beyond this point should not need to know the version.
SET(CMAKE_IMPORT_FILE_VERSION)
