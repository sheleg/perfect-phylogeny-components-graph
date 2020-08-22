find_package(Catch2 REQUIRED)

set(TARGET_NAME matching_search_tests)

add_executable(${TARGET_NAME}
        Sample.cpp
        AlleleColumnTest.cpp
        PerfectPhylogenyTest.cpp
        PerfectPhylogenyGraphTest.cpp)

target_link_libraries(${TARGET_NAME}
        PUBLIC Catch2::Catch2)

target_link_libraries(${TARGET_NAME}
        PUBLIC matching_search)

include(CTest)
include(Catch)
catch_discover_tests(${TARGET_NAME})
