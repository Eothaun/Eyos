set(glm_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm/glm")
find_path(glm_INCLUDE_DIR
    NAMES glm.hpp
    PATHS ${glm_INCLUDE_DIRS}
    PATH_SUFFIXES glm
)

mark_as_advanced(glm_FOUND glm_INCLUDE_DIR GLM_VERSION)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(glm
    REQUIRED_VARS glm_INCLUDE_DIR
    VERSION_VAR GLM_VERSION
)

if(glm_FOUND)
    set(glm_INCLUDE_DIRS ${glm_INCLUDE_DIR})
endif()

if(glm_FOUND AND NOT TARGET glm::glm)
    add_library(glm::glm INTERFACE IMPORTED)
    set_target_properties(glm::glm PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${glm_INCLUDE_DIRS}"
    )
endif()