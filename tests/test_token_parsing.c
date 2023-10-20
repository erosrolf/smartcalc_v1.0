#include "tests.h"

START_TEST(token_parsing_test_01) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int is_unary = 1;
  int return_value = 0;
  unsigned int ch_pointer = 2;
  char str[] = "2(-2.12345-111";
  return_value = token_parsing(str, &sn, &sc, &ch_pointer, &is_unary);
  ck_assert_int_eq(return_value, NUM);
  ck_assert_double_eq(sn->data, -2.12345);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(token_parsing_test_02) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int is_unary = 0;
  int return_value = 0;
  unsigned int ch_pointer = 4;
  char str[] = "2(-2-2.";
  return_value = token_parsing(str, &sn, &sc, &ch_pointer, &is_unary);
  ck_assert_int_eq(return_value, LOW_RANG);
  ck_assert_int_eq(sc->data, '-');
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(token_parsing_test_03) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int is_unary = 1;
  int return_value = 0;
  unsigned int ch_pointer = 2;
  char str[] = "22*2-2.";
  return_value = token_parsing(str, &sn, &sc, &ch_pointer, &is_unary);
  ck_assert_int_eq(return_value, MID_RANG);
  ck_assert_int_eq(sc->data, '*');
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(token_parsing_test_04) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int is_unary = 1;
  unsigned int ch_pointer = 0;
  char str[] = "-12345.6789*0.000004-0002.";
  while (str[ch_pointer]) {
    token_parsing(str, &sn, &sc, &ch_pointer, &is_unary);
  }
  ck_assert_int_eq(sc->data, '-');
  ck_assert_int_eq(sc->next->data, '*');
  ck_assert_double_eq_tol(sn->next->next->data, -12345.6789, 0.7);
  ck_assert_double_eq_tol(sn->next->data, 0.000004, 0.7);
  ck_assert_double_eq_tol(sn->data, 2, 0.7);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(token_parsing_test_05) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int is_unary = 1;
  unsigned int ch_pointer = 0;
  char str[] = "-12345.6789*(-0.000004-0002.)";
  while (str[ch_pointer]) {
    token_parsing(str, &sn, &sc, &ch_pointer, &is_unary);
  }
  ck_assert_int_eq(sc->data, ')');
  ck_assert_int_eq(sc->next->data, '-');
  ck_assert_int_eq(sc->next->next->data, '(');
  ck_assert_int_eq(sc->next->next->next->data, '*');
  ck_assert_double_eq_tol(sn->next->next->data, -12345.6789, 0.7);
  ck_assert_double_eq_tol(sn->next->data, -0.000004, 0.7);
  ck_assert_double_eq_tol(sn->data, 2, 0.7);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(token_parsing_test_06) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int is_unary = 0;
  unsigned int ch_pointer = 0;
  char str[] = "8^3";
  while (str[ch_pointer]) {
    token_parsing(str, &sn, &sc, &ch_pointer, &is_unary);
  }
  ck_assert_int_eq(sc->data, '^');
  ck_assert_double_eq_tol(sn->next->data, 8, 0.7);
  ck_assert_double_eq_tol(sn->data, 3, 0.7);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(token_parsing_test_07) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int is_unary = 0;
  unsigned int ch_pointer = 0;
  char str[] = "sin(2+2)";
  while (str[ch_pointer]) {
    token_parsing(str, &sn, &sc, &ch_pointer, &is_unary);
  }
  ck_assert_int_eq(sc->next->next->next->data, SIN);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(token_parsing_test_08) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int is_unary = 0;
  unsigned int ch_pointer = 0;
  char str[] = "sqrt(2+2)";
  while (str[ch_pointer]) {
    token_parsing(str, &sn, &sc, &ch_pointer, &is_unary);
  }
  ck_assert_int_eq(sc->next->next->next->data, SQRT);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

Suite *test_token_parsing() {
  Suite *suite = suite_create("token_parsing_suite");

  TCase *tc_token_parsing = tcase_create("token_parsing_test");
  tcase_add_test(tc_token_parsing, token_parsing_test_01);
  tcase_add_test(tc_token_parsing, token_parsing_test_02);
  tcase_add_test(tc_token_parsing, token_parsing_test_03);
  tcase_add_test(tc_token_parsing, token_parsing_test_04);
  tcase_add_test(tc_token_parsing, token_parsing_test_05);
  tcase_add_test(tc_token_parsing, token_parsing_test_06);
  tcase_add_test(tc_token_parsing, token_parsing_test_07);
  tcase_add_test(tc_token_parsing, token_parsing_test_08);
  suite_add_tcase(suite, tc_token_parsing);

  return suite;
}
