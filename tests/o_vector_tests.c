/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include "o_vector.h"
#include "o_vector_private.h"

#include <stdlib.h>
#include <check.h>

START_TEST(create_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(int);
    ck_assert_uint_eq(vector->size, 0U);
    ck_assert_uint_eq(vector->capacity, 0U);
    ck_assert_uint_eq(vector->data_type_size, sizeof(int));
    ck_assert_ptr_eq(vector->data, NULL);
}
END_TEST

START_TEST(delete_test) {
    o_vector_delete(NULL);
    ck_assert_int_eq(0, 0); // it just works.
}
END_TEST

START_TEST(reserve_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(int);
    o_vector_reserve(vector, 2U);
    ck_assert_uint_eq(vector->capacity, 2U);
    ck_assert_ptr_ne(vector->data, NULL);
    o_vector_reserve(vector, 2364U);
    ck_assert_uint_eq(vector->capacity, 2364U);
    ck_assert_ptr_ne(vector->data, NULL);
}
END_TEST

START_TEST(push_back_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(unsigned);
    unsigned val = 31111U;
    o_vector_push_back(vector, &val);
    ck_assert_uint_eq(vector->size, 1U);
    ck_assert_uint_eq(vector->capacity, 1U);
    ck_assert_ptr_ne(vector->data, NULL);
    ck_assert_uint_eq(((unsigned*)vector->data)[0], val);
    o_vector_push_back(vector, &val);
    ck_assert_uint_eq(vector->size, 2U);
    ck_assert_uint_eq(vector->capacity, 2U);
    ck_assert_ptr_ne(vector->data, NULL);
    ck_assert_uint_eq(((unsigned*)vector->data)[0], val);
    ck_assert_uint_eq(((unsigned*)vector->data)[1], val);
}
END_TEST

START_TEST(pop_back_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(unsigned);
    unsigned val0 = 31111U;
    unsigned val1 = 4324234U;
    o_vector_push_back(vector, &val0);
    o_vector_push_back(vector, &val1);
    o_vector_pop_back(vector);
    ck_assert_uint_eq(vector->size, 1U);
    ck_assert_uint_eq(vector->capacity, 2U);
    ck_assert_ptr_ne(vector->data, NULL);
    ck_assert_uint_eq(((unsigned*)vector->data)[0], val0);
    o_vector_pop_back(vector);
    ck_assert_uint_eq(vector->size, 0U);
    ck_assert_uint_eq(vector->capacity, 2U);
    ck_assert_ptr_ne(vector->data, NULL);
}
END_TEST

START_TEST(reserve_and_push_back_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(unsigned);
    o_vector_reserve(vector, 2564U);
    ck_assert_uint_eq(vector->size, 0U);
    ck_assert_uint_eq(vector->capacity, 2564U);
    const unsigned val = 1234U;
    o_vector_push_back(vector, &val);
    ck_assert_uint_eq(vector->size, 1U);
    ck_assert_uint_eq(vector->capacity, 2564U);
    ck_assert_uint_eq(((unsigned*)vector->data)[0], val);
    o_vector_push_back(vector, &val);
    ck_assert_uint_eq(vector->size, 2U);
    ck_assert_uint_eq(vector->capacity, 2564U);
    ck_assert_uint_eq(((unsigned*)vector->data)[0], val);
    ck_assert_uint_eq(((unsigned*)vector->data)[1], val);
}
END_TEST

START_TEST(size_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(int);
    const int a = 31111;
    o_vector_push_back(vector, &a);
    ck_assert_uint_eq(o_vector_size(vector), 1U);
    o_vector_push_back(vector, &a);
    ck_assert_uint_eq(o_vector_size(vector), 2U);
    o_vector_pop_back(vector);
    ck_assert_uint_eq(o_vector_size(vector), 1U);
    o_vector_pop_back(vector);
    ck_assert_uint_eq(o_vector_size(vector), 0U);
}
END_TEST

