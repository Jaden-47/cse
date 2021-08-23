#include "trie.h"
#include "code.h"
#include <stdio.h>
#include <stdlib.h>

//
// Constructor for a TrieNode.
//
// code:   Code of the constructed TrieNode.
// returns: Pointer to a TrieNode that has been allocated memory.
//
TrieNode *trie_node_create(uint16_t code) {
  TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
  if (!node) {
    puts("failed malloc trie node in trie_node_create");
    exit(-1);
  } else {
    for (int i = 0; i < ALPHABET; i++) {
      node->children[i] = NULL;
    }
    node->code = code;
    return node;
  }
}

//
// Destructor for a TrieNode.
//
// n:       TrieNode to free allocated memory for.
// returns: Void.
//
void trie_node_delete(TrieNode *n) {
  free(n);
  n = NULL;
  return;
}

//
// Initializes a Trie: a root TrieNode with the index EMPTY_CODE.
//
// returns: Pointer to the root of a Trie.
//
TrieNode *trie_create(void) {
  TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
  if (!node) {
    puts("failed malloc trie node in trie_create");
    exit(-1);
  } else {
    for (int n = 0; n < ALPHABET; n++) {
      node->children[n] = NULL;
    }
    node->code = EMPTY_CODE;
  }
  return node;
}
//
// Deletes a sub-Trie starting from the sub-Trie's root.
//
// n:       Root of the sub-Trie to delete.
// returns: Void.
//
void trie_delete(TrieNode *n) {
  if (!n) {
    return;
  }
  for (int i = 0; i < ALPHABET; i++) {
    if (n->children[i]) {
      trie_delete(n->children[i]);
    }
  }
  trie_node_delete(n);
  return;
}

//
// Resets a Trie to just the root TrieNode.
//
// root:    Root of the Trie to reset.
// returns: Void.
//
void trie_reset(TrieNode *root) {
  if (!root) {
    return;
  }
  for (int j = 0; j < ALPHABET; j++) {
    if (root->children[j]) {
      trie_delete(root->children[j]);
    }
  }
}

//
// Returns a pointer to the child TrieNode reprsenting the symbol sym.
// If the symbol doesn't exist, NULL is returned.
//
// n:       TrieNode to step from.
// sym:     Symbol to check for.
// returns: Pointer to the TrieNode representing the symbol.
//
TrieNode *trie_step(TrieNode *n, uint8_t sym) {
  if (n == NULL) {
    return NULL;
  }
  if (n->children[sym] == NULL) {
    return NULL;
  } else {
    return n->children[sym];
  }
}
