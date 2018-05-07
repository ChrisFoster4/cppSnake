#cmake_minimum_required(VERSION 3.10)
cmake_minimum_required(VERSION 3.00)
project(cppSnake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -lglut -lGL -Wall -fpermissive")

#find_package(OpenGl REQUIRED)
#find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

#include_directories(.)
include_directories(
        ${PROJECT_SOURCE_DIR}
        ${FREEGLUT_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        .
)

#target_link_libraries(testas ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
add_executable(cppSnake
        main.cpp
        main.h
        projectile.cpp
        projectile.h)
