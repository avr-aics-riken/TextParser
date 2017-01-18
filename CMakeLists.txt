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
#
###################################################################################
#
#-*- CMAKE -*-#
# Process this file with cmake to produce a configure script.

# Following parameters must be given at cmake command line
# INSTALL_DIR, CXX, CC, F90


cmake_minimum_required(VERSION 2.6)

# Compilers
set (CMAKE_CXX_COMPILER "${CXX}")
set (CMAKE_C_COMPILER "${CC}")
set (CMAKE_Fortran_COMPILER "${F90}")

enable_language(CXX C) # これ以前にコンパイラを指定しておく

# Fortran API
option(USE_FAPI "Turn on Fortran API" "OFF")

if(enable_fapi STREQUAL "yes")
	set(USE_FAPI "ON")
	message("Fortran API : ON")
  enable_language(Fortran)
else()
	message("Fortran API : OFF")
endif()


project(TextParser)
set(PROJECT_VERSION "1.7.0")

# project()でCMAKE_INSTALL_PREFIX=/usr/localとなるので、再定義
set (CMAKE_INSTALL_PREFIX "${INSTALL_DIR}")


# Version Info.
message("${PROJECT_NAME} Version : ${PROJECT_VERSION}")

# Revision No.
set(LIB_REVISION "20170118_1200")


# TextParser Install Dir.
message("Install directory : ${CMAKE_INSTALL_PREFIX}")


# Test
enable_testing()


# BUILD_TYPE
set(CMAKE_BUILD_TYPE Release)


# BUILD options
set(TP_BUILD_CROSS OFF CACHE BOOL "Build by corss compiling?")
set(TP_BUILD_MPI OFF CACHE BOOL "Build with MPI support?")
set(TP_BUILD_OMP OFF CACHE BOOL "Build with OpenMP support?")


# K/FX10
if(comp_kind STREQUAL "FJ")

  # native environment
  IF (CMAKE_SYSTEM_PROCESSOR MATCHES "s64fx")
    message("Compiler: FJ native")

    if(USE_FAPI)
      set(MPI_FCLIBS "${MPI_FCLIBS} ${MPI_LIBS} libmpi_f77.a libmpi_f90.a")
    endif()

    # gcc compatible flag(-Xg)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Xg")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xg")

    # PIC flag
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -KPIC")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -KPIC")

    # OpenMP flag(-Kopenmp)
    IF (TP_BUILD_OMP)
      SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Kopenmp")
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Kopenmp")
    ENDIF()

    IF (CMAKE_BUILD_TYPE MATCHES "Release")
      SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Kfast")
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Kfast")
    ENDIF()

    # Prevent CMake from adding GNU-specific linker flags (-rdynamic)
    SET(CMAKE_C_COMPILER_ID "Fujitsu" CACHE STRING "Fujitsu C cross-compiler" FORCE)
    SET(CMAKE_CXX_COMPILER_ID "Fujitsu" CACHE STRING "Fujitsu C++ cross-compiler" FORCE)

    # FindOpenMP.cmake does not try -Kopenmp,but the package will try specific
    # flags based on the compier ID.
    SET(OMP_FLAG_Fujitsu "-Kopenmp")
  ENDIF()


  # K cross compiling
  IF (TP_BUILD_CROSS)
    message("Compiler: FJ cross")

    if(USE_FAPI)
      set(MPI_FCLIBS "${MPI_FCLIBS} ${MPI_LIBS} libmpi_f77.a libmpi_f90.a")
    endif()

    # Prevent CMake from adding GNU-specific linker flags (-rdynamic)
    SET(CMAKE_C_COMPILER_ID "Fujitsu" CACHE STRING "Fujitsu C cross-compiler" FORCE)
    SET(CMAKE_CXX_COMPILER_ID "Fujitsu" CACHE STRING "Fujitsu C++ cross-compiler" FORCE)

    # gcc compatible flag(-Xg)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Xg")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xg")

    # PIC flag
    #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -KPIC")
    #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -KPIC")

    # OpenMP flag(-Kopenmp)
    IF (TP_BUILD_OMP)
      SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Kopenmp")
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Kopenmp")
    ENDIF()

    IF (CMAKE_BUILD_TYPE MATCHES "Release")
      SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Kfast")
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Kfast")
    ENDIF()

    # FindOpenMP.cmake does not try -Kopenmp, but the package will try specific
    # flags based on the compier ID.
    SET(OMP_FLAG_Fujitsu "-Kopenmp")
  endif()
endif()


# Non K/FX environment
if(comp_kind STREQUAL "FJ")
  # skip
