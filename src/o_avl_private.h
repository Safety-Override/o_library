/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef int(*o_compare_func_t)(const void*, const void*);

struct o_avl_node_s {
    void* key;
    int height;
    struct o_avl_node_s* left;
    struct o_avl_node_s* right;
};

struct o_avl_s {
    o_compare_func_t key_cmp;
    size_t key_type_size;
    struct o_avl_node_s* begin;
};