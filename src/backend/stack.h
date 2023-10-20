#ifndef STACK_H
#define STACK_H

typedef struct Stack_num {
  double data;
  struct Stack_num *next;
} Stack_num;

typedef struct Stack_ch {
  char data;
  struct Stack_ch *next;
} Stack_ch;

Stack_ch *push_stack_ch(Stack_ch *sc);
Stack_num *push_stack_num(Stack_num *sn);
Stack_ch *pop_stack_ch(Stack_ch *sc);
Stack_num *pop_stack_num(Stack_num *sn);
void add_data_to_stack_num(Stack_num *sn, double data);
void add_data_to_stack_ch(Stack_ch *sc, char data);
void free_stack_ch(Stack_ch *sc);
void free_stack_num(Stack_num *sn);
void print_stack_ch(Stack_ch *sc);
void print_stack_num(Stack_num *sn);

#endif
