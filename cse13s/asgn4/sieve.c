// sieve.c contains function for sieve method

#include "sieve.h"
#include <math.h>
#include <stdio.h>
//
// Cited from asgn4.pdf
// The Sieve of Erastothenes
// Sets bits in a BitVector representing prime numbers.
// Composite numbers are sieved out by clearing bits.
//
// v: The BitVector to sieve.
//
void sieve(BitVector *v) {
  bv_set_all_bits(v);
  bv_clr_bit(v, 0);
  bv_clr_bit(v, 1);
  bv_set_bit(v, 2);
  for (uint32_t i = 2; i < sqrtl(bv_get_len(v)); i++) {
    // Prime means bit is set
    if (bv_get_bit(v, i)) {
      for (uint32_t k = 0; (k + i) * i <= bv_get_len(v); k++) {
        bv_clr_bit(v, (k + i) * i);
      }
    }
  }
  return;
}
