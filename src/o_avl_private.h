/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include <stddef.h>

struct o_avl_node_s {
    struct o_avl_node_s* parent;
    struct o_avl_node_s* left;
    struct o_avl_node_s* right;
    unsigned char height;
};
