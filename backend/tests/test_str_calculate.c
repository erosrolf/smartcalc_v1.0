#include "tests.h"

START_TEST(str_calc_test_01) {
  char str[10];
  sprintf(str, "2-2+2");
  double res = 0;
  str_calc(str, &res);
  ck_assert_double_eq_tol(res, 2, 7);
}
END_TEST

Suite *test_str_calc() {
  Suite *suite = suite_create("str_calc_suite");

  TCase *tc_str_calc = tcase_create("str_calc_test");
  tcase_add_test(tc_str_calc, str_calc_test_01);
  suite_add_tcase(suite, tc_str_calc);

  return suite;
}
