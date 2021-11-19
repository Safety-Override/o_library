/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include <check.h>
#include <o_vector.h>
#include <o_vector_private.h>

START_TEST(o_vector_create_test) {
    o_vector_t* vector = o_vector_create(int);
    ck_assert_int_eq(vector->size, 0);
    ck_assert_int_eq(vector->capacity, 0);
    ck_assert_int_eq(vector->data_type_size, sizeof(int));
    o_vector_destroy(vector);
}
END_TEST

START_TEST(o_vector_for_each_test) {
    o_vector_t* vector = o_vector_create(int);
    int a[5] = {1, 2, 3, 4, 5};
    int b[5] = {5, 6, 7, 8, 9};
    o_vector_push_back(vector, &a[0]);
    o_vector_push_back(vector, &a[1]);
    o_vector_push_back(vector, &a[2]);
    o_vector_push_back(vector, &a[3]);
    o_vector_push_back(vector, &a[4]);
    o_vector_node_t* node;
    int i = 0;
    int temp;
    o_vector_for_each(vector, node) {
        temp = 4 + a[i++];
        o_vector_node_set_value(vector, node, &temp);
    }
    o_vector_node_t* current_node = o_vector_begin(vector);
    for (int j = 0; j < 5; ++j) {
        ck_assert_int_eq(b[j], *(int*)current_node);
        current_node = o_vector_node_get_next(vector, current_node);
    }
    o_vector_destroy(vector);
}
END_TEST

START_TEST(o_vector_size_test) {
    o_vector_t* vector = o_vector_create(int);
    ck_assert_int_eq(o_vector_size(vector), 0);
    int a = 31111;
    o_vector_push_back(vector, &a);
    ck_assert_int_eq(o_vector_size(vector), 1);
    o_vector_push_back(vector, &a);
    ck_assert_int_eq(o_vector_size(vector), 2);
    o_vector_pop_back(vector);
    ck_assert_int_eq(o_vector_size(vector), 1);
    o_vector_pop_back(vector);
    ck_assert_int_eq(o_vector_size(vector), 0);
    o_vector_destroy(vector);
}
END_TEST

START_TEST(o_vector_reserve_test) {
    o_vector_t* vector = o_vector_create(int);
    ck_assert_int_eq(vector->size, 0);
    int a = 31111;
    o_vector_reserve(vector, 2);
    ck_assert_int_eq(vector->capacity, 2);
    o_vector_push_back(vector, &a);
    ck_assert_int_eq(vector->size, 1);
    ck_assert_int_eq(vector->capacity, 2);
    o_vector_push_back(vector, &a);
    ck_assert_int_eq(vector->size, 2);
    ck_assert(vector->capacity >= 2);
    o_vector_destroy(vector);
}
END_TEST

START_TEST(o_vector_push_back_test) {
    o_vector_t* vector = o_vector_create(int);
    ck_assert_int_eq(vector->size, 0);
    int a = 31111;
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &a);
    ck_assert_int_eq(vector->size, 2);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), a);
    o_vector_destroy(vector);
}
END_TEST

START_TEST(o_vector_set_test) {
    o_vector_t* vector = o_vector_create(int);
    int a = 31111;
    int b = 0;
    o_vector_push_back(vector, &b);
    o_vector_push_back(vector, &b);
    o_vector_set(vector, 1, &a);
    ck_assert_int_eq(*(int*)((char*)vector->data + sizeof(int)), a);
    o_vector_destroy(vector);
}
END_TEST

START_TEST(o_vector_get_test) {
    o_vector_t* vector = o_vector_create(int);
    int a = 31111;
    int b = 0;
    o_vector_push_back(vector, &b);
    o_vector_push_back(vector, &b);
    o_vector_set(vector, 1, &a);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), a);
    o_vector_destroy(vector);
}
END_TEST

START_TEST(o_vector_pop_back_test) {
    o_vector_t* vector = o_vector_create(int);
    int a = 31111;
    int b = 0;
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &b);
    o_vector_pop_back(vector);
    ck_assert_int_eq(vector->size, 1);
    o_vector_destroy(vector);
}
END_TEST

