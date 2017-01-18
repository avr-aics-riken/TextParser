#!/bin/bash

prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=@CMAKE_INSTALL_PREFIX@
includedir=@CMAKE_INSTALL_PREFIX@/include
libdir=@CMAKE_INSTALL_PREFIX@/lib

usage()
{
    cat <<EOF

Usage: tp-config [OPTION]

Known values for OPTION are:

  --cxx       print C++ compiler command
  --cflags    print C/C++ pre-processor and compiler flags
  --fc        print Fortran90 compiler command
  --fcflags   print Fortran90 pre-processor and compiler flags
  --fclibs    print library linking information for Fortran90 program
  --fclink    print Fortran90 program linker command
  --libs      print library linking information for C++ program
  --help      display this help and exit
  --version   output version information

EOF

    exit $1
}

if test $# -eq 0; then
    usage 1
fi

cflags=false
libs=false

while test $# -gt 0; do
    case "$1" in
    -*=*) optarg=`echo "$1" | sed 's/[-_a-zA-Z0-9]*=//'` ;;
    *) optarg= ;;
    esac

    case "$1" in
    --version)
cat <<EOF

TextParser : Text Parser Library  Version : @PACKAGE_VERSION@ : @LIB_REVISION@

Copyright (C) 2012-2015 Institute of Industrial Science, The University of Tokyo.
All rights reserved.

Copyright (c) 2014-2016 Advanced Institute for Computational Science, RIKEN.
All rights reserved.

Copyright (c) 2016-2017 Research Institute for Information Technology, Kyushu University.
All rights reserved.

EOF
      exit 0
      ;;

    --help)
      usage 0
      ;;

    --cxx)
      echo @CMAKE_CXX_COMPILER@
      ;;

    --cflags)
      echo -I@CMAKE_INSTALL_PREFIX@/include
      ;;

    --fc)
      echo @LIB_FC@
      ;;

    --fclink)
      echo @LIB_FC_LD@
      ;;

    --fcflags)
      echo -I@CMAKE_INSTALL_PREFIX@/include
      ;;

    --fclibs)
      echo -L@CMAKE_INSTALL_PREFIX@/lib -l@LIB_NAME@
      ;;

    --libs)
      echo -L@CMAKE_INSTALL_PREFIX@/lib -l@LIB_NAME@
      ;;

    *)
      usage
      exit 1
      ;;
    esac
    shift
done

exit 0
