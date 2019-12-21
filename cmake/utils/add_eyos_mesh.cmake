# add_eyos_mesh <FILE>
# 
# === Brief:
# Add a custom build command for .obj (wavefront) model file. To be compiled to a BGFX .bin file.
#
# === Arguments:
# <FILE> : A relative path from '${PROJECT_SOURCE_DIR}/data/' to a .obj model file
# 
# === Description:
# A model will be compiled to a BGFX .bin file. the relative file will be placed in: '${PROJECT_SOURCE_DIR}/build/${FILENAME}.bin'
# 
# === Note:
# You still need to add the file as a dependency to a project in order for it to be compiled.
function(add_eyos_mesh FILE)
	set(INPUT_DIRECTORY_PREFIX "${PROJECT_SOURCE_DIR}/data")
	set(OUTPUT_DIRECTORY_PREFIX "${PROJECT_SOURCE_DIR}/build")
	get_filename_component(FILENAME ${FILE} NAME_WE)
	get_filename_component(FILE_DIRECTORY ${FILE} DIRECTORY)
	set(BIN_FILE "${FILE_DIRECTORY}/${FILENAME}.bin")
	set(ABS_BIN_FILE "${OUTPUT_DIRECTORY_PREFIX}/${BIN_FILE}")
	set(ABS_INPUT_FILE "${INPUT_DIRECTORY_PREFIX}/${FILE}")


	file( MAKE_DIRECTORY "${OUTPUT_DIRECTORY_PREFIX}/${FILE_DIRECTORY}")
	add_custom_command(
		MAIN_DEPENDENCY
		${ABS_INPUT_FILE}
		OUTPUT
		${ABS_BIN_FILE}
		COMMAND
		"${TOOL_GEOMETRYC_EXE}" "-f" "${ABS_INPUT_FILE}" "-o" "${ABS_BIN_FILE}"
		COMMENT "Compiling .obj model ${FILE} to ${BIN_FILE}"
	)
endfunction(add_eyos_mesh)