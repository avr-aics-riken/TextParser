###################################################################################
#
# TextParser - Text Parsing Library
#
# Copyright (C) 2012-2014 Institute of Industrial Science, The University of
# Tokyo.
# All rights reserved.
#
# Copyright (c) 2014-2016 Advanced Institute for Computational Science, RIKEN.
# All rights reserved.
#
# Copyright (c) 2016-2017 Research Institute for Information Technology, Kyushu University.
# All rights reserved.
#
#
###################################################################################

## テスト５はテスト自体の記述がおかしい？

include_directories(${PROJECT_BINARY_DIR}/include ${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_BINARY_DIR}/src)


##### cpp

add_executable(Example1_cpp Example1_cpp.cpp)
if(TP_BUILD_MPI)
  target_link_libraries(Example1_cpp -lTPmpi)
else()
  target_link_libraries(Example1_cpp -lTP)
endif()
add_test(test_cpp_1 Example1_cpp)
#add_test(test_cpp_1 Example1_cpp WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tmp)
##

add_executable(Example2_cpp Example2_cpp.cpp)
if(TP_BUILD_MPI)
  target_link_libraries(Example2_cpp -lTPmpi)
else()
  target_link_libraries(Example2_cpp -lTP)
endif()
add_test(test_cpp_2 Example2_cpp)

##

add_executable(Example3_cpp Example3_cpp.cpp)
if(TP_BUILD_MPI)
  target_link_libraries(Example3_cpp -lTPmpi)
else()
  target_link_libraries(Example3_cpp -lTP)
endif()
add_test(test_cpp_3 Example3_cpp)

##

if(TP_BUILD_MPI)
  add_executable(Example3_cpp_mpi Example3_cpp_mpi.cpp)
  target_link_libraries(Example3_cpp_mpi -lTPmpi)
  add_test(test_cpp_mpi_3 Example3_cpp_mpi)
endif()

##

if(TP_BUILD_MPI)
  add_executable(Example3-1_cpp_mpi Example3-1_cpp_mpi.cpp)
  target_link_libraries(Example3-1_cpp_mpi -lTPmpi)
  add_test(test_cpp_mpi_3-1 Example3-1_cpp_mpi)
endif()

##

add_executable(Example4_cpp Example4_cpp.cpp)
if(TP_BUILD_MPI)
  target_link_libraries(Example4_cpp -lTPmpi)
else()
  target_link_libraries(Example4_cpp -lTP)
endif()
add_test(test_cpp_4 Example4_cpp)

##

add_executable(Example5_cpp Example5_cpp.cpp)
if(TP_BUILD_MPI)
  target_link_libraries(Example5_cpp -lTPmpi)
else()
  target_link_libraries(Example5_cpp -lTP)
endif()
# add_test(test_cpp_5 Example5_cpp)

##

add_executable(Example6_cpp Example6_cpp.cpp)
if(TP_BUILD_MPI)
  target_link_libraries(Example6_cpp -lTPmpi)
else()
  target_link_libraries(Example6_cpp -lTP)
endif()
add_test(test_cpp_6 Example6_cpp)

##

add_executable(Example7_cpp Example7_cpp.cpp)
if(TP_BUILD_MPI)
  target_link_libraries(Example7_cpp -lTPmpi)
else()
  target_link_libraries(Example7_cpp -lTP)
endif()
add_test(test_cpp_7 Example7_cpp)

##

add_executable(Example8_cpp Example8_cpp.cpp)
if(TP_BUILD_MPI)
  target_link_libraries(Example8_cpp -lTPmpi)
else()
  target_link_libraries(Example8_cpp -lTP)
endif()
add_test(test_cpp_8 Example8_cpp)



##### C

add_executable(Example1_c Example1_c.c)
if(TP_BUILD_MPI)
  target_link_libraries(Example1_c -lTPmpi)
else()
  target_link_libraries(Example1_c -lTP)
endif()
target_link_libraries(Example1_c ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
add_test(test_c_1 Example1_c)

##

add_executable(Example2_c Example2_c.c)
if(TP_BUILD_MPI)
  target_link_libraries(Example2_c -lTPmpi)
else()
  target_link_libraries(Example2_c -lTP)
endif()
target_link_libraries(Example2_c ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
add_test(test_c_2 Example2_c)

##

add_executable(Example3_c Example3_c.c)
if(TP_BUILD_MPI)
  target_link_libraries(Example3_c -lTPmpi)
else()
  target_link_libraries(Example3_c -lTP)
endif()
target_link_libraries(Example3_c ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
add_test(test_c_3 Example3_c)

##

add_executable(Example4_c Example4_c.c)
if(TP_BUILD_MPI)
  target_link_libraries(Example4_c -lTPmpi)
else()
  target_link_libraries(Example4_c -lTP)
endif()
target_link_libraries(Example4_c ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
add_test(test_c_4 Example4_c)

##

add_executable(Example5_c Example5_c.c)
if(TP_BUILD_MPI)
  target_link_libraries(Example5_c -lTPmpi)
else()
  target_link_libraries(Example5_c -lTP)
endif()
target_link_libraries(Example5_c ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
add_test(test_c_5 Example5_c)

##

add_executable(Example7_c Example7_c.c)
if(TP_BUILD_MPI)
  target_link_libraries(Example7_c -lTPmpi)
else()
  target_link_libraries(Example7_c -lTP)
endif()
target_link_libraries(Example7_c ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
add_test(test_c_7 Example7_c)



##### Fortran

if(USE_FAPI)

  add_executable(Example1_f90 Example1_f90.f90)
  if(TP_BUILD_MPI)
    target_link_libraries(Example1_f90 -lTPmpi)
  else()
    target_link_libraries(Example1_f90 -lTP)
  endif()
  target_link_libraries(Example1_f90 -lTP_fapi ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
  add_test(test_f90_1 Example1_f90)

##

  add_executable(Example2_f90 Example2_f90.f90)
  if(TP_BUILD_MPI)
    target_link_libraries(Example2_f90 -lTPmpi)
  else()
    target_link_libraries(Example2_f90 -lTP)
  endif()
  target_link_libraries(Example2_f90 -lTP_fapi ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
  add_test(test_f90_2 Example2_f90)

##

  add_executable(Example3_f90 Example3_f90.f90)
  if(TP_BUILD_MPI)
    target_link_libraries(Example3_f90 -lTPmpi)
  else()
    target_link_libraries(Example3_f90 -lTP)
  endif()
  target_link_libraries(Example3_f90 -lTP_fapi ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
  add_test(test_f90_3 Example3_f90)

##

  add_executable(Example4_f90 Example4_f90.f90)
  if(TP_BUILD_MPI)
    target_link_libraries(Example4_f90 -lTPmpi)
  else()
    target_link_libraries(Example4_f90 -lTP)
  endif()
  target_link_libraries(Example4_f90 -lTP_fapi ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
  add_test(test_f90_4 Example4_f90)

##

  add_executable(Example5_f90 Example5_f90.f90)
  if(TP_BUILD_MPI)
    target_link_libraries(Example5_f90 -lTPmpi)
  else()
    target_link_libraries(Example5_f90 -lTP)
  endif()
  target_link_libraries(Example5_f90 -lTP_fapi ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
  # add_test(test_f90_5 Example5_f90)

##

  add_executable(Example7_f90 Example7_f90.f90)
  if(TP_BUILD_MPI)
    target_link_libraries(Example7_f90 -lTPmpi)
  else()
    target_link_libraries(Example7_f90 -lTP)
  endif()
  target_link_libraries(Example7_f90 -lTP_fapi ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})
  add_test(test_f90_7 Example7_f90)

endif()
