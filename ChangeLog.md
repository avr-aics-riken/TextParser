# TextParser - Text Parsing Library

 - Copyright (c) 2012-2015 Institute of Industrial Science, The University of Tokyo. All rights reserved.
 - Copyright (c) 2014-2016 Advanced Institute for Computational Science, RIKEN. All rights reserved.
 - Copyright (c) 2016-2017 Research Institute for Information Technology, Kyushu University. All rights reserved.


## REVISION HISTORY

---
- 2017-02-11 Version 1.7.7
  - modify Readme.md

---
- 2017-01-30 Version 1.7.6
  - change ctest for mpi version
  - split examples into serial and MPI

---
- 2017-01-30 Version 1.7.5
  - Remove tp-config

---
- 2017-01-29 Version 1.7.4
  - Move Doxygen related files from top to doc

---
- 2017-01-22 Version 1.7.3
  - Change install command line for fx10

---
- 2017-01-22 Version 1.7.2
  - Change the description of CMakeLists.txt with module.cmake

  - Tested

    |Compiler|Serial|S-Ex.C|S-Test|MPI |M-Ex.C|M-Test|
    |:--     |:--:  |:--:  |:--:  |:--:|:--:  |:--:  |
    |Intel 17.0.1 |OK|OK|35% failed|OK|OK|91% failed|
    |GNU 6.2.0    |OK|OK|35% failed|OK|OK|91% failed|
    |FJ      |OK|OK|all failed|OK|OK|all failed|

---
- 2017-01-18 Version 1.7.1
  - add `target_link_libraries(Example?_c ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})` for Examples/CMakeLists.txt
  - add `CMAKE_C_LINK_EXECUTABLE` and `CMAKE_Fortran_LINK_EXECUTABLE`, Linker must be a CXX compiler.
  - Tested

    |Compiler|Serial|S-Ex.C|S-Test|MPI |M-Ex.C|M-Test|
    |:--     |:--:  |:--:  |:--:  |:--:|:--:  |:--:  |
    |Intel 17.0.1 |OK|OK|5 items failed|OK|OK|95% failed|
    |GNU 6.2.0    |OK|OK|5 items failed|OK|OK|95% failed|
    |FJ      |OK|OK|all failed|OK|OK|all failed|


- 2017-01-18 Version 1.7.0
  - Cmake only
  - modify file structure, build process
  - change MACRO from `FFV_HOME >> TP_HOME`
  - Compile OK : Intel serial/mpi, /w fapi, GNU serial
  - Example tests failed.
  - Compilation on FX10 has not been tested yet.
  - Delete bomb from ;
    - `config.h.in.cmake`
    - `tp-config.in.cmake`
    - `python_api/TextParser_python_api.cpp`
  - ChangeLog >> md style
  - Tested

    |Compiler|Serial|S-Ex.C|S-Test|MPI |M-Ex.C|M-Test|
    |:--     |:--:  |:--:  |:--:  |:--:|:--:  |:--:  |
    |Intel 17.0.1 |OK|OK|5 items failed|OK|OK|95% failed|
    |GNU 6.2.0    |OK|NG|–|OK|NG|–|
    |FJ      |OK|NG|–|OK|NG|–|

    * Note
    	* Serial/MPI >> C/C++/Fortran compilation
    	* Ex.C >> Example compilation
    	* Test >> Example test

---
- 2016-07-21 Version 1.6.6

---
- 2016-07-06
  - add cmake

---
- 2015-11-28 Version 1.6.5
  - r45 --with-comp becomes essential
  - change configure.ac, INSTALL, and NEWS

---
- 2015-08-17  Version 1.6.4
  - r44 bug fix : installing serial version

---
- 2015-06-14 Version 1.6.3
  - r43 more bug fix for install package

---
- 2015-06-13 Version 1.6.2
  - r42 bug fix for install package

---
- 2015-06-10 Version 1.6.1
  - r41 claen package

---
- 2015-06-09 Version 1.6.0
  - r40 introduce BUILD_DIR to keep source directory clean
  - Change to run configure
  - Change configure.ac

---
- 2015-03-14 Version 1.5.8
 - r39 update year
 - add mpiicc, mpiicpc

