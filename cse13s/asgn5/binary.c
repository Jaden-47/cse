// binary.c - Describe the function for binary insertion sort

#include "binary.h"

//
// Using binary insertion sort to sort array
//
// array: array needs to sort
// n: length of the array
//
void binary(uint32_t *array, int n) {
  int value, left, right, mid, temp;
  move_binary = 0;
  com_binary = 0;
  for (int i = 1; i < n; i++) {
    value = array[i];
    left = 0;
    right = i;

    // find the middle using binary method
    while (left < right) {
      mid = left + ((right - left) / 2);
      com_binary += 1;
      if (value >= (int)array[mid]) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }

    // insert the element and move other element to following postion
    for (int j = i; j > left; j--) {
      temp = array[j - 1];
      array[j - 1] = array[j];
      array[j] = temp;
      move_binary += 3;
    }
  }
}
