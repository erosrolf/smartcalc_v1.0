#include "tests.h"

START_TEST(inpt_validator_test_01) {
  char str[] = "-(log(2+2))";
  ck_assert_int_eq(inpt_validator(str), OK);
}
END_TEST

START_TEST(inpt_validator_test_02) {
  char str[] = "()2+2)";
  ck_assert_int_eq(inpt_validator(str), ERR);
}
END_TEST

START_TEST(inpt_validator_test_03) {
  char str[] = "(-2+-2)";
  ck_assert_int_eq(inpt_validator(str), ERR);
}
END_TEST

Suite *test_inpt_validator() {
  Suite *suite = suite_create("inpt_validator_suite");

  TCase *tc_inpt_validator = tcase_create("inpt_validator_test");
  tcase_add_test(tc_inpt_validator, inpt_validator_test_01);
  tcase_add_test(tc_inpt_validator, inpt_validator_test_02);
  tcase_add_test(tc_inpt_validator, inpt_validator_test_03);
  suite_add_tcase(suite, tc_inpt_validator);

  return suite;
}
