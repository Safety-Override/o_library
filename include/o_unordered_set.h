/** 
 * Copyright (c) 2022 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_UNORDERED_SET_H_
#define O_UNORDERED_SET_H_

#include "hidden/o_unordered_set_hidden.h"

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    o_unordered_set_node_t* node;
    bool insertion_took_place;
} o_unordered_set_insert_result_t;

#define o_unordered_set_create(K, key_equal, hash) \
        o_unordered_set_create_hidden(K, key_cmp, hash)
 
bool o_unordered_set_empty(const o_unordered_set_t* set);

void o_unordered_set_clear(o_unordered_set_t* set);

o_unordered_set_insert_result_t o_unordered_set_insert(o_unordered_set_t* set, const void* key);

void o_unordered_set_erase(o_unordered_set_t* set, const void* key);

void o_unordered_set_delete(o_unordered_set_t* set);

void o_unordered_set_destructor(o_unordered_set_t** set);

#define WITH_O_UNORDERED_SET_DTOR __attribute__((__cleanup__(o_unordered_set_destructor)))

void o_unordered_set_swap(o_unordered_set_t* first_set, o_unordered_set_t* second_set);

o_unordered_set_node_t* o_unordered_set_find(o_unordered_set_t* set, const void* key);

bool o_unordered_set_contains(const o_unordered_set_t* set, const void* key);

o_unordered_set_node_t* o_unordered_set_begin(o_unordered_set_t* set);

o_unordered_set_node_t* o_unordered_set_end(o_unordered_set_t* set);

const o_unordered_set_node_t* o_unordered_set_cbegin(const o_unordered_set_t* set);

const o_unordered_set_node_t* o_unordered_set_cend(const o_unordered_set_t* set);

o_unordered_set_node_t* o_unordered_set_node_get_next(o_unordered_set_t* set, o_unordered_set_node_t* node);

const o_unordered_set_node_t* o_unordered_set_cnode_get_next(const o_unordered_set_t* set, const o_unordered_set_node_t* node);

const void* o_unordered_set_node_get_key(const o_unordered_set_t* set, const o_unordered_set_node_t* node);

void o_unordered_set_node_erase(o_unordered_set_t* set, o_unordered_set_node_t* node);

size_t o_unordered_set_size(const o_unordered_set_t* set);

#endif  // O_UNORDERED_SET_H_