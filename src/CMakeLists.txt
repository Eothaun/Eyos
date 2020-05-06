# Include targets. Target file specify the target settings.
# Target[TargetName]SourceList.cmake files specifiy the source files of the target
# see root/cmake folder!
include(TargetEngine)
include(TargetEyos)

# Installation of the engine and the game
install(TARGETS Eyos Engine
RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}
)
# move all the assets on install:
if(EXISTS ${ASSETS_DIR})
    install(DIRECTORY ${ASSETS_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX})
endif()