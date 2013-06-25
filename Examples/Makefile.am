SUBDIRS = tpp_examples
EXTRA_DIST=Makefile_hand

if MPI
MPIPROGRAMS=Example3_cpp_mpi Example3-1_cpp_mpi
Example3_cpp_mpi_SOURCES=Example3_cpp_mpi.cpp
Example3_1_cpp_mpi_SOURCES=Example3-1_cpp_mpi.cpp
Example3_cpp_mpi_LDADD= -lstdc++ -L../lib -lTextParser_mpi
Example3_1_cpp_mpi_LDADD= -lstdc++ -L../lib -lTextParser_mpi
else
MPIPROGRAMS=
endif
if FORTRAN
FORTRANPROGRAMS= Example1_f90 Example2_f90 Example3_f90 Example4_f90 Example5_f90
Example1_f90_SOURCES=Example1_f90.f90
Example2_f90_SOURCES=Example2_f90.f90
Example3_f90_SOURCES=Example3_f90.f90
Example4_f90_SOURCES=Example4_f90.f90
Example5_f90_SOURCES=Example5_f90.f90
Example1_f90_LDADD=  -lstdc++ -L../lib -lTextParser -lTextParser_f90api
Example2_f90_LDADD=  -lstdc++ -L../lib -lTextParser -lTextParser_f90api
Example3_f90_LDADD=  -lstdc++ -L../lib -lTextParser -lTextParser_f90api
Example4_f90_LDADD=  -lstdc++ -L../lib -lTextParser -lTextParser_f90api
Example5_f90_LDADD=  -lstdc++ -L../lib -lTextParser -lTextParser_f90api
Example1_f90.o:../include/TextParser.inc ../lib/libTextParser.la ../lib/libTextParser_f90api.la
Example2_f90.o:../include/TextParser.inc ../lib/libTextParser.la ../lib/libTextParser_f90api.la
Example3_f90.o:../include/TextParser.inc ../lib/libTextParser.la ../lib/libTextParser_f90api.la
Example4_f90.o:../include/TextParser.inc ../lib/libTextParser.la ../lib/libTextParser_f90api.la
Example5_f90.o:../include/TextParser.inc ../lib/libTextParser.la ../lib/libTextParser_f90api.la
else
FORTRANPROGRAMS=
endif


noinst_PROGRAMS=Example1_cpp Example2_cpp Example3_cpp Example4_cpp \
Example5_cpp Example6_cpp \
Example1_c Example2_c Example3_c Example4_c Example5_c \
${FORTRANPROGRAMS} ${MPIPROGRAMS}

# Example3_cpp_mpi_newAPI

#Example_f90_tmp Example_tmp Example_tmp2 
# Example_c_tmp

DISTCLEANFILES=*~
#CLEANFILES=Output*.txt nodq/Output*.txt

LDADD=-L../lib -lTextParser -lstdc++
CXXFLAGS=-I../include
CFLAGS=-I../include
FCFLAGS=-I../include

Example1_cpp_SOURCES=Example1_cpp.cpp
Example1_c_SOURCES=Example1_c.c
Example2_cpp_SOURCES=Example2_cpp.cpp
Example2_c_SOURCES=Example2_c.c
Example3_cpp_SOURCES=Example3_cpp.cpp
Example3_c_SOURCES=Example3_c.c
Example4_cpp_SOURCES=Example4_cpp.cpp
Example4_c_SOURCES=Example4_c.c

Example5_cpp_SOURCES=Example5_cpp.cpp
Example5_c_SOURCES=Example5_c.c
Example6_cpp_SOURCES=Example6_cpp.cpp

#Example3_cpp_mpi_newAPI_SOURCES=Example3_cpp_mpi_newAPI.cpp

#Example_f90_tmp_SOURCES=Example_f90_tmp.f90

#Example_f90_tmp_LDADD=-L../lib -lstdc++ -lTextParser -lTextParser_f90api

#Example3_cpp_mpi_newAPI_LDADD= -lstdc++ -L../lib -lTextParser -lTextParser_mpi


Example1_cpp.o:../include/TextParser.h ../lib/libTextParser.la
Example2_cpp.o:../include/TextParser.h ../lib/libTextParser.la
Example3_cpp.o:../include/TextParser.h ../lib/libTextParser.la
Example4_cpp.o:../include/TextParser.h ../lib/libTextParser.la
Example5_cpp.o:../include/TextParser.h ../lib/libTextParser.la

Example1_c.o:../include/TextParser.h ../lib/libTextParser.la
Example2_c.o:../include/TextParser.h ../lib/libTextParser.la
Example3_c.o:../include/TextParser.h ../lib/libTextParser.la
Example4_c.o:../include/TextParser.h ../lib/libTextParser.la
Example5_c.o:../include/TextParser.h ../lib/libTextParser.la



.PHONY: