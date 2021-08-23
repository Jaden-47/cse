// quick.c DEscribe the function for quick sort
//

#include "quick.h"

int partition(uint32_t *array, int left, int right) {
  int pivot = array[left];
  int low = left + 1;
  int high = right;
  int temp;
  while (1) {
    // find the element should put at left
    while (low <= high && (int)array[high] >= pivot) {
      com_quick += 1;
      high -= 1;
    }
    com_quick += 1;

    // find the element should put at right
    while (low <= high && (int)array[low] <= pivot) {
      com_quick += 1;
      low += 1;
    }
    com_quick += 1;

    // swap if find
    if (low < high) {
      temp = array[low];
      array[low] = array[high];
      array[high] = temp;
      move_quick += 3;
    } else {
      break;
    }
  }

  // swap the pivot to the middle
  temp = array[left];
  array[left] = array[high];
  array[high] = temp;
  move_quick += 3;
  return high;
}
void quick(uint32_t *array, int left, int right) {
  if (left < right) {
    int index = partition(array, left, right);
    // put smaller element in the left, bigger element in the right
    quick(array, left, index - 1);
    // sort the left part
    quick(array, index + 1, right);
    // sort the right part
    return;
  }
}
