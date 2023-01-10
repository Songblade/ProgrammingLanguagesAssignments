cmake_minimum_required(VERSION 3.23)
project(release2)

set(CMAKE_CXX_STANDARD 14)

add_executable(release2
        main.cpp
        Duck.hpp
        Duck.cpp
        AllMyDucks.hpp
        AllMyDucks.cpp
        Behaviors.cpp
        Behaviors.hpp)
