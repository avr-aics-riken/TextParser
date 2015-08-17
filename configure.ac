###################################################################################
#
# TextParser - Text Parsing Library
#
# Copyright (C) 2012-2015 Institute of Industrial Science, The University of Tokyo.
# All rights reserved.
#
# Copyright (c) 2014-2015 Advanced Institute for Computational Science, RIKEN.
# All rights reserved.
#
###################################################################################
#
#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.



AC_PREREQ([2.57])

AC_INIT([TextParser], [1.6.4], [keno@{riken,iis.u-tokyo.ac}.jp], [TextParser])

echo "----------------------------------------"
echo "Running TextParser Configure Script"
echo "----------------------------------------"

AC_CONFIG_SRCDIR([src/TextParser.cpp])


#
# Specify directory for auxillary build tools (e.g., install-sh, config.sub, config.guess) and M4 files.
#

AC_CONFIG_AUX_DIR(config)


#
# To prevent the source codes from breaking, we suppress to do configure in the source directory.
#

if test -e configure.ac ; then
echo "Please run configure from a separate build directory. It is not allowd to run configure in the source directory."
echo "Pleaes try ..."
echo " "
echo "$ cd BUILD_DIR"
echo "$ ../configure [options]"
exit
fi


#
# Configure should create config.h from config.h.in
#

AC_CONFIG_HEADERS([config.h])


#
# Use automake
#

AM_INIT_AUTOMAKE()


#
# revision No.
#
TP_REVISION="20150614_1430"
AC_SUBST(TP_REVISION)


#
# FORTRAN
#

FC=$F90
FCFLAGS=$F90FLAGS


#
# compiler
#
AC_ARG_WITH(comp, [AC_HELP_STRING([--with-comp=(INTEL|FJ|GNU)],[Specify Compiler type])], , with_comp=none)



#
# FORTRAN API
#
AC_ARG_ENABLE(fapi,
[  --enable-fapi    Turn on Fortran API [[default=no]]],
[case "${enableval}" in
  yes) enable_fapi=yes ;;
  no)  enable_fapi=no ;;
  *) AC_MSG_ERROR(bad value for --enable-fapi) ;;
esac],
enable_fapi=no)

# TP_FAPI is true, if measure timing
AC_SUBST(TP_FAPI)
AM_CONDITIONAL([TP_FAPI], [test x"${enable_fapi}" = x"yes"])




#
# MPI setting. wrappers like mpicxx, mpicc, mpiCC, mpiicpc, mpiicc, mpic++, mpiFCCpx are taking 
# into consideration, if not add in case.
#

enable_mpi="none"


TP_CXX="$CXX"
AC_SUBST(TP_CXX)

case "$TP_CXX" in
  mpicxx)   enable_mpi="wrappermpi" ;;
  mpicc)    enable_mpi="wrappermpi" ;;
  mpiicc)   enable_mpi="wrappermpi" ;;
  mpiicpc)  enable_mpi="wrappermpi" ;;
  mpiCC)    enable_mpi="wrappermpi" ;;
  mpic++)   enable_mpi="wrappermpi" ;;
  mpiFCCpx) enable_mpi="wrappermpi" ;;
  CC)       enable_mpi="wrappermpi" ;;
esac





#
# MPI environment
#
AC_SUBST(MPICH_DIR)
AC_SUBST(MPICH_CFLAGS)
AC_SUBST(MPICH_LDFLAGS)
AC_SUBST(MPICH_LIBS)
AC_SUBST(MPICH_FCLIBS)


#
# if wrapper compiler is specified, skip this part
#

if test x"$enable_mpi" = x"none" ; then

# OpenMPI // ompが指定されていれば変数をセット
  AC_ARG_WITH(ompi, [AC_HELP_STRING([--with-ompi=dir],[Specify OpenMPI install directory])], , with_ompi=none)

  if test x"$with_ompi" != x"none" ; then
    MPICH_DIR=$with_ompi;
    MPICH_CFLAGS=-I$MPICH_DIR/include
    MPICH_LDFLAGS=-L$MPICH_DIR/lib
    enable_mpi="ompi"
  fi

fi



#
# MPI Library for fortran
#

if test x"$with_comp" = x"FJ" ; then
  MPICH_LIBS=""
  case "$host" in
  sparc*)
    MPICH_FCLIBS="$MPICH_LIBS"" -lmpi_f77 -lmpi_f90"
    ;;
  esac
elif test x"$enable_mpi" = x"ompi" ; then
  MPICH_LIBS="-lmpi"
  MPICH_FCLIBS="$MPICH_LIBS"" -lmpi_f77 -lmpi_f90"
fi


# warning
#
if test x"$enable_mpi" != x"wrappermpi" ; then
  if test x"$with_ompi" = x"none" ; then
    echo "  Warning: OpenMPI library is not specified."
    echo "           If compilation error occurs about MPI, specify --with-ompi option."
  fi
fi



#
# default prefix setting
#
AC_PREFIX_DEFAULT([/usr/local/TextParser])
if test x"$prefix" = x"NONE" ; then
  TP_INST_DIR=/usr/local/TextParser
else
  TP_INST_DIR="$prefix"
fi



#
# example
#
#AC_ARG_WITH(example, [AC_HELP_STRING([--with-example=(no|yes)],[make example [no]])], , with_example=no)



#
# Special flags
#


if test x"$enable_mpi" = x"none" ; then
  TP_LIBS="-lTP"
else
  TP_LIBS="-lTPmpi"
fi
AC_SUBST(TP_LIBS)

# SERIALTARGET = true, if serial
AM_CONDITIONAL([SERIALTARGET], [test "$enable_mpi" = "none"])


TP_CFLAGS="-I$TP_INST_DIR/include"
AC_SUBST(TP_CFLAGS)

TP_LDFLAGS="-L$TP_INST_DIR/lib"
AC_SUBST(TP_LDFLAGS)

TP_FC="$FC"
AC_SUBST(TP_FC)


if test x"${enable_fapi}" = x"yes" ; then
  TP_FC_LD="$FC"
  if test "$with_comp" = "FJ"; then
    TP_FC_LD="$CXX"" --linkfortran"
  fi
  AC_SUBST(TP_FC_LD)
fi


#
# MAKE_SUB_DIRS
#
AC_SUBST(MAKE_SUB_DIRS)
MAKE_SUB_DIRS="src doc"

#if test "$with_example" = "yes" ; then
#  MAKE_SUB_DIRS="$MAKE_SUB_DIRS"" Examples"
#fi



#
# Checks for programs.
#
AC_PROG_CXX
AC_PROG_CC
AC_PROG_F77
AC_PROG_FC
AC_PROG_RANLIB


#
# Checks for libraries.
#



#
# Checks for header files.
#
AC_CHECK_HEADERS([stdlib.h string.h])



#
# Checks for typedefs, structures, and compiler characteristics.
#
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T


#
# Checks for library functions.
#
AC_CONFIG_FILES([ \
                 Makefile \
                 src/Makefile \
                 doc/Makefile \
                 tp-config
                 include/tpVersion.h \
                 ])

AC_OUTPUT

chmod +x ./tp-config

echo "---------------------------------------------"
echo "Finished Running TextParser Configure Script"
echo "---------------------------------------------"
