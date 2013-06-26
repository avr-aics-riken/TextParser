###################################################################################
#
# TextParser - Text Parsing Library
#
# Copyright (C) 2012-2013 Institute of Industrial Science, The University of Tokyo.
# All rights reserved.
#
###################################################################################
#

EXTRA_DIST=TextParser_fapi.f90

if SERIALTARGET
  lib_LIBRARIES = libTP.a
  libTP_a_SOURCES  = TextParser.cpp TextParserElement.cpp TextParserTree.cpp
  libTP_a_CXXFLAGS = -I$(top_builddir)/include
else
  lib_LIBRARIES = libMPITP.a
  libMPITP_a_SOURCES  = TextParser.cpp TextParserElement.cpp TextParserTree.cpp
  libMPITP_a_CXXFLAGS = @MPICH_CFLAGS@ -I$(top_builddir)/include
endif


#libTP_fapi_a_SOURCES  = TextParser_fapi.f90
#libTP_fapi_a_CXXFLAGS = @MPICH_CFLAGS@ -I$(top_builddir)/include


nobase_include_HEADERS = \
  $(top_builddir)/include/TextParser.h \
  $(top_builddir)/include/TextParserCommon.h \
  $(top_builddir)/include/TextParserElement.h \
  $(top_builddir)/include/TextParserTree.h \
  $(top_builddir)/include/TextParser.inc


