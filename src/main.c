#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

int main(int argc, char **argv) {
  char *test = my_malloc(10);
  strcpy(test, "foo");
  printf("%s\n", test);

  printList();
/*  my_free(test);*/

  char *test2 = my_malloc(30);
  strcpy(test2, "food");
  printf("%s\n", test2);

/*  my_free(test2);*/

  printList();

  return 0;
}
