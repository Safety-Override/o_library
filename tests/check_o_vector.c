#include <check.h>
#include <o_vector.h>
#include <o_vector_private.h>

void setup(void) {
}

void teardown(void) {
}

START_TEST(zero) {
    o_vector_t* vector = o_vector_create(int);
    ck_assert_int_eq(vector->size, 0);
    ck_assert_int_eq(vector->capacity, 0);
    ck_assert_int_eq(vector->data_type_size, sizeof(int));
}
END_TEST

Suite* suite_zero(void)
{
    Suite* s;
    TCase* tc;
    s = suite_create("suite_zero");
    tc = tcase_create("zero");
    tcase_add_test(tc, zero);

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