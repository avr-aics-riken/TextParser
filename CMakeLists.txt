###################################################################################
#
# TextParser - Text Parsing Library
#
# Copyright (C) 2012-2014 Institute of Industrial Science, The University of
# Tokyo.
# All rights reserved.
#
###################################################################################
#
#-*- CMAKE -*-#
# Process this file with cmake to produce a configure script.

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

ENABLE_LANGUAGE(CXX C)

PROJECT(TextParser)

# TextParser install dir.
message(CMAKE_INSTALL_PREFIX: "${CMAKE_INSTALL_PREFIX}")
set(TP_DIR "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}")
message("TextParser install dir : ${TP_DIR}")


# BUILD_TYPE (/Release/Debug/MinSizeRel/RelwithDebInfo)
#SET(CMAKE_BUILD_TYPE RELEASE) #shファイルに記載


# BUILD OPTION
IF(comp_type STREQUAL intel)
	SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
ELSEIF(comp_type STREQUAL fx)
	SET(CMAKE_CXX_FLAGS_RELEASE "-Kfast,ocl,preex,simd=2,uxsimd,array_private,parallel,openmp,optmsg=2 -V -Nsrc -x0")
ELSEIF(comp_type STREQUAL win)
	SET(CMAKE_CXX_FLAGS_RELEASE "/MD")
ELSEIF(comp_type STREQUAL gnu)
	SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
ENDIF()

# Exam.(if.CMAKE_BUILD_TYPE=Debug)
#SET(CMAKE_C_FLAGS_DEBUG "")

ADD_DEFINITIONS(-DHAVE_CONFIG_H)

# Version info.
SET(VERSION "1.6.6")
SET(${PROJECT_NAME}_MAJOR_VERSION 1)
SET(${PROJECT_NAME}_MINOR_VERSION 6)
SET(${PROJECT_NAME}_PATCH_LEVEL 6)
set(PACKAGE_VERSION ${VERSION})


# Revision No.
SET(TP_REVISION "20160706_1200")

# configure files
configure_file( config.h.in.cmake config.h )
configure_file( tp-config.in.cmake tp-config)
configure_file( include/tpVersion.h.in ${PROJECT_BINARY_DIR}/include/tpVersion.h)

# DIR_name
SET(TP TextParser)

#Fortran
SET(F90 ${TMP_F90})
SET(FC ${F90})


SET(CMAKE_Fortran_COMPILER "${F90}")
SET(CMAKE_Fortran_FLAGS_RELEASE "-O3")
SET(F90FLAGS "${CMAKE_Fortran_FLAGS_RELEASE}")
SET(FCFLAGS ${F90FLAGS})


#Compiler Type / Message

IF(comp STREQUAL INTEL)

	MESSAGE("Compiler INTEL")

ELSEIF(comp STREQUAL FJ)

	MESSAGE("Compiler FJ")

ELSEIF(comp STREQUAL GNU)
	
	MESSAGE("Compiler GNU")

ELSEIF(comp STREQUAL none)
	
	MESSAGE("Specify Compiler none")

ENDIF()


#Fortran API
OPTION(enable_fapi "Turn on Fortran API" OFF)

IF(enable_fapi STREQUAL ON)

	SET(enable_fapi yes)

	MESSAGE("Fortran API ON.")
