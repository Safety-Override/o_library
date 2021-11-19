cmake_minimum_required(VERSION 3.0)

project(o_library_tests)

add_executable(o_vector_tests o_vector_tests.c)

target_include_directories(o_vector_tests PRIVATE ../src)

target_link_libraries(o_vector_tests o_library check subunit pthread rt)