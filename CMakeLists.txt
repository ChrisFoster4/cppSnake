cmake_minimum_required(VERSION 3.00)
project(cppSnake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lpthread -lglut -lGL -Wall -fpermissive")

add_executable(cppSnake
        main.h
        main.cpp
        snake.h
        snake.cpp
        .
        fruit.cpp fruit.h)
