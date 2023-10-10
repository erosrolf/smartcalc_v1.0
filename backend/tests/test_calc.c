#include "tests.h"

START_TEST(calc_test_01) {
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
  return_value = calc(&sn, &sc);
  ck_assert_int_eq(return_value, 0);
  ck_assert_double_eq_tol(sn->data, 5.1, 7);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(calc_test_02) {
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
  return_value = calc(&sn, &sc);
  ck_assert_int_eq(return_value, 0);
  ck_assert_double_eq_tol(sn->data, -1.1, 7);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(calc_test_03) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int return_value = 0;
  sn = push_stack_num(sn);
  add_data_to_stack_num(sn, 3.3);
  sc = push_stack_ch(sc);
  add_data_to_stack_ch(sc, '*');
  sn = push_stack_num(sn);
  add_data_to_stack_num(sn, 3.0);
  return_value = calc(&sn, &sc);
  ck_assert_int_eq(return_value, 0);
  ck_assert_double_eq_tol(sn->data, 9.9, 7);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

Suite *test_calc() {
  Suite *suite = suite_create("calc_suite");

  TCase *tc_calc = tcase_create("calc_test");
  tcase_add_test(tc_calc, calc_test_01);
  tcase_add_test(tc_calc, calc_test_02);
  tcase_add_test(tc_calc, calc_test_03);
  suite_add_tcase(suite, tc_calc);

  return suite;
}
