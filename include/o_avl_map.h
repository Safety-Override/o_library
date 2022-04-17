/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_AVL_MAP_H_
#define O_AVL_MAP_H_

#include <stddef.h>
#include <stdbool.h>

#include "o_functions.h"

typedef struct o_avl_map_s o_avl_map_t;
typedef struct o_avl_node_s o_avl_map_node_t;

typedef struct {
    o_avl_map_node_t* node;
    bool insertion_took_place;
} o_avl_map_insert_result_t;

typedef struct {
    o_avl_map_node_t* node;
    bool assignment_took_place;
} o_avl_map_insert_or_assign_result_t;

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

o_avl_map_t* o_avl_map_create_f(o_compare_func_t key_cmp, size_t sizeof_node, size_t offsetof_key, size_t sizeof_key, size_t offsetof_value, size_t sizeof_value);

#define o_avl_map_create(K, V, key_cmp)                                                                                                                   \
({                                                                                                                                                        \
    o_avl_map_create_f(key_cmp, O_AVL_MAP_NODE_SIZE(K, V), O_AVL_MAP_NODE_OFFSETOF_KEY(K, V), sizeof(K), O_AVL_MAP_NODE_OFFSETOF_VALUE(K, V), sizeof(V)); \
})
 
bool o_avl_map_empty(const o_avl_map_t* map);

void o_avl_map_clear(o_avl_map_t* map);

o_avl_map_insert_result_t o_avl_map_insert(o_avl_map_t* map, const void* key, const void* value);

o_avl_map_insert_or_assign_result_t o_avl_map_insert_or_assign(o_avl_map_t* map, const void* key, const void* value);

void o_avl_map_erase(o_avl_map_t* map, const void* key);

void o_avl_map_delete(o_avl_map_t* map);

void o_avl_map_swap(o_avl_map_t* first_map, o_avl_map_t* second_map);

o_avl_map_node_t* o_avl_map_find(o_avl_map_t* map, const void* key);

bool o_avl_map_contains(const o_avl_map_t* map, const void* key);

o_avl_map_node_t* o_avl_map_lower_bound(o_avl_map_t* map, const void* key);

o_avl_map_node_t* o_avl_map_upper_bound(o_avl_map_t* map, const void* key);

o_avl_map_node_t* o_avl_map_begin(o_avl_map_t* map);

o_avl_map_node_t* o_avl_map_end(o_avl_map_t* map);

const o_avl_map_node_t* o_avl_map_cbegin(const o_avl_map_t* map);

const o_avl_map_node_t* o_avl_map_cend(const o_avl_map_t* map);

o_avl_map_node_t* o_avl_map_node_get_next(o_avl_map_t* map, o_avl_map_node_t* node);

const o_avl_map_node_t* o_avl_map_cnode_get_next(const o_avl_map_t* map, const o_avl_map_node_t* node);

const void* o_avl_map_node_get_key(const o_avl_map_t* map, const o_avl_map_node_t* node);

const void* o_avl_map_node_get_value(const o_avl_map_t* map, const o_avl_map_node_t* node);

void o_avl_map_node_set_value(o_avl_map_t* map, o_avl_map_node_t* node, const void* value);

void o_avl_map_node_erase(o_avl_map_t* map, o_avl_map_node_t* node);

size_t o_avl_map_size(const o_avl_map_t* map);

#endif // O_AVL_MAP_H_