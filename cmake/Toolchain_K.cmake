set(CMAKE_SYSTEM_NAME Linux)

include(CMakeForceCompiler)

if(with_MPI)
  CMAKE_FORCE_C_COMPILER(mpifccpx GNU)
  CMAKE_FORCE_CXX_COMPILER(mpiFCCpx GNU)
  #CMAKE_FORCE_Fortran_Compiler is not supported ver. 2.6
  #CMAKE_FORCE_Fortran_COMPILER(frtpx GNU)
  set(CMAKE_Fortran_COMPILER mpifrtpx)
  set(CMAKE_Fortran_COMPILER_WORKS true)
else()
  CMAKE_FORCE_C_COMPILER(fccpx GNU)
  CMAKE_FORCE_CXX_COMPILER(FCCpx GNU)
  #CMAKE_FORCE_Fortran_Compiler is not supported ver. 2.6
  #CMAKE_FORCE_Fortran_COMPILER(frtpx GNU)
  set(CMAKE_Fortran_COMPILER frtpx)
  set(CMAKE_Fortran_COMPILER_WORKS true)
endif()


set(CMAKE_FIND_ROOT_PATH   /opt/FJSVfxlang/1.2.1)
#set(CMAKE_FIND_ROOT_PATH   /opt/FJSVXosDevkit/sparc64fx/target)  #couldnt work 2015/1/28
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
