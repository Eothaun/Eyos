add_subdirectory(glm)
# Uncomment below if you want GLM debug messages about available features
#target_compile_definitions(glm INTERFACE GLM_FORCE_MESSAGES=1)
target_compile_definitions(glm INTERFACE GLM_FORCE_EXPLICIT_CTOR) 
add_subdirectory(enet)

add_subdirectory(Catch2)

set(BGFX_BUILD_EXAMPLES OFF)
add_subdirectory(bgfx.cmake)