START_TEST(resize_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(int);
    o_vector_resize(vector, 7U);
    ck_assert_uint_eq(vector->size, 7U);
    ck_assert_uint_eq(vector->capacity, 7U);
    for (size_t i = 0; i < 7U; ++i) {  
        ck_assert_uint_eq(((unsigned*)vector->data)[i], 0);
    }
}
END_TEST

START_TEST(get_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(int);
    o_vector_resize(vector, 3U);
    int a = 31111;
    const int b = 34549;
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &b);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 0U), 0);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1U), 0);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 2U), 0);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 3U), a);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 4U), b);
}
END_TEST

START_TEST(set_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(int);
    int a = 31111;
    const int b = 34549;
    o_vector_push_back(vector, &b);
    o_vector_push_back(vector, &b);
    o_vector_set(vector, 1, &a);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1U), a);
}
END_TEST

START_TEST(push_back_array_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(int);
    int val = 12721;
    o_vector_push_back(vector, &val);
    int arr[5] = {1, 2, 3, 4, 5};
    o_vector_push_back_array(vector, arr, 3);
    ck_assert_uint_eq(o_vector_size(vector), 4U);
    ck_assert_uint_eq(vector->capacity, 4U);
    for (size_t i = 0; i < 3; ++i) {
        ck_assert_int_eq(*(int*)o_vector_get(vector, i + 1), arr[i]);
    }
}
END_TEST

START_TEST(empty_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(int);
    int a = 31111;
    int b = 0;
    ck_assert(o_vector_empty(vector));
    o_vector_push_back(vector, &b);
    ck_assert(!o_vector_empty(vector));
    o_vector_push_back(vector, &b);
    ck_assert(!o_vector_empty(vector));
    o_vector_pop_back(vector);
    ck_assert(!o_vector_empty(vector));
    o_vector_pop_back(vector);
    ck_assert(o_vector_empty(vector));
}
END_TEST

START_TEST(begin_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(int);
    int a = 31111;
    int b = 0;
    o_vector_push_back(vector, &b);
    o_vector_push_back(vector, &b);
    o_vector_set(vector, 1, &a);
    ck_assert_ptr_eq(o_vector_begin(vector), vector->data);
}
END_TEST

START_TEST(end_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(int);
    int a = 31111;
    int b = 0;
    o_vector_push_back(vector, &b);
    o_vector_push_back(vector, &b);
    o_vector_set(vector, 1, &a);
    ck_assert_ptr_eq(o_vector_end(vector), (void*)((char*)vector->data + sizeof(int) * 2));
}
END_TEST

START_TEST(capacity_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(int);
    ck_assert_int_eq(o_vector_capacity(vector), 0);
    int a = 31111;
    o_vector_reserve(vector, 2);
    ck_assert_uint_eq(o_vector_capacity(vector), 2U);
    o_vector_push_back(vector, &a);
    ck_assert_uint_eq(o_vector_capacity(vector), 2U);
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &a);
    ck_assert_uint_eq(o_vector_capacity(vector), 4U);
    ck_assert_uint_eq(o_vector_capacity(vector), vector->capacity);
}
END_TEST

START_TEST(clear_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(int);
    ck_assert_int_eq(o_vector_capacity(vector), 0);
    int a = 31111;
    const int b = 5;
    o_vector_reserve(vector, 2);
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &a);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 3), a);
    ck_assert_uint_eq(o_vector_capacity(vector), 4U);
    o_vector_clear(vector);
    ck_assert_uint_eq(o_vector_size(vector), 0U);
    ck_assert_uint_eq(o_vector_capacity(vector), 0U);
    ck_assert_ptr_eq(vector->data, NULL);
    o_vector_push_back(vector, &b);
    o_vector_push_back(vector, &b);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), b);
    ck_assert_uint_eq(o_vector_capacity(vector), 2U);
    ck_assert_uint_eq(o_vector_size(vector), 2U);
}
END_TEST

