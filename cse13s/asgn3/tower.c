#include "stack.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#define OPTIONS "n::sr"

// This program aims to print out the
// result of tower of brahma by two method
// stack and recursion
// it will get the command and argument from
// command line and print as it is said.

void prt_mv(int n, char a, char b);
// print the movement
//
// n: the number of disk
// a: from the first peg
// b: to the second peg
//

void move_rec(int n, char a, char b, char c);
// movement fot the recursion method
//
// n: the number of disk
// a: the first peg
// b: the second peg
// c: the third peg
//

void print_stack();
// create three peg and print them out using move_stack function
//

void move_stack(int n, Stack *pa, Stack *pb, Stack *pc);
// movement for the stack method
//
// pa: the first peg
// pb: the second peg
// pc: the third peg
//

int mv_rec_count = 0;
int mv_stack_count = 0;
// counters for recursion and stack method.

int size_stack = 5;
// initialize the size

char name1 = 'A';
char name2 = 'B';
char name3 = 'C';
// innitialize the name for three peg

int print_option1 = 0;
int print_option2 = 0;
// to determine whether to print out the result by recursion or stack method.

int main(int argc, char **argv) {
  int c = 0;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    // get the command from command line
    switch (c) {
    case 'n':
      // set the value of size, and if there isn't, kepp default as 5
      size_stack = atoi(argv[optind]);

      break;
    case 's':
      // print out the result using the stack method
      print_option1 = 1;
      break;
    case 'r':
      // print out the result using the recursion method
      print_option2 = 1;
      break;
    default:
      break;
    }
  }
  if (print_option1 == 1) {
    // print the stack method with header and number of moves
    print_stack();
    printf("\nNumber of moves: %d\n\n", mv_stack_count);
  }
  if (print_option2 == 1) {
    // print recursion method with header and number of moves
    printf("================================\n");
    printf("--------   RECURSION   ---------\n");
    printf("================================\n");
    move_rec(size_stack, 'A', 'B', 'C');
    printf("\nNumber of moves: %d\n\n", mv_rec_count);
  }
  return 0;
}

void print_stack() {
  // set three pege
  Stack *pegA = stack_create(size_stack, name1);
  Stack *pegB = stack_create(size_stack, name2);
  Stack *pegC = stack_create(size_stack, name3);
  for (int i = 0; i < size_stack; i++) {
    pegA->items[i] = i + 1;
    pegB->items[i] = 0;
    pegC->items[i] = 0;
  }
  // print header and the movement, number of movement as well
  printf("================================\n");
  printf("----------   STACKS   ----------\n");
  printf("================================\n");
  move_stack(size_stack, pegA, pegB, pegC);
}

void move_stack(int n, Stack *pa, Stack *pb, Stack *pc) {
  int from_peg, to_peg, disk;
  int bit_store[n];               // use to decide which disk to move
  int pos[n];                     // store the disk position on which peg
  int i, j;                       // used for iterator
  int temp = 2 + (n % 2);         // store the first peg move to
  int total_moves = (1 << n) - 1; // total moves count
  char f_peg_name, t_peg_name;    // char name for from and to peg name

  // initialize the bit and position array
  // give bit all 0
  // give position all on the first pegA
  //
  for (i = 0; i < n; i++) {
    bit_store[i] = 0;
    pos[i] = 1;
  }

  // iterate 2^n-1 times for each move
  //
  for (i = 1; i <= total_moves; i++) {

    // iterate when finding the smallest 1 in digit
    //
    for (j = 0; bit_store[j] != 0; j++) // decide which disk to move
    {
      bit_store[j] = 0;
    }
    bit_store[j] = 1; // adding 1 to the number
    disk = j + 1;     // find the disk to move

    // the first disk to move situation
    // it can go only go clockwise or counterclockwise
    // when the first move have benn decided
    //
    if (disk == 1) {
      from_peg = pos[0];
      to_peg = 6 - from_peg - temp;

      // pop from the original peg
      //
      switch (from_peg) {
      case 1:
        f_peg_name = pa->name;
        stack_pop(pa);
        break;
      case 2:
        f_peg_name = pb->name;
        stack_pop(pb);
        break;
      case 3:
        f_peg_name = pc->name;
        stack_pop(pc);
        break;
      default:
        break;
      }

      // push to the new peg
      //
      switch (to_peg) {
      case 1:
        t_peg_name = pa->name;
        stack_push(pa, disk);
        break;
      case 2:
        t_peg_name = pb->name;
        stack_push(pb, disk);
        break;
      case 3:
        t_peg_name = pc->name;
        stack_push(pc, disk);
        break;
      default:
        break;
      }

      mv_stack_count++; // counter for number of moves increment
      printf("Move disk %d from peg %c to peg %c\n", disk, f_peg_name,
             t_peg_name);
      temp = from_peg; // store the peg that move from last time
    } else {
      // the other disk should move as the direction of the first disk:
      // clockwise or counter clockwise
      //
      from_peg = pos[disk - 1];
      to_peg = 6 - pos[0] - pos[disk - 1];

      // pop from the original peg
      switch (from_peg) {
      case 1:
        f_peg_name = pa->name;
        stack_pop(pa);
        break;
      case 2:
        f_peg_name = pb->name;
        stack_pop(pb);
        break;
      case 3:
        f_peg_name = pc->name;
        stack_pop(pc);
        break;
      default:
        break;
      }

      // push to the new peg
      switch (to_peg) {
      case 1:
        t_peg_name = pa->name;
        stack_push(pa, disk);
        break;
      case 2:
        t_peg_name = pb->name;
        stack_push(pb, disk);
        break;
      case 3:
        t_peg_name = pc->name;
        stack_push(pc, disk);
        break;
      default:
        break;
      }

      mv_stack_count++; // counter for number of moves increment
      printf("Move disk %d from peg %c to peg %c\n", disk, f_peg_name,
             t_peg_name);
    }
    pos[disk - 1] = to_peg; // upate the position of the disk
  }
}

void prt_mv(int n, char a, char b) {
  // print movement and let the couter++
  printf("Move disk %d from peg %c to peg %c\n", n, a, b);
  mv_rec_count += 1;
}

void move_rec(int n, char a, char b, char c) {
  if (n == 1) {
    // base situation
    prt_mv(n, a, b);
  } else {
    // recursive situation
    move_rec(n - 1, a, c, b);
    prt_mv(n, a, b);
    move_rec(n - 1, c, b, a);
  }
}
