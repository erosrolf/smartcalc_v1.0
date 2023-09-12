#include "calculator.h"
#include "stack.h"
#include <stdio.h>
#include <string.h>

typedef struct Number {
  double val;
} Number;

typedef struct Operation {
  char ch;
} Operation;

int parser(char *inpt) {
  int err = OK;

  return err;
}
/*
int main(int argc, char *argv[]) {
  Circle c;
  Stack_node *sn = NULL;
  char buf[100];
  char name[20];
  printf("Try: <name> <x> <y> <r> or q to exit\n");
  while (fgets(buf, 99, stdin) != NULL) {
    sscanf(buf, "%s %f %f %f", name, &c.x, &c.y, &c.r);
    if (strcmp(name, "q") == 0)
      break;
    sn = push_stack_node(sn);
    set_stack_node_name(sn, name);
    set_stack_node_data(sn, &c, sizeof(Circle));
  }

  printf(" --- \n");
  Stack_node *t = sn;
  while (t) {
    Circle *hc = (Circle *)t->data;
    printf("Name \'%s\' x=%f, y=%f r=%f\n", t->name, hc->x, hc->y, hc->r);
    t = t->next;
  }

  free_stack_node(sn);
  return 0;
}
*/
