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

  if (!calculate(str))
    exit(1);

  // sn = pop_stack_num(sn);

  return 0;
}
