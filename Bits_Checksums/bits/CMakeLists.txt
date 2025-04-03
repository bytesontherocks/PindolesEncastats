cmake_minimum_required(VERSION 3.13)

set(ProjectName "BitsAndTemplates")
project(${ProjectName} CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -Werror")

add_executable(${ProjectName})
target_sources(${ProjectName}  PUBLIC  src/main.cpp)
target_link_libraries(${ProjectName} ${CMAKE_THREAD_LIBS_INIT} )
