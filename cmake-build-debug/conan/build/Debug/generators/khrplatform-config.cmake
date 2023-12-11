########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(khrplatform_FIND_QUIETLY)
    set(khrplatform_MESSAGE_MODE VERBOSE)
else()
    set(khrplatform_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/khrplatformTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${khrplatform_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(khrplatform_VERSION_STRING "cci.20200529")
set(khrplatform_INCLUDE_DIRS ${khrplatform_INCLUDE_DIRS_DEBUG} )
set(khrplatform_INCLUDE_DIR ${khrplatform_INCLUDE_DIRS_DEBUG} )
set(khrplatform_LIBRARIES ${khrplatform_LIBRARIES_DEBUG} )
set(khrplatform_DEFINITIONS ${khrplatform_DEFINITIONS_DEBUG} )

# Only the first installed configuration is included to avoid the collision
foreach(_BUILD_MODULE ${khrplatform_BUILD_MODULES_PATHS_DEBUG} )
    message(${khrplatform_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


