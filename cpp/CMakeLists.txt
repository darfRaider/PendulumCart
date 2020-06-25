cmake_minimum_required(VERSION 2.8)

# set the project name
project(DynSim)

enable_testing()
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(src/mechanical/include
					src/math/include)
add_subdirectory(src)
add_subdirectory(test)

#add_executable(DynSim src/main.cpp)
add_executable(Test test/main.cpp)
add_executable(Gui src/main.cpp)

#set_target_properties( DynSim Test
#    PROPERTIES
#    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
#)
target_link_libraries(Test GTest::GTest GTest::Main)
#target_link_libraries(DynSim mechanical math)
target_link_libraries(Gui dynSimGUIlib)
