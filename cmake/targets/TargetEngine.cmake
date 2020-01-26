add_library(Engine SHARED)

# include target source list
include(TargetEngineSourceList)

add_library(Engine::Engine ALIAS Engine)


target_link_libraries(Engine 
    PUBLIC
    glm
    enet
    eventpp
)

target_include_directories(Engine
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/third_party/enet/include>
)

target_compile_definitions(Engine PRIVATE BUILD_SHARED_LIBS)

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

if(NOT MSVC)
	# Appearently GCC needs this otherwise the filesystem is not linked? even though it's in the C++17 standard?
	target_link_libraries(Engine PUBLIC stdc++fs)  # link to libstdc++fs
endif()

SetCppVersionOfTarget(Engine)