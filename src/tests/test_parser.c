#include "tests.h"

START_TEST(parser_test_01) {
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int return_value = 0;
  unsigned int ch_pointer = 0;
  char *str = (char *)malloc(3);
  str = "(-";
  printf("str = %s\n", str);
  return_value = parser(str, &sn, &sc, &ch_pointer);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

Suite *test_parser() {
  Suite *suite = suite_create("parser_suite");

  TCase *tc_parser = tcase_create("parser_test");
  tcase_add_test(tc_parser, parser_test_01);
  suite_add_tcase(suite, tc_parser);

  return suite;
}
