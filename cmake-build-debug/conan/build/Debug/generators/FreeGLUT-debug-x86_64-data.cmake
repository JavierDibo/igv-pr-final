########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

list(APPEND freeglut_COMPONENT_NAMES FreeGLUT::freeglut_static)
list(REMOVE_DUPLICATES freeglut_COMPONENT_NAMES)
list(APPEND freeglut_FIND_DEPENDENCY_NAMES glu opengl_system)
list(REMOVE_DUPLICATES freeglut_FIND_DEPENDENCY_NAMES)
set(glu_FIND_MODE "NO_MODULE")
set(opengl_system_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(freeglut_PACKAGE_FOLDER_DEBUG "C:/Users/jfdg0/.conan2/p/b/freegce335745f9483/p")
set(freeglut_BUILD_MODULES_PATHS_DEBUG )


set(freeglut_INCLUDE_DIRS_DEBUG "${freeglut_PACKAGE_FOLDER_DEBUG}/include")
set(freeglut_RES_DIRS_DEBUG )
set(freeglut_DEFINITIONS_DEBUG "-DFREEGLUT_STATIC=1"
			"-DFREEGLUT_LIB_PRAGMAS=0")
set(freeglut_SHARED_LINK_FLAGS_DEBUG )
set(freeglut_EXE_LINK_FLAGS_DEBUG )
set(freeglut_OBJECTS_DEBUG )
set(freeglut_COMPILE_DEFINITIONS_DEBUG "FREEGLUT_STATIC=1"
			"FREEGLUT_LIB_PRAGMAS=0")
set(freeglut_COMPILE_OPTIONS_C_DEBUG )
set(freeglut_COMPILE_OPTIONS_CXX_DEBUG )
set(freeglut_LIB_DIRS_DEBUG "${freeglut_PACKAGE_FOLDER_DEBUG}/lib")
set(freeglut_BIN_DIRS_DEBUG )
set(freeglut_LIBRARY_TYPE_DEBUG STATIC)
set(freeglut_IS_HOST_WINDOWS_DEBUG 1)
set(freeglut_LIBS_DEBUG glut)
set(freeglut_SYSTEM_LIBS_DEBUG glu32 gdi32 winmm user32)
set(freeglut_FRAMEWORK_DIRS_DEBUG )
set(freeglut_FRAMEWORKS_DEBUG )
set(freeglut_BUILD_DIRS_DEBUG )
set(freeglut_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(freeglut_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${freeglut_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${freeglut_COMPILE_OPTIONS_C_DEBUG}>")
set(freeglut_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${freeglut_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${freeglut_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${freeglut_EXE_LINK_FLAGS_DEBUG}>")


set(freeglut_COMPONENTS_DEBUG FreeGLUT::freeglut_static)
########### COMPONENT FreeGLUT::freeglut_static VARIABLES ############################################

set(freeglut_FreeGLUT_freeglut_static_INCLUDE_DIRS_DEBUG "${freeglut_PACKAGE_FOLDER_DEBUG}/include")
set(freeglut_FreeGLUT_freeglut_static_LIB_DIRS_DEBUG "${freeglut_PACKAGE_FOLDER_DEBUG}/lib")
set(freeglut_FreeGLUT_freeglut_static_BIN_DIRS_DEBUG )
set(freeglut_FreeGLUT_freeglut_static_LIBRARY_TYPE_DEBUG STATIC)
set(freeglut_FreeGLUT_freeglut_static_IS_HOST_WINDOWS_DEBUG 1)
set(freeglut_FreeGLUT_freeglut_static_RES_DIRS_DEBUG )
set(freeglut_FreeGLUT_freeglut_static_DEFINITIONS_DEBUG "-DFREEGLUT_STATIC=1"
			"-DFREEGLUT_LIB_PRAGMAS=0")
set(freeglut_FreeGLUT_freeglut_static_OBJECTS_DEBUG )
set(freeglut_FreeGLUT_freeglut_static_COMPILE_DEFINITIONS_DEBUG "FREEGLUT_STATIC=1"
			"FREEGLUT_LIB_PRAGMAS=0")
set(freeglut_FreeGLUT_freeglut_static_COMPILE_OPTIONS_C_DEBUG "")
set(freeglut_FreeGLUT_freeglut_static_COMPILE_OPTIONS_CXX_DEBUG "")
set(freeglut_FreeGLUT_freeglut_static_LIBS_DEBUG glut)
set(freeglut_FreeGLUT_freeglut_static_SYSTEM_LIBS_DEBUG glu32 gdi32 winmm user32)
set(freeglut_FreeGLUT_freeglut_static_FRAMEWORK_DIRS_DEBUG )
set(freeglut_FreeGLUT_freeglut_static_FRAMEWORKS_DEBUG )
set(freeglut_FreeGLUT_freeglut_static_DEPENDENCIES_DEBUG opengl::opengl glu::glu)
set(freeglut_FreeGLUT_freeglut_static_SHARED_LINK_FLAGS_DEBUG )
set(freeglut_FreeGLUT_freeglut_static_EXE_LINK_FLAGS_DEBUG )
set(freeglut_FreeGLUT_freeglut_static_NO_SONAME_MODE_DEBUG FALSE)

# COMPOUND VARIABLES
set(freeglut_FreeGLUT_freeglut_static_LINKER_FLAGS_DEBUG
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${freeglut_FreeGLUT_freeglut_static_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${freeglut_FreeGLUT_freeglut_static_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${freeglut_FreeGLUT_freeglut_static_EXE_LINK_FLAGS_DEBUG}>
)
set(freeglut_FreeGLUT_freeglut_static_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${freeglut_FreeGLUT_freeglut_static_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${freeglut_FreeGLUT_freeglut_static_COMPILE_OPTIONS_C_DEBUG}>")