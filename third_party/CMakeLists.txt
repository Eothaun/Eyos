add_subdirectory(glm)
target_compile_definitions(glm INTERFACE GLM_FORCE_EXPLICIT_CTOR) 
# Uncomment below if you want GLM debug messages about available features
#target_compile_definitions(glm INTERFACE GLM_FORCE_MESSAGES=1)

add_subdirectory(enet)

add_subdirectory(Catch2)

add_subdirectory(bgfx.cmake)
if(BGFX_SUPRESS_WARNING)
    message(STATUS "BGFX will compile with no warnings!")
    if(MSVC)
        target_compile_options(bgfx PUBLIC /w)
        target_compile_options(bgfx INTERFACE /w)
        target_compile_options(bimg INTERFACE /w)
        target_compile_options(bx INTERFACE /w)
        target_compile_options(astc PUBLIC /w)
    else()
        target_compile_options(bgfx INTERFACE -w)
        target_compile_options(bimg INTERFACE -w)
        target_compile_options(bx INTERFACE -w)
        target_compile_options(astc PUBLIC -w)
    endif()
endif(BGFX_SUPRESS_WARNING)

add_subdirectory(gainput)
target_include_directories(gainput INTERFACE "gainput/lib/include")

# Not used at the moment, so disabled in build
# add_subdirectory(CrossWindow)

add_subdirectory(bgfx_example_common_eyos)
