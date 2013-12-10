ORDERDIS
========
CS 214 Assignment 6 -- Fake Malloc
========
Ian Lozinski (iml22), Edward Zaneski(epz5)


Usage: ```make <target>; ./<target>```

The goal of this assignment was to produce a fake malloc that safeguards against
dangerous operations. Operations like passing a pointer to something that has already
been freed to free(), or malloc()ing space that isn't available are considered unsafe.

To demonstrate these safeguards, the main.c file shows some operations that are
unsafe. It also shows operations that should work safely.

The heap is represented as a char array[5000]  Blocks are represented as a linked list.
When there is nothing allocated in the heap, the list contains one element, the head.
Each node contains:
  * An offset
  * A size
  * A pointer to the previous block
  * A pointer to the next block
  * A flag, representing if the block is in use



###Complexity analysis:
Mallocing O(1)
Free O(1)
