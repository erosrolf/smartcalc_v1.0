#include "parser.h"
#include "return_codes.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PARSER_C
#define PARSER_C

int is_num(char *s) { return ((*s >= '0') && (*s <= '9')) || *s == '.'; }

int is_ch(char *s) {
  return *s == '-' || *s == '+' || *s == '*' || *s == '/' || *s == '%' ||
         *s == '^' || *s == '(' || *s == ')';
}

int is_func(char *s) {
  return *s == 'c' || *s == 's' || *s == 't' || *s == 'a' || *s == 'l';
}

static int is_err(char *s) { return s[0] == 'e' && s[1] == 'r' && s[2] == 'r'; }

static int minus_is_correct(char *str, int n) {
  int after = 0, before = 0;
  after = (is_num(&str[n + 1]) || str[n + 1] == '(' || is_func(&str[n + 1]));
  if (n)
    before = (is_num(&str[n - 1]) || str[n - 1] == '(' || str[n - 1] == ')' ||
              str[n - 1] == '/' || str[n - 1] == '*');
  else
    before = 1;
  return after && before;
}

static int dot_validator(char *str) {
  int return_value = OK;
  int dot = 0;
  int i = 0;
  while (str[i] != 0x00 && return_value == OK) {
    if (str[i] == '.' && str[i + 1] == 0x00)
      return_value = ERR;
    if (str[i] == '.')
      dot++;
    if (!is_num(str))
      dot = 0;
    if (dot > 1)
      return_value = ERR;
    i++;
  }
  return return_value;
}

int inpt_validator(char *str) {
  int n = 0;
  int open_br = 0;
  int close_br = 0;
  int return_value = dot_validator(str);
  while (str[n] != 0x00 && return_value == OK) {
    if (is_err(str))
      return_value = ERR;
    if (str[n] == '(') {
      if (str[n + 1] == ')')
        return_value = ERR;
      else
        ++open_br;
    }
    if (str[n] == ')') {
      if (!open_br)
        return_value = ERR;
      else
        ++close_br;
    }
    if (n && is_func(&str[n]) && is_num(&str[n - 1]))
      return_value = ERR;
    if (str[n] == '-') {
      if (!minus_is_correct(str, n))
        return_value = ERR;
    }
    ++n;
  }
  if (open_br == close_br && return_value == OK)
    return_value = OK;
  else
    return_value = ERR;
  return return_value;
}

static int func_to_ch(char *s, unsigned int *ch_pointer) {
  int return_value = ERR;
  if (*s == 'c' || *s == 's' || *s == 't') {
    if (s[1] == 'o' && s[2] == 's') {
      *ch_pointer += 3;
      return_value = COS;
    } else if (s[1] == 'i' && s[2] == 'n') {
      *ch_pointer += 3;
      return_value = SIN;
    } else if (s[1] == 'a' && s[2] == 'n') {
      *ch_pointer += 3;
      return_value = TAN;
    } else if (s[1] == 'q' && s[2] == 'r' && s[3] == 't') {
      *ch_pointer += 4;
      return_value = SQRT;
    }
  } else if (*s == 'a') {
    if (s[1] == 'c') {
      *ch_pointer += 4;
      return_value = ACOS;
    } else if (s[1] == 's') {
      *ch_pointer += 4;
      return_value = ASIN;
    } else if (s[1] == 't') {
      *ch_pointer += 4;
      return_value = ATAN;
    }
  }
  return return_value;
}

int get_rang(char oper) {
  int return_value = NUM;
  if (oper == '(')
    return_value = OPEN_BR;
  if (oper == '-' || oper == '+')
    return_value = LOW_RANG;
  if (oper == '/' || oper == '*')
    return_value = MID_RANG;
  if (oper == '^' || oper == '%')
    return_value = HIGH_RANG;
  if (is_func(&oper))
    return_value = TOP_RANG;
  if (return_value == ')')
    return_value = CLOSE_BR;
  return return_value;
}

int operand_to_ch_stack(char *str, unsigned int *ch_pointer, Stack_ch **sc) {
  int return_value = OK;
  char ch = 0;
  if (is_ch(str)) {
    ch = *str;
    *ch_pointer += 1;
    return_value = get_rang(*str);
  } else if (is_func(str)) {
    ch = func_to_ch(str, ch_pointer);
    return_value = TOP_RANG;
  }
  if (return_value != ERR) {
    *sc = push_stack_ch(*sc);
    add_data_to_stack_ch(*sc, ch);
  }
  return return_value;
}

int num_to_num_stack(char *str, unsigned int *ch_pointer, Stack_num **sn,
                     int *is_unary) {
  int return_value = NUM;
  double d = 0;
  char *start = str;
  if (is_num(str) || *is_unary)
    *is_unary = 0;
  d = strtod(start, &str);
  *ch_pointer += str - start;
  *sn = push_stack_num(*sn);
  add_data_to_stack_num(*sn, d);
  return return_value;
}

// parse any lexlem and push to correct type stack
int token_parsing(char *str, Stack_num **sn, Stack_ch **sc,
                  unsigned int *ch_pointer, int *is_unary) {
  if (str[*ch_pointer] == 0x00)
    return STR_DONE;
  int return_value = OK;
  if (is_num(str + *ch_pointer) || (str[*ch_pointer] == '-' && *is_unary) ||
      (str[*ch_pointer] == '+' && *is_unary)) {
    return_value =
        num_to_num_stack(str + *ch_pointer, ch_pointer, sn, is_unary);
  } else if (is_ch(str + *ch_pointer) || is_func(str + *ch_pointer)) {
    if (str[*ch_pointer] == '(')
      *is_unary = 1;
    return_value = operand_to_ch_stack(str + *ch_pointer, ch_pointer, sc);
  }
  return return_value;
}

#endif // PARSER_C
