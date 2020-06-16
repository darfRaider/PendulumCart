cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 11)
project(TestProject)
add_compile_options(-fPIC)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=gnu++11")
add_subdirectory(src)


