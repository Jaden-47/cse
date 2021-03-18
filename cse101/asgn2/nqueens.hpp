#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class nqueens
{
public:
  int columns;
  int cnt;                      // the column/row size of the board
  int *column;                  // the index means the column,and the value means the
                                // row, -1 means did not exist
  stack<class nqueens> q_stack; // using as recursion to store the class value in each loop
  nqueens();                    // default constructor, never used
  nqueens(int i);               // construct a board with i*i size
  void insert(int i, int k);    // insert a queen to the given place
  bool is_valid(int i);         // determine the new queen is in valid in ith column
  bool all_valid();             // return whether there is space for more queen
  bool find();                  // find all the solutions and fill in the list, return true if find solutions
  void ptr_copy(int *, int *);  // deep copy the two pointer
  string print();               // print the whole board only with queen on
  void del();                   // delete the the nqueens
};