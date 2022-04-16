/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include <stddef.h>

struct o_forward_list_node_s {
    struct o_forward_list_node_s* next;
    char data[0];
};

struct o_forward_list_s {
    struct o_forward_list_node_s* front;
    size_t data_type_size;
};