########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(opengl-registry_FIND_QUIETLY)
    set(opengl-registry_MESSAGE_MODE VERBOSE)
else()
    set(opengl-registry_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/opengl-registryTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${opengl-registry_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(opengl-registry_VERSION_STRING "cci.20220929")
set(opengl-registry_INCLUDE_DIRS ${opengl-registry_INCLUDE_DIRS_DEBUG} )
set(opengl-registry_INCLUDE_DIR ${opengl-registry_INCLUDE_DIRS_DEBUG} )
set(opengl-registry_LIBRARIES ${opengl-registry_LIBRARIES_DEBUG} )
set(opengl-registry_DEFINITIONS ${opengl-registry_DEFINITIONS_DEBUG} )

# Only the first installed configuration is included to avoid the collision
foreach(_BUILD_MODULE ${opengl-registry_BUILD_MODULES_PATHS_DEBUG} )
    message(${opengl-registry_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


