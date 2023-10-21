#include "tests.h"

START_TEST(calc_expression_test_01) {
  char str[10];
  sprintf(str, "2+2*2");
  double res = 0;
  int return_value = calc_expression(str, &res, 0);
  ck_assert_double_eq_tol(res, 6, 1e-06);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_02) {
  char str[] = "5/2-2.6*10";
  double res = 0;
  int return_value = calc_expression(str, &res, 0);
  ck_assert_double_eq_tol(res, -23.5, 1e-06);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_03) {
  char str[] = "-5*3";
  double res = 0;
  int return_value = calc_expression(str, &res, 0);
  ck_assert_double_eq_tol(res, -15, 1e-06);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_04) {
  char str[] = "1-(2+2)/2";
  double res = 0;
  int return_value = calc_expression(str, &res, 0);
  ck_assert_double_eq_tol(res, -1, 1e-06);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_05) {
  char str[] = "3+(7-5/(2+3))*(7-2)";
  double res = 0;
  int return_value = calc_expression(str, &res, 0);
  ck_assert_double_eq_tol(res, 33, 1e-06);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_06) {
  char str[] = "(-(-(-(2+2))))";
  double res = 0;
  int return_value = calc_expression(str, &res, 0);
  ck_assert_double_eq_tol(res, -4, 1e-06);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_07) {
  char str[] = "(8*8)^(1/2)";
  double res = 0;
  int return_value = calc_expression(str, &res, 0);
  ck_assert_double_eq_tol(res, 8, 1e-06);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_08) {
  char str[] = "sin(11)";
  double res = 0;
  int return_value = calc_expression(str, &res, 0);
  ck_assert_double_eq_tol(res, -0.999990, 1e-06);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_09) {
  char str[] = "sin(cos(3.14159265358979323846/2))";
  double res = 0;
  int return_value = calc_expression(str, &res, 0);
  ck_assert_double_eq_tol(res, 0, 1e-06);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_10) {
  char str[] = "6--6";
  double res = 0;
  int return_value = calc_expression(str, &res, 0);
  ck_assert_double_eq_tol(res, 0, 1e-06);
  ck_assert_int_eq(return_value, VALIDATE_ERR);
}
END_TEST

START_TEST(calc_expression_test_11) {
  char str[] = "2^sin(1)*2^cos(1)";
  double res = 0;
  int return_value = calc_expression(str, &res, 0);
  ck_assert_double_eq_tol(res, 2.605885, 1e-06);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_12) {
  char str[] = "sqrt(4-2+2)";
  double res = 0;
  int return_value = calc_expression(str, &res, 0);
  ck_assert_double_eq_tol(res, 2, 1e-06);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_13) {
  char str[] = "sqrt(X)";
  double res = 0;
  int return_value = calc_expression(str, &res, 4);
  ck_assert_double_eq_tol(res, 2, 1e-06);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(calc_expression_test_14) {
  char str[] = "-X*2";
  double res = 0;
  int return_value = calc_expression(str, &res, -4);
  ck_assert_double_eq_tol(res, 8, 1e-06);
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
  tcase_add_test(tc_calc_expression, calc_expression_test_10);
  tcase_add_test(tc_calc_expression, calc_expression_test_11);
  tcase_add_test(tc_calc_expression, calc_expression_test_12);
  tcase_add_test(tc_calc_expression, calc_expression_test_13);
  tcase_add_test(tc_calc_expression, calc_expression_test_14);
  suite_add_tcase(suite, tc_calc_expression);

  return suite;
}
