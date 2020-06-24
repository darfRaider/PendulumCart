cmake_minimum_required(VERSION 2.8)
find_package(Qt5 COMPONENTS Widgets)
include_directories(include build
${Qt5Widgets_INCLUDE_DIRS})
SET(CMAKE_AUTOUIC ON)  
				  
#qt5_wrap_ui (mainwindow  mainwindow.ui)

add_library(gui STATIC
  src/GUI.cpp
  src/qcustomplot.cpp
  src/mainwindow.cpp
)

target_compile_options(gui PRIVATE -fPIC)
