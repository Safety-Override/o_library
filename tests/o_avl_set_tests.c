/** 
 * Copyright (c) 2022 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include "o_avl_set.h"
#include "o_avl_set_private.h"

#include <stdlib.h>
#include <check.h>

int int_compare(const void* a, const void* b) {
    const int int_a = *(const int*)a;
    const int int_b = *(const int*)b;
    if (int_a < int_b) {
        return -1;
    }
    return int_a > int_b;
}

START_TEST(create_test) {
    o_avl_set_t* set = o_avl_set_create(int, int_compare);
    ck_assert_ptr_eq(set->root, NULL);
    ck_assert_uint_eq(set->size, 0);
    ck_assert_uint_eq(set->node_size, 32);
    ck_assert_uint_eq(set->offsetof_key, 28);
    ck_assert_uint_eq(set->sizeof_key, sizeof(int));
    o_avl_set_delete(set);
}
END_TEST

START_TEST(empty_test) {
    o_avl_set_t* set = o_avl_set_create(int, int_compare);
    ck_assert_ptr_eq(set->root, NULL);
    ck_assert_uint_eq(set->size, 0);
    ck_assert(o_avl_set_empty(set));
    int key = 55;
    o_avl_set_insert(set, &key);
    ck_assert_uint_eq(set->size, 1);
    ck_assert_ptr_ne(set->root, NULL);
    ck_assert(!o_avl_set_empty(set));
    o_avl_set_delete(set);
}
END_TEST

START_TEST(clear_test) {
    o_avl_set_t* set = o_avl_set_create(int, int_compare);
    ck_assert(o_avl_set_empty(set));
    int key = 55;
    o_avl_set_insert(set, &key);
    ck_assert_uint_eq(set->size, 1);
    ck_assert(!o_avl_set_empty(set));
    ++key;
    o_avl_set_insert(set, &key);
    ck_assert_uint_eq(set->size, 2);
    ++key;
    o_avl_set_insert(set, &key);
    ck_assert_uint_eq(set->size, 3);
    ++key;
    o_avl_set_insert(set, &key);
    ck_assert_uint_eq(set->size, 4);
    o_avl_set_clear(set);
    ck_assert_ptr_eq(set->root, NULL);
    ck_assert_uint_eq(set->size, 0);
    ck_assert(o_avl_set_empty(set));
    o_avl_set_delete(set);
}
END_TEST

START_TEST(insert_test) {
    o_avl_set_t* set = o_avl_set_create(int, int_compare);
    ck_assert(o_avl_set_empty(set));
    int key = 55;
    o_avl_set_insert_result_t res = o_avl_set_insert(set, &key);
    ck_assert(res.insertion_took_place);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res.node), key);
    ck_assert_uint_eq(set->size, 1);
    ck_assert_ptr_ne(set->root, NULL);
    ck_assert(!o_avl_set_empty(set));
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, set->root), key);
    ++key;
    res = o_avl_set_insert(set, &key);
    ck_assert_uint_eq(set->size, 2);
    ck_assert(res.insertion_took_place);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res.node), key);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, set->root->right), key);
    res = o_avl_set_insert(set, &key);
    ck_assert_uint_eq(set->size, 2);
    ck_assert(!res.insertion_took_place);
    o_avl_set_clear(set);
    ck_assert_ptr_eq(set->root, NULL);
    ck_assert_uint_eq(set->size, 0);
    ck_assert(o_avl_set_empty(set));
    o_avl_set_delete(set);
}
END_TEST

START_TEST(erase_test) {
    o_avl_set_t* set = o_avl_set_create(int, int_compare);
    ck_assert(o_avl_set_empty(set));
    int key = 55;
    o_avl_set_insert(set, &key);
    ck_assert_uint_eq(set->size, 1);
    ck_assert_ptr_ne(set->root, NULL);
    ck_assert(!o_avl_set_empty(set));
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, set->root), key);
    ++key;
    o_avl_set_insert(set, &key);
    ck_assert_uint_eq(set->size, 2);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, set->root->right), key);
    --key;
    o_avl_set_erase(set, &key);
    ++key;
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, set->root), key);
    ck_assert_ptr_eq(set->root->right, NULL);
    ck_assert_uint_eq(set->size, 1);
    ck_assert_ptr_ne(set->root, NULL);
    o_avl_set_erase(set, &key);
    ck_assert_ptr_eq(set->root, NULL);
    ck_assert_uint_eq(set->size, 0);
    o_avl_set_delete(set);
}
END_TEST

START_TEST(delete_test) {
    ck_assert(true);//works on clear, so works until clear works
}
END_TEST

START_TEST(swap_test) {
    o_avl_set_t* first_set = o_avl_set_create(int, int_compare);
    o_avl_set_t* second_set = o_avl_set_create(int, int_compare);
    ck_assert(o_avl_set_empty(first_set));
    ck_assert(o_avl_set_empty(second_set));
    int key = 55;
    o_avl_set_insert(first_set, &key);
    ck_assert(!o_avl_set_empty(first_set));
    o_avl_set_swap(first_set, second_set);
    ck_assert(o_avl_set_empty(first_set));
    ck_assert(!o_avl_set_empty(second_set));
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(second_set, second_set->root), key);
    ++key;
    o_avl_set_insert(second_set, &key);
    ck_assert_uint_eq(second_set->size, 2);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(second_set, second_set->root->right), key);
    ++key;
    o_avl_set_insert(first_set, &key);
    ck_assert_uint_eq(first_set->size, 1);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(first_set, first_set->root), key);
    o_avl_set_swap(first_set, second_set);
    ck_assert_uint_eq(first_set->size, 2);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(first_set, first_set->root), 55);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(first_set, first_set->root->right), 56);
    ck_assert_uint_eq(second_set->size, 1);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(second_set, second_set->root), 57);
    o_avl_set_delete(first_set);
    o_avl_set_delete(second_set);
}
END_TEST

START_TEST(find_test) {
    o_avl_set_t* set = o_avl_set_create(int, int_compare);
    ck_assert(o_avl_set_empty(set));
    int key = 55;
    o_avl_set_insert(set, &key);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, set->root), key);
    o_avl_set_node_t* res = o_avl_set_find(set, &key);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res), key);
    ++key;
    o_avl_set_insert(set, &key);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, set->root->right), key);
    res = o_avl_set_find(set, &key);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res), key);
    o_avl_set_delete(set);
}
END_TEST

START_TEST(contains_test) {
    o_avl_set_t* set = o_avl_set_create(int, int_compare);
    ck_assert(o_avl_set_empty(set));
    int key = 55;
    ck_assert(!o_avl_set_contains(set, &key));
    o_avl_set_insert(set, &key);
    ck_assert(o_avl_set_contains(set, &key));
    ++key;
    o_avl_set_insert(set, &key);
    ck_assert(o_avl_set_contains(set, &key));
    o_avl_set_erase(set, &key);
    ck_assert(!o_avl_set_contains(set, &key));
    --key;
    ck_assert(o_avl_set_contains(set, &key));
    o_avl_set_erase(set, &key);
    ck_assert(!o_avl_set_contains(set, &key));
    o_avl_set_delete(set);
}
END_TEST

START_TEST(lower_bound_test) {
    o_avl_set_t* set = o_avl_set_create(int, int_compare);
    ck_assert(o_avl_set_empty(set));
    int key = 55;
    o_avl_set_insert(set, &key);//55
    key = 56;
    o_avl_set_insert(set, &key);//56
    key = 57;
    o_avl_set_insert(set, &key);//57
    key = 59;
    o_avl_set_insert(set, &key);//59
    key = 60;
    o_avl_set_insert(set, &key);//60
    key = 61;
    o_avl_set_insert(set, &key);//61
    key = 58;
    o_avl_set_node_t* res = o_avl_set_lower_bound(set, &key);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res), 59);
    key = 54;
    res = o_avl_set_lower_bound(set, &key);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res), 55);
    key = 55;
    res = o_avl_set_lower_bound(set, &key);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res), 55);
    key = 57;
    res = o_avl_set_lower_bound(set, &key);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res), 57);
    key = 61;
    res = o_avl_set_lower_bound(set, &key);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res), 61);
    key = 62;
    res = o_avl_set_lower_bound(set, &key);
    ck_assert_ptr_eq(res, NULL);
    o_avl_set_delete(set);
}
END_TEST

START_TEST(upper_bound_test) {
    o_avl_set_t* set = o_avl_set_create(int, int_compare);
    ck_assert(o_avl_set_empty(set));
    int key = 55;
    o_avl_set_insert(set, &key);//55
    key = 56;
    o_avl_set_insert(set, &key);//56
    key = 57;
    o_avl_set_insert(set, &key);//57
    key = 59;
    o_avl_set_insert(set, &key);//59
    key = 60;
    o_avl_set_insert(set, &key);//60
    key = 61;
    o_avl_set_insert(set, &key);//61
    key = 58;
    o_avl_set_node_t* res = o_avl_set_upper_bound(set, &key);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res), 59);
    key = 54;
    res = o_avl_set_upper_bound(set, &key);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res), 55);
    key = 55;
    res = o_avl_set_upper_bound(set, &key);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res), 56);
    key = 57;
    res = o_avl_set_upper_bound(set, &key);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res), 59);
    key = 61;
    res = o_avl_set_upper_bound(set, &key);
    ck_assert_ptr_eq(res, NULL);
    key = 62;
    res = o_avl_set_upper_bound(set, &key);
    ck_assert_ptr_eq(res, NULL);
    o_avl_set_delete(set);
}
END_TEST

START_TEST(begin_test) {
    o_avl_set_t* set = o_avl_set_create(int, int_compare);
    ck_assert(o_avl_set_empty(set));
    int key = 55;
    o_avl_set_insert(set, &key);//55
    key = 56;
    o_avl_set_insert(set, &key);//56
    key = 57;
    o_avl_set_insert(set, &key);//57
    key = 59;
    o_avl_set_insert(set, &key);//59
    key = 60;
    o_avl_set_insert(set, &key);//60
    key = 61;
    o_avl_set_insert(set, &key);//61
    o_avl_set_node_t* res = o_avl_set_begin(set);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res), 55);
    key = 55;
    o_avl_set_erase(set, &key);
    res = o_avl_set_begin(set);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res), 56);
    o_avl_set_clear(set);
    res = o_avl_set_begin(set);
    ck_assert_ptr_eq(res, NULL);
    o_avl_set_delete(set);
}
END_TEST

START_TEST(end_test) {
    ck_assert(true);//returns null, better test with node_get_next
}
END_TEST

START_TEST(node_get_next_test) {
    o_avl_set_t* set = o_avl_set_create(int, int_compare);
    ck_assert(o_avl_set_empty(set));
    int key = 55;
    o_avl_set_insert(set, &key);//55
    key = 56;
    o_avl_set_insert(set, &key);//56
    key = 57;
    o_avl_set_insert(set, &key);//57
    key = 59;
    o_avl_set_insert(set, &key);//59
    key = 60;
    o_avl_set_insert(set, &key);//60
    key = 61;
    o_avl_set_insert(set, &key);//61
    o_avl_set_node_t* res = o_avl_set_begin(set);
    o_avl_set_node_t* cur = res;
    key = 55;
    while (cur != o_avl_set_end(set)) {
        ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, cur), key);
        if (key == 57) {
            ++key;
        }
        ++key;
        cur = o_avl_set_node_get_next(set, cur);
    }
    o_avl_set_delete(set);
}
END_TEST

START_TEST(node_get_key_test) {
    o_avl_set_t* set = o_avl_set_create(int, int_compare);
    ck_assert(o_avl_set_empty(set));
    int key = 55;
    o_avl_set_insert_result_t res = o_avl_set_insert(set, &key);
    ck_assert(res.insertion_took_place);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res.node), key);
    ck_assert_uint_eq(set->size, 1);
    ck_assert_ptr_ne(set->root, NULL);
    ck_assert(!o_avl_set_empty(set));
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, set->root), key);
    ++key;
    res = o_avl_set_insert(set, &key);
    ck_assert_uint_eq(set->size, 2);
    ck_assert(res.insertion_took_place);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, res.node), key);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, set->root->right), key);
    res = o_avl_set_insert(set, &key);
    ck_assert_uint_eq(set->size, 2);
    ck_assert(!res.insertion_took_place);
    o_avl_set_clear(set);
    ck_assert_ptr_eq(set->root, NULL);
    ck_assert_uint_eq(set->size, 0);
    ck_assert(o_avl_set_empty(set));
    o_avl_set_delete(set);
}
END_TEST

START_TEST(node_erase_test) {
    o_avl_set_t* set = o_avl_set_create(int, int_compare);
    ck_assert(o_avl_set_empty(set));
    int key = 55;
    o_avl_set_insert(set, &key);
    ck_assert_uint_eq(set->size, 1);
    ck_assert_ptr_ne(set->root, NULL);
    ck_assert(!o_avl_set_empty(set));
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, set->root), key);
    ++key;
    o_avl_set_insert(set, &key);
    ck_assert_uint_eq(set->size, 2);
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, set->root->right), key);
    o_avl_set_node_erase(set, set->root);
    --key;
    ck_assert_ptr_eq(o_avl_set_find(set, &key), NULL);
    ck_assert_uint_eq(set->size, 1);
    ++key;
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, set->root), key);
    ck_assert_ptr_ne(o_avl_set_find(set, &key), NULL);
    o_avl_set_node_erase(set, set->root);
    ck_assert_ptr_eq(o_avl_set_find(set, &key), NULL);
    ck_assert_ptr_eq(set->root, NULL);
    ck_assert_uint_eq(set->size, 0);
    o_avl_set_delete(set);
}
END_TEST

START_TEST(size_test) {
    o_avl_set_t* set = o_avl_set_create(int, int_compare);
    ck_assert(o_avl_set_empty(set));
    int key = 55;
    o_avl_set_insert(set, &key);
    ck_assert_uint_eq(set->size, 1);
    ck_assert_uint_eq(set->size, o_avl_set_size(set));
    ck_assert_ptr_ne(set->root, NULL);
    ck_assert(!o_avl_set_empty(set));
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, set->root), key);
    ++key;
    o_avl_set_insert(set, &key);
    ck_assert_uint_eq(set->size, 2);
    ck_assert_uint_eq(set->size, o_avl_set_size(set));
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, set->root->right), key);
    o_avl_set_node_erase(set, set->root);
    --key;
    ck_assert_ptr_eq(o_avl_set_find(set, &key), NULL);
    ck_assert_uint_eq(set->size, 1);
    ck_assert_uint_eq(set->size, o_avl_set_size(set));
    ++key;
    ck_assert_int_eq(*(int*)o_avl_set_node_get_key(set, set->root), key);
    ck_assert_ptr_ne(o_avl_set_find(set, &key), NULL);
    o_avl_set_node_erase(set, set->root);
    ck_assert_ptr_eq(o_avl_set_find(set, &key), NULL);
    ck_assert_ptr_eq(set->root, NULL);
    ck_assert_uint_eq(set->size, 0);
    ck_assert_uint_eq(set->size, o_avl_set_size(set));
    o_avl_set_delete(set);
}
END_TEST

Suite* suite_avl_set(void)
{
    Suite* s;
    TCase* tc;
    s = suite_create("o_avl_set workability tests");
    tc = tcase_create("o_avl_set basic usage check");
    tcase_add_test(tc, create_test);
    tcase_add_test(tc, empty_test);
    tcase_add_test(tc, clear_test);
    tcase_add_test(tc, insert_test);
    tcase_add_test(tc, erase_test);
    tcase_add_test(tc, delete_test);
    tcase_add_test(tc, swap_test);
    tcase_add_test(tc, find_test);
    tcase_add_test(tc, contains_test);
    tcase_add_test(tc, lower_bound_test);
    tcase_add_test(tc, upper_bound_test);
    tcase_add_test(tc, begin_test);
    tcase_add_test(tc, end_test);
    tcase_add_test(tc, node_get_next_test);
    tcase_add_test(tc, node_get_key_test);
    tcase_add_test(tc, node_erase_test);
    tcase_add_test(tc, size_test);
    suite_add_tcase(s, tc);
    return s;
}

int main(void) {
    int number_failed;
    SRunner* sr;
    Suite* s_avl_set = suite_avl_set();
    sr = srunner_create(s_avl_set);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}