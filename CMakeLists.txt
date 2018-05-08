#cmake_minimum_required(VERSION 3.10)
cmake_minimum_required(VERSION 3.00)
project(cppSnake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lpthread -lglut -lGL -Wall -fpermissive")


#include_directories(
#        ${PROJECT_SOURCE_DIR}
#        ${FREEGLUT_INCLUDE_DIR}
#        ${GLEW_INCLUDE_DIR}
#        ${OPENGL_INCLUDE_DIR}
#        .
#)
#find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)

#include_directories(.)

#target_link_libraries(testas ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
add_executable(cppSnake
        main.h
        main.cpp
        projectile.h
        projectile.cpp
        .
        )
