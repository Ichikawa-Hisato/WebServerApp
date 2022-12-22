cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# set the project name and version
project(server)

# compile executable file
add_executable(service server_service.cpp)
