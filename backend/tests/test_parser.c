#include "tests.h"

START_TEST(parser_test_01) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int return_value = 0;
  unsigned int ch_pointer = 2;
  char str[20] = "2(-2.12345+20";
  return_value = parser(str, &sn, &sc, &ch_pointer);
  ck_assert_int_eq(return_value, 0);
  ck_assert_double_eq(sn->data, -2.12345);
  free_stack_num(sn);
  free_stack_ch(sc);
}
END_TEST

START_TEST(parser_test_02) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int return_value = 0;
  unsigned int ch_pointer = 4;
  char str[15] = "2(-2-2.";
  return_value = parser(str, &sn, &sc, &ch_pointer);
  ck_assert_int_eq(return_value, LOW_RANG);
  ck_assert_int_eq(sc->data, '-');
}
END_TEST

START_TEST(parser_test_03) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int return_value = 0;
  unsigned int ch_pointer = 2;
  char str[15] = "22*2-2.";
  return_value = parser(str, &sn, &sc, &ch_pointer);
  ck_assert_int_eq(return_value, MID_RANG);
  ck_assert_int_eq(sc->data, '*');
}
END_TEST

Suite *test_parser() {
  Suite *suite = suite_create("parser_suite");

  TCase *tc_parser = tcase_create("parser_test");
  tcase_add_test(tc_parser, parser_test_01);
  tcase_add_test(tc_parser, parser_test_02);
  tcase_add_test(tc_parser, parser_test_03);
  suite_add_tcase(suite, tc_parser);

  return suite;
}
