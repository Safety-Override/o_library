/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include "o_container.h"
#include "o_container_private.h"

#include "o_forward_list.h"
#include "o_vector.h"

o_container_node_t* o_container_begin(o_container_t container)
{
    return (o_container_node_t*)container.begin(container.object);
}

o_container_node_t* o_container_end(o_container_t container)
{
    return (o_container_node_t*)container.end(container.object);
}

o_container_node_t* o_container_node_get_next(o_container_t container, o_container_node_t* node)
{
    return (o_container_node_t*)container.next(container.object, node);
}

void* o_container_node_get_value(o_container_t container, o_container_node_t* node)
{
    return container.get_value(container.object, node);
}

o_container_t o_container_create_from_vector(o_vector_t* vec)
{
    o_container_t container;
    container.object = vec;
    container.begin = (void*(*)(void*))o_vector_begin;
    container.end = (void*(*)(void*))o_vector_end;
    container.next = (void*(*)(void*, void*))o_vector_node_get_next;
    container.get_value = (void*(*)(void*, void*))o_vector_node_get_value;
    return container;
}

o_container_t o_container_create_from_forward_list(o_forward_list_t* list)
{
    o_container_t container;
    container.object = list;
    container.begin = (void*(*)(void*))o_forward_list_begin;
    container.end = (void*(*)(void*))o_forward_list_end;
    container.next = (void*(*)(void*, void*))o_forward_list_node_get_next;
    container.get_value = (void*(*)(void*, void*))o_forward_list_node_get_value;
    return container;
}

void o_container_create_error(void)
{
    return;
}