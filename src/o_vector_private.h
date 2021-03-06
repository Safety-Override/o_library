/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_VECTOR_PRIVATE_H_
#define O_VECTOR_PRIVATE_H_

#include <stddef.h>

struct o_vector_s {
    size_t size;
    size_t capacity;
    size_t data_type_size;
    void* data;
};

struct o_vector_node_s {
    char data[0];
};

#endif  // O_VECTOR_PRIVATE_H_