/** 
 * Copyright (c) 2022 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include "o_unordered_set.h"
#include "o_unordered_set_private.h"
#include "o_forward_list.h"
#include "o_vector.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "o_functions.h"

static void* node_get_key(o_unordered_set_t* set, o_unordered_set_node_t* node) {
    return o_forward_list_node_get_value(&set->instance, node);
}

o_unordered_set_t* o_unordered_set_create_f(size_t node_size, size_t offsetof_key, size_t sizeof_key, o_key_equal_func_t key_equal, o_hash_func_t hash) {
    o_unordered_set_t* set = calloc(1, sizeof(o_unordered_set_t));
    set->instance.node_size = node_size;
    set->instance.offsetof_value = offsetof_key;
    set->instance.sizeof_value = sizeof_key;
    set->hash = hash;
    set->key_equal = key_equal;
    set->vec.data_type_size = sizeof(o_forward_list_t);
    return set;
}

bool o_unordered_set_empty(const o_unordered_set_t* set) {
    return !set->size;
}

void o_unordered_set_clear(o_unordered_set_t* set) {
    
}

o_unordered_set_insert_result_t o_unordered_set_insert(o_unordered_set_t* set, const void* key) {
    
}

void o_unordered_set_erase(o_unordered_set_t* set, const void* key) {
    
}

void o_unordered_set_delete(o_unordered_set_t* set) {
    
}

void o_unordered_set_destructor(o_unordered_set_t** set) {
    o_unordered_set_delete(*set);
}

void o_unordered_set_swap(o_unordered_set_t* first_set, o_unordered_set_t* second_set) {
    o_swap(*first_set, *second_set);
}

o_unordered_set_node_t* o_unordered_set_find(o_unordered_set_t* set, const void* key) {
    size_t pos_in_vec = set->hash(key) % o_vector_size(&set->vec);
    o_forward_list_node_t* cur_node = ((o_forward_list_t*)o_vector_get(&set->vec, pos_in_vec))->front;
    while (cur_node != o_forward_list_end(&set->instance)) {
        if (set->key_equal(key, o_forward_list_node_get_value(&set->instance,cur_node))) {
            return cur_node;
        }
        cur_node = o_forward_list_node_get_next(&set->instance, cur_node);
    }
    return NULL;
}

bool o_unordered_set_contains(const o_unordered_set_t* set, const void* key) {
    return !!o_unordered_set_find(set, key);
}

o_unordered_set_node_t* o_unordered_set_begin(o_unordered_set_t* set) {
    return o_forward_list_begin((o_forward_list_t*)o_vector_begin(&set->vec));
}

o_unordered_set_node_t* o_unordered_set_end(o_unordered_set_t* set) {
    return NULL;
}

const o_unordered_set_node_t* o_unordered_set_cbegin(const o_unordered_set_t* set) {
    return o_unordered_set_begin((o_unordered_set_t*)set);
}

const o_unordered_set_node_t* o_unordered_set_cend(const o_unordered_set_t* set) {
    return o_unordered_set_end((o_unordered_set_t*)set);
}

o_unordered_set_node_t* o_unordered_set_node_get_next(o_unordered_set_t* set, o_unordered_set_node_t* node) {
    if (o_forward_list_node_get_next(&set->instance, node)) {
        return o_forward_list_node_get_next(&set->instance, node);
    }
    size_t pos_in_vec = set->hash(o_forward_list_node_get_value(&set->instance, node)) % o_vector_size(&set->vec);
    for (size_t i = pos_in_vec + 1; i < set->vec.size; ++i) {
        if (((o_forward_list_t*)o_vector_get(&set->vec, i))->front) {
            return ((o_forward_list_t*)o_vector_get(&set->vec, i))->front;
        }
    }
    return NULL;
}

const o_unordered_set_node_t* o_unordered_set_cnode_get_next(const o_unordered_set_t* set, const o_unordered_set_node_t* node) {
    return o_unordered_set_node_get_next((o_unordered_set_t*)set, (o_unordered_set_node_t*)node);
}

const void* o_unordered_set_node_get_key(const o_unordered_set_t* set, const o_unordered_set_node_t* node) {
    return node_get_key((o_unordered_set_t*)set, (o_unordered_set_node_t*)node);
}

void o_unordered_set_node_erase(o_unordered_set_t* set, o_unordered_set_node_t* node) {
    
}

size_t o_unordered_set_size(const o_unordered_set_t* set) {
    return set->size;
}