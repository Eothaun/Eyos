add_executable(Eyos)
add_executable(Eyos::Eyos ALIAS Eyos)

include(EyosSourceList)

target_include_directories(Eyos
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

set_target_properties( Eyos
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libs"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/libs"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

 target_link_libraries(Eyos
        PRIVATE 
        Engine
 )

 SetCppVersionOfTarget(Engine)