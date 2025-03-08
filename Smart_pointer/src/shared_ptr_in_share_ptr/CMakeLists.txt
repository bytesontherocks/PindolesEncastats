cmake_minimum_required(VERSION 3.13)

set(ProjectName "shared_ptr_in_share_ptr")
project(${ProjectName} CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${ProjectName})
target_sources(${ProjectName}  PUBLIC  src/main.cpp)
target_link_libraries(${ProjectName} ${CMAKE_THREAD_LIBS_INIT} )
