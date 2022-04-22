/** 
 * Copyright (c) 2022 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_VECTOR_HIDDEN_H_
#define O_VECTOR_HIDDEN_H_

#include <stddef.h>

typedef struct o_vector_s o_vector_t;
typedef struct o_vector_node_s o_vector_node_t;

o_vector_t* o_vector_create_f(size_t data_type_size);

#define o_vector_create_hidden(T) \
({                                \
    o_vector_create_f(sizeof(T)); \
})

#endif  // O_VECTOR_HIDDEN_H_