---
- 2014-09-24 Version 1.5.7
  - r38 bug fix
  - TextParser::getValue
  - TextParserTree::getElement

---
- 2014-06-26 Version 1.5.6
  - r37 python api bug fix
  - add a user guide of English version

---
- 2014-06-21 Version 1.5.5
  - r36 serial build
  - confirm serial build and add description to INSTALL
  - update user guide

---
- 2014-06-14 Version 1.5.4
  - r35 update user guide

---
- 2014-05-31 Version 1.5.3
  - r34 add python api
  - /python_api
  - add RIKEN's copyright
---
- 2014-05-28 Version 1.5.2
  - r33 remove include header config.h in TextParserElement.cpp

---
- 2014-03-08 Version 1.5.1
  - r32 libMPITP.a >> libTPmpi.a

---
- 2014-03-04 Version 1.5.0
  - r31 version format
  - change output format for tp-config --version

---
- 2014-03-01 Version 1.4.9
  - r30 change filename Version.h to avoid conflict with other files

---
- 2014-02-26 Version 1.4.8
  - r29 bugfix
  - bool TextParser::getInspectedVector(std::string label, std::string *vec, const int nvec)

---
- 2014-02-21 Version 1.4.7
  - r28 regular expression for windows [ver 1.4.7]

---
- 2014-02-11 Version 1.4.6
  - r27 add CC compiler wrapper script in configure.ac for NERSC Hopper [ver 1.4.6]

---
- 2013-11-02 Version 1.4.5
  - r26 update configure.ac
  - r25 cleanup configure.ac
  - expire MPICH version and target detection
  - change Fortran compiler from FC to F90

---
- 2013-10-30 Version 1.4.4
  - r24 correct syntax
  - TextParset.cpp, L.2751 size_t nmatch=1 >> const int nmatch=1
  - update chk-uname, add Marvericks

---
- 2013-10-02 Version 1.4.3
  - r23 modify for intel mpi
  - include mpi.h before stdio.h to suppress error message #error "SEEK_SET is #defined but must not be for the C++ binding of MPI"

---
- 2013-08-14 Version 1.4.2
  - r22 suppress error message in chkLabel(), chkNode()

---
- 2013-08-14 Version 1.4.1
  - r21 packaging
  - r20 add bool getLabelVector(const string root, vector<string>& nodes)
  - r19 add bool getInspectedVector(const std::string label, float *vec, const int nvec )

---
- 2013-08-13 Version 1.4.0
  - r18 packaging
  - r17 add utility methods such as TextParser::getInspectedValue()
  - r16 modify README

---
- 2013-07-20 Version 1.3.7
  - r15 Introduce getVersionInfo()
  - add Version.h.in

---
- 2013-07-07 Version 1.3.6
  - r14 reflect master's update to r13 by hand
  - hand merge
  - update style of ChangeLog and NEWS
  - update configure.ac, fortran api
  - remove stdc++ from TP_LIBS

---
- 2013-07-03 Version 1.3.5
  - r13 exp.branch, add --enable-fapi option

---
- 2013-07-02 Version 1.3.4
  - r12 exp.branch, change order of link lib., place stdc++ at last

---
- 2013-06-27 Version 1.3.3
  - r11 update INSTALL
  - r10 exp. branch; bug fix of configure

---
- 2013-06-26 Version 1.3.2
  - r9 exp. branch, update NES/ChangeLog
  - r8 exp. branch, select serial/mpi target

---
- 2013-06-25 Version 1.3.1
  - r7 start experimental branch & 1.3.1

---
- 2013-05-07 Version 1.3
  - r6 ver 1.3
  - registration of ver. 1.3

---
- 2012-11-27 Version 1.2
  - r5 ver 1.2
  - registration of ver. 1.2 again
  - r4 ver 1.2
  - registration of ver. 1.2

---
- 2012-10-09 Version 1.1
  - r3 ver 1.1
  - registration of ver. 1.1

---
- 2012-06-22 Version 1.0
  - r2 ver 1.0
  - registration of ver. 1.0

---
- 2012-04-27 Version 0.9
