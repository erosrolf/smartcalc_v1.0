#ifndef TESTS_H
#define TESTS_H

#define M_PI 3.14159265358979323846

#include "../src/backend/calculate.h"
#include "../src/backend/parser.h"
#include "../src/backend/return_codes.h"
#include "../src/backend/stack.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

Suite *test_inpt_validator();
Suite *test_token_parsing();
Suite *test_math_operation();
Suite *test_calc_expression();

void run_test(Suite *s, int *fail);

#endif
