#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

#define malloc(x) my_malloc(x, __FILE__, __LINE__)
#define free(x) my_free(x, __FILE__, __LINE__)
#define printList(x) printList(__LINE__, x)

int main(int argc, char **argv) {
  printList(0);  /* Should have one block, one in use */

  free(0);       /* Should throw error */

  char *test1 = malloc(10);
  printList(2); /* Should have two blocks, one in use */

}
