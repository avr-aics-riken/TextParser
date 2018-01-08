###################################################################################
#
# TextParser - Text Parsing Library
#
# Copyright (c) 2012-2014 Institute of Industrial Science, The University of Tokyo.
# All rights reserved.
#
# Copyright (c) 2014-2016 Advanced Institute for Computational Science, RIKEN.
# All rights reserved.
#
# Copyright (c) 2016-2018 Research Institute for Information Technology, Kyushu University.
# All rights reserved.
#
#
###################################################################################


#message("Examples : " )
#message("         : PROJECT_BINARY_DIR = " ${PROJECT_BINARY_DIR})
#message("         : PROJECT_SOURCE_DIR = " ${PROJECT_SOURCE_DIR})
#message("         : enable_fapi        = " ${enable_fapi})
#message("         : enable_test        = " ${enable_test})
#message("         : with_MPI           = " ${with_MPI})
#message("         : IMPLICIT_LINK_LIBS = " ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
#message("         : CMAKE_EXE_LINKER_FLAGS = " ${CMAKE_EXE_LINKER_FLAGS})

include_directories(${PROJECT_BINARY_DIR}/include ${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_BINARY_DIR}/src)



# Test for MPI
if(with_MPI)

##### cpp
add_executable(Example3_cpp_mpi Example3_cpp_mpi.cpp)
target_link_libraries(Example3_cpp_mpi -lTPmpi)
set (test_parameters -np 4 "Example3_cpp_mpi")
add_test(NAME test_cpp_mpi_3
         COMMAND "mpirun" ${test_parameters})

add_executable(Example3-1_cpp_mpi Example3-1_cpp_mpi.cpp)
target_link_libraries(Example3-1_cpp_mpi -lTPmpi)
set (test_parameters -np 4 "Example3-1_cpp_mpi")
add_test(NAME test_cpp_mpi_3-1
         COMMAND "mpirun" ${test_parameters})

# Test for Serial
else(with_MPI)

##### cpp
add_executable(Example1_cpp Example1_cpp.cpp)
target_link_libraries(Example1_cpp -lTP)
add_test(test_cpp_1 Example1_cpp)

##
add_executable(Example2_cpp Example2_cpp.cpp)
target_link_libraries(Example2_cpp -lTP)
add_test(test_cpp_2 Example2_cpp)

##
add_executable(Example3_cpp Example3_cpp.cpp)
target_link_libraries(Example3_cpp -lTP)
add_test(test_cpp_3 Example3_cpp)

##
add_executable(Example4_cpp Example4_cpp.cpp)
target_link_libraries(Example4_cpp -lTP)
add_test(test_cpp_4 Example4_cpp)

##
add_executable(Example5_cpp Example5_cpp.cpp)
target_link_libraries(Example5_cpp -lTP)
add_test(test_cpp_5 Example5_cpp)

##
add_executable(Example6_cpp Example6_cpp.cpp)
target_link_libraries(Example6_cpp -lTP)
add_test(test_cpp_6 Example6_cpp)

##
add_executable(Example7_cpp Example7_cpp.cpp)
target_link_libraries(Example7_cpp -lTP)
add_test(test_cpp_7 Example7_cpp)

##
add_executable(Example8_cpp Example8_cpp.cpp)
target_link_libraries(Example8_cpp -lTP)
add_test(test_cpp_8 Example8_cpp)

##### C

