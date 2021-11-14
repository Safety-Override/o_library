cmake_minimum_required(VERSION 3.0)

project(o_library_tests)

add_executable(check_o_vector check_o_vector.c)

target_link_libraries(check_o_vector o_library check subunit pthread rt)