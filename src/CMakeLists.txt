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
# Copyright (c) 2016-2017 Research Institute for Information Technology, Kyushu University.
# All rights reserved.
#
#
###################################################################################


set(tp_files
       TextParser.cpp
			 TextParserElement.cpp
			 TextParserTree.cpp)

if(SERIALTARGET)
	add_library(TP STATIC ${tp_files})

  # tpVersion.hをサーチするためにBINARYを先に書く
  include_directories(${PROJECT_BINARY_DIR}/include ${PROJECT_SOURCE_DIR}/include)

	install(TARGETS TP DESTINATION lib)

else(SERIALTARGET)
	add_library(TPmpi STATIC ${tp_files})
  include_directories(${PROJECT_BINARY_DIR}/include)
	include_directories(${PROJECT_SOURCE_DIR}/include)

	add_definitions(-DENABLE_MPI)
	add_definitions(-DBUILD_MPI)

	install(TARGETS TPmpi DESTINATION lib)

endif(SERIALTARGET)

set(EXTRA_DIST "${EXTRA_DIST} Makefile_hand")

install(FILES ${PROJECT_SOURCE_DIR}/include/TextParser.h
              ${PROJECT_SOURCE_DIR}/include/TextParserCommon.h
              ${PROJECT_SOURCE_DIR}/include/TextParserElement.h
							${PROJECT_SOURCE_DIR}/include/TextParserTree.h

              ${PROJECT_BINARY_DIR}/include/tpVersion.h
        DESTINATION include )

if(USE_FAPI)
  add_library(TP_fapi STATIC TextParser_fapi.f90)

  if(SERIALTARGET)
    include_directories(${PROJECT_SOURCE_DIR}/include)
  else()
    #include_directories(${PROJECT_SOURCE_DIR}/include ${MPI_DIR}/include)
    include_directories(${PROJECT_SOURCE_DIR}/include)
  endif()

  set_target_properties (TP_fapi PROPERTIES LINKER_LANGUAGE CXX)
  install (TARGETS TP_fapi DESTINATION lib)
  install (FILES ${PROJECT_SOURCE_DIR}/include/TextParser.inc DESTINATION include)
endif(USE_FAPI)

###
