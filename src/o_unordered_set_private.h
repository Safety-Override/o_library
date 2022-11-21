/** 
 * Copyright (c) 2022 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_UNORDERED_SET_PRIVATE_H_
#define O_UNORDERED_SET_PRIVATE_H_

#include <stddef.h>
#include <limits.h>
#include <o_vector_private.h>
#include <o_forward_list_private.h>
#include "o_functions.h"

struct o_unordered_set_s {
    size_t size;
    struct o_forward_list_s instance;
    o_key_equal_func_t key_equal;
    o_hash_func_t hash;
    struct o_vector_s vec;
};

struct o_unordered_set_node_s {
    char data[0];
};

#endif  // O_UNORDERED_SET_PRIVATE_H_