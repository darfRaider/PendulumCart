# Find includes in corresponding build directories
include_directories( ${CMAKE_BINARY_DIR} )

# Generate ui_mainwindow.h
find_package(Qt5Widgets REQUIRED)

QT5_WRAP_UI(QT_UIS_HDRS
            mainwindow.ui)


# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5PrintSupport)
message(STATUS "Found QT5 Widgets at ${Qt5Widgets_DIR}")



# Add GUI library 
add_library(gui STATIC
  qcustomplot.cpp 
  mainwindow.cpp 
  src/util.cpp
  ${QT_UIS_HDRS}
)

# Use the Widgets module from Qt 5.
target_link_libraries(gui mechanical Qt5::Widgets Qt5::PrintSupport)
