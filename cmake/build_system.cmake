# build system.cmake

# All source files
include(${CMAKE_SOURCE_DIR}/cmake/sources.cmake)

# All header files
include_directories(${CMAKE_SOURCE_DIR}/headers)

# clang-tidy checks
include(${CMAKE_SOURCE_DIR}/cmake/checks.cmake)

# Add Tests
include(${CMAKE_SOURCE_DIR}/cmake/add_tests.cmake)

# Build Targets
include(${CMAKE_SOURCE_DIR}/cmake/add_targets.cmake)