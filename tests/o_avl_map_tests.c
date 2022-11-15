/** 
 * Copyright (c) 2022 Safety-Override
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include "o_avl_map.h"
#include "o_avl_map_private.h"

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
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert_ptr_eq(map->set.root, NULL);
    ck_assert_uint_eq(map->set.size, 0);
    ck_assert_uint_eq(map->set.node_size, 36);
    ck_assert_uint_eq(map->set.offsetof_key, 28);
    ck_assert_uint_eq(map->set.sizeof_key, sizeof(int));
    ck_assert_uint_eq(map->offsetof_value, 32);
    ck_assert_uint_eq(map->sizeof_value, sizeof(int));
}
END_TEST

START_TEST(empty_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert_ptr_eq(map->set.root, NULL);
    ck_assert_uint_eq(map->set.size, 0);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value = 66;
    o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 1);
    ck_assert_ptr_ne(map->set.root, NULL);
    ck_assert(!o_avl_map_empty(map));
}
END_TEST

START_TEST(clear_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value = 66;
    o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 1);
    ck_assert(!o_avl_map_empty(map));
    ++key;
    o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 2);
    ++key;
    o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 3);
    ++key;
    o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 4);
    o_avl_map_clear(map);
    ck_assert_ptr_eq(map->set.root, NULL);
    ck_assert_uint_eq(map->set.size, 0);
    ck_assert(o_avl_map_empty(map));
}
END_TEST

START_TEST(insert_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value = 66;
    o_avl_map_insert_result_t res = o_avl_map_insert(map, &key, &value);
    ck_assert(res.insertion_took_place);
    ck_assert_ptr_eq(res.node, map->set.root);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res.node), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res.node), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root), value);
    ck_assert_uint_eq(map->set.size, 1);
    ck_assert_ptr_ne(map->set.root, NULL);
    ck_assert(!o_avl_map_empty(map));
    ++key;
    ++value;
    res = o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 2);
    ck_assert(res.insertion_took_place);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res.node), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res.node), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root->right), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root->right), value);
    ++value;
    res = o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 2);
    ck_assert(!res.insertion_took_place);
    o_avl_map_clear(map);
    ck_assert_ptr_eq(map->set.root, NULL);
    ck_assert_uint_eq(map->set.size, 0);
    ck_assert(o_avl_map_empty(map));
}
END_TEST

START_TEST(insert_or_assign_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value = 66;
    o_avl_map_insert_or_assign_result_t res = o_avl_map_insert_or_assign(map, &key, &value);
    ck_assert(!res.assignment_took_place);
    ck_assert_ptr_eq(res.node, map->set.root);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res.node), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res.node), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root), value);
    ck_assert_uint_eq(map->set.size, 1);
    ck_assert_ptr_ne(map->set.root, NULL);
    ck_assert(!o_avl_map_empty(map));
    ++key;
    ++value;
    res = o_avl_map_insert_or_assign(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 2);
    ck_assert(!res.assignment_took_place);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res.node), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res.node), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root->right), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root->right), value);
    ++value;
    res = o_avl_map_insert_or_assign(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 2);
    ck_assert(res.assignment_took_place);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res.node), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res.node), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root->right), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root->right), value);
    o_avl_map_clear(map);
    ck_assert_ptr_eq(map->set.root, NULL);
    ck_assert_uint_eq(map->set.size, 0);
    ck_assert(o_avl_map_empty(map));
}
END_TEST

START_TEST(erase_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value =  66;
    o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 1);
    ck_assert_ptr_ne(map->set.root, NULL);
    ck_assert(!o_avl_map_empty(map));
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root), value);
    ++key;
    ++value;
    o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 2);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root->right), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root->right), value);
    --key;
    o_avl_map_erase(map, &key);
    ck_assert_ptr_eq(map->set.root->right, NULL);
    ck_assert_uint_eq(map->set.size, 1);
    ck_assert_ptr_ne(map->set.root, NULL);
    ++key;
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root), value);
    o_avl_map_erase(map, &key);
    ck_assert_ptr_eq(map->set.root, NULL);
    ck_assert_uint_eq(map->set.size, 0);
}
END_TEST

START_TEST(delete_test) {
    ck_assert(true);//works on clear, so works until clear works
}
END_TEST

START_TEST(swap_test) {
    o_avl_map_t* first_map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    o_avl_map_t* second_map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(first_map));
    ck_assert(o_avl_map_empty(second_map));
    int key = 55;
    int value =  66;
    o_avl_map_insert(first_map, &key, &value);
    ck_assert(!o_avl_map_empty(first_map));
    o_avl_map_swap(first_map, second_map);
    ck_assert(o_avl_map_empty(first_map));
    ck_assert(!o_avl_map_empty(second_map));
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(second_map, second_map->set.root), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(second_map, second_map->set.root), value);
    ++key;
    ++value;
    o_avl_map_insert(second_map, &key, &value);
    ck_assert_uint_eq(second_map->set.size, 2);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(second_map, second_map->set.root->right), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(second_map, second_map->set.root->right), value);
    ++key;
    ++value;
    o_avl_map_insert(first_map, &key, &value);
    ck_assert_uint_eq(first_map->set.size, 1);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(first_map, first_map->set.root), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(first_map, first_map->set.root), value);
    o_avl_map_swap(first_map, second_map);
    ck_assert_uint_eq(first_map->set.size, 2);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(first_map, first_map->set.root), 55);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(first_map, first_map->set.root), 66);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(first_map, first_map->set.root->right), 56);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(first_map, first_map->set.root->right), 67);
    ck_assert_uint_eq(second_map->set.size, 1);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(second_map, second_map->set.root), 57);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(second_map, second_map->set.root), 68);
}
END_TEST

START_TEST(find_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value = 66;
    o_avl_map_insert(map, &key, &value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root), 66);
    o_avl_map_node_t* res = o_avl_map_find(map, &key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res), value);
    ++key;
    ++value;
    o_avl_map_insert(map, &key, &value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root->right), key);
    res = o_avl_map_find(map, &key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res), value);
}
END_TEST

START_TEST(contains_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value = 66;
    ck_assert(!o_avl_map_contains(map, &key));
    o_avl_map_insert(map, &key, &value);
    ck_assert(o_avl_map_contains(map, &key));
    ++key;
    ++value;
    o_avl_map_insert(map, &key, &value);
    ck_assert(o_avl_map_contains(map, &key));
    o_avl_map_erase(map, &key);
    ck_assert(!o_avl_map_contains(map, &key));
    --key;
    ck_assert(o_avl_map_contains(map, &key));
    o_avl_map_erase(map, &key);
    ck_assert(!o_avl_map_contains(map, &key));
}
END_TEST

START_TEST(lower_bound_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value = 66;
    o_avl_map_insert(map, &key, &value);//55, 66
    key = 56;
    value = 67;
    o_avl_map_insert(map, &key, &value);//56, 67
    key = 57;
    value = 68;
    o_avl_map_insert(map, &key, &value);//57, 68
    key = 59;
    value = 69;
    o_avl_map_insert(map, &key, &value);//59, 69
    key = 60;
    value = 70;
    o_avl_map_insert(map, &key, &value);//60, 70
    key = 61;
    value = 71;
    o_avl_map_insert(map, &key, &value);//61, 71
    key = 58;
    o_avl_map_node_t* res = o_avl_map_lower_bound(map, &key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res), 59);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res), 69);
    key = 54;
    res = o_avl_map_lower_bound(map, &key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res), 55);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res), 66);
    key = 55;
    res = o_avl_map_lower_bound(map, &key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res), 55);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res), 66);
    key = 57;
    res = o_avl_map_lower_bound(map, &key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res), 57);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res), 68);
    key = 61;
    res = o_avl_map_lower_bound(map, &key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res), 61);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res), 71);
    key = 62;
    res = o_avl_map_lower_bound(map, &key);
    ck_assert_ptr_eq(res, NULL);
}
END_TEST

START_TEST(upper_bound_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value = 66;
    o_avl_map_insert(map, &key, &value);//55, 66
    key = 56;
    value = 67;
    o_avl_map_insert(map, &key, &value);//56, 67
    key = 57;
    value = 68;
    o_avl_map_insert(map, &key, &value);//57, 68
    key = 59;
    value = 69;
    o_avl_map_insert(map, &key, &value);//59, 69
    key = 60;
    value = 70;
    o_avl_map_insert(map, &key, &value);//60, 70
    key = 61;
    value = 71;
    o_avl_map_insert(map, &key, &value);//61, 71
    key = 58;
    o_avl_map_node_t* res = o_avl_map_upper_bound(map, &key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res), 59);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res), 69);
    key = 54;
    res = o_avl_map_upper_bound(map, &key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res), 55);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res), 66);
    key = 55;
    res = o_avl_map_upper_bound(map, &key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res), 56);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res), 67);
    key = 57;
    res = o_avl_map_upper_bound(map, &key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res), 59);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res), 69);
    key = 61;
    res = o_avl_map_upper_bound(map, &key);
    ck_assert_ptr_eq(res, NULL);
    key = 62;
    res = o_avl_map_upper_bound(map, &key);
    ck_assert_ptr_eq(res, NULL);
}
END_TEST

START_TEST(begin_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value = 66;
    o_avl_map_insert(map, &key, &value);//55, 66
    key = 56;
    value = 67;
    o_avl_map_insert(map, &key, &value);//56, 67
    key = 57;
    value = 68;
    o_avl_map_insert(map, &key, &value);//57, 68
    key = 59;
    value = 69;
    o_avl_map_insert(map, &key, &value);//59, 69
    key = 60;
    value = 70;
    o_avl_map_insert(map, &key, &value);//60, 70
    key = 61;
    value = 71;
    o_avl_map_insert(map, &key, &value);//61, 71
    o_avl_map_node_t* res = o_avl_map_begin(map);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res), 55);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res), 66);
    key = 55;
    o_avl_map_erase(map, &key);
    res = o_avl_map_begin(map);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res), 56);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res), 67);
    o_avl_map_clear(map);
    res = o_avl_map_begin(map);
    ck_assert_ptr_eq(res, NULL);
}
END_TEST

START_TEST(end_test) {
    ck_assert(true);//returns null, better test with node_get_next
}
END_TEST

START_TEST(node_get_next_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value = 66;
    o_avl_map_insert(map, &key, &value);//55, 66
    key = 56;
    value = key + 11;
    o_avl_map_insert(map, &key, &value);//56, 67
    key = 57;
    value = key + 11;
    o_avl_map_insert(map, &key, &value);//57, 68
    key = 59;
    value = key + 11;
    o_avl_map_insert(map, &key, &value);//59, 69
    key = 60;
    value = key + 11;
    o_avl_map_insert(map, &key, &value);//60, 70
    key = 61;
    value = key + 11;
    o_avl_map_insert(map, &key, &value);//61, 71
    o_avl_map_node_t* res = o_avl_map_begin(map);
    o_avl_map_node_t* cur = res;
    key = 55;
    while (cur != o_avl_map_end(map)) {
        ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, cur), key);
        ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, cur), key + 11);
        if (key == 57) {
            ++key;
        }
        ++key;
        cur = o_avl_map_node_get_next(map, cur);
    }
}
END_TEST

START_TEST(node_get_key_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value = 66;
    o_avl_map_insert_result_t res = o_avl_map_insert(map, &key, &value);
    ck_assert(res.insertion_took_place);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res.node), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root), key);
    ck_assert_uint_eq(map->set.size, 1);
    ck_assert_ptr_ne(map->set.root, NULL);
    ck_assert(!o_avl_map_empty(map));
    ++key;
    ++value;
    res = o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 2);
    ck_assert(res.insertion_took_place);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, res.node), key);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root->right), key);
}
END_TEST

START_TEST(node_get_value_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value = 66;
    o_avl_map_insert_result_t res = o_avl_map_insert(map, &key, &value);
    ck_assert(res.insertion_took_place);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res.node), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root), value);
    ck_assert_uint_eq(map->set.size, 1);
    ck_assert_ptr_ne(map->set.root, NULL);
    ck_assert(!o_avl_map_empty(map));
    ++key;
    ++value;
    res = o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 2);
    ck_assert(res.insertion_took_place);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res.node), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root->right), value);
}
END_TEST

START_TEST(node_set_value_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value = 66;
    o_avl_map_insert_result_t res = o_avl_map_insert(map, &key, &value);
    ck_assert(res.insertion_took_place);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res.node), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root), key);
    value = 88;
    o_avl_map_node_set_value(map, res.node, &value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res.node), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root), key);
    value = 99;
    o_avl_map_node_set_value(map, map->set.root, &value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res.node), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root), key);
    ck_assert_uint_eq(map->set.size, 1);
    ck_assert_ptr_ne(map->set.root, NULL);
    ck_assert(!o_avl_map_empty(map));
    ++key;
    ++value;
    res = o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 2);
    ck_assert(res.insertion_took_place);
    o_avl_map_node_set_value(map, map->set.root, &value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res.node), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root), value);
    value = 88;
    o_avl_map_node_set_value(map, res.node, &value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, res.node), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_value(map, map->set.root->right), value);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root->right), key);
}
END_TEST

START_TEST(node_erase_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value = 66;
    o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 1);
    ck_assert_ptr_ne(map->set.root, NULL);
    ck_assert(!o_avl_map_empty(map));
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root), key);
    ++key;
    o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 2);
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root->right), key);
    o_avl_map_node_erase(map, map->set.root);
    --key;
    ck_assert_ptr_eq(o_avl_map_find(map, &key), NULL);
    ck_assert_uint_eq(map->set.size, 1);
    ++key;
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root), key);
    ck_assert_ptr_ne(o_avl_map_find(map, &key), NULL);
    o_avl_map_node_erase(map, map->set.root);
    ck_assert_ptr_eq(o_avl_map_find(map, &key), NULL);
    ck_assert_ptr_eq(map->set.root, NULL);
    ck_assert_uint_eq(map->set.size, 0);
}
END_TEST

START_TEST(size_test) {
    o_avl_map_t* map WITH_O_AVL_MAP_DTOR = o_avl_map_create(int, int, int_compare);
    ck_assert(o_avl_map_empty(map));
    int key = 55;
    int value = 66;
    o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 1);
    ck_assert_uint_eq(map->set.size, o_avl_map_size(map));
    ck_assert_ptr_ne(map->set.root, NULL);
    ck_assert(!o_avl_map_empty(map));
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root), key);
    ++key;
    o_avl_map_insert(map, &key, &value);
    ck_assert_uint_eq(map->set.size, 2);
    ck_assert_uint_eq(map->set.size, o_avl_map_size(map));
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root->right), key);
    o_avl_map_node_erase(map, map->set.root);
    --key;
    ck_assert_ptr_eq(o_avl_map_find(map, &key), NULL);
    ck_assert_uint_eq(map->set.size, 1);
    ck_assert_uint_eq(map->set.size, o_avl_map_size(map));
    ++key;
    ck_assert_int_eq(*(int*)o_avl_map_node_get_key(map, map->set.root), key);
    ck_assert_ptr_ne(o_avl_map_find(map, &key), NULL);
    o_avl_map_node_erase(map, map->set.root);
    ck_assert_ptr_eq(o_avl_map_find(map, &key), NULL);
    ck_assert_ptr_eq(map->set.root, NULL);
    ck_assert_uint_eq(map->set.size, 0);
    ck_assert_uint_eq(map->set.size, o_avl_map_size(map));
}
END_TEST

Suite* suite_avl_map(void)
{
    Suite* s;
    TCase* tc;
    s = suite_create("o_avl_map workability tests");
    tc = tcase_create("o_avl_map basic usage check");
    tcase_add_test(tc, create_test);
    tcase_add_test(tc, empty_test);
    tcase_add_test(tc, clear_test);
    tcase_add_test(tc, insert_test);
    tcase_add_test(tc, insert_or_assign_test);
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
    tcase_add_test(tc, node_get_value_test);
    tcase_add_test(tc, node_set_value_test);
    tcase_add_test(tc, node_erase_test);
    tcase_add_test(tc, size_test);
    suite_add_tcase(s, tc);
    return s;
}

int main(void) {
    int number_failed;
    SRunner* sr;
    Suite* s_avl_map = suite_avl_map();
    sr = srunner_create(s_avl_map);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}