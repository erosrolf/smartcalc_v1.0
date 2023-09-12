#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STACK_C
#define STACK_C

Stack_node *push_stack_node(Stack_node *sn) {
  Stack_node *t = (Stack_node *)malloc(sizeof(Stack_node));
  t->name = NULL;
  t->data = NULL;
  t->next = sn;
  return t;
}

Stack_node *pop_stack_node(Stack_node *sn) {
  Stack_node *t = sn->next;

  if (!sn)
    return NULL;
  if (sn->name)
    free(sn->name);
  if (sn->data)
    free(sn->data);
  free(sn);
  return t;
}

void free_stack_node(Stack_node *sn) {
  while (sn)
    sn = pop_stack_node(sn);
}

void set_stack_node_name(Stack_node *sn, char *name) {
  if (sn->name)
    free(sn->name);
  sn->name = (char *)malloc(strlen(name) + 1);
  strcpy(sn->name, name);
}

void set_stack_node_data(Stack_node *sn, void *data, unsigned int size) {
  if (sn->data)
    free(sn->data);
  sn->data = malloc(size);
  memcpy(sn->data, data, size);
}

#endif
