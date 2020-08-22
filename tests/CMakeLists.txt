find_package(Catch2 REQUIRED)
add_executable(
        matching_search_tests
        Sample.cpp
        IsPerfectPhylogenyPair.cpp)
target_link_libraries(matching_search_tests Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(matching_search_tests)
