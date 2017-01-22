set(CMAKE_SYSTEM_NAME Linux)

include(CMakeForceCompiler)

if(with_MPI)
  CMAKE_FORCE_C_COMPILER(mpifccpx GNU)
  CMAKE_FORCE_CXX_COMPILER(mpiFCCpx GNU)
  CMAKE_FORCE_Fortran_COMPILER(mpifrtpx GNU)

  #CMAKE_FORCE_Fortran_Compiler is not supported ver. 2.6
  #set(CMAKE_Fortran_COMPILER mpifrtpx GNU)
  #set(CMAKE_Fortran_COMPILER_WORKS true)
  #set(CMAKE_Fortran_LINK_EXECUTABLE "${CMAKE_CXX_COMPILER}")
else()
  CMAKE_FORCE_C_COMPILER(fccpx GNU)
  CMAKE_FORCE_CXX_COMPILER(FCCpx GNU)
  CMAKE_FORCE_Fortran_COMPILER(frtpx GNU)

  #CMAKE_FORCE_Fortran_Compiler is not supported ver. 2.6
  #set(CMAKE_Fortran_COMPILER frtpx GNU)
  #set(CMAKE_Fortran_COMPILER_WORKS true)
  #set(CMAKE_Fortran_LINK_EXECUTABLE "${CMAKE_CXX_COMPILER}")
endif()

set(CMAKE_FIND_ROOT_PATH /opt/FJSVfxlang/1.2.1)   # RIIT fx10, hayaka
set(CMAKE_INCLUDE_PATH /opt/FJSVfxlang/1.2.1/include)
set(CMAKE_LIBRARY_PATH /opt/FJSVfxlang/1.2.1/lib64)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

#set(CMAKE_CXX_FLAGS "-Xg -std=gnu++03"  CACHE STRING "" FORCE)
#set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -Kparallel"  CACHE STRING "" FORCE)
