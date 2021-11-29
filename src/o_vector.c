/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include "o_vector.h"
#include "o_vector_private.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <o_functions.h>
#include <limits.h>

static inline size_t next_pow2(size_t x) {
    return x == 1 ? 1 : 1 << (CHAR_BIT * sizeof(unsigned) - __builtin_clz((unsigned)x - 1)); 
}

o_vector_t* o_vector_create_t(size_t data_type_size) {
    o_vector_t* temp = calloc(1, sizeof(o_vector_t));
    temp->data_type_size = data_type_size;
    return temp;
}

size_t o_vector_size(const o_vector_t* vec) {
    return vec->size;
}

void o_vector_push_back(o_vector_t* vec, const void* data) {
    if (o_unlikely(vec->size == vec->capacity)) {
        o_vector_reserve(vec, o_max(vec->capacity * 2, 1));
    }
    memcpy(((char*)vec->data) + vec->size * (vec->data_type_size), data, vec->data_type_size);
    ++vec->size;
}

void o_vector_set(o_vector_t* vec, size_t index, const void* data) {
    memcpy(((char*)vec->data) + index * (vec->data_type_size), data, vec->data_type_size);
}

const void* o_vector_get(const o_vector_t* vec, size_t index) {
    return ((char*)vec->data) + index * (vec->data_type_size);
}

void o_vector_pop_back(o_vector_t* vec) {
    --vec->size;
}

void o_vector_resize(o_vector_t* vec, size_t new_size) {
    if (vec->size < new_size) {
        o_vector_reserve(vec, new_size);
        memset((char*)vec->data + vec->size * vec->data_type_size, 0, (new_size - vec->size) * vec->data_type_size);
    }
    vec->size = new_size;
}

void o_vector_reserve(o_vector_t* vec, size_t new_capacity) {
    if (o_likely(vec->capacity < new_capacity)) {
        vec->data = realloc(vec->data, vec->data_type_size * new_capacity);
        vec->capacity = new_capacity;
    }
}

void o_vector_destroy(o_vector_t* vec) {
    free(vec->data);
    free(vec);
}

void o_vector_push_back_array(o_vector_t* vec, const void* data, size_t data_amount) {
    if (vec->capacity < data_amount + vec->size) {
        o_vector_reserve(vec, next_pow2(data_amount + vec->size));
    }
    memcpy(((char*)vec->data) + vec->size * (vec->data_type_size), data, vec->data_type_size * data_amount);
    vec->size += data_amount;
}

const o_vector_node_t* o_vector_cbegin(const o_vector_t* vec) {
    return o_vector_begin((o_vector_t*)vec);
}

o_vector_node_t* o_vector_begin(o_vector_t* vec){
    return vec->data;
}

o_vector_node_t* o_vector_end(o_vector_t* vec) {
    return (void*)((char*)vec->data + vec->size * vec->data_type_size);
}

const o_vector_node_t* o_vector_cend(const o_vector_t* vec) {
    return o_vector_end((o_vector_t*)vec);
}

bool o_vector_empty(const o_vector_t* vec) {
    return !vec->size;
}

size_t o_vector_capacity(const o_vector_t* vec) {
    return vec->capacity;
}

void o_vector_clear(o_vector_t* vec) {
    free(vec->data);
    vec->capacity = 0;
    vec->size = 0;
    vec->data = NULL;
}

void o_vector_swap(o_vector_t* first_vec, o_vector_t* second_vec) {
    o_swap(*first_vec, *second_vec);
}

void o_vector_insert(o_vector_t* vec, const void* data, size_t index) {
    if (o_unlikely(vec->size == vec->capacity)) {
        o_vector_reserve(vec, o_max(vec->capacity * 2, 1));
    }
    memmove((char*)vec->data + vec->data_type_size * (index + 1), (char*)vec->data + vec->data_type_size * index, (vec->size - index) * vec->data_type_size);
    memcpy((char*)vec->data + vec->data_type_size * index, data, vec->data_type_size);
    ++vec->size;
}

void o_vector_erase(o_vector_t* vec, size_t index) {
    memmove((char*)vec->data + vec->data_type_size * index, (char*)vec->data + vec->data_type_size * (index + 1), (vec->size - index - 1) * vec->data_type_size);
    --vec->size;
}

const o_vector_node_t* o_vector_cnode_get_next(const o_vector_t* vec, const o_vector_node_t* node) {
    return o_vector_node_get_next((o_vector_t*)vec, (o_vector_node_t*)node);
}

o_vector_node_t* o_vector_node_get_next(o_vector_t* vec, o_vector_node_t* node) {
    return (void*)((char*)node + vec->data_type_size);
}

void o_vector_node_set_value(o_vector_t* vec, o_vector_node_t* node, const void* data) {
    memcpy(node->data, data, vec->data_type_size);
}

const void* o_vector_node_get_value(const o_vector_t* vec, const o_vector_node_t* node) {
    return node->data;
}
