# Find includes in corresponding build directories
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

if (${CMAKE_VERSION} LESS "3.10")
  cmake_policy(SET CMP0071 NEW)
endif()

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport)

# Generate ui_mainwindow.h
QT5_WRAP_UI(QT_UIS_HDRS
            mainwindow.ui)

# Add GUI library 
add_library(gui STATIC
  qcustomplot.cpp 
  mainwindow.cpp 
  ${QT_UIS_HDRS})

# Use the Widgets module from Qt 5.
target_link_libraries(gui Qt5::Widgets Qt5::PrintSupport)
