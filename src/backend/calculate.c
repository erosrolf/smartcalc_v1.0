#include "calculate.h"
#include "return_codes.h"
#include "stack.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef CALCULATE_C
#define CALCULATE_C

int math_operation(Stack_num **sn, Stack_ch **sc) {
  int return_value = OK;
  double res = 0;
  Stack_num *num_tmp = *sn;
  Stack_ch *operation = *sc;
  if (num_tmp->next && is_ch(&operation->data)) { // binaty operations
    if (num_tmp->next && operation->data == '+') {
      res = num_tmp->next->data + num_tmp->data;
    } else if (operation->data == '-') {
      res = num_tmp->next->data - num_tmp->data;
    } else if (operation->data == '*') {
      res = num_tmp->next->data * num_tmp->data;
    } else if (operation->data == '/') {
      if (num_tmp->data == 0)
        return_value = DIV_BY_ZERO;
      else
        res = num_tmp->next->data / num_tmp->data;
    } else if (operation->data == '^') {
      res = pow(num_tmp->next->data, num_tmp->data);
    } else if (operation->data == '%') {
      if (num_tmp->data == 0)
        return_value = DIV_BY_ZERO;
      else
        res = fmod(num_tmp->next->data, num_tmp->data);
    }
    *sn = pop_stack_num(*sn);
  } else if (operation->data == '-') { // unary operations
    res = num_tmp->data * -1;
  } else if (operation->data == SIN) {
    res = sin(num_tmp->data);
  } else if (operation->data == COS) {
    res = cos(num_tmp->data);
  } else if (operation->data == TAN) {
    if (cos(operation->data) == 0)
      return_value = TAN_INDEFINED;
    else
      res = tan(num_tmp->data);
  } else if (operation->data == ACOS) {
    res = acos(num_tmp->data);
  } else if (operation->data == ASIN) {
    res = asin(num_tmp->data);
  } else if (operation->data == ATAN) {
    res = atan(num_tmp->data);
  } else if (operation->data == SQRT) {
    res = sqrt(num_tmp->data);
  } else if (operation->data == LN) {
    res = log(num_tmp->data);
  } else if (operation->data == LOG) {
    res = log10(num_tmp->data);
  } else {
    return_value = CALC_ERR;
    fprintf(stderr, "CALC_ERR, operation = %c\n", operation->data);
  }
  if (return_value == OK) {
    *sc = pop_stack_ch(*sc);
    add_data_to_stack_num(*sn, res);
  }
  return return_value;
}

int calc_expression(char *str, double *res) {
  if (inpt_validator(str) != OK) {
    fprintf(stderr, "%s", "incorrect expression\n");
    return VALIDATE_ERR;
  }
  int return_value = OK;
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  int is_unary = 1;
  unsigned int n = 0;
  while (str[n] && return_value == OK) {
    if (str[n] == ')') {
      n++;
      while (sc->data != '(' && return_value == OK)
        return_value = math_operation(&sn, &sc);
      if (return_value == OK)
        sc = pop_stack_ch(sc);
    } else if (str[n] > 'a' && str[n] < 'z') {
      token_parsing(str, &sn, &sc, &n, &is_unary);
    } else if (sc && n && get_rang(str[n]) > 1 &&
               get_rang(str[n]) <= get_rang(sc->data)) {
      return_value = math_operation(&sn, &sc);
    } else {
      token_parsing(str, &sn, &sc, &n, &is_unary);
    }
  }
  while (sc != 0 && return_value == OK) {
    return_value = math_operation(&sn, &sc);
  }
  *res = sn->data;
  free_stack_ch(sc);
  free_stack_num(sn);
  return return_value;
}

#endif // CALCULATE_C
