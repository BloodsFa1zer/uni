cmake_minimum_required(VERSION 3.27)
project(lab2_6)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2_6 main.cpp
        benchmark_MacOS.h
        benchmark_Windows.h)
