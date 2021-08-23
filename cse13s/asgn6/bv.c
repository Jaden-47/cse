// bv.c - Describe the function for bitvector
//

#include "bv.h"
#include <stdio.h>
#include <stdlib.h>
//
// Creates a new BitVector of specified length
//
// bit_len : The length in bit of the BitVector.
//
BitVector *bv_create(uint32_t bit_len) {
  BitVector *b = (BitVector *)malloc(sizeof(BitVector));
  if (!b) {
    return 0;
  }
  b->length = bit_len;
  uint32_t vector_length;
  if (bit_len % 8 == 0) {
    vector_length = bit_len / 8;
  } else {
    vector_length = bit_len / 8 + 1;
  }
  b->vector = (uint8_t *)malloc(sizeof(uint8_t) * vector_length);
  return b;
}

//
// Destructor for a bitvector
//
// v: the bitvector to free allocated memory
//
void bv_delete(BitVector *v) {
  if (v != NULL) {
    free(v->vector);
    free(v);
  }
  return;
}

//
// Reutrns the length in bits fo the BitVector
//
// v : The BitVector.
//
uint32_t bv_get_len(BitVector *v) {
  if (v == NULL) {
    return 0;
  }
  return v->length;
}

//
// Sets the bit at index in the BitVector.
//
//  v: The BitVector
//  i : Index of the bit to set.
//
void bv_set_bit(BitVector *v, uint32_t i) {
  uint32_t j = i / 8;
  uint8_t p = i % 8;
  v->vector[j] |= (1 << p);
}

//
// Clears the bit at index in the BitVector.
//
//  v : The BitVector.
//  i : Index of the bit to clear.
//
void bv_clr_bit(BitVector *v, uint32_t i) {
  uint32_t j = i / 8;
  uint8_t p = i % 8;
  v->vector[j] &= ~(1 << p);
}

//
// Gets a bit from a BitVector.
//
// v : The BitVector.
// i : Index of the bit to get
//
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  uint32_t j = (long long)i / 8;
  uint8_t p = i % 8;
  if (v->vector[j] & (1 << p)) {
    return 1;
  } else {
    return 0;
  };
}

//
// Sets all bits in a BitVector.
//
// v : The BitVector.
//
void bv_set_all_bits(BitVector *v) {
  for (uint32_t i = 0; i < (v->length); i++) {
    bv_set_bit(v, i);
  }
}