START_TEST(swap_test) {
    int a = 31111;
    int b = 5;
    o_vector_t* vector_one WITH_O_VECTOR_DTOR = o_vector_create(int);
    o_vector_push_back(vector_one, &a);
    o_vector_push_back(vector_one, &a);
    o_vector_push_back(vector_one, &a);
    o_vector_push_back(vector_one, &a);
    o_vector_t* vector_two WITH_O_VECTOR_DTOR = o_vector_create(int);
    o_vector_push_back(vector_two, &b);
    o_vector_push_back(vector_two, &b);
    void* first_data_array = vector_one->data;
    void* second_data_array = vector_two->data;
    o_vector_swap(vector_one, vector_two);
    ck_assert_uint_eq(vector_one->data_type_size, vector_two->data_type_size);
    // Check first vector.
    ck_assert_ptr_eq(o_vector_begin(vector_one), second_data_array);
    ck_assert_uint_eq(o_vector_capacity(vector_one), 2U);
    ck_assert_uint_eq(o_vector_size(vector_one), 2U);
    ck_assert_int_eq(*(int*)o_vector_get(vector_one, 0), b);
    ck_assert_int_eq(*(int*)o_vector_get(vector_one, 1), b);
    // Check second vector.
    ck_assert_ptr_eq(o_vector_begin(vector_two), first_data_array);
    ck_assert_uint_eq(o_vector_capacity(vector_two), 4U);
    ck_assert_uint_eq(o_vector_size(vector_two), 4U);
    ck_assert_int_eq(*(int*)o_vector_get(vector_two, 0), a);
    ck_assert_int_eq(*(int*)o_vector_get(vector_two, 1), a);
    ck_assert_int_eq(*(int*)o_vector_get(vector_two, 2), a);
    ck_assert_int_eq(*(int*)o_vector_get(vector_two, 3), a);

    o_vector_push_back(vector_one, &b);
    o_vector_push_back(vector_one, &b);
    ck_assert_int_eq(*(int*)o_vector_get(vector_one, 2), b);
    ck_assert_int_eq(*(int*)o_vector_get(vector_one, 3), b);
    ck_assert_uint_eq(o_vector_size(vector_one), 4U);
}
END_TEST

START_TEST(insert_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(int);
    int a = 31111;
    int b = 5;
    o_vector_insert(vector, &a, 0);
    ck_assert_uint_eq(o_vector_size(vector), 1U);
    ck_assert_uint_eq(o_vector_capacity(vector), 1U);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 0), a);
    o_vector_insert(vector, &b, 0);
    ck_assert_uint_eq(o_vector_size(vector), 2U);
    ck_assert_uint_eq(o_vector_capacity(vector), 2U);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 0), b);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), a);
    o_vector_insert(vector, &a, 0);
    ck_assert_uint_eq(o_vector_size(vector), 3U);
    ck_assert_uint_eq(o_vector_capacity(vector), 4U);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 0), a);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), b);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 2), a);
    o_vector_insert(vector, &b, 1);
    ck_assert_uint_eq(o_vector_size(vector), 4U);
    ck_assert_uint_eq(o_vector_capacity(vector), 4U);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 0), a);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), b);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 2), b);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 3), a);
    o_vector_insert(vector, &a, 4);
    ck_assert_uint_eq(o_vector_size(vector), 5U);
    ck_assert_uint_eq(o_vector_capacity(vector), 8U);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 0), a);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), b);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 2), b);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 3), a);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 4), a);
}
END_TEST

START_TEST(erase_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(int);
    int arr[5] = {1, 2, 3, 4, 5};
    o_vector_push_back_array(vector, arr, 5);
    ck_assert_uint_eq(o_vector_size(vector), 5U);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 0), arr[0]);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), arr[1]);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 2), arr[2]);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 3), arr[3]);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 4), arr[4]);
    o_vector_erase(vector, 2);
    ck_assert_uint_eq(o_vector_size(vector), 4U);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 0), arr[0]);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), arr[1]);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 2), arr[3]);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 3), arr[4]);
    o_vector_erase(vector, 3);
    ck_assert_uint_eq(o_vector_size(vector), 3U);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 0), arr[0]);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), arr[1]);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 2), arr[3]);
    o_vector_erase(vector, 0);
    ck_assert_uint_eq(o_vector_size(vector), 2U);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 0), arr[1]);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), arr[3]);
}
END_TEST

