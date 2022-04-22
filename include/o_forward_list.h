/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef O_FORWARD_LIST_H_
#define O_FORWARD_LIST_H_

#include "hidden/o_forward_list_hidden.h"

#include <stddef.h>
#include <stdbool.h>

#define o_forward_list_create(T)        \
        o_forward_list_create_hidden(T)

const void* o_forward_list_front(const o_forward_list_t* list);

void o_forward_list_push_front(o_forward_list_t* list, const void* data);

void o_forward_list_pop_front(o_forward_list_t* list);

bool o_forward_list_empty(const o_forward_list_t* list);

void o_forward_list_delete(o_forward_list_t* list);

void o_forward_list_destructor(o_forward_list_t** list);

#define WITH_O_FORWARD_LIST_DTOR __attribute__((__cleanup__(o_forward_list_destructor)))

void o_forward_list_clear(o_forward_list_t* list);

void o_forward_list_swap(o_forward_list_t* first_list, o_forward_list_t* second_list);

void o_forward_list_resize(o_forward_list_t* list, size_t new_size);

o_forward_list_node_t* o_forward_list_before_begin(o_forward_list_t* list);

o_forward_list_node_t* o_forward_list_begin(o_forward_list_t* list);

const o_forward_list_node_t* o_forward_list_cbegin(const o_forward_list_t* list);

const o_forward_list_node_t* o_forward_list_cend(const o_forward_list_t* list);

o_forward_list_node_t* o_forward_list_end(o_forward_list_t* list);

void o_forward_list_node_splice_after(o_forward_list_t* list, o_forward_list_node_t* node, o_forward_list_t* insert_list);

void o_forward_list_node_insert_after(o_forward_list_t* list, o_forward_list_node_t* node, const void* data);

void o_forward_list_node_erase_after(o_forward_list_t* list, o_forward_list_node_t* node);

o_forward_list_node_t* o_forward_list_node_get_next(o_forward_list_t* list, o_forward_list_node_t* node);

const o_forward_list_node_t* o_forward_list_cnode_get_next(const o_forward_list_t* list, const o_forward_list_node_t* node);

void o_forward_list_node_set_value(o_forward_list_t* list, o_forward_list_node_t* node, const void* data);

const void* o_forward_list_node_get_value(const o_forward_list_t* list, const o_forward_list_node_t* node);

#endif  // O_FORWARD_LIST_H_