include_directories(include)
find_package(Qt5Widgets)                                                                                 
add_library(math INTERFACE)
add_library(matrix STATIC
			src/Matrix.c)
target_link_libraries(math INTERFACE Qt5::Widgets)