add_executable(Example1_c Example1_c.c)
target_link_libraries(Example1_c -lTP)
set_target_properties(Example1_c PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Example1_c ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
add_test(test_c_1 Example1_c)

##
add_executable(Example2_c Example2_c.c)
target_link_libraries(Example2_c -lTP)
set_target_properties(Example2_c PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Example2_c ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
add_test(test_c_2 Example2_c)

##
add_executable(Example3_c Example3_c.c)
target_link_libraries(Example3_c -lTP)
set_target_properties(Example3_c PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Example3_c ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
add_test(test_c_3 Example3_c)

##
add_executable(Example4_c Example4_c.c)
target_link_libraries(Example4_c -lTP)
set_target_properties(Example4_c PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Example4_c ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
add_test(test_c_4 Example4_c)

##
add_executable(Example5_c Example5_c.c)
target_link_libraries(Example5_c -lTP)
set_target_properties(Example5_c PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Example5_c ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
add_test(test_c_5 Example5_c)

##
add_executable(Example7_c Example7_c.c)
target_link_libraries(Example7_c -lTP)
set_target_properties(Example7_c PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Example7_c ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
add_test(test_c_7 Example7_c)

##### Fortran

if(enable_fapi)

##
add_executable(Example1_f90 Example1_f90.f90)

# Intel / PGI compilerはfortran compilerを使う
if(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  #
elseif(CMAKE_Fortran_COMPILER_ID STREQUAL "PGI")
  #
else()
  set_target_properties(Example1_f90 PROPERTIES LINKER_LANGUAGE CXX)
endif()

# リンクはTP_fapiを先に
target_link_libraries(Example1_f90 -lTP_fapi)
target_link_libraries(Example1_f90 -lTP)

# Fujitsuの場合 --linkfortranは必須
if(USE_F_TCS STREQUAL "YES")
  target_link_libraries(Example1_f90 ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES} "--linkfortran")
else()
  target_link_libraries(Example1_f90 ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
endif()

add_test(test_f90_1 Example1_f90)

##
add_executable(Example2_f90 Example2_f90.f90)
if(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  #
elseif(CMAKE_Fortran_COMPILER_ID STREQUAL "PGI")
  #
else()
  set_target_properties(Example2_f90 PROPERTIES LINKER_LANGUAGE CXX)
endif()
target_link_libraries(Example2_f90 -lTP_fapi)
target_link_libraries(Example2_f90 -lTP)

if(USE_F_TCS STREQUAL "YES")
  target_link_libraries(Example2_f90 ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES} "--linkfortran")
else()
  target_link_libraries(Example2_f90 ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
endif()

add_test(test_f90_2 Example2_f90)

##

add_executable(Example3_f90 Example3_f90.f90)
if(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  #
elseif(CMAKE_Fortran_COMPILER_ID STREQUAL "PGI")
  #
else()
  set_target_properties(Example3_f90 PROPERTIES LINKER_LANGUAGE CXX)
endif()
target_link_libraries(Example3_f90 -lTP_fapi)
target_link_libraries(Example3_f90 -lTP)

if(USE_F_TCS STREQUAL "YES")
  target_link_libraries(Example3_f90 ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES} "--linkfortran")
else()
  target_link_libraries(Example3_f90 ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
endif()

add_test(test_f90_3 Example3_f90)

##
add_executable(Example4_f90 Example4_f90.f90)
if(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  #
elseif(CMAKE_Fortran_COMPILER_ID STREQUAL "PGI")
  #
else()
  set_target_properties(Example4_f90 PROPERTIES LINKER_LANGUAGE CXX)
endif()
target_link_libraries(Example4_f90 -lTP_fapi)
target_link_libraries(Example4_f90 -lTP)

if(USE_F_TCS STREQUAL "YES")
  target_link_libraries(Example4_f90 ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES} "--linkfortran")
else()
  target_link_libraries(Example4_f90 ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
endif()

add_test(test_f90_4 Example4_f90)

##
add_executable(Example5_f90 Example5_f90.f90)
if(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  #
elseif(CMAKE_Fortran_COMPILER_ID STREQUAL "PGI")
  #
else()
  set_target_properties(Example5_f90 PROPERTIES LINKER_LANGUAGE CXX)
endif()
target_link_libraries(Example5_f90 -lTP_fapi)
target_link_libraries(Example5_f90 -lTP)

if(USE_F_TCS STREQUAL "YES")
  target_link_libraries(Example5_f90 ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES} "--linkfortran")
else()
  target_link_libraries(Example5_f90 ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
endif()

add_test(test_f90_5 Example5_f90)

##
add_executable(Example7_f90 Example7_f90.f90)
if(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  #
elseif(CMAKE_Fortran_COMPILER_ID STREQUAL "PGI")
  #
else()
  set_target_properties(Example7_f90 PROPERTIES LINKER_LANGUAGE CXX)
endif()
target_link_libraries(Example7_f90 -lTP_fapi)
target_link_libraries(Example7_f90 -lTP)

if(USE_F_TCS STREQUAL "YES")
  target_link_libraries(Example7_f90 ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES} "--linkfortran")
else()
  target_link_libraries(Example7_f90 ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
endif()

add_test(test_f90_7 Example7_f90)


endif(enable_fapi)

endif(with_MPI)
