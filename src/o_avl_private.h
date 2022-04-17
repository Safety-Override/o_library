/** 
 * Copyright (c) 2022 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_AVL_PRIVATE_H_
#define O_AVL_PRIVATE_H_

#include <stddef.h>

struct o_avl_node_s {
    struct o_avl_node_s* parent;
    struct o_avl_node_s* left;
    struct o_avl_node_s* right;
    unsigned char height;
};

#endif  // O_AVL_PRIVATE_H_