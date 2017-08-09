##****************************************************************************
## Copyright © 2015 Jan Erik Breimo. All rights reserved.
## Created by Jan Erik Breimo on 2015-08-31.
##
## This file is distributed under the Simplified BSD License.
## License text is included with the source distribution.
##****************************************************************************
# Try to find Yson
# Once done this will define
#  YSON_FOUND - System has Yson
#  YSON_INCLUDE_DIR - The Yson include directories
#  YSON_LIBRARY - The libraries needed to use Yson
#  YSON_DEFINITIONS - Compiler switches required for using Yson

set(DEBUG_LIBRARY_NAME Yson.debug)

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(LIBRARY_NAME ${DEBUG_LIBRARY_NAME})
else(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(LIBRARY_NAME Yson)
endif(CMAKE_BUILD_TYPE MATCHES DEBUG)

if(WIN32)
    set(POSSIBLE_INCLUDE_PATHS
        $ENV{HOMEDRIVE}$ENV{HOMEPATH}/include
        ${CMAKE_SOURCE_DIR}/../include
        )
    set(POSSIBLE_LIBRARY_PATHS
        $ENV{HOMEDRIVE}$ENV{HOMEPATH}/lib
        ${CMAKE_SOURCE_DIR}/../lib
        )
else(WIN32)
    set(POSSIBLE_INCLUDE_PATHS
        $ENV{HOME}/include
        )
    set(POSSIBLE_LIBRARY_PATHS
        $ENV{HOME}/lib
        )
    set(YSON_DEFINITIONS -std=c++11)
endif(WIN32)

find_path(YSON_INCLUDE_DIR Yson/YsonDefinitions.hpp
          PATH_SUFFIXES Yson
          PATHS ${POSSIBLE_INCLUDE_PATHS})

find_library(YSON_LIBRARY
             NAMES ${LIBRARY_NAME} lib${LIBRARY_NAME}
             PATHS ${POSSIBLE_LIBRARY_PATHS})

find_library(YSON_DEBUG_LIBRARY
             NAMES ${DEBUG_LIBRARY_NAME} lib${DEBUG_LIBRARY_NAME}
             PATHS ${POSSIBLE_LIBRARY_PATHS})

include(FindPackageHandleStandardArgs)

# Handle the QUIETLY and REQUIRED arguments and set YSON_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Yson DEFAULT_MSG
                                  YSON_INCLUDE_DIR YSON_LIBRARY)

mark_as_advanced(YSON_INCLUDE_DIR YSON_LIBRARY YSON_DEBUG_LIBRARY)
