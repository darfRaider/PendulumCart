# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport)

QT5_WRAP_UI(QT_UIS_HDRS
            mainwindow.ui)

# Add GUI library 
add_library(dynSimGUI qcustomplot.cpp mainwindow.cpp ${QT_UIS_HDRS})

# Use the Widgets module from Qt 5.
target_link_libraries(dynSimGUI Qt5::Widgets Qt5::PrintSupport)
  

