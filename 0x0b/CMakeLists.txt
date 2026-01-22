# (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

add_executable(a_condition_variables snippets/a_condition_variables.cpp)
add_executable(b_smart_ptr_v1 snippets/b_smart_ptr_v1.cpp)
add_executable(c_smart_ptr_v2 snippets/c_smart_ptr_v2.cpp)

add_library(ui_lib STATIC snippets/d_ui_lib.cpp snippets/d_ui_lib.hpp)
# target_include_directories(<project> PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/<path>)

# apply to all targets below
link_libraries(ui_lib)
add_executable(d_use_ui_lib snippets/d_use_ui_lib.cpp)
