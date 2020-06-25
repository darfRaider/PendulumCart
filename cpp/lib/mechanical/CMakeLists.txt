include_directories(include
  ../math/include)

add_library(mechanical SHARED
  src/Pendulum2d.cpp
  src/Physics.cpp
  )
target_link_libraries(mechanical math)
