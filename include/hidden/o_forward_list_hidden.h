/** 
 * Copyright (c) 2022 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_FORWARD_LIST_HIDDEN_H_
#define O_FORWARD_LIST_HIDDEN_H_

#include <stddef.h>

typedef struct o_forward_list_s o_forward_list_t;
typedef struct o_forward_list_node_s o_forward_list_node_t;

#define O_DEFINE_FORWARD_LIST_NODE_STRUCT(V) struct { \
    struct o_forward_list_node_s* next;               \
    V value;                                          \
    char end[0];                                      \
}
#define O_FORWARD_LIST_NODE_OFFSETOF_VALUE(V) offsetof(O_DEFINE_FORWARD_LIST_NODE_STRUCT(V), value)
#define O_FORWARD_LIST_NODE_SIZE(V) offsetof(O_DEFINE_FORWARD_LIST_NODE_STRUCT(V), end)

o_forward_list_t* o_forward_list_create_f(size_t node_size, size_t offsetof_value, size_t sizeof_value);

#define o_forward_list_create_hidden(T)                                                                     \
({                                                                                                          \
    o_forward_list_create_f(O_FORWARD_LIST_NODE_SIZE(T), O_FORWARD_LIST_NODE_OFFSETOF_VALUE(T), sizeof(T)); \
})

#endif  // O_FORWARD_LIST_HIDDEN_H_