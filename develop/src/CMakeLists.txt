cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name and version
project(server CXX)

# compile executable file
#add_executable(service server_service.cpp server_service.h ${COMMUNICATE} ${UTIL})
add_executable(serverApp server_service.cpp)

# set include directory
#target_include_directories(service PRIVATE ./communicate ./util)
