add_library(Engine SHARED)

# include target source list
include(TargetEngineSourceList)

add_library(Engine::Engine ALIAS Engine)

find_package(glm 0.9.9 REQUIRED)
target_link_libraries(Engine 
    PUBLIC
    glm
)

find_package(enet 1.3.14 REQUIRED)

target_link_libraries(Engine 
    PUBLIC
    enet
)

target_include_directories(Engine
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/third_party/enet/include>
)

set_target_properties( Engine
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/bin"
)

if(WIN32)
    target_link_libraries(Engine 
        PRIVATE
        ws2_32.lib
        winmm.lib
    )
endif()

SetCppVersionOfTarget(Engine)