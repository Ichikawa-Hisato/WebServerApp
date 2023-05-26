cmake_minimum_required(VERSION 3.1)
project(sampleApp CXX)
add_executable(sampleApp sampleApp.cpp)
target_include_directories(sampleApp PRIVATE ./util)
