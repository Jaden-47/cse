// Describe the function for bubble sort
//

#include "bubble.h"

//
// do bubble sort to an array
//
// array: array needs to be sorted
// n: length of the array
//

void bubble(uint32_t *array, int n) {
  // comparison and move counter initialize
  com_bubble = 0;
  move_bubble = 0;
  int k;
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      com_bubble += 1;
      // compare between the nearest element
      if (array[j] > array[j + 1]) {
        // if it is bigger, then swap
        k = array[j];
        array[j] = array[j + 1];
        array[j + 1] = k;
        move_bubble += 3;
      }
    }
  }
  return;
}
