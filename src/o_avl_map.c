/** 
 * Copyright (c) 2022 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include "o_avl_map.h"
#include "o_avl_map_private.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "o_avl_set.h"
#include "o_functions.h"

static void* node_get_value(o_avl_map_t* map, o_avl_map_node_t* node) {
    return (char*)node + map->offsetof_value;
}

o_avl_map_t* o_avl_map_create_f(o_compare_func_t key_cmp, size_t sizeof_node, size_t offsetof_key, size_t sizeof_key, size_t offsetof_value, size_t sizeof_value) {
    o_avl_map_t* map = calloc(1, sizeof(o_avl_map_t));
    map->set.key_cmp = key_cmp;
    map->set.size = 0;
    map->set.sizeof_node = sizeof_node;
    map->set.offsetof_key = offsetof_key;
    map->set.sizeof_key = sizeof_key;
    map->offsetof_value = offsetof_value;
    map->sizeof_value = sizeof_value;
    return map;
}
 
bool o_avl_map_empty(const o_avl_map_t* map) {
    return o_avl_set_empty(map->set);
}

void o_avl_map_clear(o_avl_map_t* map) {
    o_avl_set_clear(map->set);
}

o_avl_map_insert_result_t o_avl_map_insert(o_avl_map_t* map, const void* key) {
    // TODO

}

o_avl_map_insert_or_assign_result_t o_avl_map_insert_or_assign(o_avl_map_t* map, const void* key) {
    // TODO
}

void o_avl_map_erase(o_avl_map_t* map, const void* key) {
    o_avl_set_erase(map->set, key);
}

void o_avl_map_delete(o_avl_map_t* map) {
    o_avl_set_clear(map->set);
    free(map);
}

void o_avl_map_swap(o_avl_map_t* first_map, o_avl_map_t* second_map) {
    o_swap(*first_map, *second_map);
}

o_avl_map_node_t* o_avl_map_find(o_avl_map_t* map, const void* key) {
    return o_avl_set_find(map->set, key);
}

bool o_avl_map_contains(const o_avl_map_t* map, const void* key) {
    return o_avl_set_contains(map->set, key);
}

o_avl_map_node_t* o_avl_map_lower_bound(o_avl_map_t* map, const void* key) {
    return o_avl_set_lower_bound(map->set, key);
}

o_avl_map_node_t* o_avl_map_upper_bound(o_avl_map_t* map, const void* key) {
    return o_avl_set_upper_bound(map->set, key);
}

o_avl_map_node_t* o_avl_map_begin(o_avl_map_t* map) {
    return o_avl_set_begin(map->set);
}

o_avl_map_node_t* o_avl_map_end(o_avl_map_t* map) {
    return o_avl_set_end(map->set);
}

const o_avl_map_node_t* o_avl_map_cbegin(const o_avl_map_t* map) {
    return o_avl_set_cbegin(map->set);
}

const o_avl_map_node_t* o_avl_map_cend(const o_avl_map_t* map) {
    return o_avl_set_cend(map->set);
}

o_avl_map_node_t* o_avl_map_node_get_next(o_avl_map_t* map, o_avl_map_node_t* node) {
    return o_avl_set_node_get_next(map->set, node);
}

const o_avl_map_node_t* o_avl_map_cnode_get_next(const o_avl_map_t* map, const o_avl_map_node_t* node) {
    return o_avl_set_cnode_get_next(map->set, node);
}

const void* o_avl_map_node_get_key(const o_avl_map_t* map, const o_avl_map_node_t* node) {
    return o_avl_set_node_get_key(map->set, node);
}

const void* o_avl_map_node_get_value(const o_avl_map_t* map, const o_avl_map_node_t* node) {
    return node_get_value((o_avl_map_t*)map, (o_avl_map_node_t*)node);
}

void o_avl_map_node_set_value(o_avl_map_t* map, o_avl_map_node_t* node, const void* value) {
    memcpy(node_get_value((o_avl_map_t*)map, (o_avl_map_node_t*)node), value, map->sizeof_value);
}

void o_avl_map_node_erase(o_avl_map_t* map, o_avl_map_node_t* node) {
    o_avl_set_node_erase(map->set, node);
}

size_t o_avl_map_size(const o_avl_map_t* map) {
    return o_avl_set_size(map->set);
}