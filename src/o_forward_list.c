/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include "o_forward_list.h"
#include "o_forward_list_private.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifdef WIN32
#include <malloc.h>
#else
#include <alloca.h>
#endif  // WIN32

#include "o_functions.h"

static void* node_get_value(o_forward_list_t* list, o_forward_list_node_t* node) {
    return (char*)node + list->offsetof_value;
}

o_forward_list_t* o_forward_list_create_f(size_t node_size, size_t offsetof_value, size_t sizeof_value) {
    o_forward_list_t* list = calloc(1, sizeof(o_forward_list_t));
    list->node_size = node_size;
    list->offsetof_value = offsetof_value;
    list->sizeof_value = sizeof_value;
    return list;
}

const void* o_forward_list_front(const o_forward_list_t* list) {
    return node_get_value((o_forward_list_t*)list, (o_forward_list_node_t*)list->front);
}

void o_forward_list_push_front(o_forward_list_t* list, const void* data) {
    o_forward_list_node_t* node_after_insert = o_forward_list_begin(list);
    list->front = malloc(list->node_size);
    memcpy(node_get_value(list, list->front), data, list->sizeof_value);
    list->front->next = node_after_insert;
}

void o_forward_list_pop_front(o_forward_list_t* list) {
    o_forward_list_node_t* node_after_pop = list->front->next;
    free(list->front);
    list->front = node_after_pop;
}

bool o_forward_list_empty(const o_forward_list_t* list) {
    return !list->front;
}

void o_forward_list_delete(o_forward_list_t* list) {
    if (list) {
        o_forward_list_clear(list);
        free(list);
    }
}

void o_forward_list_destructor(o_forward_list_t** list) {
    o_forward_list_delete(*list);
}

void o_forward_list_clear(o_forward_list_t* list) {
    while (!o_forward_list_empty(list)) {
        o_forward_list_pop_front(list);
    }
}

void o_forward_list_swap(o_forward_list_t* first_list, o_forward_list_t* second_list) {
    o_swap(*first_list, *second_list);
}

void o_forward_list_resize(o_forward_list_t* list, size_t new_size) {
    o_forward_list_node_t* current_node = o_forward_list_before_begin(list);
    for (; new_size; --new_size) {
        if (o_forward_list_node_get_next(list, current_node) == o_forward_list_end(list)) {
            void* null_value = alloca(list->sizeof_value);
            memset(null_value, 0, list->sizeof_value);
            o_forward_list_node_insert_after(list, current_node, null_value);
        }
        current_node = o_forward_list_node_get_next(list, current_node);
    }
    while (o_forward_list_node_get_next(list, current_node) != o_forward_list_end(list)) {
        o_forward_list_node_erase_after(list, current_node);
    }
}

o_forward_list_node_t* o_forward_list_before_begin(o_forward_list_t* list) {
    return (void*)list;
}

o_forward_list_node_t* o_forward_list_begin(o_forward_list_t* list) {
    return list->front;
}

const o_forward_list_node_t* o_forward_list_cbegin(const o_forward_list_t* list) {
    return o_forward_list_begin((o_forward_list_t*)list);
}

const o_forward_list_node_t* o_forward_list_cend(const o_forward_list_t* list) {
    return o_forward_list_end((o_forward_list_t*)list);
}

o_forward_list_node_t* o_forward_list_end(o_forward_list_t* list) {
    return NULL;
}

void o_forward_list_node_insert_after(o_forward_list_t* list, o_forward_list_node_t* node, const void* data) {
    o_forward_list_node_t* node_after_insert = o_forward_list_node_get_next(list, node);
    node->next = malloc(list->node_size);
    memcpy(node_get_value(list, node->next), data, list->sizeof_value);
    node->next->next = node_after_insert;
}

void o_forward_list_node_splice_after(o_forward_list_t* list, o_forward_list_node_t* node, o_forward_list_t* insert_list) {
    o_forward_list_node_t* node_after_insert = node->next;
    node->next = o_forward_list_begin(insert_list);
    o_forward_list_node_t* current_node = o_forward_list_begin(insert_list);
    while (o_forward_list_node_get_next(insert_list, current_node) != o_forward_list_end(insert_list)) {
        current_node = o_forward_list_node_get_next(insert_list, current_node);
    }
    current_node->next = node_after_insert;
    free(insert_list);
}

void o_forward_list_node_erase_after(o_forward_list_t* list, o_forward_list_node_t* node) {
    o_forward_list_node_t* node_after_pop = node->next->next;
    free(node->next);
    node->next = node_after_pop;
}

o_forward_list_node_t* o_forward_list_node_get_next(o_forward_list_t* list, o_forward_list_node_t* node) {
    return node->next;
}

const o_forward_list_node_t* o_forward_list_cnode_get_next(const o_forward_list_t* list, const o_forward_list_node_t* node) {
    return o_forward_list_node_get_next((o_forward_list_t*)list, (o_forward_list_node_t*)node);
}

void o_forward_list_node_set_value(o_forward_list_t* list, o_forward_list_node_t* node, const void* data) {
    memcpy(node_get_value(list, node), data, list->sizeof_value);
}

const void* o_forward_list_node_get_value(const o_forward_list_t* list, const o_forward_list_node_t* node) {
    return node_get_value((o_forward_list_t*)list, (o_forward_list_node_t*)node);
}
