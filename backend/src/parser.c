#include "parser.h"
#include "return_codes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PARSER_C
#define PARSER_C
static int is_unary_m(char *s, int ch_pointer) {
  if (*s != '-')
    return 0;
  if (ch_pointer)
    return s[-1] == '(' || s[-1] == '*' || s[-1] == '/';
  else
    return 1;
}

static int is_num(char *s, int ch_pointer) {
  return ((*s >= '0') && (*s <= '9')) || *s == '.' || is_unary_m(s, ch_pointer);
}

static int is_ch(char *s, int ch_pointer) {
  if (is_unary_m(s, ch_pointer)) {
    return 0;
  }
  return *s == '-' || *s == '+' || *s == '*' || *s == '/' || *s == '(' ||
         *s == ')';
}

int get_rang(Stack_ch *sc) {
  int return_value = ERR;
  if (sc->data == '(')
    return_value = 1;
  if (sc->data == '-' || sc->data == '+')
    return_value = 2;
  if (sc->data == '/' || sc->data == '*')
    return_value = 3;
  if (return_value == '^')
    return_value = 4;
  if (return_value == ')')
    return_value = 5;
  return return_value;
}

/*
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
 * ch_pointer указатель на символ строки *str, после выполнения указывает на
 * первый элемент после числа
 */
static int str_to_num(char *str, unsigned int *ch_pointer, double *d) {
  if (!is_num(str, *ch_pointer))
    return ERR;
  int size = 0;
  while (is_num(str + size, size))
    ++size;
  char *buf = (char *)malloc(sizeof(char) * size + 1);
  if (!buf)
    exit(MEM_ERR);
  memcpy(buf, str, size);
  buf[size] = 0x00;
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

/*
 * расшифровывает из строки одну лекслему, на которую указывает ch_pointer
 * закидывает ее в соответствующий стек и возвращает:
 * 0 - число
 * 1 - '('
 * 2 - '+' || '-'
 * 3 - '*' || '/'
 * 4 - 'functions'
 * 5 - ')'
 * 6 - конец строки
 * при ошибке возвращает -1
 * так же возвращающие коды можно посмотреть err_codes.h
 */
int parser(char *str, Stack_num **sn, Stack_ch **sc, unsigned int *ch_pointer) {
  int return_value = OK;
  if (str[*ch_pointer] != 0x00) {
    if (is_num(str + *ch_pointer, *ch_pointer)) {
      if (!str_to_num_stack(str + *ch_pointer, ch_pointer, sn))
        return_value = 0;
      else
        return_value = ERR;
    } else if (is_ch(str + *ch_pointer, *ch_pointer)) {
      if (!str_to_ch_stack(str + *ch_pointer, ch_pointer, sc))
        return_value = get_rang(*sc);
      else
        return_value = ERR;
    }
  } else
    return_value = STR_DONE;
  return return_value;
}

#endif
