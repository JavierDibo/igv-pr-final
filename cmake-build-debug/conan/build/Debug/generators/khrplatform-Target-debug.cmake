# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(khrplatform_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(khrplatform_FRAMEWORKS_FOUND_DEBUG "${khrplatform_FRAMEWORKS_DEBUG}" "${khrplatform_FRAMEWORK_DIRS_DEBUG}")

set(khrplatform_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET khrplatform_DEPS_TARGET)
    add_library(khrplatform_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET khrplatform_DEPS_TARGET
             PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${khrplatform_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${khrplatform_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:>
             APPEND)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### khrplatform_DEPS_TARGET to all of them
conan_package_library_targets("${khrplatform_LIBS_DEBUG}"    # libraries
                              "${khrplatform_LIB_DIRS_DEBUG}" # package_libdir
                              "${khrplatform_BIN_DIRS_DEBUG}" # package_bindir
                              "${khrplatform_LIBRARY_TYPE_DEBUG}"
                              "${khrplatform_IS_HOST_WINDOWS_DEBUG}"
                              khrplatform_DEPS_TARGET
                              khrplatform_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "khrplatform"    # package_name
                              "${khrplatform_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${khrplatform_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Debug ########################################
    set_property(TARGET khrplatform::khrplatform
                 PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${khrplatform_OBJECTS_DEBUG}>
                 $<$<CONFIG:Debug>:${khrplatform_LIBRARIES_TARGETS}>
                 APPEND)

    if("${khrplatform_LIBS_DEBUG}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET khrplatform::khrplatform
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     khrplatform_DEPS_TARGET
                     APPEND)
    endif()

    set_property(TARGET khrplatform::khrplatform
                 PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Debug>:${khrplatform_LINKER_FLAGS_DEBUG}> APPEND)
    set_property(TARGET khrplatform::khrplatform
                 PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Debug>:${khrplatform_INCLUDE_DIRS_DEBUG}> APPEND)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET khrplatform::khrplatform
                 PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Debug>:${khrplatform_LIB_DIRS_DEBUG}> APPEND)
    set_property(TARGET khrplatform::khrplatform
                 PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Debug>:${khrplatform_COMPILE_DEFINITIONS_DEBUG}> APPEND)
    set_property(TARGET khrplatform::khrplatform
                 PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Debug>:${khrplatform_COMPILE_OPTIONS_DEBUG}> APPEND)

########## For the modules (FindXXX)
set(khrplatform_LIBRARIES_DEBUG khrplatform::khrplatform)
