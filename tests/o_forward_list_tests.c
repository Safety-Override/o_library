/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include "o_forward_list.h"
#include "o_forward_list_private.h"

#include <stdlib.h>
#include <check.h>

START_TEST(create_test) {
    o_forward_list_t* list WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(int);
    ck_assert_uint_eq(list->node_size, sizeof(void*) + sizeof(int));
    ck_assert_uint_eq(list->offsetof_value, sizeof(void*));
    ck_assert_uint_eq(list->sizeof_value, sizeof(int));
    ck_assert_ptr_eq(list->front, NULL);
}
END_TEST

START_TEST(push_front_test) {
    o_forward_list_t* list WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(unsigned);
    unsigned val = 31111U;
    o_forward_list_push_front(list, &val);
    ck_assert_uint_eq(list->node_size, sizeof(void*) + sizeof(unsigned));
    ck_assert_uint_eq(list->offsetof_value, sizeof(void*));
    ck_assert_uint_eq(list->sizeof_value, sizeof(unsigned));
    ck_assert_ptr_eq(list->front->next, NULL);
    ck_assert_uint_eq(*(unsigned*)((char*)list->front + list->offsetof_value), val);
    unsigned another_val = 311435U;
    o_forward_list_push_front(list, &another_val);
    ck_assert_ptr_eq(list->front->next->next, NULL);
    ck_assert_uint_eq(*(unsigned*)((char*)list->front + list->offsetof_value), another_val);
    ck_assert_uint_eq(*(unsigned*)((char*)list->front->next + list->offsetof_value), val);
}
END_TEST

START_TEST(pop_front_test) {
    o_forward_list_t* list WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(unsigned);
    unsigned val0 = 31111U;
    unsigned val1 = 4324234U;
    o_forward_list_push_front(list, &val0);
    o_forward_list_push_front(list, &val1);
    o_forward_list_pop_front(list);
    ck_assert_ptr_eq(list->front->next, NULL);
    ck_assert_uint_eq(*(unsigned*)((char*)list->front + list->offsetof_value), val0);
    o_forward_list_pop_front(list);
    ck_assert_ptr_eq(list->front, NULL);
}
END_TEST

START_TEST(clear_test) {
    o_forward_list_t* list WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(int);
    int a = 31111;
    const int b = 5;
    o_forward_list_push_front(list, &a);
    o_forward_list_push_front(list, &a);
    o_forward_list_push_front(list, &a);
    o_forward_list_push_front(list, &a);
    o_forward_list_clear(list);
    ck_assert_ptr_eq(list->front, NULL);
    o_forward_list_push_front(list, &b);
    o_forward_list_push_front(list, &b);
    ck_assert_int_eq(*(int*)((char*)list->front->next + list->offsetof_value), b);
    ck_assert_ptr_eq(list->front->next->next, NULL);
}
END_TEST

START_TEST(delete_test) {
    o_forward_list_delete(NULL);
    ck_assert_int_eq(0, 0); // it just works bacause it calls clear and free functions.
}
END_TEST

START_TEST(front_test) {
    o_forward_list_t* list WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(int);
    int a = 31111;
    int b = 0;
    o_forward_list_push_front(list, &a);
    ck_assert_int_eq(*(int*)o_forward_list_front(list), a);
    o_forward_list_push_front(list, &b);
    ck_assert_int_eq(*(int*)o_forward_list_front(list), b);
    o_forward_list_pop_front(list);
    ck_assert_int_eq(*(int*)o_forward_list_front(list), a);
}
END_TEST

START_TEST(empty_test) {
    o_forward_list_t* list WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(int);
    int a = 31111;
    int b = 0;
    ck_assert(o_forward_list_empty(list));
    o_forward_list_push_front(list, &b);
    ck_assert(!o_forward_list_empty(list));
    o_forward_list_push_front(list, &b);
    ck_assert(!o_forward_list_empty(list));
    o_forward_list_pop_front(list);
    ck_assert(!o_forward_list_empty(list));
    o_forward_list_pop_front(list);
    ck_assert(o_forward_list_empty(list));
}
END_TEST

