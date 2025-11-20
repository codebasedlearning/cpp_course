# (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

cmake_minimum_required(VERSION 3.20)    # Enforce at least CMake 3.20 for good C++23 support
project(cpp_course LANGUAGES CXX)       # Use the LANGUAGES keyword to declare C++ explicitly

set(CMAKE_CXX_STANDARD 23)              # Requests C++23 mode for targets
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Fails configuration if the compiler can’t provide the requested standard
set(CMAKE_CXX_EXTENSIONS OFF)           # Improves portability

add_subdirectory(0x00)
add_subdirectory(0x01)
add_subdirectory(0x02)
add_subdirectory(0x03)
add_subdirectory(0x04)
add_subdirectory(0x0x_am1)
add_subdirectory(0x05)
add_subdirectory(0x06)
