/* malloc.h
 * Authors: Ian Lozinski, Edward Zaneski
 * 12/9/2013
 * CS214
 */
#ifndef MALLOC_H
#define MALLOC_H

#include <stdlib.h>

#define heap_size 5000

char heap[heap_size];

typedef struct block_ {
  unsigned int offset;
  unsigned int size;
  struct block_ *next;
  struct block_ *prev;
  int free;
} block;

block *head = NULL;

/* Destroys a node */
void destroy_node(block *n) {
  free(n);
}

void *my_malloc(unsigned int size, char *file, unsigned int line) {
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

  /* Iterate through to find a block that can accomodate size */
  for (p = head; p != NULL; p = p->next) {
    if (p->free && p->size >= size) {       /* Found suitable block */

      t = malloc(sizeof(block));
      t->free = 0;
      t->size = size;
      t->offset = p->offset;
      t->prev = p->prev;
      t->next = p;

      if (p == head) {
        head = t;
      } else {
        p->prev->next = t;
      }

      p->prev = t;
      p->offset += size;
      p->size -= size;

      return heap + t->offset;
    }
  }

  /* Getting here means we don't have a block of big enough space */
  fprintf(stderr, "ERROR: Not enough free space at %s:%d\n", file, line);
  return NULL;
}


/* Recursively merges block p with all adjacent free blocks */
void compress(block *p) {
  block *t;

  if (p && p->next && p->next->free) { /* If block to the right is free, merge with it! */
    p->size += p->next->size;
    t = p->next;
    p->next = p->next->next;
    destroy_node(t);              /* Clean up by destroying the node out of work */
    compress(p->next);
  }

  if (p && p->prev && p->prev->free) { /* If adjacent blocks are free, merge them! */
    p->prev->size += p->size;
    p->prev->next = p->next;
    t = p->prev;
    destroy_node(p);              /* Clean up by destroying the node out of work */
    compress(t);
  }
}


/* Prints out every block in the heap */
/* Also checks the number of blocks match what is expected */
void printList(int line, int expectedBlocks) {
  block *p;
  int actualBlocks = 0;

  printf("\nLine number: %d\n", line);
  for (p = head; p != NULL; p = p->next, actualBlocks++) {
    printf("STATUS: %4s, OFFSET: %4d, SIZE: %4d, PHYSICAL ADDRESS: %p\n",
        (p->free ? "FREE" : "USED"), p->offset, p->size, heap + p->offset);
  }
  printf("Actual blocks: %d | Expected blocks: %d\nOutcome: %s\n\n",
      actualBlocks, expectedBlocks, (expectedBlocks == actualBlocks ? "PASS" : "FAIL"));
}


/* Frees a block so that it can be allocated again */
/* Merges newly freed block with adjacent free blocks */
void my_free(void *foo, char *file, unsigned int line) {
  block *p, *t;
  int offset = foo - (void *)heap, i = 0;

  /* Check every block to see if it's the target */
  for (p = head; p != NULL; p = p->next) {
    if (p->offset == offset) {
      if (p->free) {
        fprintf(stderr, "INVALID FREE: Already free!\n");
        return;
      }
      p->free = 1;                    /* Disable the lock on the block */
      compress(p);
      return;
    }
  }

  /* Getting here means we tried to free something that wasn't malloc'd */
  fprintf(stderr, "ERROR: Invalid free (space not allocated) at file: %s:%d\n", file, line);

}

#endif
