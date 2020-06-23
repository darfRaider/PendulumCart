include_directories(${odePendulum_SOURCE_DIR}/include)

find_package(Boost)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

message(STATUS "QT5 include" ${Qt5Widgets_LIBRARIES_DIRS})

add_library(Misc STATIC Pendulum2d.cpp
						Physics.cpp)
						

add_executable(Program main.cpp)
target_link_libraries(Program ${Boost_LIBRARIES} ${Qt5Widgets_LIBRARIES} Misc)

