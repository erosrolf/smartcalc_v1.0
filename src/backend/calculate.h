#include "parser.h"
#include "stack.h"

#ifndef CALCULATE_H
#define CALCULATE_H

int math_operation(Stack_num **sn, Stack_ch **sc);
int calc_expression(char *str, double *res);

#endif // CALCULATE_H
