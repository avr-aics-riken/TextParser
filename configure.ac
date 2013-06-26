###################################################################################
#
# TextParser - Text Parsing Library
#
# Copyright (C) 2012-2013 Institute of Industrial Science, The University of Tokyo.
# All rights reserved.
#
###################################################################################
#
#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([TextParser], [1.3.2], [keno@iis.u-tokyo.ac.jp], [TextParser])
AM_INIT_AUTOMAKE()
AC_CONFIG_SRCDIR([src/TextParser.cpp])
AC_CONFIG_HEADERS([config.h])


#
# revision No.
#
TP_REVISION="20130626_2300"
AC_SUBST(TP_REVISION)


#
# platform
#
TP_DEVICE="$($SHELL ./tp-uname)"
AC_SUBST(TP_DEVICE)



#
# FORTRAN API
#
#AC_ARG_WITH(fapi, [AC_HELP_STRING([--with-fapi=(no|yes)],[Specify fortran api mode])], , with_fapi=no)
#AC_SUBST(TP_FAPI)
#if test "$with_fapi" = "enable" ; then
#  TP_FAPI=
#else
#  TP_FAPI=
#fi



#
# compiler libs
#
AC_ARG_WITH(comp, [AC_HELP_STRING([--with-comp=(INTEL|FJ)],[Specify Compiler type])], , with_comp=none)
AC_SUBST(COMPILER_LIBS)
case "$with_comp" in
"INTEL")
  COMPILER_LIBS="-lifport -lifcore"
  ;;
"FJ")
  COMPILER_LIBS="--linkfortran"
  ;;
esac

enable_mpi="none"



#
# MPICH environment
#
AC_SUBST(MPICH_DIR)
AC_SUBST(MPICH_CFLAGS)
AC_SUBST(MPICH_LDFLAGS)
AC_SUBST(MPICH_LIBS)
AC_SUBST(MPICH_FCLIBS)
AC_ARG_WITH(mpich, [AC_HELP_STRING([--with-mpich=dir],[Specify MPICH install directory])], , with_mpich=none)
if test "$with_mpich" != "none" ; then
  MPICH_DIR=$with_mpich;
  MPICH_CFLAGS=-I$MPICH_DIR/include
  MPICH_LDFLAGS=-L$MPICH_DIR/lib
  enable_mpi="mpich"
fi

#
# OpenMPI environment
#
if test "$with_mpich" = "none" ; then
  AC_ARG_WITH(ompi, [AC_HELP_STRING([--with-ompi=dir],[Specify OpenMPI install directory])], , with_ompi=none)
  if test "$with_ompi" != "none" ; then
    MPICH_DIR=$with_ompi;
    MPICH_CFLAGS=-I$MPICH_DIR/include
    MPICH_LDFLAGS=-L$MPICH_DIR/lib
    enable_mpi="ompi"
  fi
fi



#
# MPI Library
#
if test "$with_comp" = "FJ" ; then
  MPICH_LIBS=""
  case "$host" in
  sparc*)
    MPICH_FCLIBS="$MPICH_LIBS"" -lmpi_f77 -lmpi_f90"
    ;;
  esac
elif test "$enable_mpi" = "mpich" ; then
  MPICH_LIBS="-lmpich"
  MPICH_FCLIBS="$MPICH_LIBS"" -lfmpich"
  case "$CPM_DEVICE" in
  "Lion"|"Snow_Leopard"|"Leopard"|"Mountain_Lion")
    ;;
  esac
elif test "$enable_mpi" = "ompi" ; then
  MPICH_LIBS="-lmpi"
  MPICH_FCLIBS="$MPICH_LIBS"" -lmpi_f77 -lmpi_f90"
  case "$CPM_DEVICE" in
  "Lion"|"Snow_Leopard"|"Leopard"|"Mountain_Lion")
    ;;
  esac
fi

if test "$enable_mpi" = "none" ; then
  echo "  Warning: Neither MPICH nor OpenMPI library is not specified."
  echo "           If compilation error occurs about MPI, specify --with-mpich or --with-ompi option."
fi



#
# default prefix setting
#
AC_PREFIX_DEFAULT([/usr/local/TextParser])
if test "$prefix" = "NONE" ; then
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
TP_CFLAGS="-I$TP_INST_DIR/include"
AC_SUBST(TP_CFLAGS)

TP_LDFLAGS="-L$TP_INST_DIR/lib"
AC_SUBST(TP_LDFLAGS)


if test "$enable_mpi" = "none" ; then
  TP_LIBS="-lTP"
else
  TP_LIBS="-lMPITP"
fi
AC_SUBST(TP_LIBS)

# SERIALTARGET = true, if serial
AM_CONDITIONAL([SERIALTARGET], [test "$enable_mpi" = "none"])


TP_CXX="$CXX"
AC_SUBST(TP_CXX)

TP_FC="$FC"
AC_SUBST(TP_FC)

TP_FC_LD="$FC"
if test "$with_comp" = "FJ"; then
  TP_FC_LD="$CXX"" --linkfortran"
else
  TP_LIBS="$TP_LIBS"" -lstdc++"
fi
AC_SUBST(TP_FC_LD)


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
AC_CHECK_HEADER_STDBOOL
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
                 ])

AC_OUTPUT

chmod +x ./tp-config

