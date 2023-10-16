#include "tests.h"

START_TEST(str_calc_test_01) {
  char str[10];
  sprintf(str, "2+2*2");
  double res = 0;
  int return_value = str_calc(str, &res);
  ck_assert_double_eq_tol(res, 6, 0.7);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(str_calc_test_02) {
  char str[] = "5/2-2.6*10";
  double res = 0;
  int return_value = str_calc(str, &res);
  ck_assert_double_eq_tol(res, -23.5, 0.7);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(str_calc_test_03) {
  char str[] = "-5*3";
  double res = 0;
  int return_value = str_calc(str, &res);
  ck_assert_double_eq_tol(res, -15, 0.7);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

// START_TEST(str_calc_test_04) {
//   char str[] = "-(2+2)";
//   double res = 0;
//   int return_value = str_calc(str, &res);
//   ck_assert_double_eq_tol(res, -4, 0.7);
//   ck_assert_int_eq(return_value, OK);
// }
// END_TEST

START_TEST(str_calc_test_05) {
  char str[] = "3+(7-5/(2+3))*(7-2)";
  double res = 0;
  int return_value = str_calc(str, &res);
  ck_assert_double_eq_tol(res, 33, 0.7);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

Suite *test_str_calc() {
  Suite *suite = suite_create("str_calc_suite");

  TCase *tc_str_calc = tcase_create("str_calc_test");
  tcase_add_test(tc_str_calc, str_calc_test_01);
  tcase_add_test(tc_str_calc, str_calc_test_02);
  tcase_add_test(tc_str_calc, str_calc_test_03);
  // tcase_add_test(tc_str_calc, str_calc_test_04);
  tcase_add_test(tc_str_calc, str_calc_test_05);
  suite_add_tcase(suite, tc_str_calc);

  return suite;
}
