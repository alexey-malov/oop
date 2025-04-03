# Add source to this project's executable.
add_executable (data_abstraction "data_abstraction.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET data_abstraction PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
