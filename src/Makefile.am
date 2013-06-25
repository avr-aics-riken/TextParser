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

lib_LIBRARIES = libMPITP.a libTP.a

#libTP_fapi.a


libTP_a_SOURCES  = TextParser.cpp TextParserElement.cpp TextParserTree.cpp
libTP_a_CXXFLAGS = -I$(top_builddir)/include

libMPITP_a_SOURCES  = TextParser.cpp TextParserElement.cpp TextParserTree.cpp
libMPITP_a_CXXFLAGS = @MPICH_CFLAGS@ -I$(top_builddir)/include

#libTP_fapi_a_SOURCES  = TextParser_fapi.f90
#libTP_fapi_a_CXXFLAGS = @MPICH_CFLAGS@ -I$(top_builddir)/include

libTP_a_includedir = $(includedir)
libTP_a_include_HEADERS = \
  $(top_builddir)/include/TextParser.h \
  $(top_builddir)/include/TextParserCommon.h \
  $(top_builddir)/include/TextParserElement.h \
  $(top_builddir)/include/TextParserTree.h \
  $(top_builddir)/include/TextParser.inc


