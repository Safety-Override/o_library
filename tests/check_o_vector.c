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
}
END_TEST

START_TEST(o_vector_for_each_test) {
    o_vector_t* vector = o_vector_create(int);
    int a[5] = {1, 2, 3, 4, 5};
    int b[5] = {5, 6, 7, 8, 9};
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &a);
    o_vector_push_back(vector, &a);
    o_vector_node_t* node;
    int i = 0;
    int temp;
    o_vector_for_each(vector, node) {
        temp = 4 + a[i++];
        o_vector_node_set_value(vector, node, &temp);
    }
    i = 0;
    o_vector_for_each(vector, node) {
        ck_assert_int_eq(b[i++], *(int*)o_vector_node_get_value(vector, node));
    }
}
END_TEST

START_TEST(o_vector_size_test) {
    o_vector_t* vector = o_vector_create(int);
    ck_assert_int_eq(vector->size, 0);
    int a = 31111;
    o_vector_push_back(vector, &a);
    ck_assert_int_eq(vector->size, 1);
    o_vector_push_back(vector, &a);
    ck_assert_int_eq(vector->size, 2);
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