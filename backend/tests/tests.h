#ifndef TESTS_H
#define TESTS_H

#include "../src/calculate.h"
#include "../src/parser.h"
#include "../src/return_codes.h"
#include "../src/stack.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

Suite *test_token_parsing();
Suite *test_math_operation();
Suite *test_str_calc();

void run_test(Suite *s, int *fail);

#endif
