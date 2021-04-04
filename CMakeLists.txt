cmake_minimum_required(VERSION 3.17)
project(cryptarithmetic_puzzles VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
set(SOURCES src/Node.cpp src/Utils.cpp main.cpp)
add_executable(cryptarithmetic_puzzles ${SOURCES})