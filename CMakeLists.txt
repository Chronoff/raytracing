cmake_minimum_required(VERSION 3.10)
project(raytracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(app src/main.cpp)

target_include_directories(app PRIVATE include)


