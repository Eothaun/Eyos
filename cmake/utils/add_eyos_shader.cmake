# add_eyos_shader(<FILE>)
# 
# === Brief:
# Add a shader compile target to the shader file.
# 
# === Arguments:
# <FILE> : A relative path from '${PROJECT_SOURCE_DIR}/data/shaders/' to a .sc shader
# Eg: for the physical path "E:\Project\C++\RTS_Sideproject\Eyos\data\shaders\cubes\fs_cubes.sc", Argument <FILE> would be: "cubes\fs_cubes.sc"
# 
# === Description:
# The output directories are: 
# For Dx9:			'${PROJECT_SOURCE_DIR}/build/shaders/dx9/${FILE}.bin'
# For Dx11:			'${PROJECT_SOURCE_DIR}/build/shaders/dx11/${FILE}.bin'
# For OpenGL ES:	'${PROJECT_SOURCE_DIR}/build/shaders/essl/${FILE}.bin'
# For Glsl:			'${PROJECT_SOURCE_DIR}/build/shaders/glsl/${FILE}.bin'
# For SpirV:		'${PROJECT_SOURCE_DIR}/build/shaders/spirv/${FILE}.bin'
# 
# === NOTE:
# For shader type identification (fragment, vertex, compute). The first two characters are used, "fs", "ps" and "cs" respectively.
# 
# This function just adds the custom build step, you still need to add it to a project for the shader to compile!
function( add_eyos_shader FILE )
	set(ABSOLUTE_FILE "${PROJECT_SOURCE_DIR}/data/shaders/${FILE}")

	get_filename_component( FILENAME "${FILE}" NAME_WE )
	string( SUBSTRING "${FILENAME}" 0 2 TYPE )
	if( "${TYPE}" STREQUAL "fs" )
		set( TYPE "FRAGMENT" )
		set( D3D_PREFIX "ps" )
	elseif( "${TYPE}" STREQUAL "vs" )
		set( TYPE "VERTEX" )
		set( D3D_PREFIX "vs" )
	elseif( "${TYPE}" STREQUAL "cs" )
		set( TYPE "COMPUTE" )
 		set( D3D_PREFIX "cs" )
	else()
		set( TYPE "" )
	endif()

	#Afterwards, FILENAME is used as the name of the file, so I want to preserve folder structure
	get_filename_component(FILENAME_DIRECTORY "${FILE}" DIRECTORY)
	set(FILENAME "${FILENAME_DIRECTORY}/${FILENAME}")

	message("Shader: ${FILENAME} is type: ${TYPE}")

	if( NOT "${TYPE}" STREQUAL "" )
		set( COMMON FILE ${ABSOLUTE_FILE} ${TYPE} INCLUDES ${BGFX_DIR}/examples/common ${BGFX_DIR}/src)
		set( OUTPUTS "" )
		set( OUTPUTS_PRETTY "" )

		if( WIN32 )
			# dx9
			if( NOT "${TYPE}" STREQUAL "COMPUTE" )
				set( DX9_OUTPUT ${PROJECT_SOURCE_DIR}/build/shaders/dx9/${FILENAME}.bin )
				shaderc_parse( DX9 ${COMMON} WINDOWS PROFILE ${D3D_PREFIX}_3_0 O 3 OUTPUT ${DX9_OUTPUT} )
				list( APPEND OUTPUTS "DX9" )
				set( OUTPUTS_PRETTY "${OUTPUTS_PRETTY}DX9, " )
			endif()

			# dx11
			set( DX11_OUTPUT ${PROJECT_SOURCE_DIR}/build/shaders/dx11/${FILENAME}.bin )
			if( NOT "${TYPE}" STREQUAL "COMPUTE" )
				shaderc_parse( DX11 ${COMMON} WINDOWS PROFILE ${D3D_PREFIX}_5_0 O 3 OUTPUT ${DX11_OUTPUT} )
			else()
				shaderc_parse( DX11 ${COMMON} WINDOWS PROFILE ${D3D_PREFIX}_5_0 O 1 OUTPUT ${DX11_OUTPUT} )
			endif()
			list( APPEND OUTPUTS "DX11" )
			set( OUTPUTS_PRETTY "${OUTPUTS_PRETTY}DX11, " )
		endif()

#		if( APPLE )
#			# metal
#			set( METAL_OUTPUT ${BGFX_DIR}/examples/runtime/shaders/metal/${FILENAME}.bin )
#			shaderc_parse( METAL ${COMMON} OSX PROFILE metal OUTPUT ${METAL_OUTPUT} )
#			list( APPEND OUTPUTS "METAL" )
#			set( OUTPUTS_PRETTY "${OUTPUTS_PRETTY}Metal, " )
#		endif()

		# essl
		if( NOT "${TYPE}" STREQUAL "COMPUTE" )
			set( ESSL_OUTPUT ${PROJECT_SOURCE_DIR}/build/shaders/essl/${FILENAME}.bin )
			shaderc_parse( ESSL ${COMMON} ANDROID OUTPUT ${ESSL_OUTPUT} )
			list( APPEND OUTPUTS "ESSL" )
			set( OUTPUTS_PRETTY "${OUTPUTS_PRETTY}ESSL, " )
		endif()

		# glsl
		set( GLSL_OUTPUT ${PROJECT_SOURCE_DIR}/build/shaders/glsl/${FILENAME}.bin )
		if( NOT "${TYPE}" STREQUAL "COMPUTE" )
			shaderc_parse( GLSL ${COMMON} LINUX PROFILE 120 OUTPUT ${GLSL_OUTPUT} )
		else()
			shaderc_parse( GLSL ${COMMON} LINUX PROFILE 430 OUTPUT ${GLSL_OUTPUT} )
		endif()
		list( APPEND OUTPUTS "GLSL" )
		set( OUTPUTS_PRETTY "${OUTPUTS_PRETTY}GLSL, " )

		# spirv
		if( NOT "${TYPE}" STREQUAL "COMPUTE" )
			set( SPIRV_OUTPUT ${PROJECT_SOURCE_DIR}/build/shaders/spirv/${FILENAME}.bin )
			shaderc_parse( SPIRV ${COMMON} LINUX PROFILE spirv OUTPUT ${SPIRV_OUTPUT} )
			list( APPEND OUTPUTS "SPIRV" )
			set( OUTPUTS_PRETTY "${OUTPUTS_PRETTY}SPIRV" )
			set( OUTPUT_FILES "" )
			set( COMMANDS "" )
		endif()

		foreach( OUT ${OUTPUTS} )
			list( APPEND OUTPUT_FILES ${${OUT}_OUTPUT} )
			list( APPEND COMMANDS COMMAND "${TOOL_SHADERC_EXE}" ${${OUT}} )
			get_filename_component( OUT_DIR ${${OUT}_OUTPUT} DIRECTORY )
			file( MAKE_DIRECTORY ${OUT_DIR} )
		endforeach()

		message("Custom command, abs: ${ABSOLUTE_FILE}   output_files: ${OUTPUT_FILES}    commands: ${COMMANDS}")

		# My version already depends on a relative path
		#file( RELATIVE_PATH PRINT_NAME ${PROJECT_SOURCE_DIR}/data/shaders/ ${FILE} )
		set(PRINT_NAME ${FILE})
		add_custom_command(
			MAIN_DEPENDENCY
			${ABSOLUTE_FILE}
			OUTPUT
			${OUTPUT_FILES}
			${COMMANDS}
			COMMENT "Compiling shader ${PRINT_NAME} for ${OUTPUTS_PRETTY}"
		)
	endif()
endfunction(add_eyos_shader)