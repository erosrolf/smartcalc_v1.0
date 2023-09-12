#ifndef STACK_H
#define STACK_H

typedef struct Stack_node {
  char *name;
  void *data;
  char *data_type;
  struct Stack_node *next;
} Stack_node;

Stack_node *push_stack_node(Stack_node *sn);
Stack_node *pop_stack_node(Stack_node *sn);
void free_stack_node(Stack_node *sn);
void set_stack_node_name(Stack_node *sn, char *name);
void set_stack_node_data(Stack_node *sn, void *data, unsigned int size);

#endif
