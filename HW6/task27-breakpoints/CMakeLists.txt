cmake_minimum_required(VERSION 3.16)
project(task27_breakpoints)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DULYANIN)

add_executable(task27_breakpoints
        CMakeLists.txt
        main.cpp)
