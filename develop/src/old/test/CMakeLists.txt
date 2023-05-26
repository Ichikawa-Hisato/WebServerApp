cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name and version
project(sample)

# compile executable file
add_executable(sample sample.cpp)
