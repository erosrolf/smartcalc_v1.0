#ifndef TESTS_H
#define TESTS_H

// #include "../backend/calculate.h"
#include "../backend/parser.h"
#include "../backend/return_codes.h"
#include "../backend/stack.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

Suite *test_parser();

void run_test(Suite *s, int *fail);

#endif
