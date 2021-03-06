cmake_minimum_required(VERSION 3.10)
project(DynamicSimulation)

find_package(Boost REQUIRED)

enable_testing()
find_package(GTest QUIET)

if(${GTest_FOUND})
  message(STATUS "Found google testing framework.")
  add_subdirectory(test)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${Boost_INCLUDE_DIRS}
                    lib/mechanical/include
                    lib/math/include
                    lib/gui/include
                    lib/gui
					lib/simulator/include)

add_subdirectory(lib/gui)
add_subdirectory(lib/math)
add_subdirectory(lib/mechanical)
add_subdirectory(lib/simulator)
add_subdirectory(lib/vrep)

if(${GTest_FOUND})
  add_executable(Test test/main.cpp)
  target_link_libraries(Test math mechanical GTest::GTest GTest::Main)
  set_target_properties( Test
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  )
endif()

add_executable(DynamicSimulation src/main.cpp)

set_target_properties( DynamicSimulation
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(DynamicSimulation gui)
