include_directories(${odePendulum_SOURCE_DIR}/include)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_library(Mechanical STATIC Pendulum2d.cpp
							  Physics.cpp)
						
add_executable(Program main.cpp)
target_link_libraries(Program ${Boost_LIBRARIES} Mechanical)
