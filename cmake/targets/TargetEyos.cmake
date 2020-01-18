#xwin_add_executable(Eyos "")
add_executable(Eyos)
add_executable(Eyos::Eyos ALIAS Eyos)

# include target source list
include(TargetEyosSourceList)

if(USE_PREBUILT_BGFX_TOOLS)
	set(TOOL_GEOMETRYC_EXE ${PROJECT_SOURCE_DIR}/tools/geometryc.exe)
	set(TOOL_SHADERC_EXE ${PROJECT_SOURCE_DIR}/tools/shaderc.exe)
	set(TOOL_TEXTUREC_EXE ${PROJECT_SOURCE_DIR}/tools/texturec.exe)
	set(TOOL_TEXTUREV_EXE ${PROJECT_SOURCE_DIR}/tools/texturev.exe)
else()
	set(TOOL_GEOMETRYC_EXE $<TARGET_FILE:geometryc>)
	set(TOOL_SHADERC_EXE $<TARGET_FILE:shaderc>)
	set(TOOL_TEXTUREC_EXE $<TARGET_FILE:texturec>)
	set(TOOL_TEXTUREV_EXE $<TARGET_FILE:texturev>)
endif(USE_PREBUILT_BGFX_TOOLS)

#
# BGFX settings:
#

if(${BUILD_ASSETS})
	file(GLOB_RECURSE SHADER_SRC_FILES RELATIVE ${PROJECT_SOURCE_DIR}/data/shaders/ "${PROJECT_SOURCE_DIR}/data/shaders/*.sc")
	foreach(SHADER_SRC_FILE ${SHADER_SRC_FILES})
		message(STATUS "Shader File: ${SHADER_SRC_FILE}")
		add_eyos_shader(${SHADER_SRC_FILE})
	endforeach()
	
	file(GLOB_RECURSE MODEL_FILES RELATIVE ${PROJECT_SOURCE_DIR}/data/ "${PROJECT_SOURCE_DIR}/data/*.obj")
	foreach(MODEL_FILE ${MODEL_FILES})
		message(STATUS "Model File: ${MODEL_FILE}")
		add_eyos_mesh(${MODEL_FILE})
	endforeach()
	
	file(GLOB_RECURSE SHADER_SRC_FILES_ABSOLUTE "${PROJECT_SOURCE_DIR}/data/shaders/*.sc")
	file(GLOB_RECURSE MESH_FILES_ABSOLUTE "${PROJECT_SOURCE_DIR}/data/*.obj")

	# Add resource files to the project
	target_sources(Eyos PRIVATE ${SHADER_SRC_FILES_ABSOLUTE} ${MESH_FILES_ABSOLUTE})

	# We also have asset files which don't have to be processed, but just copied over:
	file(COPY "${PROJECT_SOURCE_DIR}/data/fonts" DESTINATION "${PROJECT_SOURCE_DIR}/build")
	file(COPY "${PROJECT_SOURCE_DIR}/data/maps" DESTINATION "${PROJECT_SOURCE_DIR}/build")
	file(COPY "${PROJECT_SOURCE_DIR}/data/textures" DESTINATION "${PROJECT_SOURCE_DIR}/build")
endif()

#
# Eyos general settings:
#

# Add source to this project's executable.
target_include_directories(Eyos
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

if(WIN32)
set_target_properties( Eyos
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/bin"
	VS_DEBUGGER_WORKING_DIRECTORY "${VS_DEBUGGER_WORKING_DIRECTORY}"
)
else(WIN32)
set_target_properties( Eyos
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/libs"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/bin"
)
endif(WIN32)

target_link_libraries(Eyos
    PRIVATE 
    Engine
	bgfx
	bimg
	bx
#	example-common
	bgfx_example_common_eyos
	gainput
#	CrossWindow
)

get_target_property(EYOS_RUNTIME_OUTPUT_DIR Eyos RUNTIME_OUTPUT_DIRECTORY)
add_custom_command(TARGET Eyos POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        $<TARGET_FILE:gainput>      # <--this is in-file
        $<TARGET_FILE_DIR:Eyos>)                 # <--this is out-file path



SetCppVersionOfTarget(Eyos)