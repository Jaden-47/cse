#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

//
// Constructor for a new stack
//
// size: the maximum number of items the stack can hold
// name: the stack's single character identifier
Stack *stack_create(int size, char name) {
  Stack *s = (Stack *)malloc(sizeof(Stack));
  s->name = name;
  if (!s) {
    return 0;
  }
  s->capacity = size;
  s->top = 0;
  s->items = (int *)malloc(sizeof(int) * size);
  if (!s->items) {
    return 0;
  }
  return s;
}

//
// Destructor for a stack
//
// s: the stack to free allocated memory
//
void stack_delete(Stack *s) {
  if (s != NULL) {
    free(s->items);
    free(s);
  }
  return;
}

// pushes an item into a stack if it isn't full
//
// s: the stack to push an item into
//
void stack_push(Stack *s, int i) {
  if (!s) {
    return;
  }
  if (s->top == s->capacity) {
    s->capacity *= 2;
    s->items = (int *)realloc(s->items, s->capacity * sizeof(int));
  }
  if (s->items) {
    s->items[s->top] = i;
    s->top += 1;
  }
  return;
}

//
// pops an item off a stack if it isn't empty
//
// s: the stack to pop an item off
//
int stack_pop(Stack *s) {
  if (!s) {
    return -1;
  }
  if (s->top > 0) {
    s->top -= 1;
    return s->items[s->top];
  } else {
    return -1;
  }
}

// returns true if a stack is empty and false otherwise
//
// s: the stack to query about being empty
//
bool stack_empty(Stack *s) { return s->top == 0; }

//
// returns current top value of stack
//
// s: the stack to peek at
//
int stack_peek(Stack *s) { return s->items[s->top]; }
