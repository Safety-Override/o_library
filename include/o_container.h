/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_CONTAINER_H_
#define O_CONTAINER_H_

#include "o_forward_list.h"
#include "o_vector.h"

typedef struct {
    void* object;
    void* (*begin)(void* object);
    void* (*end)(void* object);
    void* (*next)(void* object, void* node);
    void* (*get_value)(void* object, void* node);
} o_container_t;

typedef struct o_container_node_s o_container_node_t;

#define o_container_create_from(C)  _Generic((C),                \
        o_vector_t*:       o_container_create_from_vector,       \
        o_forward_list_t*: o_container_create_from_forward_list, \
        default:           o_container_create_error              \
)(C)

o_container_node_t* o_container_begin(o_container_t container);

o_container_node_t* o_container_end(o_container_t container);

o_container_node_t* o_container_node_get_next(o_container_t container, o_container_node_t* node);

void* o_container_node_get_value(o_container_t container, o_container_node_t* node);

o_container_t o_container_create_from_vector(o_vector_t* vec);

o_container_t o_container_create_from_forward_list(o_forward_list_t* list);

void o_container_create_error(void);

#endif // O_CONTAINER_H_