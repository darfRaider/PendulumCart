cmake_minimum_required(VERSION 3.10)
project(DynamicSimulation)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Includes
include_directories(lib/mechanical/include
                    lib/math/include
                    lib/gui/include
					lib/gui)
					#                    lib/vrep/include)

# Folders containing CMakeFiles				  
add_subdirectory(lib/gui)
add_subdirectory(lib/math)
add_subdirectory(lib/mechanical)
add_subdirectory(lib/vrep)

# Google Test
find_package(GTest QUIET)
if(${GTest_FOUND})
  message(STATUS "Found google testing framework.")
  enable_testing()
  add_subdirectory(test)  

  add_executable(Test test/main.cpp)
  target_link_libraries(Test math mechanical GTest::GTest GTest::Main)
  set_target_properties( Test
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  )
endif()

# Find generate executable
add_executable(DynamicSimulation src/main.cpp)
set_target_properties( DynamicSimulation
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
target_link_libraries(DynamicSimulation gui)
