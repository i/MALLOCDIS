#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

int main(int argc, char **argv) {
  char *test = my_malloc(10);
  char *test2 = my_malloc(30);

  strcpy(test, "foo");
  printf("%s\n", test);

  strcpy(test2, "food");
  printf("%s\n", test2);

  return 0;
}
