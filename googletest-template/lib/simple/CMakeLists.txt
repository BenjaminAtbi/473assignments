# Configure the library to be tested
add_library(simple)
target_sources(simple
  PRIVATE
    Parallelogram.cpp
    Matthews.cpp
    Awards.cpp
)
target_include_directories(simple
  PUBLIC
    include/
)
set_target_properties(simple PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 17
)

