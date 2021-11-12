cmake_minimum_required(VERSION 3.0)
project(o_library C)

set (SRCS
    src/o_forward_list.c
    src/o_vector.c
    )

add_library(${PROJECT_NAME} SHARED 
    ${SRCS}
    )

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} m)