ELSE()

	SET(enable_fapi no)

	MESSAGE("Fortran API OFF. If turn on fortran API, '-Denable_fapi=yes'
option.")
ENDIF()

#MPI setting

#SET(TMP_CXX mpicxx) #install_intel.shに記述
#SET(CXX ${TMP_CXX}) #ここに記述がなくても[cmake -DCXX=mpicxx]で可能

SET(TP_CXX ${CXX})
SET(CMAKE_CXX_COMPILER "${CXX}")

IF(${TP_CXX} STREQUAL mpicxx)
	SET(enable_mpi "wrappermpi")
	MESSAGE("CMAKE_CXX_COMPILER=mpicxx")

ELSEIF(${TP_CXX} STREQUAL mpicc)
  SET(enable_mpi "wrappermpi")
  MESSAGE("CMAKE_CXX_COMPILER=mpicc")

ELSEIF(${TP_CXX} STREQUAL mpiCC)
  SET(enable_mpi "wrappermpi")
  MESSAGE("CMAKE_CXX_COMPILER=mpiCC")

ELSEIF(${TP_CXX} STREQUAL mpic++)
  SET(enable_mpi "wrappermpi")
  MESSAGE("CMAKE_CXX_COMPILER=mpic++")

ELSEIF(${TP_CXX} STREQUAL mpiFCCpx)
  SET(enable_mpi "wrappermpi")
  MESSAGE("CMAKE_CXX_COMPILER=mpiFCCpx")

ELSEIF(${TP_CXX} STREQUAL CC)
  SET(enable_mpi "wrappermpi")
  MESSAGE("CMAKE_CXX_COMPILER=CC")

ELSE()
	SET(enable_mpi "none")

ENDIF()


#OpenMPI setting // '-Dopmi=set_openMPI' '-Dwith_ompi=dir' option.
IF(enable_mpi STREQUAL none)
	IF(with_ompi)
 		SET(MPICH_DIR ${with_ompi})
	 	SET(MPICH_CFLAGS ${MPICH_DIR}/include)
 		SET(MPICH_LDFLAGS ${MPICH_DIR}/lib)
		SET(enable_mpi ${ompi})
		
		MESSAGE(STATUS "OpenMPI setting ${ompi}")
	elseif(with_msmpi)
        SET(MPICH_DIR ${with_msmpi})
	 	SET(MPICH_CFLAGS ${MPICH_DIR}/include)
 		SET(MPICH_LDFLAGS ${MPICH_DIR}/lib)
		SET(enable_mpi "msmpi")
 		
 		MESSAGE(STATUS "MSMPI setting")
	ELSE()
 		SET(with_ompi none)
	ENDIF()
ENDIF()


if(with_msmpi)
    SET(MPICH_DIR ${with_msmpi})
 	SET(MPICH_CFLAGS ${MPICH_DIR}/include)
	SET(MPICH_LDFLAGS ${MPICH_DIR}/lib)
	SET(enable_mpi "msmpi")
endif()
message("enable_mpi : ${enable_mpi}")


# MPI Library for fortran
IF(comp STREQUAL FJ)

	IF(host STREQUAL sparc*)
		SET(MPICH_FCLIBS "${MPICH_FCLIBS} ${MPICH_LIBS} libmpi_f77.a libmpi_f90.a")
	ENDIF()

ELSEIF(enable_mpi STREQUAL ompi)
	SET(MPICH_LIBS "${MPICH_LIBS} libmpi.a")
	SET(MPICH_FCLIBS "${MPICH_FCLIBS} ${MPICH_LIBS} libmpi_f77.a libmpi_f90.a")

ENDIF()


# warning
IF(NOT enable_mpi STREQUAL wrappermpi)
	IF(ompi STREQUAL none)
		Message("Warning:OpenMPI library is not specified.")
	  Message("If compilation error occurs about MPI,specify '-Dompi''-Dwith_ompi' option.")
	ENDIF()
ENDIF()


# default prefix setting
# コンパイルオプション[CMAKE_INSTALL_PREFIX]にて指定


# Special flags

IF(enable_mpi STREQUAL none)
	SET(SERIALTARGET TRUE)
#	SET(TP_LIBS "libTP.a")
	SET(TP_LIB "TP")
ELSE()
	SET(SERIALTARGET FALSE)
#	SET(TP_LIBS "libTPmpi.a")
	SET(TP_LIB "TPmpi")
ENDIF()

#SET(TP_CFLAGS "${CMAKE_INSTALL_PREFIX}/include")
#SET(TP_LDFLAGS "${CMAKE_INSTALL_PREFIX}/lib")

SET(TP_FC ${FC})

IF(enable_fapi STREQUAL yes)
	SET(TP_FC_LD ${FC})
	IF(${COMP} STREQUAL FJ)
		SET(TP_FC_LD ${CXX})
	ENDIF()
ENDIF()



##Checks for header files.
#-----------------------------------------------------------------
INCLUDE(CheckIncludeFiles)


CHECK_INCLUDE_FILES(inttypes.h HAVE_INTTYPES_H)
CHECK_INCLUDE_FILES(memory.h HAVE_MEMORY_H)
CHECK_INCLUDE_FILES(stdint.h HAVE_STDINT_H)
CHECK_INCLUDE_FILES(stdlib.h HAVE_STDLIB_H)
CHECK_INCLUDE_FILES(strings.h HAVE_STRINGS_H)
CHECK_INCLUDE_FILES(string.h HAVE_STRING_H)
CHECK_INCLUDE_FILES(sys/stat.h HAVE_SYS_STAT_H)
CHECK_INCLUDE_FILES(sys/types.h HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILES(unistd.h HAVE_UNISTD_H)


SET(EXTRA_DIST "${EXTRA_DIST} tp-config.in LICENSE Makefile_hand Examples
Doxyfile Makefile_doxygen")

SET(dist_data_DATA "${dist_data_DATA} AUTHOR COPYING ChangeLig
Makefile_doxyagen")


# MAKE_SUB_DIRS

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(doc)

# install files 

INSTALL(FILES  ${PROJECT_BINARY_DIR}/tp-config DESTINATION ${TP}/bin PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

INSTALL(FILES  AUTHORS COPYING ChangeLog README LICENSE DESTINATION
${TP}/share)

###