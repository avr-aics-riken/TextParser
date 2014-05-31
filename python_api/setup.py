###################################################################################
#
# TextParser - Text Parsing Library
#
# Copyright (C) 2012-2014 Institute of Industrial Science, The University of Tokyo.
# All rights reserved.
#
# Copyright (c) 2014 Advanced Institute for Computational Science, RIKEN.
# All rights reserved.
#
###################################################################################
#

from distutils.core import setup, Extension

module=Extension('TextParser', ['TextParser_python_api.cpp',
                          '../src/TextParser.cpp',
                          '../src/TextParserElement.cpp',
                          '../src/TextParserTree.cpp'],
                  include_dirs=['../include'],undef_macros=["HAVE_CONFIG_H"]) 
setup(name='TextParser',
        version='1.0',
        description='python wrapper for TextParser',
        ext_modules = [module])



