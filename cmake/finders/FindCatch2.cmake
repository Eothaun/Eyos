# This cmake script installs ThirdParty stuff downloading them 
message(STATUS "Searching for Catch2...")

set(Catch2_CHECK_PATHS 
    "${THIRD_PARTY}/Catch2"
    )

# First try to use the standard find_package that should be able to find the
# .cmake configuration files if installed in standard directories.

# Saveup Eigen3_DIR since the CONFIG overwrites it
set(TEMP_Catch2_DIR ${Catch2_DIR})
find_package(Catch2 QUIET CONFIG)

if (NOT Catch2_FOUND)
    # Restore
    set(Catch2_DIR ${TEMP_Catch2_DIR})
    # Standard stuff did not work, so we try to locate Catch2 in include paths
    find_path(Catch2_INCLUDE_DIR NAMES catch.hpp
        HINTS ${Catch2_CHECK_PATHS}
        PATHS ${Catch2_CHECK_PATHS}
        PATH_SUFFIXES catch include)

    if (Catch2_INCLUDE_DIR)
        # We found the include dir, we add it to the standard variable
        # ${<library>_INCLUDE_DIRS}
        set (Catch2_INCLUDE_DIRS ${Catch2_INCLUDE_DIR})
    endif (Catch2_INCLUDE_DIR)
else()
    # Catch does not export the variable, only the target
    get_target_property(Catch2_INCLUDE_DIRS Catch2::Catch2 
        INTERFACE_INCLUDE_DIRECTORIES
    )
endif()

# Handle REQUIRED/QUIET optional arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Catch2
  REQUIRED_VARS Catch2_INCLUDE_DIRS)

  if(Catch2_FOUND)
    message(STATUS "Found Catch2: include dir ${Catch2_INCLUDE_DIRS}")
endif()

if(Catch2_FOUND AND NOT TARGET Catch2::Catch2)
    add_library(Catch2::Catch2 INTERFACE IMPORTED)
    set_target_properties(Catch2::Catch2 PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${Catch2_INCLUDE_DIRS}"
    )
endif()

