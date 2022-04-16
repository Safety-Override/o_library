/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include <stddef.h>
#include <stdbool.h>

#include "o_functions.h"

typedef struct o_avl_set_s o_avl_set_t;
typedef struct o_avl_set_node_s o_avl_set_node_t;

typedef struct {
    o_avl_set_node_t* node;
    bool insertion_took_place;
} o_avl_set_insert_result_t;

#define O_AVL_SET_NODE_STRUCT(K) struct { \
    struct o_avl_set_node_s* parent;      \
    struct o_avl_set_node_s* left;        \
    struct o_avl_set_node_s* right;       \
    unsigned char height;                 \
    K key;                                \
    char end[0];                          \
}
#define O_AVL_SET_NODE_OFFSETOF_KEY(K) offsetof(O_AVL_SET_NODE_STRUCT(K), key)
#define O_AVL_SET_NODE_SIZE(K) offsetof(O_AVL_SET_NODE_STRUCT(K), end)

o_avl_set_t* o_avl_set_create_f(o_compare_func_t key_cmp, size_t node_size, size_t offsetof_key, size_t sizeof_key);

#define o_avl_set_create(K, key_cmp)                                                                \
({                                                                                                  \
    o_avl_set_create_f(key_cmp, O_AVL_SET_NODE_SIZE(K), O_AVL_SET_NODE_OFFSETOF_KEY(K), sizeof(K)); \
})
 
bool o_avl_set_empty(const o_avl_set_t* set);

void o_avl_set_clear(o_avl_set_t* set);

o_avl_set_insert_result_t o_avl_set_insert(o_avl_set_t* set, const void* key);

void o_avl_set_erase(o_avl_set_t* set, const void* key);

void o_avl_set_delete(o_avl_set_t* set);

void o_avl_set_swap(o_avl_set_t* first_set, o_avl_set_t* second_set);

o_avl_set_node_t* o_avl_set_find(o_avl_set_t* set, const void* key);

bool o_avl_set_contains(const o_avl_set_t* set, const void* key);

o_avl_set_node_t* o_avl_set_lower_bound(o_avl_set_t* set, const void* key);

o_avl_set_node_t* o_avl_set_upper_bound(o_avl_set_t* set, const void* key);

o_avl_set_node_t* o_avl_set_begin(o_avl_set_t* set);

o_avl_set_node_t* o_avl_set_end(o_avl_set_t* set);

const o_avl_set_node_t* o_avl_set_cbegin(const o_avl_set_t* set);

const o_avl_set_node_t* o_avl_set_cend(const o_avl_set_t* set);

o_avl_set_node_t* o_avl_set_node_get_next(o_avl_set_t* set, o_avl_set_node_t* node);

const o_avl_set_node_t* o_avl_set_cnode_get_next(const o_avl_set_t* set, const o_avl_set_node_t* node);

const void* o_avl_set_node_get_key(const o_avl_set_t* set, const o_avl_set_node_t* node);

void o_avl_set_node_erase(o_avl_set_t* set, o_avl_set_node_t* node);

size_t o_avl_set_size(const o_avl_set_t* set);