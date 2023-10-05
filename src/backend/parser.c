#include "parser.h"
#include "err_codes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PARSER_C
#define PARSER_C
static int is_unary_m(char *s, int ch_pointer) {
  return ((ch_pointer == 0 || s[-1] == '(') && *s == '-');
}

static int is_num(char *s, int ch_pointer) {
  return ((*s >= '0') && (*s <= '9')) || *s == '.' || is_unary_m(s, ch_pointer);
}

static int is_ch(char *s, int ch_pointer) {
  if (is_unary_m(s, ch_pointer)) {
    return 0;
  }
  return *s == '-' || *s == '+' || *s == '*' || *s == '/' || *s == '(';
}

/*
 * если *str указывает не на символ, возвращает NOT_OPERAND
 * ch_pointer указывает на символ строки, после выполнения на следующий элемент
 * после операнда
 */
static int str_to_operand(char *str, unsigned int *ch_pointer, char *ch) {
  if (!is_ch(str, *ch_pointer))
    return ERR;
  else {
    *ch = *str;
    *ch_pointer += 1;
    return OK;
  }
}
int str_to_ch_stack(char *str, unsigned int *ch_pointer, Stack_ch **sc) {
  int return_value = OK;
  char ch = 0;
  return_value = str_to_operand(str, ch_pointer, &ch);
  if (return_value == OK) {
    *sc = push_stack_ch(*sc);
    add_data_to_stack_ch(*sc, ch);
  }
  return return_value;
}

/*
 * если *str не указывает на число, возвращает ошибку NOT_NUM
 * ch_pointer указатель на символ строки *str, после выполнения указывает на
 * первый элемент после числа
 */
static int str_to_num(char *str, unsigned int *ch_pointer, double *d) {
  if (!is_num(str, *ch_pointer))
    return ERR;
  int size = 0;
  char *buf = (char *)malloc(256);
  if (!buf)
    exit(MEM_ERR);
  while (is_num(str + size, size))
    ++size;
  memcpy(buf, str, size);
  buf[size + 1] = 0x00;
  *d = atof(buf);
  free(buf);
  *ch_pointer += size;
  return OK;
}

int str_to_num_stack(char *str, unsigned int *ch_pointer, Stack_num **sn) {
  double d = 0;
  int return_value = str_to_num(str, ch_pointer, &d);
  *sn = push_stack_num(*sn);
  add_data_to_stack_num(*sn, d);
  return return_value;
}

int parser(char *str, Stack_num **sn, Stack_ch **sc, unsigned int *ch_pointer) {
  int return_value = OK;
  if (str[*ch_pointer] != 0x00) {
    if (is_num(str + *ch_pointer, *ch_pointer)) {
      return_value = str_to_num_stack(str + *ch_pointer, ch_pointer, sn);
    } else if (is_ch(str + *ch_pointer, *ch_pointer)) {
      return_value = str_to_ch_stack(str + *ch_pointer, ch_pointer, sc);
    }
  } else
    return_value = STR_DONE;
  return return_value;
}

#endif
