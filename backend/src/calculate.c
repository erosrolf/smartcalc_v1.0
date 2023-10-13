#include "calculate.h"
#include "return_codes.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef CALCULATE_C
#define CALCULATE_C

static int is_math_oper(Stack_ch *sc) {
  if (sc == NULL)
    return 0;
  int return_value = 0;
  if (sc->data == '+')
    return_value = '+';
  else if (sc->data == '-')
    return_value = '-';
  else if (sc->data == '*')
    return_value = '*';
  else if (sc->data == '/')
    return_value = '/';
  return return_value;
}

int math_operation(Stack_num **sn, Stack_ch **sc) {
  Stack_num *num_tmp = *sn;
  if (is_math_oper(*sc) == '/' && num_tmp->data == 0) {
    return ERR;
  }
  if (num_tmp->next) {
    double res = 0;
    if (is_math_oper(*sc) == '+')
      res = num_tmp->next->data + num_tmp->data;
    else if (is_math_oper(*sc) == '-')
      res = num_tmp->next->data - num_tmp->data;
    else if (is_math_oper(*sc) == '*')
      res = num_tmp->next->data * num_tmp->data;
    else if (is_math_oper(*sc) == '/')
      if (num_tmp->data != 0)
        res = num_tmp->next->data / num_tmp->data;
    *sn = pop_stack_num(*sn);
    *sc = pop_stack_ch(*sc);
    add_data_to_stack_num(*sn, res);
  }
  return OK;
}

int str_calc(char *str, double *res) {
  int return_value = OK;
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  unsigned int n = 0;
  int err = 0;
  while (str[n] && return_value == OK && err < 100) {
    if (str[n] == ')') {
      n++;
      while (sc->data != '(' && return_value == OK)
        return_value = math_operation(&sn, &sc);
      if (return_value == OK)
        sc = pop_stack_ch(sc);
    } else if (sc && str[n] != '(' && get_rang(str[n]) <= get_rang(sc->data)) {
      return_value = math_operation(&sn, &sc);
    } else {
      token_parsing(str, &sn, &sc, &n);
      printf("n = %d\n", n);
    }
    err++;
  }
  while (sc != 0 && return_value == OK) {
    return_value = math_operation(&sn, &sc);
  }
  print_stack_ch(sc);
  print_stack_num(sn);
  *res = sn->data;
  free_stack_ch(sc);
  free_stack_num(sn);
  return return_value;
}

#endif
