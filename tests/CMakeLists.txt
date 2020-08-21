cmake_minimum_required(VERSION 3.16)
project(matching_search_tests)

set(CMAKE_CXX_STANDARD 17)

find_package(Catch2 REQUIRED)
add_executable(
        matching_search_tests
        sample.cpp)
target_link_libraries(matching_search_tests Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(matching_search_tests)