START_TEST(swap_test) {
    long long a = 31111;
    int b = 5;
    o_forward_list_t* list_one WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(long long);
    o_forward_list_push_front(list_one, &a);
    o_forward_list_push_front(list_one, &a);
    o_forward_list_push_front(list_one, &a);
    o_forward_list_push_front(list_one, &a);
    o_forward_list_t* list_two WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(int);
    o_forward_list_push_front(list_two, &b);
    o_forward_list_push_front(list_two, &b);
    o_forward_list_swap(list_one, list_two);
    ck_assert_uint_eq(list_one->node_size, sizeof(void*) + sizeof(int));
    ck_assert_uint_eq(list_one->offsetof_value, sizeof(void*));
    ck_assert_uint_eq(list_one->sizeof_value, sizeof(int));
    ck_assert_uint_eq(list_two->node_size, sizeof(void*) + sizeof(long long));
    ck_assert_uint_eq(list_two->offsetof_value, sizeof(void*));
    ck_assert_uint_eq(list_two->sizeof_value, sizeof(long long));

    o_forward_list_node_t* first_list_data_node = list_one->front;
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_one, first_list_data_node), b);
    first_list_data_node = o_forward_list_node_get_next(list_one, first_list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_one, first_list_data_node), b);

    o_forward_list_node_t* second_list_data_node = list_two->front;
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_two, second_list_data_node), a);
    second_list_data_node = o_forward_list_node_get_next(list_two, second_list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_two, second_list_data_node), a);
    second_list_data_node = o_forward_list_node_get_next(list_two, second_list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_two, second_list_data_node), a);
    second_list_data_node = o_forward_list_node_get_next(list_two, second_list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_two, second_list_data_node), a);

    o_forward_list_push_front(list_one, &b);
    o_forward_list_push_front(list_one, &b);
    first_list_data_node = list_one->front;
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_one, first_list_data_node), b);
    first_list_data_node = o_forward_list_node_get_next(list_one, first_list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_one, first_list_data_node), b);
    first_list_data_node = o_forward_list_node_get_next(list_one, first_list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_one, first_list_data_node), b);
    first_list_data_node = o_forward_list_node_get_next(list_one, first_list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_one, first_list_data_node), b);
}
END_TEST

START_TEST(resize_test) {
    o_forward_list_t* list WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(int);
    o_forward_list_resize(list, 7U);
    o_forward_list_node_t* list_data_node = list->front;
    ck_assert_ptr_ne(list_data_node, NULL);
    for (size_t i = 0; i < 7U; ++i) {  
        ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), 0);
        list_data_node = o_forward_list_node_get_next(list, list_data_node);
    }
    ck_assert_ptr_eq(list_data_node, NULL);
    list_data_node = list->front;
    o_forward_list_resize(list, 5U);
    for (size_t i = 0; i < 5U; ++i) {  
        ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), 0);
        list_data_node = o_forward_list_node_get_next(list, list_data_node);
    }
    ck_assert_ptr_eq(list_data_node, NULL);
}
END_TEST

START_TEST(before_begin_test) {
    o_forward_list_t* list WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(long long);
    long long a = 31111;
    long long b = 0;
    o_forward_list_push_front(list, &a);
    o_forward_list_push_front(list, &b);
    ck_assert_ptr_eq(o_forward_list_before_begin(list), list);
}
END_TEST

START_TEST(begin_test) {
    o_forward_list_t* list WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(int);
    int a = 31111;
    int b = 0;
    o_forward_list_push_front(list, &a);
    o_forward_list_push_front(list, &b);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, o_forward_list_begin(list)), b);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, o_forward_list_begin(list)->next), a);
    ck_assert_ptr_eq(o_forward_list_begin(list), list->front);
}
END_TEST

