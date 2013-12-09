#include <stdlib.h>

#define heap_size 5000

char arry[heap_size];

typedef struct block_ {
  unsigned int offset;
  unsigned int size;
  struct block_ *next;
  struct block_ *prev;
  int free;
} block;

block *head = NULL;

void destroy_node(block *n) {
  free(n);
}

void *my_malloc(unsigned int size) {
  int i;
  block *p, *t;
  /* This should happen the first time we malloc and create the block list */
  if (head == NULL) {
    head = malloc(sizeof(block));
    head->offset = 0;
    head->size = heap_size;
    head->prev = NULL;
    head->next = NULL;
    head->free = 1;
  }

  /* Iterate through to find a block that size fits into */
  for (p = head; p != NULL; p = p->next) {
    if (p->free && p->size >= size) {       /* Found suitable block */
      t = malloc(sizeof(block));
      t->free = 0;
      t->size = size;
      t->offset = p->offset;
      t->prev = p->prev;
      t->next = p;
      p->prev = t;
      p->offset += size;
      p->size -= size;
      return arry + t->offset;
    }
  }

  /* TODO Return different error codes */
  return NULL;
}

void printList() {
  block *p;

  for (p = head; p != NULL; p = p->next)
    printf("OFFSET: %d, SIZE: %d, PHYSICAL ADDRESS: %p\n", p->offset, p->size, arry + p->offset);
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

/* Frees a block enabling it to be allocated again */
void my_free(void *foo) {
  block *p, *t;
  int offset = foo - (void *)arry;
  int i = 0;
  printf("Attempting to free from offset : %d\n", offset);

  /* Check every block to see if it's the target */
  for (p = head; p != NULL; p = p->next) {
    printf("OFFSET: %d\n", p->offset);
    if (p->offset == offset) {
      printf("got here\n");
      p->free = 1;                    /* Disable the lock on the block */
      if (p->next && p->next->free) { /* If adjacent blocks are free, merge them! */
        p->size += p->next->size;
        t = p->next;
        p->next = p->next->next;
        destroy_node(t);              /* Clean up by destroying the node out of work */
      }
      printf("Freed at 0x%p\n", foo);
      return;
    }
  }
  /* TODO error code */
}
