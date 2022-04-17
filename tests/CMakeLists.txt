cmake_minimum_required(VERSION 3.0)

project(o_library_tests)

add_executable(o_vector_tests o_vector_tests.c)
target_include_directories(o_vector_tests PRIVATE ../src)
target_link_libraries(o_vector_tests o_library check subunit pthread rt)

add_executable(o_forward_list_tests o_forward_list_tests.c)
target_include_directories(o_forward_list_tests PRIVATE ../src)
target_link_libraries(o_forward_list_tests o_library check subunit pthread rt)

add_executable(o_avl_set_tests o_avl_set_tests.c)
target_include_directories(o_avl_set_tests PRIVATE ../src)
target_link_libraries(o_avl_set_tests o_library check subunit pthread rt)