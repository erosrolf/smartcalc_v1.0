#include "calculate.h"
#include "return_codes.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

int calc(Stack_num **sn, Stack_ch **sc) {
  int return_value = OK;
  Stack_num *sn_tmp = *sn;
  Stack_ch *sc_tmp = *sc;
  if (!sn_tmp->next)
    return FEW_ARGS;
  else if (sc_tmp && sc_tmp->data == '+')
    return_value = calc_add(&sn_tmp, &sc_tmp);
  else if (sc_tmp && sc_tmp->data == '-')
    return_value = calc_sub(&sn_tmp, &sc_tmp);
  else if (sc_tmp && sc_tmp->data == '*')
    return_value = calc_mul(&sn_tmp, &sc_tmp);
  else if (sc_tmp && sc_tmp->data == '/') {
    if (sn_tmp->data == 0)
      return_value = DIV_BY_ZERO;
    else
      return_value = calc_div(&sn_tmp, &sc_tmp);
  }
  *sn = sn_tmp;
  *sc = sc_tmp;
  return return_value;
}

int calc_to_open_br(Stack_num **sn, Stack_ch **sc) {
  int return_value = OK;
  while (get_rang(*sc) != OPEN_BR && return_value == OK) {
    return_value = calc(sn, sc);
  }
  return return_value;
}

int str_calc(char *str, double *res) {
  int return_value = OK;
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  unsigned int n = 0;
  int is_operand = 0;
  while (str[n] && return_value == OK) {
    is_operand = parser(str, &sn, &sc, &n);
    if (is_operand == 5)
      return_value = calc_to_open_br(&sn, &sc);
    else if (is_operand && sc->next && (get_rang(sc) <= get_rang(sc->next))) {
      return_value = calc(&sn, &sc);
    }
  }
  while (sc && return_value == OK)
    return_value = calc(&sn, &sc);
  // print_stack_num(sn);
  // print_stack_ch(sc);
  *res = sn->data;
  free_stack_ch(sc);
  free_stack_num(sn);
  return return_value;
}

#endif
