# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(freeglut_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(freeglut_FRAMEWORKS_FOUND_DEBUG "${freeglut_FRAMEWORKS_DEBUG}" "${freeglut_FRAMEWORK_DIRS_DEBUG}")

set(freeglut_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET freeglut_DEPS_TARGET)
    add_library(freeglut_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET freeglut_DEPS_TARGET
             PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${freeglut_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${freeglut_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:opengl::opengl;glu::glu>
             APPEND)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### freeglut_DEPS_TARGET to all of them
conan_package_library_targets("${freeglut_LIBS_DEBUG}"    # libraries
                              "${freeglut_LIB_DIRS_DEBUG}" # package_libdir
                              "${freeglut_BIN_DIRS_DEBUG}" # package_bindir
                              "${freeglut_LIBRARY_TYPE_DEBUG}"
                              "${freeglut_IS_HOST_WINDOWS_DEBUG}"
                              freeglut_DEPS_TARGET
                              freeglut_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "freeglut"    # package_name
                              "${freeglut_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${freeglut_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## COMPONENTS TARGET PROPERTIES Debug ########################################

    ########## COMPONENT GLUT::GLUT #############

        set(freeglut_GLUT_GLUT_FRAMEWORKS_FOUND_DEBUG "")
        conan_find_apple_frameworks(freeglut_GLUT_GLUT_FRAMEWORKS_FOUND_DEBUG "${freeglut_GLUT_GLUT_FRAMEWORKS_DEBUG}" "${freeglut_GLUT_GLUT_FRAMEWORK_DIRS_DEBUG}")

        set(freeglut_GLUT_GLUT_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET freeglut_GLUT_GLUT_DEPS_TARGET)
            add_library(freeglut_GLUT_GLUT_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET freeglut_GLUT_GLUT_DEPS_TARGET
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Debug>:${freeglut_GLUT_GLUT_FRAMEWORKS_FOUND_DEBUG}>
                     $<$<CONFIG:Debug>:${freeglut_GLUT_GLUT_SYSTEM_LIBS_DEBUG}>
                     $<$<CONFIG:Debug>:${freeglut_GLUT_GLUT_DEPENDENCIES_DEBUG}>
                     APPEND)

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'freeglut_GLUT_GLUT_DEPS_TARGET' to all of them
        conan_package_library_targets("${freeglut_GLUT_GLUT_LIBS_DEBUG}"
                              "${freeglut_GLUT_GLUT_LIB_DIRS_DEBUG}"
                              "${freeglut_GLUT_GLUT_BIN_DIRS_DEBUG}" # package_bindir
                              "${freeglut_GLUT_GLUT_LIBRARY_TYPE_DEBUG}"
                              "${freeglut_GLUT_GLUT_IS_HOST_WINDOWS_DEBUG}"
                              freeglut_GLUT_GLUT_DEPS_TARGET
                              freeglut_GLUT_GLUT_LIBRARIES_TARGETS
                              "_DEBUG"
                              "freeglut_GLUT_GLUT"
                              "${freeglut_GLUT_GLUT_NO_SONAME_MODE_DEBUG}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET GLUT::GLUT
                     PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Debug>:${freeglut_GLUT_GLUT_OBJECTS_DEBUG}>
                     $<$<CONFIG:Debug>:${freeglut_GLUT_GLUT_LIBRARIES_TARGETS}>
                     APPEND)

        if("${freeglut_GLUT_GLUT_LIBS_DEBUG}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET GLUT::GLUT
                         PROPERTY INTERFACE_LINK_LIBRARIES
                         freeglut_GLUT_GLUT_DEPS_TARGET
                         APPEND)
        endif()

        set_property(TARGET GLUT::GLUT PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Debug>:${freeglut_GLUT_GLUT_LINKER_FLAGS_DEBUG}> APPEND)
        set_property(TARGET GLUT::GLUT PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Debug>:${freeglut_GLUT_GLUT_INCLUDE_DIRS_DEBUG}> APPEND)
        set_property(TARGET GLUT::GLUT PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Debug>:${freeglut_GLUT_GLUT_LIB_DIRS_DEBUG}> APPEND)
        set_property(TARGET GLUT::GLUT PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Debug>:${freeglut_GLUT_GLUT_COMPILE_DEFINITIONS_DEBUG}> APPEND)
        set_property(TARGET GLUT::GLUT PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Debug>:${freeglut_GLUT_GLUT_COMPILE_OPTIONS_DEBUG}> APPEND)

    ########## AGGREGATED GLOBAL TARGET WITH THE COMPONENTS #####################
    set_property(TARGET GLUT::GLUT PROPERTY INTERFACE_LINK_LIBRARIES GLUT::GLUT APPEND)

########## For the modules (FindXXX)
set(freeglut_LIBRARIES_DEBUG GLUT::GLUT)
