########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(opengl-registry_COMPONENT_NAMES "")
list(APPEND opengl-registry_FIND_DEPENDENCY_NAMES khrplatform)
list(REMOVE_DUPLICATES opengl-registry_FIND_DEPENDENCY_NAMES)
set(khrplatform_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(opengl-registry_PACKAGE_FOLDER_DEBUG "C:/Users/jfdg0/.conan2/p/opengd9728560ae872/p")
set(opengl-registry_BUILD_MODULES_PATHS_DEBUG )


set(opengl-registry_INCLUDE_DIRS_DEBUG "${opengl-registry_PACKAGE_FOLDER_DEBUG}/include")
set(opengl-registry_RES_DIRS_DEBUG )
set(opengl-registry_DEFINITIONS_DEBUG )
set(opengl-registry_SHARED_LINK_FLAGS_DEBUG )
set(opengl-registry_EXE_LINK_FLAGS_DEBUG )
set(opengl-registry_OBJECTS_DEBUG )
set(opengl-registry_COMPILE_DEFINITIONS_DEBUG )
set(opengl-registry_COMPILE_OPTIONS_C_DEBUG )
set(opengl-registry_COMPILE_OPTIONS_CXX_DEBUG )
set(opengl-registry_LIB_DIRS_DEBUG )
set(opengl-registry_BIN_DIRS_DEBUG )
set(opengl-registry_LIBRARY_TYPE_DEBUG UNKNOWN)
set(opengl-registry_IS_HOST_WINDOWS_DEBUG 1)
set(opengl-registry_LIBS_DEBUG )
set(opengl-registry_SYSTEM_LIBS_DEBUG )
set(opengl-registry_FRAMEWORK_DIRS_DEBUG )
set(opengl-registry_FRAMEWORKS_DEBUG )
set(opengl-registry_BUILD_DIRS_DEBUG )
set(opengl-registry_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(opengl-registry_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${opengl-registry_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${opengl-registry_COMPILE_OPTIONS_C_DEBUG}>")
set(opengl-registry_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${opengl-registry_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${opengl-registry_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${opengl-registry_EXE_LINK_FLAGS_DEBUG}>")


set(opengl-registry_COMPONENTS_DEBUG )