START_TEST(end_test) {
    o_forward_list_t* list WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(int);
    int a = 31111;
    int b = 0;
    o_forward_list_push_front(list, &b);
    o_forward_list_push_front(list, &b);
    ck_assert_ptr_eq(o_forward_list_end(list), NULL);
}
END_TEST

START_TEST(node_splice_after_test) {
    // In the middle.
    o_forward_list_t* list_one = o_forward_list_create(int);
    o_forward_list_t* list_two = o_forward_list_create(int);
    int a = 31111;
    int b = 0;
    o_forward_list_push_front(list_one, &a);
    o_forward_list_push_front(list_one, &a);
    o_forward_list_push_front(list_one, &a);
    o_forward_list_push_front(list_two, &b);
    o_forward_list_push_front(list_two, &b);
    o_forward_list_node_splice_after(list_one, list_one->front, list_two);
    o_forward_list_node_t* list_data_node = list_one->front;
    ck_assert_ptr_ne(list_data_node, NULL);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_one, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list_one, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_one, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list_one, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_one, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list_one, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_one, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list_one, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_one, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list_one, list_data_node);
    ck_assert_ptr_eq(list_data_node, NULL);
    o_forward_list_delete(list_one);
    // In the begining.
    o_forward_list_t* list_three = o_forward_list_create(int);
    o_forward_list_t* list_four = o_forward_list_create(int);
    o_forward_list_push_front(list_three, &a);
    o_forward_list_push_front(list_three, &a);
    o_forward_list_push_front(list_three, &a);
    o_forward_list_push_front(list_four, &b);
    o_forward_list_push_front(list_four, &b);
    o_forward_list_node_splice_after(list_three, o_forward_list_before_begin(list_three), list_four);
    list_data_node = list_three->front;
    ck_assert_ptr_ne(list_data_node, NULL);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_three, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list_three, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_three, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list_three, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_three, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list_three, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_three, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list_three, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_three, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list_three, list_data_node);
    ck_assert_ptr_eq(list_data_node, NULL);
    o_forward_list_delete(list_three);
    // At the end.
    o_forward_list_t* list_five = o_forward_list_create(int);
    o_forward_list_t* list_six = o_forward_list_create(int);
    o_forward_list_push_front(list_five, &a);
    o_forward_list_push_front(list_five, &a);
    o_forward_list_push_front(list_five, &a);
    o_forward_list_push_front(list_six, &b);
    o_forward_list_push_front(list_six, &b);
    o_forward_list_node_splice_after(list_five, list_five->front->next->next, list_six);
    list_data_node = list_five->front;
    ck_assert_ptr_ne(list_data_node, NULL);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_five, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list_five, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_five, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list_five, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_five, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list_five, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_five, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list_five, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list_five, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list_five, list_data_node);
    ck_assert_ptr_eq(list_data_node, NULL);
    o_forward_list_delete(list_five);
}
END_TEST

START_TEST(node_insert_after_test) {
    o_forward_list_t* list WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(int);
    int a = 31111;
    int b = 0;
    o_forward_list_push_front(list, &a);
    o_forward_list_push_front(list, &a);
    o_forward_list_push_front(list, &a);
    // baaa
    o_forward_list_node_insert_after(list, o_forward_list_before_begin(list), &b);
    o_forward_list_node_t* list_data_node = list->front;
    ck_assert_ptr_ne(list_data_node, NULL);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_ptr_eq(list_data_node, NULL);
    // babaa
    o_forward_list_node_insert_after(list, list->front->next, &b);
    list_data_node = list->front;
    ck_assert_ptr_ne(list_data_node, NULL);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_ptr_eq(list_data_node, NULL);
    // babaab
    o_forward_list_node_insert_after(list, list->front->next->next->next->next, &b);
    list_data_node = list->front;
    ck_assert_ptr_ne(list_data_node, NULL);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_ptr_eq(list_data_node, NULL);
}
END_TEST

