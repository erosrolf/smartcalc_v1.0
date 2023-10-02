#include "calculate.h"
#include <math.h>
#include <stdio.h>

enum error { OK, ERR, FEW_ARGS, DIV_BY_ZERO };

#ifndef CALCULATE_C
#define CALCULATE_C

static int calc_add(Stack_num **sn, Stack_ch **sc) {
  if (*sc == NULL)
    return ERR;
  Stack_num *num_tmp = *sn;
  double res = 0;
  res = num_tmp->next->data + num_tmp->data;
  *sn = pop_stack_num(*sn);
  *sc = pop_stack_ch(*sc);
  add_data_to_stack_num(*sn, res);
  return 0;
}

static int calc_sub(Stack_num **sn, Stack_ch **sc) {
  if (*sc == NULL)
    return ERR;
  Stack_num *num_tmp = *sn;
  double res = 0;
  res = num_tmp->next->data - num_tmp->data;
  *sn = pop_stack_num(*sn);
  *sc = pop_stack_ch(*sc);
  add_data_to_stack_num(*sn, res);
  return 0;
}

static int calc_mul(Stack_num **sn, Stack_ch **sc) {
  if (*sc == NULL)
    return ERR;
  Stack_num *num_tmp = *sn;
  double res = 0;
  res = num_tmp->next->data * num_tmp->data;
  *sn = pop_stack_num(*sn);
  *sc = pop_stack_ch(*sc);
  add_data_to_stack_num(*sn, res);
  return 0;
}

static int calc_div(Stack_num **sn, Stack_ch **sc) {
  if (*sc == NULL)
    return ERR;
  Stack_num *num_tmp = *sn;
  double res = 0;
  res = num_tmp->next->data / num_tmp->data;
  *sn = pop_stack_num(*sn);
  *sc = pop_stack_ch(*sc);
  add_data_to_stack_num(*sn, res);
  return 0;
}

int calculate(char *str) {
  int return_value = OK;
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  parser(str, &sn, &sc);
  if (!sn->next)
    return FEW_ARGS;
  if (sc && sc->data == '+')
    return_value = calc_add(&sn, &sc);
  if (sc && sc->data == '-')
    return_value = calc_sub(&sn, &sc);
  if (sc && sc->data == '*')
    return_value = calc_mul(&sn, &sc);
  if (sc && sc->data == '/') {
    if (sn->data == 0)
      return_value = DIV_BY_ZERO;
    else
      return_value = calc_div(&sn, &sc);
  }
  print_stack_num(sn);
  print_stack_ch(sc);
  return return_value;
}

#endif
