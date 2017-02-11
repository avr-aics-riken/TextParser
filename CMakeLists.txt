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
#
#-*- CMAKE -*-#
# Process this file with cmake to produce a configure script.

# Following parameters must be given at cmake command line
# INSTALL_DIR, CXX, CC, F90

# Build options, see Readme.md for details.
#
# -D INSTALL_DIR=install_directory
#
# -D enable_fapi={no|yes)}
#
# -D enable_test={no|yes}
#
# -D with_MPI={no|yes}
#

cmake_minimum_required(VERSION 2.8)


#######
# Build options
#######

option (enable_fapi "Turn on Fortran API" "OFF")
option (enable_test "Sample code test" "OFF")
option (with_MPI "Enable MPI" "OFF")


#######
# Project setting
#######

if(enable_fapi)
  message("PROJECT: TextParser for C, CXX, and Fortran")
  project(TextParser C CXX Fortran)
else()
  message("PROJECT: TextParser for C and CXX")
  project(TextParser C CXX)
endif()

# project()でCMAKE_INSTALL_PREFIX=/usr/localとなるので、再定義
set (CMAKE_INSTALL_PREFIX "${INSTALL_DIR}")

set(CMAKE_BUILD_TYPE Release)



#######
set(PROJECT_VERSION "1.7.7")
set(LIB_REVISION "20170211_1400")
#######




#######
# Cmake module
#######

set(CMAKE_MODULE_PATH  ${PROJECT_SOURCE_DIR}/cmake)
include(${PROJECT_SOURCE_DIR}/cmake/CompileOptionSelector.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/tp_package.cmake)

#######
# Options
#######

if(enable_fapi)
  FreeForm()
endif()

AddOptimizeOption()



#######
# Find libraries to depend
#######


#######
# Display options
#######

message(" ")
message( STATUS "Destination PATH: "               ${CMAKE_INSTALL_PREFIX})
message( STATUS "build test program: "             ${build_unit_tests})
message( STATUS "CMAKE_C_COMPILER: "               ${CMAKE_C_COMPILER})
message( STATUS "CMAKE_C_FLAGS: "                  ${CMAKE_C_FLAGS})
message( STATUS "CMAKE_CXX_COMPILER: "             ${CMAKE_CXX_COMPILER})
message( STATUS "CMAKE_CXX_FLAGS: "                ${CMAKE_CXX_FLAGS})

if(enable_fapi)
  message( STATUS "CMAKE_Fortran_COMPILER: "         ${CMAKE_Fortran_COMPILER})
  message( STATUS "CMAKE_Fortran_FLAGS: "            ${CMAKE_Fortran_FLAGS})
endif()

if(CMAKE_CXX_COMPILER MATCHES ".*FCCpx$")
else()
  if(with_MPI)
    include(FindMPI)

    if(MPI_CXX_FOUND)
      message("MPI-CXX-CMP  : ${MPI_CXX_COMPILER}")
      message("MPI-CXX-FLAGS: ${MPI_CXX_COMPILE_FLAGS}")
      message("MPI-CXX-INC  : ${MPI_CXX_INCLUDE_PATH}")
      message("MPI-LNK-FLAGS: ${MPI_CXX_LINK_FLAGS}")
      message("MPI-LIBS     : ${MPI_CXX_LIBRARIES}")
    endif(MPI_CXX_FOUND)
  endif()
endif()

message("${PROJECT_NAME} Version : ${PROJECT_VERSION}")


#######
# include PATH for libs
#######

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
    )


#######
# Test
#######

if (enable_test)
  enable_testing()
  message("Code test will be performed")
else()
  message("Code test is skipped")
endif()


add_definitions(-DHAVE_CONFIG_H)


#######
# Library name
#######

if(with_MPI)
  add_definitions(-DENABLE_MPI)
  add_definitions(-DBUILD_MPI)
endif()



#######
# Check header files
#######

include(CheckIncludeFiles)

CHECK_INCLUDE_FILES(inttypes.h HAVE_INTTYPES_H)
CHECK_INCLUDE_FILES(memory.h HAVE_MEMORY_H)
CHECK_INCLUDE_FILES(stdint.h HAVE_STDINT_H)
CHECK_INCLUDE_FILES(stdlib.h HAVE_STDLIB_H)
CHECK_INCLUDE_FILES(strings.h HAVE_STRINGS_H)
CHECK_INCLUDE_FILES(string.h HAVE_STRING_H)
CHECK_INCLUDE_FILES(sys/stat.h HAVE_SYS_STAT_H)
CHECK_INCLUDE_FILES(sys/types.h HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILES(unistd.h HAVE_UNISTD_H)


#######
# Sub Directories
#######

add_subdirectory(src)
add_subdirectory(doc)

if(enable_test)
  add_subdirectory(Examples)
endif()


#######
# configure files
#######

configure_file( config.h.in.cmake config.h )
configure_file( include/tpVersion.h.in ${PROJECT_BINARY_DIR}/include/tpVersion.h)


#######
# Install files
#######

install(FILES  ChangeLog.md
               Readme.md
               License.txt
        DESTINATION share)


#######
# Installer
#######

tp_package()
