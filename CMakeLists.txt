# cmake_minimum_required(VERSION <specify CMake version here>)
project(BMP_Reader)

set(CMAKE_CXX_STANDARD 14)

add_executable(BMP_Reader main.cpp bmp.cpp bmp.h)