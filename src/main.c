#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

#define malloc(x) my_malloc(x, __FILE__, __LINE__)
#define free(x) my_free(x, __FILE__, __LINE__)
#define printList(x) printList(__LINE__, x)

int main(int argc, char **argv) {
  printList(0);  /* Should have one block, one in use */

  char *test1 = malloc(10);
  printList(2); /* Should have two blocks, one in use */

  char *test2 = malloc(30);
  printList(3); /* Should have three blocks, two in use */

  char *test3 = malloc(30);
  printList(4); /* Should have four blocks, three in use */

  free(test1);  /* Should free fine */
  printList(4);  /* Should have four blocks, two in use */
  free(test2);  /* Should free fine */
  free(test3);  /* Should free fine */
  free(test3);  /* Should throw error */

  printList(1);  /* Should have one block, one in use */
  printList(1);  /* Should have one block, one in use */

}
