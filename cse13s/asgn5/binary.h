// binary.h - Contains the functions declarations for the binary insertion sort

#ifndef __BINARY_H__
#define __BINARY_H__

#include <inttypes.h>

// initialize the counter for comparison and move
//
int move_binary, com_binary;

//
// Using binary insertion sort to sort array
//
// array: array needs to sort
// n: length of the array
//
void binary(uint32_t *array, int n);

#endif
