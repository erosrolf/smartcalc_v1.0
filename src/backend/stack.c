#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum error { MEM_ERR = 5 };

#ifndef STACK_C
#define STACK_C

Stack_ch *push_stack_ch(Stack_ch *sc) {
  Stack_ch *t = (Stack_ch *)malloc(sizeof(Stack_ch));
  if (!t)
    exit(MEM_ERR);
  t->next = sc;
  return t;
}

Stack_num *push_stack_num(Stack_num *sn) {
  Stack_num *t = (Stack_num *)malloc(sizeof(Stack_num));
  if (!t)
    exit(MEM_ERR);
  t->next = sn;
  return t;
}

Stack_ch *pop_stack_ch(Stack_ch *sc) {
  Stack_ch *t = sc->next;
  if (!sc)
    return NULL;
  free(sc);
  return t;
}

Stack_num *pop_stack_num(Stack_num *sn) {
  Stack_num *t = sn->next;
  if (!sn)
    return NULL;
  free(sn);
  return t;
}

void add_data_to_stack_num(Stack_num *sn, double data) { sn->data = data; }

void add_data_to_stack_ch(Stack_ch *sc, char data) { sc->data = data; }

void free_stack_num(Stack_num *sn) {
  while (sn)
    sn = pop_stack_num(sn);
}

void free_stack_ch(Stack_ch *sc) {
  while (sc)
    sc = pop_stack_ch(sc);
}

void print_stack_ch(Stack_ch *sc) {
  while (sc) {
    printf("data char = %c\n", sc->data);
    sc = sc->next;
  }
}

void print_stack_num(Stack_num *sn) {
  while (sn) {
    printf("data double = %f\n", sn->data);
    sn = sn->next;
  }
}

#endif // STACK_C
