cmake_minimum_required(VERSION 3.23)
project(release1)

set(CMAKE_CXX_STANDARD 14)

add_executable(release1
        main.cpp
        Duck.hpp
        Duck.cpp
        AllMyDucks.hpp
        AllMyDucks.cpp)

