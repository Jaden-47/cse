#include "bf.h"
#include "bv.h"
#include "speck.h"
#include <stdio.h>
#include <stdlib.h>

//
// Constructor for a BloomFilter .
//
// size : The number of entries in the BloomFilter .
//
BloomFilter *bf_create(uint32_t size) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf) {
    bf->primary[0] = 0xfc28ca6885711cf7;
    bf->primary[1] = 0x2841af568222f773;
    bf->secondary[0] = 0x85ae998311115ae3;
    bf->secondary[1] = 0xb6fac2ae33a40089;
    bf->tertiary[0] = 0xd37b01df0ae8f8d0;
    bf->tertiary[1] = 0x911d454886ca7cf7;
    bf->filter = bv_create(size);
    return bf;
  }
  return (BloomFilter *)NIL;
}

void bf_delete(BloomFilter *bf) {
  bv_delete(bf->filter);
  free(bf);
  bf = NULL;
}

void bf_insert(BloomFilter *bf, char *key) {
  // first salt hash
  uint32_t val_hash1 = hash(bf->primary, key);
  val_hash1 %= bf->filter->length;
  bv_set_bit(bf->filter, val_hash1);

  // second salt hash
  uint32_t val_hash2 = hash(bf->secondary, key);
  val_hash2 %= bf->filter->length;

  bv_set_bit(bf->filter, val_hash2);

  // third salt has
  uint32_t val_hash3 = hash(bf->tertiary, key);
  val_hash3 %= bf->filter->length;
  bv_set_bit(bf->filter, val_hash3);
}

bool bf_probe(BloomFilter *bf, char *key) {
  uint8_t result = 0;
  // determine the first hash value
  uint32_t val_hash1 = hash(bf->primary, key) % bf->filter->length;
  result += bv_get_bit(bf->filter, val_hash1);

  // determine the second hash value
  uint32_t val_hash2 = hash(bf->secondary, key) % bf->filter->length;
  result += bv_get_bit(bf->filter, val_hash2);

  // determine the third hash value
  uint32_t val_hash3 = hash(bf->tertiary, key) % bf->filter->length;
  result += bv_get_bit(bf->filter, val_hash3);
  if (result == 3) {
    return true;
  } else {
    return false;
  }
}
