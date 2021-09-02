cmake_minimum_required(VERSION 3.13)

project(Sandbox CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(Sandbox)
target_sources(Sandbox  PUBLIC  src/main.cpp src/Mutex.hpp)
target_link_libraries( Sandbox ${CMAKE_THREAD_LIBS_INIT} )