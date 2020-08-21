cmake_minimum_required(VERSION 3.16)
project(matching_search)

set(CMAKE_CXX_STANDARD 17)

add_executable(matching_search main.cpp Sequence.cpp Sequence.h Nucleotide.cpp Nucleotide.h AlleleColumn.cpp AlleleColumn.h)