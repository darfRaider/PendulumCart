find_package(Qt5 COMPONENTS Widgets)
include_directories(include
					${Qt5Widgets_INCLUDE_DIRS})
add_library(gui STATIC
  src/GUI.cpp
)

target_compile_options(gui PRIVATE -fPIC)
