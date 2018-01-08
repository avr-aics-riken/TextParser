###################################################################################
#
# TextParser - Text Parsing Library
#
# Copyright (C) 2012-2015 Institute of Industrial Science, The University of Tokyo.
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


set(tp_files
       TextParser.cpp
       TextParserElement.cpp
       TextParserTree.cpp)

if(NOT with_MPI)
  add_library(TP STATIC ${tp_files})

  # tpVersion.hをサーチするためにBINARYを先に書く
  include_directories(${PROJECT_BINARY_DIR}/include ${PROJECT_SOURCE_DIR}/include)

  install(TARGETS TP DESTINATION lib)

else()
  add_library(TPmpi STATIC ${tp_files})
  include_directories(${PROJECT_BINARY_DIR}/include)
  include_directories(${PROJECT_SOURCE_DIR}/include)
  install(TARGETS TPmpi DESTINATION lib)

endif()

set(EXTRA_DIST "${EXTRA_DIST} Makefile_hand")

install(FILES ${PROJECT_SOURCE_DIR}/include/TextParser.h
              ${PROJECT_SOURCE_DIR}/include/TextParserCommon.h
              ${PROJECT_SOURCE_DIR}/include/TextParserElement.h
              ${PROJECT_SOURCE_DIR}/include/TextParserTree.h
              ${PROJECT_BINARY_DIR}/include/tpVersion.h
        DESTINATION include )

if(enable_fapi)
  add_library(TP_fapi STATIC TextParser_fapi.f90)
  include_directories(${PROJECT_SOURCE_DIR}/include)
  target_link_libraries(TP_fapi ${CMAKE_CXX_IMPLICIT_LINK_LIBRARIES})

  install (TARGETS TP_fapi DESTINATION lib)
  install (FILES ${PROJECT_SOURCE_DIR}/include/TextParser.inc DESTINATION include)
endif(enable_fapi)

###
