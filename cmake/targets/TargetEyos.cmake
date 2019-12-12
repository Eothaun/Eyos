add_executable(Eyos)
add_executable(Eyos::Eyos ALIAS Eyos)

# include target source list
include(TargetEyosSourceList)

target_include_directories(Eyos
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

set_target_properties( Eyos
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/bin"
)

 target_link_libraries(Eyos
        PRIVATE 
        Engine
 )

 SetCppVersionOfTarget(Engine)