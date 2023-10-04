#include "stack.h"

#ifndef PARSER_H
#define PARSER_H

int str_to_ch_stack(char *str, unsigned int *ch_pointer, Stack_ch **sc);
int str_to_num_stack(char *str, unsigned int *ch_pointer, Stack_num **sn,
                     Stack_ch *sc);
void parser(char *str, Stack_num **sn, Stack_ch **sc);

#endif
