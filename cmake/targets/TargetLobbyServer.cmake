add_executable(EyosLobbyServer)
add_executable(Eyos::EyosLobbyServer ALIAS EyosLobbyServer)

# include target source list
include(TargetLobbyServerSourceList)

# Add source to this project's executable.
target_include_directories(EyosLobbyServer
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

    target_link_libraries(EyosLobbyServer 
        PRIVATE
        Engine
        enet
    )

if(WIN32)
set_target_properties( EyosLobbyServer
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/bin"
	VS_DEBUGGER_WORKING_DIRECTORY "${VS_DEBUGGER_WORKING_DIRECTORY}"
)

use_vld(EyosLobbyServer)

    target_link_libraries(EyosLobbyServer 
        PRIVATE
        ws2_32.lib
        winmm.lib
    )

else(WIN32)
set_target_properties( EyosLobbyServer
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/bin"
)
endif(WIN32)
SetCppVersionOfTarget(EyosLobbyServer)
