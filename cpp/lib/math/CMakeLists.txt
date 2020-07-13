include_directories(include)
find_package(Qt5Widgets)                                                                                 
add_library(math INTERFACE)
target_link_libraries(math INTERFACE Qt5::Widgets)
