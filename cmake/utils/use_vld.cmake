# insert the option to use it:
if(WIN32)
    if(USE_VLD)
        message(STATUS "Set VLD variables")
        set(VLD_PFILES_X86 "PROGRAMFILES(X86)")
        set(VLD_PFILES "PROGRAMFILES")
        set(VLD_INCLUDE_PATH "$ENV{${VLD_PFILES_X86}}/Visual Leak Detector/include")
        set(VLD_LIB_PATH  "$ENV{${VLD_PFILES_X86}}/Visual Leak Detector/lib/Win64")
        set(VLD_DLL_PATH  "$ENV{${VLD_PFILES_X86}}/Visual Leak Detector/bin/Win64")
    endif()
endif(WIN32)


function( use_vld target )

if(USE_VLD AND WIN32)
    message(STATUS "Uses VLD")
    find_package(vld)
        target_link_libraries(${target}
        PRIVATE
        vld
        )
#copy over the required dll and xml file for vld to work:
get_target_property(VLD_DLL_DEST ${target} RUNTIME_OUTPUT_DIRECTORY)
target_compile_definitions(${target} PRIVATE USE_VLD)
message(STATUS "COPY VLD REQUIRED DLLS and MANIFEST TO FILES FROM ${VLD_DLL_PATH} TO ${VLD_DLL_DEST}")
file(COPY "${VLD_DLL_PATH}/" DESTINATION "${VLD_DLL_DEST}")
endif(USE_VLD AND WIN32)
endfunction(use_vld)