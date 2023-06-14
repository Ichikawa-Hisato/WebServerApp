cmake_minimum_required(VERSION 3.1)
project(sampleApp CXX)

set(LIBRARY_NAME lib/lib.cpp)
add_library(library STATIC ${LIBRARY_NAME})

add_executable(sampleApp sampleApp.cpp)

target_link_libraries(sampleApp library)
target_include_directories(library INTERFACE ./lib)
