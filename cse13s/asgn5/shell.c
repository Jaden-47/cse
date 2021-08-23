// shell.c Describe the function for shell sort
//

#include "shell.h"

void shell(uint32_t *array, int n) {
  int temp;
  int determine = 1;
  int gap = n * 5 / 11; // deternmine the gap algorithm
  com_shell = 0;
  move_shell = 0;
  if (gap <= 2) {
    gap = 1;
  }
  while (gap > 0) {
    // imlepment in each gap
    // below is regular insertion sort
    for (int i = gap; i < n; i++) {
      for (int j = i; j > gap - 1; j--) {
        com_shell += 1;
        // compare between each element to find which place to insert
        if (array[j] < array[j - gap]) {
          // if find, then swap each element to the following position
          temp = array[j];
          array[j] = array[j - gap];
          array[j - gap] = temp;
          move_shell += 3;
        }
      }
    }
    if (gap < 5 && determine) {
      gap = 1;
      determine = 0;
    } else {
      if (determine == 0) {
        break;
      }
      gap = gap * 5 / 11;
    }
  }
}
