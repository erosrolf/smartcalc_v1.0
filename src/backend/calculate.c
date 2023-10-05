#include "calculate.h"
#include "err_codes.h"
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

int calculate(Stack_num *sn, Stack_ch *sc) {
  int return_value = OK;
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
  return return_value;
}

int main() {
  int return_value = 0;
  char buf[256];
  unsigned int ch_pointer = 0;
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  char *str = (char *)malloc(256);
  if (fgets(buf, 255, stdin) != NULL) {
    sscanf(buf, "%s", str);
  }
  while (return_value != STR_DONE) {
    return_value = parser(str, &sn, &sc, &ch_pointer);
    printf("parser return_value = %d\n", return_value);
  }
  printf("\n");
  print_stack_num(sn);
  print_stack_ch(sc);
  return 0;
}

#endif
