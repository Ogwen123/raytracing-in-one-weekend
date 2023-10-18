cmake_minimum_required(VERSION 3.26)
project(raytracing_iow)

set(CMAKE_CXX_STANDARD 17)

add_executable(raytracing_iow main.cpp
        include/ray.h)
