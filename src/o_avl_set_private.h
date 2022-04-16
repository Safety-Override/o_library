/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include <stddef.h>

#include "o_functions.h"

struct o_avl_set_node_s {
    struct o_avl_set_node_s* parent;
    struct o_avl_set_node_s* left;
    struct o_avl_set_node_s* right;
    unsigned char height;
};

struct o_avl_set_s {
    struct o_avl_set_node_s* root;
    o_compare_func_t key_cmp;
    size_t size;
    size_t sizeof_node;
    size_t offsetof_key;
    size_t sizeof_key;
};
