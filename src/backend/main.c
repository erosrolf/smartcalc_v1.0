#include "parser.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *str = (char *)malloc(256);
  str = "2.23-1.23";
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;

  parser(str, &sn, &sc);

  while (sn) {
    printf("data double = %f\n", sn->data);
    sn = sn->next;
  }

  while (sc) {
    printf("data char = %c\n", sc->data);
    sc = sc->next;
  }

  return 0;
}
