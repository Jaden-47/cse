// Filename: stackrecursion.cpp
//
// The file basically contains two functions that generate all subsequences of
// an input string. One function is the (standard) recursive method,
// while the other is non-recursive and uses a stack. Both these functions have
// an identical output, and create a (linked) list of strings as their output.
//
// The code uses the List data structure used in a number of CSE101 assignments
// and tests.
//
// USAGE:  (the executable is generated by a Makefile)
//     ./stackrecursion <INPUT FILE> <OUTPUT FILE>
//
//     Only the first line of <INPUT FILE> is read, as a string. <OUTPUT FILE>
//     contains all subsequences, each in a separate line.
//
//
// C. Seshadhri, Jan 2020, Oct 2020

#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "nqueens.hpp"
using namespace std;

nqueens::nqueens()
{
  columns = 0;
  cnt = 0;
}

nqueens::nqueens(int i)
{
  columns = i;
  cnt = 0;
  column = (int *)calloc(columns, sizeof(int));
  for (int j = 0; j < i; j++)
  {
    column[j] = -1;
  }
}

bool nqueens::insert(int i, int k)
{
  if (column[i] == -1)
  {
    column[i] = k;
    return true;
  }
  else
  {
    return false;
  }
}

bool nqueens::is_valid(int i)
{
  for (int k = 0; k < columns; k++)
  {
    if (column[k] == column[i] || abs(k - i) == abs(column[k] - column[i]))
    {
      if (k == i || column[k] == -1)
      {
        continue;
      }
      return false;
    }
  }
  return true;
}

bool nqueens::all_valid()
{
  for (int i = 0; i < columns; i++)
  {
    if (column[i] == -1 || !(is_valid(i)))
    {
      return false;
    }
  }
  return true;
}

bool nqueens::now_valid()
{
  for (int i = 0; i < columns; i++)
  {
    if (column[i] >= 0)
    {
      for (int k = i + 1; k < columns; k++)
      {
        if (column[i] == column[k] || abs(k - i) == abs(column[k] - column[i]))
        {
          return false;
        }
      }
    }
  }
  return true;
}

void nqueens::ptr_copy(int *i, int *j)
{
  for (int k = 0; k < columns; k++)
  {
    i[k] = j[k];
  }
  return;
}

bool nqueens::find()
{
  nqueens init = nqueens(columns);
  nqueens stacktop = nqueens(columns);
  init.columns = columns;
  init.ptr_copy(init.column, column);
  q_stack.push(init);
  while (!q_stack.empty())
  {
    stacktop = q_stack.top();
    q_stack.pop();
    if (stacktop.cnt == stacktop.columns)
    {
      ptr_copy(column, stacktop.column);
      goto last;
    }
    if (stacktop.column[stacktop.cnt] == -1)
    {
      for (int j = 0; j < columns; j++)
      {
        stacktop.column[stacktop.cnt] = j;

        if (stacktop.is_valid(stacktop.cnt))
        {
          nqueens to_push = nqueens(columns);
          to_push.columns = columns;
          to_push.ptr_copy(to_push.column, stacktop.column);
          to_push.cnt = stacktop.cnt + 1;
          q_stack.push(to_push);
        }
      }
      goto end;
    }
    if (!stacktop.is_valid(stacktop.cnt))
    {
      return false;
    }
    stacktop.cnt += 1;
    q_stack.push(stacktop);
  end:;
  }
last:
  if (stacktop.all_valid())
  {
    return true;
  }
  else
  {
    return false;
  }
}

string nqueens::print()
{
  string result = "";
  for (int i = 0; i < columns; i++)
  {
    if (column[i] != -1)
    {
      result = result + to_string(i + 1) + " " + to_string(column[i] + 1) + " ";
    }
  }
  return result;
}

void nqueens::del()
{
  free(column);
  return;
}