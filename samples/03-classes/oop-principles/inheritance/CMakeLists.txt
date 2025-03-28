# Add source to this project's executable.
add_executable (inheritance "inheritance.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET inheritance PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
