cmake_minimum_required(VERSION 3.5.0)

set(TARGET opengl-first)

project(${TARGET} VERSION 0.1.0 LANGUAGES C CXX)

# OpenGL
find_package( OpenGL REQUIRED )

# NOTE: this causes a link error when adding GLAD
# include_directories( ${OPENGL_INCLUDE_DIRS} )

# GLFW
set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set( GLAD_GL "" )
add_subdirectory( glfw )

option( GLFW-CMAKE-STARTER-USE-GLFW-GLAD "Use GLAD from GLFW" OFF )

if( GLFW-CMAKE-STARTER-USE-GLFW-GLAD )
    include_directories("${GLFW_SOURCE_DIR}/deps")
    set( GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h" )
endif()

# GLAD
# add_subdirectory(glad)
include_directories( SYSTEM "glad/include" )

add_executable(${TARGET} main.cpp glad/src/glad.c)

target_link_libraries( ${TARGET} ${OPENGL_LIBRARIES} glfw )
