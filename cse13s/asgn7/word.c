#include "word.h"
#include "code.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

//
// Constructor for a word.
//
// syms:    Array of symbols a Word represents.
// len:     Length of the array of symbols.
// returns: Pointer to a Word that has been allocated memory.
//
Word *word_create(uint8_t *syms, uint32_t len) {
  Word *wd = (Word *)malloc(sizeof(Word));
  if (!wd) {
    puts("failed malloc word in word_create");
    exit(-1);
  } else {
    wd->len = len;
    wd->syms = (uint8_t *)calloc(len, sizeof(uint8_t));
    if (!wd->syms) {
      puts("failed calloc wd->syms in word_create");
      exit(-1);
    }
    for (uint32_t i = 0; i < len; i++) {
      wd->syms[i] = syms[i];
    }
    return wd;
  }
}

//
// Constructs a new Word from the specified Word appended with a symbol.
// The Word specified to append to may be empty.
// If the above is the case, the new Word should contain only the symbol.
//
// w:       Word to append to.
// sym:     Symbol to append.
// returns: New Word which represents the result of appending.
//
Word *word_append_sym(Word *w, uint8_t sym) {
  if (w->len == 0) {
    Word *new_word = word_create(&sym, 1);
    return new_word;
  } else {
    uint8_t *syms = (uint8_t *)calloc(w->len + 1, sizeof(uint8_t));
    if (!syms) {
      puts("failed calloc syms in word_append_sym");
      exit(-1);
    }

    for (uint32_t temp = 0; temp < w->len; temp++) {
      syms[temp] = w->syms[temp];
    }
    syms[w->len] = sym;
    Word *new_word = word_create(syms, w->len + 1);
    free(syms);
    syms = NULL;
    return new_word;
  }
}

//
// Destructor for a Word.
//
// w:       Word to free memory for.
// returns: Void.
//
void word_delete(Word *w) {
  free(w->syms);
  w->syms = NULL;
  free(w);
  w = NULL;
}

//
// Creates a new WordTable, which is an array of Words.
// A WordTable has a pre-defined size of MAX_CODE (UINT16_MAX - 1).
// This is because codes are 16-bit integers.
// A WordTable is initialized with a single Word at index EMPTY_CODE.
// This Word represents the empty word, a string of length of zero.
//
// returns: Initialized WordTable.
//
WordTable *wt_create(void) {
  WordTable *wt = (WordTable *)calloc(MAX_CODE, sizeof(Word));
  if (!wt) {
    puts("failed calloc wt in wt_create");
    exit(-1);
  }
  uint8_t empty = 0;
  wt[EMPTY_CODE] = word_create(&empty, 0);
  return wt;
}

//
// Resets a WordTable to having just the empty Word.
//
// wt:      WordTable to reset.
// returns: Void.
//
void wt_reset(WordTable *wt) {
  if (!wt) {
    return;
  }
  for (int i = 2; i < MAX_CODE; i++) {
    if (wt[i]) {
      word_delete(wt[i]);
    }
  }
}

//
// Deletes an entire WordTable.
// All Words in the WordTable must be deleted as well.
//
// wt:      WordTable to free memory for.
// returns: Void.
//
void wt_delete(WordTable *wt) {
  if (!wt) {
    return;
  }
  for (int i = 0; i < MAX_CODE; i++) {
    if (wt[i]) {
      word_delete(wt[i]);
    }
  }
  free(wt);
  wt = NULL;
}
