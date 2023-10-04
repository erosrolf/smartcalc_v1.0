#include "parser.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum error { OK, ERR, NOT_NUM, NOT_OPERAND, MEM_ERR };

#ifndef PARSER_C
#define PARSER_C

static int is_num(char *s) { return ((*s >= '0') && (*s <= '9')) || *s == '.'; }
static int is_ch(char *s) {
  return *s == '-' || *s == '+' || *s == '*' || *s == '/' || *s == '(';
}
static int is_unary(char *s, Stack_ch *sc, unsigned int ch_pointer) {
  if (sc)
    return ((ch_pointer == 0 || sc->data == '(') && (*s == '-' || *s == '+'));
  else
    return (ch_pointer == 0 && (*s == '-' || *s == '+'));
}

/*
 * если *str указывает не на символ, возвращает NOT_OPERAND
 * ch_pointer указывает на символ строки, после выполнения на следующий элемент
 * после операнда
 */
static int str_to_operand(char *str, unsigned int *ch_pointer, char *ch) {
  if (!is_ch(str))
    return NOT_OPERAND;
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
static int str_to_num(char *str, unsigned int *ch_pointer, double *d,
                      Stack_ch *sc) {
  if (!is_num(str) && !is_unary(str, sc, *ch_pointer))
    return NOT_NUM;
  int size = 0;
  int negate = 0;
  char *buf = (char *)malloc(256);
  if (!buf)
    exit(MEM_ERR);
  if (is_unary(str, sc, *ch_pointer)) {
    if (*str == '-') {
      negate = 1;
      // *ch_pointer += 1;
    }
  }
  while (is_num((str + negate) + size))
    ++size;
  memcpy(buf, str, size);
  buf[size + 1] = 0x00;

  printf("buf = %s\n", buf);

  *d = atof(buf);
  free(buf);
  if (negate) {
    // *d *= -1;
  }
  *ch_pointer += size + negate;
  return OK;
}

int str_to_num_stack(char *str, unsigned int *ch_pointer, Stack_num **sn,
                     Stack_ch *sc) {
  double d = 0;
  int return_value = str_to_num(str, ch_pointer, &d, sc);
  *sn = push_stack_num(*sn);
  add_data_to_stack_num(*sn, d);
  return return_value;
}

void parser(char *str, Stack_num **sn, Stack_ch **sc) {
  unsigned int ch_pointer = 0;
  while (str[ch_pointer] != 0x00) {
    if (is_num(str + ch_pointer) || is_unary(str, *sc, ch_pointer))
      str_to_num_stack(str + ch_pointer, &ch_pointer, sn, *sc);
    else if (is_ch(str + ch_pointer))
      str_to_ch_stack(str + ch_pointer, &ch_pointer, sc);
    printf("ch_pointer = %d\n", ch_pointer);
  }
}

#endif
