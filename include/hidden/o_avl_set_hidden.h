/** 
 * Copyright (c) 2022 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_AVL_SET_HIDDEN_H_
#define O_AVL_SET_HIDDEN_H_

#include <stddef.h>

#include "o_functions.h"

typedef struct o_avl_set_s o_avl_set_t;
typedef struct o_avl_node_s o_avl_set_node_t;

#define O_DEFINE_AVL_SET_NODE_STRUCT(K) struct { \
    struct o_avl_set_node_s* parent;             \
    struct o_avl_set_node_s* left;               \
    struct o_avl_set_node_s* right;              \
    unsigned char height;                        \
    K key;                                       \
    char end[0];                                 \
}
#define O_AVL_SET_NODE_OFFSETOF_KEY(K) offsetof(O_DEFINE_AVL_SET_NODE_STRUCT(K), key)
#define O_AVL_SET_NODE_SIZE(K) offsetof(O_DEFINE_AVL_SET_NODE_STRUCT(K), end)

o_avl_set_t* o_avl_set_create_f(o_compare_func_t key_cmp, size_t node_size, size_t offsetof_key, size_t sizeof_key);

#define o_avl_set_create_hidden(K, key_cmp)                                                         \
({                                                                                                  \
    o_avl_set_create_f(key_cmp, O_AVL_SET_NODE_SIZE(K), O_AVL_SET_NODE_OFFSETOF_KEY(K), sizeof(K)); \
})

#endif  // O_AVL_SET_HIDDEN_H_