START_TEST(node_get_next_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(short);
    int a[5] = {1, 2, 3, 4, 5};
    o_vector_push_back_array(vector, a, 5);
    o_vector_node_t* node = o_vector_begin(vector);
    ck_assert_ptr_eq(node, vector->data);
    node = o_vector_node_get_next(vector, node);
    ck_assert_ptr_eq(node, (void*)((char*)vector->data + sizeof(short)));
    node = o_vector_node_get_next(vector, node);
    ck_assert_ptr_eq(node, (void*)((char*)vector->data + 2 * sizeof(short)));
    node = o_vector_node_get_next(vector, node);
    ck_assert_ptr_eq(node, (void*)((char*)vector->data + 3 * sizeof(short)));
    node = o_vector_node_get_next(vector, node);
    ck_assert_ptr_eq(node, (void*)((char*)vector->data + 4 * sizeof(short)));
}
END_TEST

START_TEST(node_set_and_get_value_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(short);
    short a[5] = {1, 2, 3, 4, 5};
    o_vector_push_back_array(vector, a, 5);
    o_vector_node_t* node = o_vector_begin(vector);
    for (size_t i = 0; i < 5; ++i) {
        ck_assert_int_eq(a[i], *(short*)o_vector_node_get_value(vector, node));
        node = o_vector_node_get_next(vector, node);
    }
    ck_assert_ptr_eq(node, o_vector_end(vector));
    node = o_vector_begin(vector);
    node = o_vector_node_get_next(vector, node);
    short val = 123;
    o_vector_node_set_value(vector, node, &val);
    ck_assert_int_eq(123, *(short*)o_vector_node_get_value(vector, node));
}
END_TEST

START_TEST(for_each_test) {
    o_vector_t* vector WITH_O_VECTOR_DTOR = o_vector_create(int);
    int a[5] = {1, 2, 3, 4, 5};
    o_vector_push_back_array(vector, a, 5);
    o_vector_for_each(vector, node) {
        int temp = 4 + *(int*)o_vector_node_get_value(vector, node);
        o_vector_node_set_value(vector, node, &temp);
    }
    ck_assert_int_eq(vector->size, 5);
    ck_assert_int_eq(vector->capacity, 8);
    int expected[5] = {5, 6, 7, 8, 9};
    for (size_t i = 0; i < 5; ++i) {
        ck_assert_int_eq(expected[i], *(int*)o_vector_get(vector, i));
    }
}
END_TEST

Suite* suite_vector(void)
{
    Suite* s;
    TCase* tc;
    s = suite_create("o_vector workability tests");
    tc = tcase_create("o_vector basic usage check");
    tcase_add_test(tc, create_test);
    tcase_add_test(tc, delete_test);
    tcase_add_test(tc, reserve_test);
    tcase_add_test(tc, push_back_test);
    tcase_add_test(tc, pop_back_test);
    tcase_add_test(tc, reserve_and_push_back_test);
    tcase_add_test(tc, size_test);
    tcase_add_test(tc, resize_test);
    tcase_add_test(tc, get_test);
    tcase_add_test(tc, set_test);
    tcase_add_test(tc, push_back_array_test);
    tcase_add_test(tc, empty_test);
    tcase_add_test(tc, begin_test);
    tcase_add_test(tc, end_test);
    tcase_add_test(tc, capacity_test);
    tcase_add_test(tc, clear_test);
    tcase_add_test(tc, swap_test);
    tcase_add_test(tc, insert_test);
    tcase_add_test(tc, erase_test);
    tcase_add_test(tc, node_get_next_test);
    tcase_add_test(tc, node_set_and_get_value_test);
    tcase_add_test(tc, for_each_test);
    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    int number_failed;
    SRunner* sr;
    Suite* s_vector = suite_vector();
    sr = srunner_create(s_vector);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}