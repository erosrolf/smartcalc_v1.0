#include "parser.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum error { OK, ERR, NOT_NUM, NOT_OPERAND, MEM_ERR };

#ifndef PARSER_C
#define PARSER_C

static int is_num(char *s) { return ((*s >= '0') && (*s <= '9')) || *s == '.'; }
static int is_operand(char *s) {
  return *s == '-' || *s == '+' || *s == '*' || *s == '/' || *s == '^';
}

static int str_to_operand(char *str, unsigned int *ch_pointer, char *ch) {
  if (!is_operand(str))
    return NOT_OPERAND;
  else {
    *ch = *str;
    ch_pointer++;
    return OK;
  }
}
void str_to_ch_stack(char *str, unsigned int *ch_pointer, Stack_ch **sc) {
  char ch = 0;
  str_to_operand(str, ch_pointer, &ch);
  *sc = push_stack_ch(*sc);
  add_data_to_stack_ch(*sc, ch);
}

/*
 * если *s не указывает на число, возвращает ошибку NOT_NUM
 * ch_pointer указатель на символ строки *str
 * при успешном выполнении ch_pointer указывает на первый элемент после числа
 */
static int str_to_num(char *str, unsigned int *ch_pointer, double *d) {
  if (!is_num(str))
    return NOT_NUM;
  int return_value = OK;
  int size = 0;
  char *buf = (char *)malloc(256);
  if (!buf)
    exit(MEM_ERR);
  while (is_num(str + size))
    ++size;
  memcpy(buf, str, size);
  buf[size + 1] = 0x00;
  *d = atof(buf);
  free(buf);
  *ch_pointer = size;
  return return_value;
}

int str_to_num_stack(char *str, unsigned int *ch_pointer, Stack_num **sn) {
  double d = 0;
  int return_value = str_to_num(str, ch_pointer, &d);
  *sn = push_stack_num(*sn);
  add_data_to_stack_num(*sn, d);
  return return_value;
}

#endif
