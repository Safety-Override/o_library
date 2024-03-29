/** 
 * Copyright (c) 2022 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_AVL_MAP_H_
#define O_AVL_MAP_H_

#include "hidden/o_avl_map_hidden.h"

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    o_avl_map_node_t* node;
    bool insertion_took_place;
} o_avl_map_insert_result_t;

typedef struct {
    o_avl_map_node_t* node;
    bool assignment_took_place;
} o_avl_map_insert_or_assign_result_t;

#define o_avl_map_create(K, V, key_cmp) \
        o_avl_map_create_hidden(K, V, key_cmp) 

bool o_avl_map_empty(const o_avl_map_t* map);

void o_avl_map_clear(o_avl_map_t* map);

o_avl_map_insert_result_t o_avl_map_insert(o_avl_map_t* map, const void* key, const void* value);

o_avl_map_insert_or_assign_result_t o_avl_map_insert_or_assign(o_avl_map_t* map, const void* key, const void* value);

void o_avl_map_erase(o_avl_map_t* map, const void* key);

void o_avl_map_delete(o_avl_map_t* map);

void o_avl_map_destructor(o_avl_map_t** map);

#define WITH_O_AVL_MAP_DTOR __attribute__((__cleanup__(o_avl_map_destructor)))

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

#endif  // O_AVL_MAP_H_