include_directories(include)
add_library(mechanical STATIC
  src/Pendulum2d.cpp
  src/Physics.cpp
  )

target_compile_options(mechanical PRIVATE -std=c++11)
