cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 11)
project(odePendulum)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${odePendulum_SOURCE_DIR}/bin)
#add_compile_options(-fPIC)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c++11 -fext-numeric-literals")

add_subdirectory(src)


