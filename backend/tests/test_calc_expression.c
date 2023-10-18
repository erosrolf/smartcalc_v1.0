#include "tests.h"

START_TEST(calc_expression_test_01) {
  char str[10];
  sprintf(str, "2+2*2");
  double res = 0;
  int return_value = calc_expression(str, &res);
  ck_assert_double_eq_tol(res, 6, 0.7);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_02) {
  char str[] = "5/2-2.6*10";
  double res = 0;
  int return_value = calc_expression(str, &res);
  ck_assert_double_eq_tol(res, -23.5, 0.7);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_03) {
  char str[] = "-5*3";
  double res = 0;
  int return_value = calc_expression(str, &res);
  ck_assert_double_eq_tol(res, -15, 0.7);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_04) {
  char str[] = "1-(2+2)/2";
  double res = 0;
  int return_value = calc_expression(str, &res);
  ck_assert_double_eq_tol(res, -1, 0.7);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_05) {
  char str[] = "3+(7-5/(2+3))*(7-2)";
  double res = 0;
  int return_value = calc_expression(str, &res);
  ck_assert_double_eq_tol(res, 33, 0.7);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_06) {
  char str[] = "(-(-(-(2+2))))";
  double res = 0;
  int return_value = calc_expression(str, &res);
  ck_assert_double_eq_tol(res, -4, 0.7);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_07) {
  char str[] = "(8*8)^(1/2)";
  double res = 0;
  int return_value = calc_expression(str, &res);
  ck_assert_double_eq_tol(res, 8, 0.7);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_08) {
  char str[] = "sin(11)";
  double res = 0;
  int return_value = calc_expression(str, &res);
  ck_assert_double_eq_tol(res, -0.999990, 0.7);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_09) {
  char str[] = "sin(cos(3.14159265358979323846/2))";
  double res = 0;
  int return_value = calc_expression(str, &res);
  ck_assert_double_eq_tol(res, 0, 0.7);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

Suite *test_calc_expression() {
  Suite *suite = suite_create("calc_expression_suite");

  TCase *tc_calc_expression = tcase_create("calc_expression_test");
  tcase_add_test(tc_calc_expression, calc_expression_test_01);
  tcase_add_test(tc_calc_expression, calc_expression_test_02);
  tcase_add_test(tc_calc_expression, calc_expression_test_03);
  tcase_add_test(tc_calc_expression, calc_expression_test_04);
  tcase_add_test(tc_calc_expression, calc_expression_test_05);
  tcase_add_test(tc_calc_expression, calc_expression_test_06);
  tcase_add_test(tc_calc_expression, calc_expression_test_07);
  tcase_add_test(tc_calc_expression, calc_expression_test_08);
  tcase_add_test(tc_calc_expression, calc_expression_test_09);
  suite_add_tcase(suite, tc_calc_expression);

  return suite;
}
