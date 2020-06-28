cmake_minimum_required(VERSION 3.2)
project(DynamicSimulation)

enable_testing()
find_package(GTest QUIET)
if(${GTest_FOUND})
  message(STATUS "Found google testing framework.")
  add_subdirectory(test)
endif()

#cmake_policy(SET CMP0020 OLD) # needed by win10
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(lib/mechanical/include
                    lib/math/include
                    lib/gui)

add_subdirectory(lib/gui)
add_subdirectory(lib/math)
add_subdirectory(lib/mechanical)

if(${GTest_FOUND})
  add_executable(Test test/main.cpp)
  target_link_libraries(Test GTest::GTest GTest::Main)
endif()

add_executable(DynamicSimulation src/main.cpp)

#TODO: DO the following for google tests
set_target_properties( DynamicSimulation
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
target_link_libraries(DynamicSimulation gui)
