/** 
 * Copyright (c) 2022 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_AVL_MAP_PRIVATE_H_
#define O_AVL_MAP_PRIVATE_H_

#include "o_avl_private.h"
#include "o_avl_set_private.h"

#include <stddef.h>

struct o_avl_map_s {
    struct o_avl_set_s set;
    size_t offsetof_value;
    size_t sizeof_value;
};

#endif  // O_AVL_MAP_PRIVATE_H_
