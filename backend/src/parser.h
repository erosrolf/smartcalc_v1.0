#include "stack.h"

#ifndef PARSER_H
#define PARSER_H

int inpt_validator(char *str);
int get_rang(char oper);
int num_to_num_stack(char *str, unsigned int *ch_pointer, Stack_num **sn,
                     int *is_unary);
int operand_to_ch_stack(char *str, unsigned int *ch_pointer, Stack_ch **sc);
int token_parsing(char *str, Stack_num **sn, Stack_ch **sc,
                  unsigned int *ch_pointer, int *is_unary);

#endif
