#include "calculate.h"
#include "parser.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  char buf[256];
  char *str = (char *)malloc(256);

  if (fgets(buf, 255, stdin) != NULL) {
    sscanf(buf, "%s", str);
  }

  // calculate(str);
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;
  parser(str, &sn, &sc);
  print_stack_num(sn);
  print_stack_ch(sc);

  // sn = pop_stack_num(sn);

  return 0;
}
