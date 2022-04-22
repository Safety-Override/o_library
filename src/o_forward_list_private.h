/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_FORWARD_LIST_PRIVATE_H_
#define O_FORWARD_LIST_PRIVATE_H_

#include <stddef.h>

struct o_forward_list_node_s {
    struct o_forward_list_node_s* next;
};

struct o_forward_list_s {
    struct o_forward_list_node_s* front;
    size_t node_size;
    size_t offsetof_value;
    size_t sizeof_value;
};

#endif  // O_FORWARD_LIST_PRIVATE_H_