/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct o_vector_s o_vector_t;
typedef struct o_vector_node_s o_vector_node_t;

o_vector_t* o_vector_create_t(size_t data_type_size);

#define o_vector_create(T)        \
({                                \
    o_vector_create_t(sizeof(T)); \
})

#define o_vector_for_each(vector, entry)                     \
        for(o_vector_node_t* entry = o_vector_begin(vector); \
            entry != o_vector_end(vector);                   \
            entry = o_vector_node_get_next(vector, entry))

size_t o_vector_size(o_vector_t* vec);

void o_vector_resize(o_vector_t* vec, size_t new_size);

void o_vector_reserve(o_vector_t* vec, size_t new_capacity);

void o_vector_push_back(o_vector_t* vec, const void* data);

void o_vector_set(o_vector_t* vec, size_t index, const void* data);

void* o_vector_get(o_vector_t* vec, size_t index);

void o_vector_pop_back(o_vector_t* vec);

void o_vector_destroy(o_vector_t* vec);

void o_vector_push_back_array(o_vector_t* vec, const void* data, size_t data_amount);

o_vector_node_t* o_vector_begin(o_vector_t* vec);

o_vector_node_t* o_vector_end(o_vector_t* vec);

bool o_vector_empty(o_vector_t* vec);

size_t o_vector_capacity(o_vector_t* vec);

void o_vector_clear(o_vector_t* vec);

void o_vector_swap(o_vector_t* first_vec, o_vector_t* second_vec);

void o_vector_insert(o_vector_t* vec, const void* data, size_t index);

void o_vector_erase(o_vector_t* vec, size_t index);

o_vector_node_t* o_vector_node_get_next(o_vector_t* vec, o_vector_node_t* node);

void o_vector_node_set_value(o_vector_t* vec, o_vector_node_t* node, const void* data);

void* o_vector_node_get_value(o_vector_t* vec, o_vector_node_t* node);