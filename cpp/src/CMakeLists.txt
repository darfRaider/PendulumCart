cmake_minimum_required(VERSION 2.8.11)

#project(DynSimGUI)

message(STATUS $ENV{QT5_DIR})
if($ENV{QT5_DIR})
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{QT5_DIR}/lib/cmake")
endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5PrintSupport)

QT5_WRAP_UI(QT_UIS_HDRS
            mainwindow.ui)

# Tell CMake to create the helloworld executable
add_executable(dynSimGUI qcustomplot.cpp main.cpp mainwindow.cpp ${QT_UIS_HDRS})
add_library(dynSimGUIlib qcustomplot.cpp mainwindow.cpp ${QT_UIS_HDRS})
add_executable(testexe main.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(dynSimGUI Qt5::Widgets Qt5::PrintSupport)
target_link_libraries(dynSimGUIlib Qt5::Widgets Qt5::PrintSupport)
target_link_libraries(testexe dynSimGUIlib)
  

