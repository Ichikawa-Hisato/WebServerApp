cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name and version
project(httpSample CXX)

# find package
find_package(Threads REQUIRED)

# compile executable file
add_executable(serverSample serverSample.cpp)
add_executable(clientSample clientSample.cpp)

# module, library, target link
target_link_libraries(serverSample PUBLIC "-pthread")
target_link_libraries(clientSample PUBLIC "-pthread")
