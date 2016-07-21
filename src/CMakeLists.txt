# install file
IF(SERIALTARGET)
	ADD_LIBRARY(TP TextParser.cpp TextParserElement.cpp
TextParserTree.cpp)
	SET(libTP_a_CXXFLAGS ${PROJECT_SOURCE_DIR}/include)
	
    include_directories("${PROJECT_BINARY_DIR}/include")
	INCLUDE_DIRECTORIES(${libTP_a_CXXFLAGS})
	INSTALL(TARGETS TP DESTINATION ${TP}/lib)

ELSE(SERIALTARGET)
	ADD_LIBRARY(TPmpi TextParser.cpp TextParserElement.cpp TextParserTree.cpp)
	SET(libTPmpi_a_CXXFLAGS ${PROJECT_SOURCE_DIR}/include ${MPICH_CFLAGS})

	INCLUDE_DIRECTORIES(${libTPmpi_a_CXXFLAGS})
	
	ADD_DEFINITIONS(-DENABLE_MPI)
	ADD_DEFINITIONS(-DBUILD_MPI)

	INSTALL(TARGETS TPmpi DESTINATION ${TP}/lib)

	SET(libTPmpi_a_CXXFLAGS "${libTPmpi_a_CXXFLAGS} -DENABLE_MPI
-DBUILD_MPI")

ENDIF(SERIALTARGET)

IF(TP_FAPI)
	ADD_LIBRARY(TP_fapi SHARED TextParser_fapi.f90)
	SET(libTP_fapi_a_CXXFLAGS "${libTP_fapi_a_CXXFLAGS} ${PROJECT_SOURCE_DIR}/include ${MPICH_CFLAGS}")
	INCLUDE_DIRECTORIES(${libTP_fapi_a_CXXFLAGS})
	INSTALL(FILES libTP_fapi.a DESTINATION ${TP}/lib)
ENDIF(TP_FAPI)

SET(EXTRA_DIST "${EXTRA_DIST} Makefile_hand")

INSTALL(FILES ../include/TextParser.h ../include/TextParserCommon.h
              ../include/TextParserElement.h ../include/TextParserTree.h
              ../include/TextParser.inc 
              ${PROJECT_BINARY_DIR}/include/tpVersion.h 
        DESTINATION ${TP}/include )

###