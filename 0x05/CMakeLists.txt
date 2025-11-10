# (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

add_executable(a_asm_view snippets/a_asm_view.cpp)
add_executable(b_first_pointers snippets/b_first_pointers.cpp)
add_executable(c_more_pointers snippets/c_more_pointers.cpp)
add_executable(d_arrays_and_pointers snippets/d_arrays_and_pointers.cpp)
add_executable(e_swap snippets/e_swap.cpp)
add_executable(f_this snippets/f_this.cpp)

add_executable(copperview_one_solution solutions/copperview_one_solution.cpp)
add_executable(kengate_one_solution solutions/kengate_one_solution.cpp)
add_executable(mcallenspring_one_solution solutions/mcallenspring_one_solution.cpp)
add_executable(dontdothisorilltellyourmum_one_solution solutions/dontdothisorilltellyourmum_one_solution.cpp)

#cmake_minimum_required(VERSION 3.15)
#project(cbl_cpp)

#set(CMAKE_CXX_STANDARD 20)
#add_executable(a_arm_asm_01 snippets/a_arm_asm_01.cpp)
## target_compile_options(a_arm_asm_01 PRIVATE -O3)
#
#add_executable(a_arm_asm_02 snippets/a_arm_asm_02.cpp)
#add_executable(a_arm_asm_03 snippets/a_arm_asm_03.cpp)
#add_executable(a_arm_asm_04 snippets/a_arm_asm_04.cpp)
## target_compile_options(a_arm_asm_04 PRIVATE -s -fverbose-asm)
#
#add_executable(a_asm_01_local_vars snippets/a_asm_01_local_vars.cpp)
#target_compile_options(a_asm_01_local_vars PRIVATE -g)
#
#add_executable(a_asm_02_local_addr snippets/a_asm_02_local_addr.cpp)
#target_compile_options(a_asm_02_local_addr PRIVATE -g)
#
#add_executable(b_pointer_01_memory_layout snippets/b_pointer_01_memory_layout.cpp)
#add_executable(b_pointer_02_math snippets/b_pointer_02_math.cpp)
#add_executable(b_pointer_03_array snippets/b_pointer_03_array.cpp)
#add_executable(b_pointer_04_swap snippets/b_pointer_04_swap.cpp)
#add_executable(b_pointer_04_addon snippets/b_pointer_05_addon.cpp)
#add_executable(b_pointer_06_illegal snippets/b_pointer_06_illegal.cpp)
#
#add_executable(work_ptr_endlist snippets/work_ptr_endlist.cpp)
#add_executable(work_ptr_multiple_params snippets/work_ptr_multiple_params.cpp)
#add_executable(work_asm_call_by snippets/work_asm_call_by.cpp)
#add_executable(work_asm_stack_frame snippets/work_asm_stack_frame.cpp)
#
#add_executable(copperview exercises/copperview.cpp)
#add_executable(kengate exercises/kengate.cpp)
#add_executable(mcallenspring exercises/mcallenspring.cpp)
#
#add_executable(sol_copperview exercises/proposed_solutions/sol_copperview.cpp)
#add_executable(sol_kengate exercises/proposed_solutions/sol_kengate.cpp)
#add_executable(sol_mcallenspring exercises/proposed_solutions/sol_mcallenspring.cpp)

