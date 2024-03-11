cmake_minimum_required(VERSION 3.26)
project(lab2_1)

set(CMAKE_CXX_STANDARD 17)


# Add executable target
add_executable(main main.cpp BenchmarkMode.cpp DemonstrationMode.cpp UserManagementMode.cpp struct.h)
