###################################################################################
#
# TextParser - Text Parsing Library
#
# Copyright (C) 2012-2015 Institute of Industrial Science, The University of Tokyo.
# All rights reserved.
#
# Copyright (c) 2014-2016 Advanced Institute for Computational Science, RIKEN.
# All rights reserved.
#
# Copyright (c) 2016-2017 Research Institute for Information Technology, Kyushu University.
# All rights reserved.
#
###################################################################################

# - Try to find TextParser
# Once done, this will define
#
#  TP_FOUND - system has TextParser
#  TP_INCLUDE_DIRS - TextParser include directories
#  TP_LIBRARIES - link these to use TextParser

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(TP_PKGCONF TP)

if(CMAKE_PREFIX_PATH)
  set(TP_CANDIDATE_PATH ${CMAKE_PREFIX_PATH})
  file(GLOB tmp "${CMAKE_PREFIX_PATH}/[Jj][Hh][Pp][Cc][Nn][Dd][Ff]*/")
  list(APPEND TP_CANDIDATE_PATH ${tmp})
endif()

# Include dir
find_path(TP_INCLUDE_DIR
  NAMES TextParser.h
  PATHS ${TP_ROOT} ${TP_PKGCONF_INCLUDE_DIRS} ${TP_CANDIDATE_PATH}
  PATH_SUFFIXES include
)

# Finally the library itself
find_library(TP_LIBRARY
  NAMES TP
  PATHS ${TP_ROOT} ${TP_PKGCONF_LIBRARY_DIRS} ${TP_CANDIDATE_PATH}
  PATH_SUFFIXES lib
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(TP_PROCESS_INCLUDES TP_INCLUDE_DIR)
set(TP_PROCESS_LIBS TP_LIBRARY)
libfind_process(TP)
