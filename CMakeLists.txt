project(matching_search)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
