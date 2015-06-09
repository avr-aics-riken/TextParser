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

SUBDIRS = @MAKE_SUB_DIRS@

bin_SCRIPTS    = tp-config
CLEANFILES     = $(bin_SCRIPTS)
EXTRA_DIST     = tp-config.in LICENSE Makefile_hand BUILD_DIR/.gitkeep \
                 Examples Doxyfile Makefile_doxygen python_api
dist_data_DATA = AUTHORS COPYING ChangeLog README LICENSE

clean-local:
	find ./ -name *.obj | xargs rm -f
	find ./ -name *.exe | xargs rm -f
	find ./ -name *.lib | xargs rm -f

distclean-local: clean-local
	rm -f ./bin/*
	rm -f ./lib/*

