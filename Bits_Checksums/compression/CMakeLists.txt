cmake_minimum_required(VERSION 3.13)

set(ProjectName "Compression")
project(${ProjectName} CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(${ProjectName})
target_sources(${ProjectName}  PUBLIC  src/main.cpp)
target_link_libraries(${ProjectName} ${CMAKE_THREAD_LIBS_INIT} )
