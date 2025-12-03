# (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

add_executable(day01 solutions/day01.cpp)
add_executable(day02 solutions/day02.cpp)
add_executable(day03 solutions/day03.cpp)

add_executable(dayXX solutions/dayXX.cpp)

target_compile_options(day03 PRIVATE -O3)
