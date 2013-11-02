###################################################################################
#
# TextParser - Text Parsing Library
#
# Copyright (C) 2012-2013 Institute of Industrial Science, The University of Tokyo.
# All rights reserved.
#
###################################################################################
#

SUBDIRS = @MAKE_SUB_DIRS@

bin_SCRIPTS    = tp-config
CLEANFILES     = $(bin_SCRIPTS)
EXTRA_DIST     = tp-config.in LICENSE Makefile_hand \
                 Examples Doxyfile Makefile_doxygen
dist_data_DATA = AUTHORS COPYING ChangeLog README LICENSE

clean-local:
	find ./ -name *.obj | xargs rm -f
	find ./ -name *.exe | xargs rm -f
	find ./ -name *.lib | xargs rm -f

distclean-local: clean-local
	rm -f ./bin/*
	rm -f ./lib/*

