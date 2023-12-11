# Load the debug and release variables
get_filename_component(_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
file(GLOB DATA_FILES "${_DIR}/opengl-registry-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${opengl-registry_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${opengl-registry_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET opengl-registry::opengl-registry)
    add_library(opengl-registry::opengl-registry INTERFACE IMPORTED)
    message(${opengl-registry_MESSAGE_MODE} "Conan: Target declared 'opengl-registry::opengl-registry'")
endif()
# Load the debug and release library finders
get_filename_component(_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
file(GLOB CONFIG_FILES "${_DIR}/opengl-registry-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()