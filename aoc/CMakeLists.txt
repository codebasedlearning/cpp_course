# (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

# shared library
add_library(aoc_lib STATIC solutions/aoc.cpp solutions/aoc.hpp)
target_include_directories(aoc_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/solutions)

# apply to all targets below
link_libraries(aoc_lib)
add_compile_options(-O3 -Wall -Wextra)

# all days
add_executable(day01 solutions/day01.cpp)
add_executable(day02 solutions/day02.cpp)
add_executable(day03 solutions/day03.cpp)
add_executable(day04 solutions/day04.cpp)
add_executable(day05 solutions/day05.cpp)
add_executable(day06 solutions/day06.cpp)
add_executable(day07 solutions/day07.cpp)
add_executable(day08 solutions/day08.cpp)
add_executable(day09 solutions/day09.cpp)

add_executable(aoc_test solutions/aoc_test.cpp)

# template
add_executable(dayXX solutions/dayXX.cpp)
