#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

#define malloc(x) my_malloc(x, __FILE__, __LINE__)
#define free(x) my_free(x, __FILE__, __LINE__)

int main(int argc, char **argv) {
  char *test = malloc(10);
  strcpy(test, "foo");
/*  printf("%s\n", test);*/

  free(test);

  char *test2 = malloc(30);
  strcpy(test2, "food");
/*  printf("%s\n", test2);*/

  free(test2);
  free(test2);

  test = malloc(50000);
  free((void*)4000000);

  return 0;
}
