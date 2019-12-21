
set(enet_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/enet)
find_path(enet_INCLUDE_DIR
NAMES enet/enet.h
PATHS ${enet_INCLUDE_DIR}
PATH_SUFFIXES include
)
set(enet_VERSION 1.3.14)

mark_as_advanced(enet_FOUND enet_INCLUDE_DIR enet_VERSION)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(enet
REQUIRED_VARS enet_INCLUDE_DIR
VERSION_VAR enet_VERSION
)

if(enet_FOUND AND NOT TARGET enet::enet)
add_library(enet::enet STATIC IMPORTED)
set_target_properties(enet::enet PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${enet_INCLUDE_DIR}"
)

endif()

set_target_properties( enet
PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libs"
LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libs"
RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)