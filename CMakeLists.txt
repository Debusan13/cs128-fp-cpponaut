cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(blocks)

message(STATUS "build_dir:${CMAKE_BINARY_DIR}")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/TermOx EXCLUDE_FROM_ALL)
add_subdirectory(src)
# add_subdirectory(tests)
