cmake_minimum_required(VERSION 3.25)
project(igv-pr-final)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(${PROJECT_NAME}
        igvCamara.cpp
        igvCamara.h
        igvEscena3D.cpp
        igvEscena3D.h
        igvInterfaz.cpp
        igvInterfaz.h
        igvPunto3D.cpp
        igvPunto3D.h
        main.cpp
)

if (LINUX)
    find_path(OPENGL_REGISTRY_INCLUDE_DIRS "GL/glcorearb.h")
    target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_REGISTRY_INCLUDE_DIRS})

    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

    find_package(GLUT REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE GLUT::GLUT)
endif ()

if (WIN32)
    find_package(opengl_system)
    target_link_libraries(${PROJECT_NAME} opengl::opengl)

    find_package(opengl-registry)
    target_link_libraries(${PROJECT_NAME} opengl-registry::opengl-registry)

    find_package(FreeGLUT)
    target_link_libraries(${PROJECT_NAME} FreeGLUT::freeglut_static)
endif ()
