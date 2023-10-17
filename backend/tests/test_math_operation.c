#include "tests.h"

START_TEST(math_operation_test_01) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int return_value = 0;
  sn = push_stack_num(sn);
  add_data_to_stack_num(sn, 2.0);
  sc = push_stack_ch(sc);
  add_data_to_stack_ch(sc, '-');
  sc = push_stack_ch(sc);
  add_data_to_stack_ch(sc, '+');
  sn = push_stack_num(sn);
  add_data_to_stack_num(sn, 3.1);
  return_value = math_operation(&sn, &sc);
  ck_assert_int_eq(return_value, 0);
  ck_assert_double_eq_tol(sn->data, 5.1, 0.7);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(math_operation_test_02) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int return_value = 0;
  sn = push_stack_num(sn);
  add_data_to_stack_num(sn, 2.0);
  sc = push_stack_ch(sc);
  add_data_to_stack_ch(sc, '+');
  sc = push_stack_ch(sc);
  add_data_to_stack_ch(sc, '-');
  sn = push_stack_num(sn);
  add_data_to_stack_num(sn, 3.1);
  return_value = math_operation(&sn, &sc);
  ck_assert_int_eq(return_value, 0);
  ck_assert_double_eq_tol(sn->data, -1.1, 0.7);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(math_operation_test_03) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int return_value = 0;
  sn = push_stack_num(sn);
  add_data_to_stack_num(sn, 3.3);
  sc = push_stack_ch(sc);
  add_data_to_stack_ch(sc, '*');
  sn = push_stack_num(sn);
  add_data_to_stack_num(sn, 3.0);
  return_value = math_operation(&sn, &sc);
  ck_assert_int_eq(return_value, 0);
  ck_assert_double_eq_tol(sn->data, 9.9, 0.7);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(math_operation_test_04) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int return_value = 0;
  sn = push_stack_num(sn);
  add_data_to_stack_num(sn, 3.3);
  sc = push_stack_ch(sc);
  add_data_to_stack_ch(sc, '/');
  sn = push_stack_num(sn);
  add_data_to_stack_num(sn, 0.0);
  return_value = math_operation(&sn, &sc);
  ck_assert_int_eq(return_value, DIV_BY_ZERO);
  ck_assert_double_eq_tol(sn->data, 3.3, 0.7);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(math_operation_test_05) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int return_value = 0;
  sn = push_stack_num(sn);
  add_data_to_stack_num(sn, 3.3);
  sc = push_stack_ch(sc);
  add_data_to_stack_ch(sc, '/');
  return_value = math_operation(&sn, &sc);
  ck_assert_int_eq(return_value, ERR);
  ck_assert_double_eq_tol(sn->data, 3.3, 0.7);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(math_operation_test_06) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int return_value = 0;
  sn = push_stack_num(sn);
  add_data_to_stack_num(sn, 8);
  sc = push_stack_ch(sc);
  add_data_to_stack_ch(sc, '^');
  sn = push_stack_num(sn);
  add_data_to_stack_num(sn, 3);
  return_value = math_operation(&sn, &sc);
  ck_assert_int_eq(return_value, OK);
  ck_assert_double_eq_tol(sn->data, 512, 0.7);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

Suite *test_math_operation() {
  Suite *suite = suite_create("math_operation_suite");

  TCase *tc_math_operation = tcase_create("math_operation_test");
  tcase_add_test(tc_math_operation, math_operation_test_01);
  tcase_add_test(tc_math_operation, math_operation_test_02);
  tcase_add_test(tc_math_operation, math_operation_test_03);
  tcase_add_test(tc_math_operation, math_operation_test_04);
  tcase_add_test(tc_math_operation, math_operation_test_05);
  tcase_add_test(tc_math_operation, math_operation_test_06);
  suite_add_tcase(suite, tc_math_operation);

  return suite;
}
