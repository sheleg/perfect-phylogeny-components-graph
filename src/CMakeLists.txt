set(TARGET_NAME matching_search)

add_library(${TARGET_NAME}
        Sequence.cpp
        Sequence.h
        Nucleotide.cpp
        Nucleotide.h
        AlleleColumn.cpp
        AlleleColumn.h)

add_executable(matching_search_exec main.cpp)
target_link_libraries(matching_search_exec
        PUBLIC matching_search)

target_include_directories(${TARGET_NAME}
        INTERFACE ./)
