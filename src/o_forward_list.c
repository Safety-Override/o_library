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

#ifdef WIN32
#include <malloc.h>
/* #define alloca _malloca */
#else
#include <alloca.h>
#endif // WIN32

#include <o_functions.h>

o_forward_list_t* o_forward_list_create_t(size_t data_type_size) {
    o_forward_list_t* list = calloc(1, sizeof(o_forward_list_t));
    list->data_type_size = data_type_size;
    return list;
}

void* o_forward_list_front(o_forward_list_t* list) {
    return list->front->data;
}

void o_forward_list_push_front(o_forward_list_t* list, void* data) {
    o_forward_list_node_t* node_after_insert = o_forward_list_begin(list);
    list->front = malloc(sizeof(o_forward_list_node_t) + list->data_type_size);
    memcpy(list->front->data, data, list->data_type_size);
    list->front->next = node_after_insert;
}

void o_forward_list_pop_front(o_forward_list_t* list) {
    o_forward_list_node_t* node_after_pop = list->front->next;
    free(list->front);
    list->front = node_after_pop;
}

bool o_forward_list_empty(o_forward_list_t* list) {
    return !list->front;
}

void o_forward_list_destroy(o_forward_list_t* list) {
    o_forward_list_clear(list);
    free(list);
}

void o_forward_list_clear(o_forward_list_t* list) {
    while (!o_forward_list_empty(list)) {
        o_forward_list_pop_front(list);
    }
}

size_t o_forward_list_get_type_size(o_forward_list_t* list) {
    return list->data_type_size;
}

void o_forward_list_swap(o_forward_list_t* first_list, o_forward_list_t* second_list) {
    o_swap(*first_list, *second_list);
}

void o_forward_list_resize(o_forward_list_t* list, size_t new_size) {
    o_forward_list_node_t* current_node = o_forward_list_before_begin(list);
    for (; new_size; --new_size) {
        if (o_forward_list_node_get_next(list, current_node) == o_forward_list_end(list)) {
            void* null_value = alloca(list->data_type_size);
            memset(null_value, 0, list->data_type_size);
            o_forward_list_node_insert_after(list, current_node, null_value);
        }
    }
    while (o_forward_list_node_get_next(list, current_node) != o_forward_list_end(list)) {
        o_forward_list_node_erase_after(list, current_node);
    }
}

o_forward_list_node_t* o_forward_list_before_begin(o_forward_list_t* list) {
    return list;
}

o_forward_list_node_t* o_forward_list_begin(o_forward_list_t* list) {
    return list->front;
}

o_forward_list_node_t* o_forward_list_end(o_forward_list_t* list) {
    return NULL;
}

void o_forward_list_node_insert_after(o_forward_list_t* list, o_forward_list_node_t* node, void* data) {
    o_forward_list_node_t* node_after_insert = o_forward_list_node_get_next(list, node);
    node->next = malloc(sizeof(o_forward_list_node_t) + list->data_type_size);
    memcpy(node->next->data, data, list->data_type_size);
    node->next->next = node_after_insert;
}

void o_forward_list_node_splice_after(o_forward_list_t* list, o_forward_list_node_t* node, o_forward_list_t* insert_list) {
    o_forward_list_node_t* node_after_insert = node->next;
    node->next = o_forward_list_begin(insert_list);
    o_forward_list_node_t* current_node = node->next;
    while (o_forward_list_node_get_next(list, current_node) != o_forward_list_end(insert_list)) {
        current_node = o_forward_list_node_get_next(list, current_node);
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

void o_forward_list_node_set_value(o_forward_list_t* list, o_forward_list_node_t* node, void* data) {
    memcpy(node->data, data, list->data_type_size);
}

void* o_forward_list_node_get_value(o_forward_list_t* list, o_forward_list_node_t* node) {
    return node->data;
}
