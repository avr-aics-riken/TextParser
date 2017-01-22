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
###################################################################################

##
## Packaging
##

macro (tp_package)
include (InstallRequiredSystemLibraries)

set (CPACK_PACKAGE_NAME "${PROJECT}")
set (CPACK_PACKAGE_VENDOR "RIIT")

set (CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set (CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "Light-weight text parsing library")
set (CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/License.txt")
set (CPACK_RESOURCE_FILE_README  "${PROJECT_SOURCE_DIR}/Readme.md")

set (CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")
set (CPACK_SOURCE_GENERATOR "TGZ;ZIP")

# config for source installer
set (CPACK_SOURCE_OUTPUT_CONFIG_FILE "${PROJECT_BINARY_DIR}/CPackSourceConfig.cmake")

set (CPACK_SOURCE_IGNORE_FILES "/BUILD/;/build/;/.git/;.#;/#;/.DS_Store" CACHE STRING "CPACK will ignore this files" )

# config for binary installer
#set (CPACK_OUTPUT_CONFIG_FILE "${PROJECT_BINARY_DIR}/CPackConfig.cmake")

include (CPack)
endmacro()
