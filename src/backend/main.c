#include "parser.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *str = (char *)malloc(256);
  str = "2.23-1.23";
  unsigned int ch_pointer = 0;
  Stack_num *sn = NULL;
  Stack_ch *sc = NULL;

  str_to_num_stack(str + ch_pointer, &ch_pointer, &sn);
  str_to_ch_stack(str + ch_pointer, &ch_pointer, &sc);
  printf("new str = \'%s\'\nch_pointer = \'%d\'\n", str + ch_pointer,
         ch_pointer);

  while (sn) {
    printf("data = %f\n", sn->data);
    sn = sn->next;
  }

  while (sc) {
    printf("data = %c\n", sc->data);
    sc = sc->next;
  }

  return 0;
}