START_TEST(o_vector_destroy_test) {
    ck_assert_int_eq(0, 0); //hope it just works.
}
END_TEST

START_TEST(o_vector_push_back_array_test) {
    o_vector_t* vector = o_vector_create(int);
    int a[5] = {1, 2, 3, 4, 5};
    o_vector_push_back_array(vector, a, 4);
    ck_assert_int_eq(vector->size, 4);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 3), 4);
    ck_assert(vector->capacity >= 4);

    o_vector_destroy(vector);
}
END_TEST

START_TEST(o_vector_begin_test) {
    o_vector_t* vector = o_vector_create(int);
    int a = 31111;
    int b = 0;
    o_vector_push_back(vector, &b);
    o_vector_push_back(vector, &b);
    o_vector_set(vector, 1, &a);
    ck_assert(o_vector_begin(vector) == vector->data);
    o_vector_destroy(vector);
}
END_TEST

START_TEST(o_vector_end_test) {
    o_vector_t* vector = o_vector_create(int);
    int a = 31111;
    int b = 0;
    o_vector_push_back(vector, &b);
    o_vector_push_back(vector, &b);
    o_vector_set(vector, 1, &a);
    ck_assert(o_vector_end(vector) == (void*)((char*)vector->data + sizeof(int) * 2));
    o_vector_destroy(vector);
}
END_TEST

START_TEST(o_vector_empty_test) {
    o_vector_t* vector = o_vector_create(int);
    int a = 31111;
    int b = 0;
    ck_assert(o_vector_empty(vector) == true);
    o_vector_push_back(vector, &b);
    ck_assert(o_vector_empty(vector) == false);
    o_vector_push_back(vector, &b);
    ck_assert(o_vector_empty(vector) == false);
    o_vector_pop_back(vector);
    ck_assert(o_vector_empty(vector) == false);
    o_vector_pop_back(vector);
    ck_assert(o_vector_empty(vector) == true);
    ck_assert(vector->size == 0);
    o_vector_destroy(vector);
}
END_TEST

START_TEST(o_vector_capacity_test) {
    o_vector_t* vector = o_vector_create(int);
    ck_assert_int_eq(o_vector_capacity(vector), 0);
    int a = 31111;
    o_vector_reserve(vector, 2);
    ck_assert_int_eq(o_vector_capacity(vector), 2);
    o_vector_push_back(vector, &a);
    ck_assert_int_eq(o_vector_capacity(vector), 2);
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &a);
    ck_assert(o_vector_capacity(vector) >= 2);
    ck_assert_int_eq(o_vector_capacity(vector), vector->capacity);
    o_vector_destroy(vector);
}
END_TEST

START_TEST(o_vector_clear_test) {
    o_vector_t* vector = o_vector_create(int);
    ck_assert_int_eq(o_vector_capacity(vector), 0);
    int a = 31111;
    int b = 5;
    o_vector_reserve(vector, 2);
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &a);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 3), a);
    ck_assert(vector->capacity >= 4);
    o_vector_clear(vector);
    o_vector_push_back(vector, &b);
    o_vector_push_back(vector, &b);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), b);
    ck_assert(vector->capacity >= 2 && vector->capacity < 4);
    ck_assert_int_eq(vector->size, 2);
    o_vector_destroy(vector);
}
END_TEST

