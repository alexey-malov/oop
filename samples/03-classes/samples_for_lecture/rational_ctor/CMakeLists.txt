# CMakeList.txt : CMake project for rational_ctor, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (rational_ctor "rational_ctor.cpp" "rational_ctor.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET rational_ctor PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
