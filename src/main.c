#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

#define malloc(x) my_malloc(x, __FILE__, __LINE__)
#define free(x) my_free(x, __FILE__, __LINE__)

int main(int argc, char **argv) {
  char *test1 = malloc(10);
  printList();

  char *test2 = malloc(30);
  printList();

  char *test3 = malloc(30);
  printList();

  free(test3);
  free(test3);
  free(test1);
  free(test2);
  printList();

  return 0;
}
