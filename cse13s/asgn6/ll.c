#define _CRT_SECURE_NO_DEPRECATE
#include "ll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListNode *ll_node_create(HatterSpeak *gs) {
  ListNode *new = malloc(sizeof(ListNode));
  if (new == NULL)
    return (ListNode *)NIL;
  new->gs = gs;
  return new;
}

//
// Destructor for a ListNode .
//
// n: The ListNode to free .
//
void ll_node_delete(ListNode *n) {
  free(n);
  n = NULL;
}

//
// Destructor for a linked list of ListNodes .
//
// head : The head of the linked list .
//
void ll_delete(ListNode *head) {
  if (!head)
    return;
  ll_delete(head->next);
  free(head->gs);
  head->gs = NULL;
  ll_node_delete(head);
  head = NULL;
}

//
// Creates and inserts a ListNode into a linked list .
//
// head : The head of the linked list to insert in.
// gs: HatterSpeak struct .
//
ListNode *ll_insert(ListNode **head, HatterSpeak *gs) {
  ListNode *ans = ll_node_create(gs);
  if (ans == NULL)
    return (ListNode *)NIL;
  ans->next = *head;
  return ans;
}

//
// To tell the whether two string is the same
// return True or False
//
// chara[]: first string
// charb[]: second string
//
bool cmp(char a[], char b[]) {
  int T = 0;
  while (a[T] && b[T] && a[T] == b[T]) {
    ++T;
  }
  if (a[T] ^ b[T])
    return 0;
  return 1;
}

//
// Searches for a specific key in a linked list .
// Returns the ListNode if found and NULL otherwise .
//
// head : The head of the linked list to search in.
// key: The key to search for .
ListNode *ll_lookup(ListNode **head, char *key) {
  seeks++;
  ListNode *now = head[0], *prev = 0;
  if (now == NULL)
    return (ListNode *)NIL;
  while (now) {
    nodes_travel++;
    if (cmp(now->gs->oldspeak, key)) {
      if (move_to_front && prev) {
        prev->next = now->next;
        now->next = head[0];
        head[0] = now;
      }
      return now;
    }
    prev = now;
    now = now->next;
  }
  return 0;
}
