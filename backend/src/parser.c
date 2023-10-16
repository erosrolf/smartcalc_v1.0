#include "parser.h"
#include "return_codes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PARSER_C
#define PARSER_C

int is_num(char *s) { return ((*s >= '0') && (*s <= '9')) || *s == '.'; }

int is_ch(char *s) {
  return *s == '-' || *s == '+' || *s == '*' || *s == '/' || *s == '(' ||
         *s == ')';
}

// возвращает преоритет операции
int get_rang(char oper) {
  int return_value = NUM;
  if (oper == '(')
    return_value = OPEN_BR;
  if (oper == '-' || oper == '+')
    return_value = LOW_RANG;
  if (oper == '/' || oper == '*')
    return_value = MID_RANG;
  if (return_value == '^')
    return_value = TOP_RANG;
  if (return_value == ')')
    return_value = CLOSE_BR;
  return return_value;
}

/*
 * ch_pointer указывает на символ строки, после выполнения на следующий элемент
 * после операнда
 */
static int str_to_operand(char *str, unsigned int *ch_pointer, char *ch) {
  if (!is_ch(str))
    return ERR;
  else {
    *ch = *str;
    *ch_pointer += 1;
    return get_rang(*str);
  }
}

int operand_to_ch_stack(char *str, unsigned int *ch_pointer, Stack_ch **sc) {
  int return_value = OK;
  char ch = 0;
  return_value = str_to_operand(str, ch_pointer, &ch);
  if (return_value != ERR) {
    *sc = push_stack_ch(*sc);
    add_data_to_stack_ch(*sc, ch);
  }
  return return_value;
}

/*
 * ch_pointer указатель на символ строки *str, после выполнения указывает на
 * первый элемент после числа
 */
static int str_to_num(char *str, unsigned int *ch_pointer, double *d,
                      int *is_unary) {
  int size = 0;
  while (is_num(str + size) || *is_unary) {
    if (*is_unary)
      *is_unary = 0;
    ++size;
  }
  *d = strtod(str, &str);
  *ch_pointer += size;
  return NUM;
}

int num_to_num_stack(char *str, unsigned int *ch_pointer, Stack_num **sn,
                     int *is_unary) {
  double d = 0;
  int return_value = str_to_num(str, ch_pointer, &d, is_unary);
  *sn = push_stack_num(*sn);
  add_data_to_stack_num(*sn, d);
  return return_value;
}

/*
 * расшифровывает из строки одну лекслему, на которую указывает ch_pointer
 * закидывает ее в соответствующий стек и возвращает: get_rang(char oper);
 * при ошибке возвращает -1
 * возвращающие коды можно посмотреть return_codes.h
 */
int token_parsing(char *str, Stack_num **sn, Stack_ch **sc,
                  unsigned int *ch_pointer, int *is_unary) {
  if (str[*ch_pointer] == 0x00)
    return STR_DONE;
  int return_value = OK;
  if (is_num(str + *ch_pointer) || (str[*ch_pointer] == '-' && *is_unary)) {
    return_value =
        num_to_num_stack(str + *ch_pointer, ch_pointer, sn, is_unary);
  } else if (is_ch(str + *ch_pointer)) {
    if (str[*ch_pointer] == '(')
      *is_unary = 1;
    return_value = operand_to_ch_stack(str + *ch_pointer, ch_pointer, sc);
  }
  return return_value;
}

#endif
