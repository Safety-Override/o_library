/** 
 * Copyright (c) 2022 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_AVL_SET_H_
#define O_AVL_SET_H_

#include "hidden/o_avl_set_hidden.h"

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    o_avl_set_node_t* node;
    bool insertion_took_place;
} o_avl_set_insert_result_t;

#define o_avl_set_create(K, key_cmp) \
        o_avl_set_create_hidden(K, key_cmp)
 
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

#endif  // O_AVL_SET_H_