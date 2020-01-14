cmake_minimum_required(VERSION 3.13)
# declare project
project(Eyos VERSION 0.0.1 DESCRIPTION "Yet another student RTS"  LANGUAGES CXX)

#define global warning settings this will be for all projects! If one spscific target shall only have something see target ... cmake folder!
if(MSVC)
add_compile_options(/W3 /MP)
else()
add_compile_options(-W -Wall)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options( -fdiagnostics-format=json)
    endif()
endif()

# add module path to CMAKE_MODULE_PATH
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake/finders")
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake/targets")
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake/utils")
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/third_party/Catch2/contrib")

# insert modules
include(SetCppVersionOfTarget)
include(GitSubmodule)
include(target_source_local)
include(add_eyos_mesh)
include(add_eyos_shader)
include(use_vld)
include(ClangFormat)

# declare options
option(BGFX_SUPRESS_WARNING "BGFX supress warnings" ON)
option(BGFX_BUILD_EXAMPLES "BGFX Build no EXAMPLES" OFF)
option(BUILD_TESTING "Build tests" OFF)
option(BUILD_WITH_CALNG_FORMAT "Build with clang format" OFF)
option(BUILD_CXX_20 "C++20" OFF)
option(GIT_SUBMODULE "Check submodules during build" ON)
option(USE_PREBUILT_BGFX_TOOLS "If on, uses the .exe's in {EYOS_SOURCE_DIR}/tools for geometryc and shaderc, otherwise it will be compiled from source" ON)
option(GAINPUT_SAMPLES "Build Samples for Gainput" OFF)
option(GAINPUT_TESTS "Build Tests for Gainput" OFF)
option(USE_VLD "Makes use of VLD" OFF)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(THIRD_PARTY "${CMAKE_CURRENT_SOURCE_DIR}/third_party")
set(ASSETS_DIR "${CMAKE_INSTALL_PREFIX}/data")

if(WIN32)
    set(VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
endif(WIN32)

# get git submodules
GitSubmodule()

# Include third-party components we need for the build
add_subdirectory(third_party)

# include source directories
add_subdirectory(src)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    message(STATUS "TESTING ON")
    enable_testing()
    add_subdirectory(tests)
else()
      message(STATUS "TESTING OFF")
endif()

if(BUILD_WITH_CALNG_FORMAT)
    target_clangformat_setup(Eyos)
endif()
