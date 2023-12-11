# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(opengl-registry_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(opengl-registry_FRAMEWORKS_FOUND_DEBUG "${opengl-registry_FRAMEWORKS_DEBUG}" "${opengl-registry_FRAMEWORK_DIRS_DEBUG}")

set(opengl-registry_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET opengl-registry_DEPS_TARGET)
    add_library(opengl-registry_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET opengl-registry_DEPS_TARGET
             PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${opengl-registry_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${opengl-registry_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:khrplatform::khrplatform>
             APPEND)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### opengl-registry_DEPS_TARGET to all of them
conan_package_library_targets("${opengl-registry_LIBS_DEBUG}"    # libraries
                              "${opengl-registry_LIB_DIRS_DEBUG}" # package_libdir
                              "${opengl-registry_BIN_DIRS_DEBUG}" # package_bindir
                              "${opengl-registry_LIBRARY_TYPE_DEBUG}"
                              "${opengl-registry_IS_HOST_WINDOWS_DEBUG}"
                              opengl-registry_DEPS_TARGET
                              opengl-registry_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "opengl-registry"    # package_name
                              "${opengl-registry_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${opengl-registry_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Debug ########################################
    set_property(TARGET opengl-registry::opengl-registry
                 PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${opengl-registry_OBJECTS_DEBUG}>
                 $<$<CONFIG:Debug>:${opengl-registry_LIBRARIES_TARGETS}>
                 APPEND)

    if("${opengl-registry_LIBS_DEBUG}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET opengl-registry::opengl-registry
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     opengl-registry_DEPS_TARGET
                     APPEND)
    endif()

    set_property(TARGET opengl-registry::opengl-registry
                 PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Debug>:${opengl-registry_LINKER_FLAGS_DEBUG}> APPEND)
    set_property(TARGET opengl-registry::opengl-registry
                 PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Debug>:${opengl-registry_INCLUDE_DIRS_DEBUG}> APPEND)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET opengl-registry::opengl-registry
                 PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Debug>:${opengl-registry_LIB_DIRS_DEBUG}> APPEND)
    set_property(TARGET opengl-registry::opengl-registry
                 PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Debug>:${opengl-registry_COMPILE_DEFINITIONS_DEBUG}> APPEND)
    set_property(TARGET opengl-registry::opengl-registry
                 PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Debug>:${opengl-registry_COMPILE_OPTIONS_DEBUG}> APPEND)

########## For the modules (FindXXX)
set(opengl-registry_LIBRARIES_DEBUG opengl-registry::opengl-registry)
