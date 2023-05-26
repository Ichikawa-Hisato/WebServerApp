cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name and version
project(server CXX)

# compile executable file
add_executable(sampleApp sampleApp.cpp)

# set include directory
#target_include_directories(service PRIVATE ./communicate ./util)