else()

  if(TP_BUILD_MPI)
    include(FindMPI)

    if(MPI_CXX_FOUND)
      message("MPI-CXX-CMP  : ${MPI_CXX_COMPILER}")
      message("MPI-CXX-FLAGS: ${MPI_CXX_COMPILE_FLAGS}")
      message("MPI-CXX-INC  : ${MPI_CXX_INCLUDE_PATH}")
      message("MPI-LNK-FLAGS: ${MPI_CXX_LINK_FLAGS}")
      message("MPI-LIBS     : ${MPI_CXX_LIBRARIES}")
    endif(MPI_CXX_FOUND)

    # MPI Library for fortran

    if(USE_FAPI)
      set(MPI_LIBS "${MPI_LIBS} libmpi.a")
      set(MPI_FCLIBS "${MPI_FCLIBS} ${MPI_LIBS} libmpi_f77.a libmpi_f90.a")
    endif()

  endif()

  # compiler options
  if(comp_kind STREQUAL "INTEL")
    message("Compiler: INTEL")
    set(CMAKE_C_FLAGS "-O3")
    set(CMAKE_CXX_FLAGS "-O3")

    if(USE_FAPI)
      set(CMAKE_Fortran_FLAGS "-O3")
    endif()

    IF (TP_BUILD_OMP)
      SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -qopenmp")
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -qopenmp")
      if(USE_FAPI)
        SET(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -qopenmp")
      endif()
    ENDIF()

    # PIC flag
    #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    #if(USE_FAPI)
    #  SET(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -fPIC")
    #endif()

  elseif(comp_kind STREQUAL "GNU")
    message("Compiler: GNU")
    set(CMAKE_C_FLAGS "-O3")
	  set(CMAKE_CXX_FLAGS "-O3")

    if(USE_FAPI)
      set(CMAKE_Fortran_FLAGS "-O3")
    endif()

    IF (TP_BUILD_OMP)
      SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
      if(USE_FAPI)
        SET(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -fopenmp")
      endif()
    ENDIF()

    # PIC flag
    #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    #if(USE_FAPI)
    #  SET(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -fPIC")
    #endif()

  else()
    message("Compiler: none")
    set(CMAKE_C_FLAGS "")
    set(CMAKE_CXX_FLAGS "")
  endif()

  #message("Compiler ID : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
  #message("enable_mpi : ${ENABLE_MPI}")
endif()



# Check
if(USE_FAPI)
  if(NOT CMAKE_Fortran_COMPILER)
    message("ERROR : enable_fapi is specified but Fortran compiler is not given")
    return()
  endif()
endif()


# Test option
option (TP_TEST "Sample code test" "ON")

if (enable_test STREQUAL "no")
  set (TP_TEST "OFF")
  message("Code test is skipped")
else()
  message("Code test will be performed")
endif()


add_definitions(-DHAVE_CONFIG_H)


# Library name

if(TP_BUILD_MPI STREQUAL "OFF")
	set(SERIALTARGET TRUE)
	set(LIB_NAME "TP")
else()
	set(SERIALTARGET FALSE)
	set(LIB_NAME "TPmpi")
endif()


# String for tp-config
if(USE_FAPI)
  set(LIB_FC ${CMAKE_Fortran_COMPILER})
	set(LIB_FC_LD ${CMAKE_Fortran_COMPILER})

	if(${comp_kind} STREQUAL "FJ")
		set(LIB_FC_LD ${CMAKE_CXX_COMPILER})
	endif()
endif()


## Check header files

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



# Sub Directories

add_subdirectory(src)
add_subdirectory(doc)

if(TP_TEST)
  add_subdirectory(Examples)
endif()


# configure files
configure_file( config.h.in.cmake config.h )
configure_file( tp-config.in.cmake tp-config)
configure_file( include/tpVersion.h.in ${PROJECT_BINARY_DIR}/include/tpVersion.h)

# Install files
install(FILES  ${PROJECT_BINARY_DIR}/tp-config
        DESTINATION bin
        PERMISSIONS
        OWNER_READ
        OWNER_WRITE
        OWNER_EXECUTE
        GROUP_READ
        GROUP_EXECUTE
        WORLD_READ
        WORLD_EXECUTE)

install(FILES  ChangeLog.md
               Readme.md
               License.txt
        DESTINATION share)

# Installer
include (InstallRequiredSystemLibraries)

set (CPACK_PACKAGE_NAME "${PROJECT}")
set (CPACK_PACKAGE_VENDOR "RIIT")

set (CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set (CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "Light-weight text parsing library")
set (CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/License.txt")
set (CPACK_RESOURCE_FILE_README  "${PROJECT_SOURCE_DIR}/Readme.md")

set (CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")
set (CPACK_SOURCE_GENERATOR "TGZ;ZIP")

# config for source installer
set (CPACK_SOURCE_OUTPUT_CONFIG_FILE "${PROJECT_BINARY_DIR}/CPackSourceConfig.cmake")

set (CPACK_SOURCE_IGNORE_FILES "/BUILD/;/.git/;.#;/#;/.DS_Store" CACHE STRING "CPACK will ignore this files" )

# config for binary installer
#set (CPACK_OUTPUT_CONFIG_FILE "${PROJECT_BINARY_DIR}/CPackConfig.cmake")

include (CPack)

###
