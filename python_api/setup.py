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