START_TEST(node_erase_after_test) {
    o_forward_list_t* list WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(int);
    int a = 31111;
    int b = 0;
    o_forward_list_push_front(list, &a);
    o_forward_list_push_front(list, &a);
    o_forward_list_push_front(list, &b);
    o_forward_list_push_front(list, &a);
    // Erase first element.
    o_forward_list_node_erase_after(list, o_forward_list_before_begin(list));
    o_forward_list_node_t* list_data_node = list->front;
    ck_assert_ptr_ne(list_data_node, NULL);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_ptr_eq(list_data_node, NULL);
    // Erase middle element.
    o_forward_list_node_erase_after(list, list->front);
    list_data_node = list->front;
    ck_assert_ptr_ne(list_data_node, NULL);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_ptr_eq(list_data_node, NULL);
    // Erase last element.
    o_forward_list_node_erase_after(list, list->front);
    list_data_node = list->front;
    ck_assert_ptr_ne(list_data_node, NULL);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_ptr_eq(list_data_node, NULL);
}
END_TEST

START_TEST(node_get_next_test) {
    o_forward_list_t* list WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(int);
    int a = 31111;
    int b = 0;
    o_forward_list_push_front(list, &a);
    o_forward_list_push_front(list, &b);
    o_forward_list_node_t* list_data_node = list->front;
    ck_assert_ptr_ne(list_data_node, NULL);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), b);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_ptr_eq(list_data_node, NULL);
}
END_TEST

START_TEST(node_set_value_test) {
    o_forward_list_t* list WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(int);
    int a = 31111;
    int b = 0;
    o_forward_list_push_front(list, &b);
    o_forward_list_push_front(list, &b);
    o_forward_list_node_t* list_data_node = list->front;
    ck_assert_ptr_ne(list_data_node, NULL);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), b);
    o_forward_list_node_set_value(list, list_data_node, &a);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), b);
    o_forward_list_node_set_value(list, list_data_node, &a);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_ptr_eq(list_data_node, NULL);
}
END_TEST

START_TEST(node_get_value_test) {
    o_forward_list_t* list WITH_O_FORWARD_LIST_DTOR = o_forward_list_create(int);
    int a = 31111;
    int b = 0;
    o_forward_list_push_front(list, &b);
    o_forward_list_push_front(list, &b);
    o_forward_list_node_t* list_data_node = list->front;
    ck_assert_ptr_ne(list_data_node, NULL);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), b);
    o_forward_list_node_set_value(list, list_data_node, &a);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), b);
    o_forward_list_node_set_value(list, list_data_node, &a);
    ck_assert_int_eq(*(int*)o_forward_list_node_get_value(list, list_data_node), a);
    list_data_node = o_forward_list_node_get_next(list, list_data_node);
    ck_assert_ptr_eq(list_data_node, NULL);
}
END_TEST

Suite* suite_forward_list(void)
{
    Suite* s;
    TCase* tc;
    s = suite_create("o_forward_list workability tests");
    tc = tcase_create("o_forward_list basic usage check");
    tcase_add_test(tc, create_test);
    tcase_add_test(tc, push_front_test);
    tcase_add_test(tc, pop_front_test);
    tcase_add_test(tc, clear_test);
    tcase_add_test(tc, delete_test);
    tcase_add_test(tc, front_test);
    tcase_add_test(tc, empty_test);
    tcase_add_test(tc, swap_test);
    tcase_add_test(tc, resize_test);
    tcase_add_test(tc, before_begin_test);
    tcase_add_test(tc, begin_test);
    tcase_add_test(tc, end_test);
    tcase_add_test(tc, node_splice_after_test);
    tcase_add_test(tc, node_insert_after_test);
    tcase_add_test(tc, node_erase_after_test);
    tcase_add_test(tc, node_get_next_test);
    tcase_add_test(tc, node_set_value_test);
    tcase_add_test(tc, node_get_value_test);
    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    int number_failed;
    SRunner* sr;
    Suite* s_forward_list = suite_forward_list();
    sr = srunner_create(s_forward_list);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}