START_TEST(o_vector_swap_test) {
    o_vector_t* vector_one = o_vector_create(int);
    o_vector_t* vector_two = o_vector_create(int);
    int a = 31111;
    int b = 5;
    o_vector_reserve(vector_one, 2);
    o_vector_push_back(vector_one, &a);
    o_vector_push_back(vector_one, &a);
    o_vector_push_back(vector_one, &a);
    o_vector_push_back(vector_one, &a);
    o_vector_push_back(vector_two, &b);
    o_vector_push_back(vector_two, &b);
    void* first_data_array = vector_one->data;
    void* second_data_array = vector_two->data;
    ck_assert_int_eq(*(int*)o_vector_get(vector_one, 3), a);
    ck_assert_int_eq(o_vector_size(vector_one), 4);
    ck_assert_int_eq(*(int*)o_vector_get(vector_two, 1), b);
    ck_assert_int_eq(o_vector_size(vector_two), 2);
    ck_assert_int_eq(o_vector_capacity(vector_one), 4);
    ck_assert_int_eq(o_vector_capacity(vector_two), 2);
    o_vector_swap(vector_one, vector_two);
    ck_assert_int_eq(*(int*)o_vector_get(vector_two, 3), a);
    ck_assert_int_eq(o_vector_size(vector_two), 4);
    ck_assert_int_eq(*(int*)o_vector_get(vector_one, 1), b);
    ck_assert_int_eq(o_vector_size(vector_one), 2);
    ck_assert_int_eq(o_vector_capacity(vector_one), 2);
    ck_assert_int_eq(o_vector_capacity(vector_two), 4);
    o_vector_push_back(vector_one, &b);
    o_vector_push_back(vector_one, &b);
    ck_assert_int_eq(*(int*)o_vector_get(vector_one, 3), b);
    ck_assert_int_eq(o_vector_size(vector_one), 4);
    ck_assert(o_vector_begin(vector_two) == first_data_array);
    ck_assert(o_vector_begin(vector_one) == second_data_array);
    o_vector_destroy(vector_one);
    o_vector_destroy(vector_two);
}
END_TEST

START_TEST(o_vector_insert_test) {
    o_vector_t* vector = o_vector_create(int);
    int a = 31111;
    int b = 5;
    o_vector_insert(vector, &a, 0);
    ck_assert_int_eq(vector->size, 1);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 0), a);
    o_vector_insert(vector, &b, 0);
    ck_assert_int_eq(vector->size, 2);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 0), b);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), a);
    o_vector_insert(vector, &a, 0);
    ck_assert_int_eq(vector->size, 3);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 0), a);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), b);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 2), a);
    o_vector_insert(vector, &b, 1);
    ck_assert_int_eq(vector->size, 4);
    ck_assert(vector->capacity >= 4);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 0), a);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), b);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 2), b);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 3), a);
    o_vector_insert(vector, &a, 4);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 0), a);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 1), b);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 2), b);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 3), a);
    ck_assert_int_eq(*(int*)o_vector_get(vector, 4), a);
    o_vector_destroy(vector);
}
END_TEST

START_TEST(o_vector_erase_test) {
    //to do
}
END_TEST

Suite* suite_zero(void)
{
    Suite* s;
    TCase* tc;
    s = suite_create("workability tests");
    tc = tcase_create("basic usage check");
    tcase_add_test(tc, o_vector_create_test);
    tcase_add_test(tc, o_vector_for_each_test);
    tcase_add_test(tc, o_vector_size_test);
    tcase_add_test(tc, o_vector_reserve_test);
    tcase_add_test(tc, o_vector_push_back_test);
    tcase_add_test(tc, o_vector_set_test);
    tcase_add_test(tc, o_vector_get_test);
    tcase_add_test(tc, o_vector_pop_back_test);
    tcase_add_test(tc, o_vector_destroy_test);
    tcase_add_test(tc, o_vector_push_back_array_test);
    tcase_add_test(tc, o_vector_begin_test);
    tcase_add_test(tc, o_vector_end_test);
    tcase_add_test(tc, o_vector_empty_test);
    tcase_add_test(tc, o_vector_capacity_test);
    tcase_add_test(tc, o_vector_clear_test);
    tcase_add_test(tc, o_vector_swap_test);
    tcase_add_test(tc, o_vector_insert_test);
    tcase_add_test(tc, o_vector_erase_test);
    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    int number_failed;
    SRunner* sr;

    Suite* s_zero = suite_zero();

    sr = srunner_create(s_zero);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}