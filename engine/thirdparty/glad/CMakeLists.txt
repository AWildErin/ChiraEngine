cmake_minimum_required(VERSION 3.16)
project(glad)
set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

option(GLAD_USE_GL_41 "Use OpenGL 4.1 instead of OpenGL 4.3" ON)
if(APPLE OR GLAD_USE_GL_41)
    set(GLAD_GL_VERSION "41")
else()
    set(GLAD_GL_VERSION "43")
endif()

add_library(${PROJECT_NAME} STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/${GLAD_GL_VERSION}/include/glad/glversion.h
        ${CMAKE_CURRENT_SOURCE_DIR}/${GLAD_GL_VERSION}/include/glad/gl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/${GLAD_GL_VERSION}/src/gl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/${GLAD_GL_VERSION}/include/KHR/khrplatform.h)
target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC
        ${OPENGL_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/${GLAD_GL_VERSION}/include)
