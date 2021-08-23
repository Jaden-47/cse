// shell.h - Contains the function declarations for the shell sort
//

#ifndef __SHELL_H__
#define __SHELL_H__

#include <inttypes.h>

// counter for compares and moves
//
int move_shell, com_shell;

//
// do the shell sort for an array
//
// n: the length of the array
//
void shell(uint32_t *array, int n);

#endif
