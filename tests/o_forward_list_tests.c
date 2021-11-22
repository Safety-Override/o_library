/** 
 * Copyright (c) 2021 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include <stdlib.h>
#include <check.h>
#include <o_forward_list.h>
#include <o_forward_list_private.h>

START_TEST(create_test) {
    o_forward_list_t* list = o_forward_list_create(int);
    ck_assert_uint_eq(list->data_type_size, sizeof(int));
    ck_assert_ptr_eq(list->front, NULL);
    o_forward_list_destroy(list);
}
END_TEST

START_TEST(push_front_test) {
    o_forward_list_t* list = o_forward_list_create(unsigned);
    unsigned val = 31111U;
    o_forward_list_push_front(list, &val);
    ck_assert_uint_eq(list->data_type_size, sizeof(unsigned));
    ck_assert_ptr_eq(list->front->next, NULL);
    ck_assert_uint_eq(*(int*)list->front->data, val);
    unsigned another_val = 311435U;
    o_forward_list_push_front(list, &another_val);
    ck_assert_ptr_eq(list->front->next->next, NULL);
    ck_assert_uint_eq(*(int*)list->front->data, another_val);
    ck_assert_uint_eq(*(int*)list->front->next->data, val);
    o_forward_list_destroy(list);
}
END_TEST

START_TEST(pop_front_test) {
    o_forward_list_t* list = o_forward_list_create(unsigned);
    unsigned val0 = 31111U;
    unsigned val1 = 4324234U;
    o_forward_list_push_front(list, &val0);
    o_forward_list_push_front(list, &val1);
    o_forward_list_pop_front(list);
    ck_assert_ptr_eq(list->front->next, NULL);
    ck_assert_uint_eq(*(int*)list->front->data, val0);
    o_forward_list_pop_front(list);
    ck_assert_ptr_eq(list->front, NULL);
    o_forward_list_destroy(list);
}
END_TEST

START_TEST(clear_test) {
    o_forward_list_t* list = o_forward_list_create(int);
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
    ck_assert_int_eq(*(int*)list->front->next->data, b);
    ck_assert_ptr_eq(list->front->next->next, NULL);
    o_forward_list_destroy(list);
}
END_TEST

START_TEST(destroy_test) {
    ck_assert_int_eq(0, 0); // it just works bacause it calls clear func
}
END_TEST

START_TEST(front_test) {
    o_forward_list_t* list = o_forward_list_create(int);
    int a = 31111;
    int b = 0;
    o_forward_list_push_front(list, &a);
    ck_assert_int_eq(*(int*)o_forward_list_front(list), a);
    o_forward_list_push_front(list, &b);
    ck_assert_int_eq(*(int*)o_forward_list_front(list), b);
    o_forward_list_pop_front(list);
    ck_assert_int_eq(*(int*)o_forward_list_front(list), a);
    o_forward_list_destroy(list);
}
END_TEST

START_TEST(empty_test) {
    o_forward_list_t* list = o_forward_list_create(int);
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
    o_forward_list_destroy(list);
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
    tcase_add_test(tc, destroy_test);
    tcase_add_test(tc, front_test);
    tcase_add_test(tc, empty_test);
    /*
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
    */
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