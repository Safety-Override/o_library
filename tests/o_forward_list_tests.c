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

Suite* suite_forward_list(void)
{
    Suite* s;
    TCase* tc;
    s = suite_create("o_forward_list workability tests");
    tc = tcase_create("o_forward_list basic usage check");
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