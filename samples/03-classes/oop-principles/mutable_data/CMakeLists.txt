# Add source to this project's executable.
add_executable (mutable_data "mutable_data.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET mutable_data PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
