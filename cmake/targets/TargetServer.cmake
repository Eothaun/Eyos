add_executable(EyosDedicatedServer)
add_executable(Eyos::EyosDedicatedServer ALIAS EyosDedicatedServer)

# include target source list
include(TargetServerSourceList)

# Add source to this project's executable.
target_include_directories(EyosDedicatedServer
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

    target_link_libraries(EyosDedicatedServer 
        PRIVATE
        Engine
        enet
        eventpp
    )

if(WIN32)
set_target_properties( EyosDedicatedServer
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/bin"
	VS_DEBUGGER_WORKING_DIRECTORY "${VS_DEBUGGER_WORKING_DIRECTORY}"
)

use_vld(EyosDedicatedServer)

    target_link_libraries(EyosDedicatedServer 
        PRIVATE
        ws2_32.lib
        winmm.lib
    )

else(WIN32)
set_target_properties( EyosDedicatedServer
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/bin"
)
endif(WIN32)
SetCppVersionOfTarget(EyosDedicatedServer)
