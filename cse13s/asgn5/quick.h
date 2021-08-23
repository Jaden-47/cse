// quick.c - Contains the function declarations for the quick sort

#ifndef __QUICK_H__
#define __QUICK_H__

#include <inttypes.h>

// initialize the counter for comparison and move
int com_quick, move_quick;

//
// quick sort the array
//
// array: array need to sort
// left: min index of the array
// rightL max index of the array
//
void quick(uint32_t *array, int left, int right);

//
// get the partition for the recursion
// left: min index of the array
// right: max index of the array
//
int partition(uint32_t *array, int left, int right);
#endif
