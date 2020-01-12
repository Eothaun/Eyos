project(bgfx_example_common_eyos VERSION 0.1.0 DESCRIPTION "A modified version of the BGFX example-common project. Made for the Eyos Project" LANGUAGES CXX C)


file( GLOB_RECURSE GLOB_SOURCES *.c *.cpp *.h)
file( GLOB_RECURSE GLOB_HEADERS *.h)

add_library(bgfx_example_common_eyos STATIC ${GLOB_SOURCES})
target_include_directories(bgfx_example_common_eyos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries( bgfx_example_common_eyos PUBLIC bgfx dear-imgui meshoptimizer gainput )
target_compile_definitions( bgfx_example_common_eyos PRIVATE "-D_CRT_SECURE_NO_WARNINGS" "-D__STDC_FORMAT_MACROS" "-DENTRY_CONFIG_IMPLEMENT_MAIN=1" )
