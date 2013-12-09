#include <stdlib.h>

#define heap_size 5000

char arry[heap_size];

typedef struct block_ {
  unsigned int offset;
  unsigned int size;
  struct block_ *next;
  int free;
} block;

block *head = NULL;


void *my_malloc(unsigned int size) {
  int i;
  block *p, *t;
  /* If head is NULL, we create head */
  if (head == NULL) {
    head = malloc(sizeof(block));
    head->offset = 0;
    head->size = heap_size;
    head->next = NULL;
    head->free = 1;
  }

  for (p = head; p != NULL; p = p->next) {
    if (p->free && p->size >= size) {
      t = malloc(sizeof(block));
      t->size = size;
      t->offset = p->offset;
      t->next = p;
      t->free = 0;

      p->offset += size;
      p->size -= size;

      printf("alloc'd %d bytes\n", size);
      printf("0x%x\n", (int)(arry + t->offset));
      return arry + t->offset;
    }
  }

  /* Return different error codes */
  return NULL;
}
/*
[0,0,0,0,0]
  head.offset = 0
  head.size = 5
[x,0,0,0,0]
  head.offset = 1
  head.size = 4
[x,y,0,0,0]
  head.offset = 2
  head.size = 3
[0,y,0,0,0]
  head.offset = 2
  head.size = 3
  head.next.offset = 0
  head.next.size = 1

[0, 0, y, 0, 0]

[x, 0, y, 0, 0]
*/

void my_free(void *foo) {
}
