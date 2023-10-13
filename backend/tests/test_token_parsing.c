#include "tests.h"

START_TEST(token_parsing_test_01) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int return_value = 0;
  unsigned int ch_pointer = 2;
  char str[15] = "2(-2.12345";
  return_value = token_parsing(str, &sn, &sc, &ch_pointer);
  ck_assert_int_eq(return_value, NUM);
  ck_assert_double_eq(sn->data, -2.12345);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(token_parsing_test_02) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int return_value = 0;
  unsigned int ch_pointer = 4;
  char str[15] = "2(-2-2.";
  return_value = token_parsing(str, &sn, &sc, &ch_pointer);
  ck_assert_int_eq(return_value, LOW_RANG);
  ck_assert_int_eq(sc->data, '-');
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(token_parsing_test_03) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int return_value = 0;
  unsigned int ch_pointer = 2;
  char str[15] = "22*2-2.";
  return_value = token_parsing(str, &sn, &sc, &ch_pointer);
  ck_assert_int_eq(return_value, MID_RANG);
  ck_assert_int_eq(sc->data, '*');
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(token_parsing_test_04) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  unsigned int ch_pointer = 0;
  char str[30] = "-12345.6789*0.000004-0002.";
  while (str[ch_pointer]) {
    token_parsing(str, &sn, &sc, &ch_pointer);
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

Suite *test_token_parsing() {
  Suite *suite = suite_create("token_parsing_suite");

  TCase *tc_token_parsing = tcase_create("token_parsing_test");
  tcase_add_test(tc_token_parsing, token_parsing_test_01);
  tcase_add_test(tc_token_parsing, token_parsing_test_02);
  tcase_add_test(tc_token_parsing, token_parsing_test_03);
  tcase_add_test(tc_token_parsing, token_parsing_test_04);
  suite_add_tcase(suite, tc_token_parsing);

  return suite;
}
