cmake_minimum_required(VERSION 3.23)
project(main)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(main main.cpp pet.cpp engine.cpp
        player.cpp enemy.cpp action.cpp)
