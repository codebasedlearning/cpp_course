# (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

add_executable(a_const snippets/a_const.cpp)
add_executable(b_new_delete snippets/b_new_delete.cpp)
add_executable(c_unique_ptr snippets/c_unique_ptr.cpp)
add_executable(d_smallbuffer_example snippets/d_smallbuffer_example.cpp)
add_executable(e_addressof snippets/e_addressof.cpp)

add_executable(study_alloc_and_free snippets/study_alloc_and_free.cpp)
add_executable(study_2d_arrays snippets/study_2d_arrays.cpp)

add_executable(reedsfield_one_solution solutions/reedsfield_one_solution.cpp)
add_executable(southbirdsgale_one_solution solutions/southbirdsgale_one_solution.cpp)
add_executable(rosepond_one_solution solutions/rosepond_one_solution.cpp)
add_executable(mcallenspringsmart_one_solution solutions/mcallenspringsmart_one_solution.cpp)

# comment in for sanitizer
target_compile_options(c_unique_ptr PRIVATE -fsanitize=address -fno-omit-frame-pointer -g)
target_link_options(c_unique_ptr PRIVATE -fsanitize=address)

target_compile_options(southbirdsgale_one_solution PRIVATE -fsanitize=address -fno-omit-frame-pointer -g)
target_link_options(southbirdsgale_one_solution PRIVATE -fsanitize=address)
