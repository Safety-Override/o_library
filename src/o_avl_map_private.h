/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include <stddef.h>

#include "o_avl_set_private.h"

struct o_avl_map_node_s {
    struct o_avl_set_node_s set_node;
};

struct o_avl_map_s {
    struct o_avl_set_s set;
    size_t offsetof_value;
    size_t sizeof_value;
};
