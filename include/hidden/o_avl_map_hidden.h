/** 
 * Copyright (c) 2022 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_AVL_MAP_HIDDEN_H_
#define O_AVL_MAP_HIDDEN_H_

#include <stddef.h>

#include "o_functions.h"

typedef struct o_avl_map_s o_avl_map_t;
typedef struct o_avl_node_s o_avl_map_node_t;

#define O_DEFINE_AVL_MAP_NODE_STRUCT(K, V) struct { \
    struct o_avl_map_node_s* parent;                \
    struct o_avl_map_node_s* left;                  \
    struct o_avl_map_node_s* right;                 \
    unsigned char height;                           \
    K key;                                          \
    V value;                                        \
    char end[0];                                    \
}
#define O_AVL_MAP_NODE_OFFSETOF_KEY(K, V) offsetof(O_AVL_MAP_NODE_STRUCT(K, V), key)
#define O_AVL_MAP_NODE_OFFSETOF_VALUE(K, V) offsetof(O_AVL_MAP_NODE_STRUCT(K, V), value)
#define O_AVL_MAP_NODE_SIZE(K, V) offsetof(O_AVL_MAP_NODE_STRUCT(K, V), end)

o_avl_map_t* o_avl_map_create_f(o_compare_func_t key_cmp, size_t node_size, size_t offsetof_key, size_t sizeof_key, size_t offsetof_value, size_t sizeof_value);

#define o_avl_map_create_hidden(K, V, key_cmp)                                                                                                            \
({                                                                                                                                                        \
    o_avl_map_create_f(key_cmp, O_AVL_MAP_NODE_SIZE(K, V), O_AVL_MAP_NODE_OFFSETOF_KEY(K, V), sizeof(K), O_AVL_MAP_NODE_OFFSETOF_VALUE(K, V), sizeof(V)); \
})

#endif  // O_AVL_MAP_HIDDEN_H_