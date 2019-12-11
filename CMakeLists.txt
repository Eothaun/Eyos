cmake_minimum_required(VERSION 3.10)
# declare project
project(Eyos VERSION 0.0.1 DESCRIPTION "Yet another student RTS"  LANGUAGES CXX)

#define global warning settings

if(MSVC)
add_compile_options(/W3)
else()
add_compile_options(-W -Wall)
endif()

# add module path to CMAKE_MODULE_PATH
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# insert modules
include(SetCppVersionOfTarget)
include(GitSubmodule)
include(target_source_local)

# declare options
option(BUILD_TESTING "Build tests" OFF)
option(BUILD_CXX_20 "C++20" OFF)

# get git submodules
GitSubmodule()

# Include third-party components we need for the build
add_subdirectory(third_party)

# include source directories
add_subdirectory(src)


if(BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    enable_testing()
    add_subdirectory(tests)
endif()