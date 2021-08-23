#include "binary.h"
#include "bubble.h"
#include "quick.h"
#include "shell.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTIONS "Absqip::r::n::"
#define BIT_MASK 0x3fffffff // stands for  2^30-1

//
// print the array as the format
// array: array need to print
// n: length of the array
//
void print_array(uint32_t *array, int n);

// print option initialized
int prt_op_b = 0, prt_op_s = 0, prt_op_q = 0, prt_op_i = 0;

// print element, random seed, and array size initialized
int prt_ele = 100, rand_seed = 8222022, ary_size = 100;

int main(int argc, char **argv) {
  int c = 0;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'A':
      // employ all sorting algorithms
      prt_op_b = 1;
      prt_op_s = 1;
      prt_op_q = 1;
      prt_op_i = 1;
      break;
    case 'b':
      // employ bubble sort
      prt_op_b = 1;
      break;
    case 's':
      // employ shell sort
      prt_op_s = 1;
      break;
    case 'q':
      // employ quick sort
      prt_op_q = 1;
      break;
    case 'i':
      // employ binary insertion sort
      prt_op_i = 1;
      break;
    case 'p':
      // store the print element size
      prt_ele = atoi(argv[optind]);
      break;
    case 'r':
      // random seed change
      rand_seed = atoi(argv[optind]);
      break;
    case 'n':
      // array size change
      ary_size = atoi(argv[optind]);
      break;
    default:
      break;
    }
  }

  srand(rand_seed); // random seed innitialized

  // initialize the array of random numbers
  uint32_t *ary_rand = (uint32_t *)calloc(ary_size, sizeof(uint32_t));
  if (!ary_rand) {
    return -1;
  }

  // initialize the array of copy, used for each sorting algorithms
  uint32_t *ary_copy = (uint32_t *)calloc(ary_size, sizeof(uint32_t));
  if (!ary_copy) {
    return -1;
  }

  // set each random numbers to the array
  for (int i = 0; i < ary_size; i++) {
    uint32_t num = rand();
    num &= BIT_MASK; // let it less than 2^30-1
    ary_rand[i] = num;
  }

  // print the result for binary insertion sort
  if (prt_op_i == 1) {
    memcpy(ary_copy, ary_rand, sizeof(uint32_t) * ary_size);
    binary(ary_copy, ary_size);
    printf("Binary Insertion Sort\n");
    printf("%d elements, %d moves, %d compares\n", ary_size, move_binary,
           com_binary);
    print_array(ary_copy, prt_ele);
  }

  // print the result for quick sort
  if (prt_op_q == 1) {
    memcpy(ary_copy, ary_rand, sizeof(uint32_t) * ary_size);
    quick(ary_copy, 0, ary_size - 1);
    printf("Quick Sort\n");
    printf("%d elements, %d moves, %d compares\n", ary_size, move_quick,
           com_quick);
    print_array(ary_copy, prt_ele);
  }

  // print the result for the shell sort
  if (prt_op_s == 1) {
    memcpy(ary_copy, ary_rand, sizeof(uint32_t) * ary_size);
    shell(ary_copy, ary_size);
    printf("Shell Sort\n");
    printf("%d elements, %d moves, %d compares\n", ary_size, move_shell,
           com_shell);
    print_array(ary_copy, prt_ele);
  }

  // print the result for the bubble sort
  if (prt_op_b == 1) {
    memcpy(ary_copy, ary_rand, sizeof(uint32_t) * ary_size);
    bubble(ary_copy, ary_size);
    printf("Bubble Sort\n");
    printf("%d elements, %d moves, %d compares\n", ary_size, move_bubble,
           com_bubble);
    print_array(ary_copy, prt_ele);
  }

  // free memory for the calloc function
  free(ary_copy);
  ary_copy = NULL;
  free(ary_rand);
  ary_rand = NULL;
}

//
// print the array as the needed format
//
// array: array need to print
// n: length of the array
//
void print_array(uint32_t *array, int n) {
  int j = 0;
  for (int i = 0; i < n; i++) {
    if (j < 6) {
      if (i < n - 1) {
        printf("%13" PRIu32, array[i]);
        j += 1;
      } else {
        printf("%13" PRIu32, array[i]);
        printf("\n");
        j += 1;
      }
    } else {
      printf("%13" PRIu32, array[i]);
      printf("\n");
      j = 0;
    }
  }
}
