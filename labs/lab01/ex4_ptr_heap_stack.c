#include <stdio.h>
#include <stdlib.h>

int* int_on_stack() {
  // Allocates memory on the stack for an integer
  int x = 5;

  // Returns a pointer that points to the number 5
  return &x;
}

int* int_on_heap() {
  // TODO: allocate memory on the heap for an integer
  ______ ptr_to_5 = ______;

  // TODO: store the number 5 in memory you just allocated
  ______ = 5;

  // Returns a pointer that points to the number 5
  return ptr_to_5;
}

int main() {
  int* ptr_to_stack = int_on_stack();
  int* ptr_to_heap = int_on_heap();

  printf("ptr_to_stack is the address %p\n", ptr_to_stack);
  printf("ptr_to_heap is the address %p\n", ptr_to_heap);

  return 0;
}
