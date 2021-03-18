#ifndef __LL_HPP__
#define __LL_HPP__

#ifndef NIL
#define NIL (void *)0
#endif

#include <string>
#include <iostream>

using namespace std;

// the following line 13 to line 37 codes are from codio prep:linkedlist folder

struct Node
{
	int cnt;
	string data;
	Node *next;
};

class LinkedList
{
private:
	Node *head; // Stores head of linked list
public:
	LinkedList();							  // Default constructor sets head to null
	void insert(string);					  // insert int into list
	Node *find(string);						  // find string in list, and return pointer to node with that string. If there are multiple copies, this only finds one copy
	Node *find(string, Node *);				  // recursive find
	Node *deleteNode(string);				  // remove a node with int (if it exists), and return pointer to deleted node. This does not delete all nodes with the value.
	Node *deleteNode(string, Node *, Node *); // recursive remove
	void deleteList();						  // deletes every node to prevent memory leaks, and frees memory
	void deleteList(Node *);				  // recursive delete
	string print();							  // Construct string with data of list in order
	string print(Node *);					  // recursive construct string
	int length();							  // Returns the length of the linked list
	int length(Node *);						  // recursive length computation
	void sortList();						  // sorting the list as decending rank of cnt, easy to use
	void sortList(Node *, Node *, Node *);	  // sorting the list as decending rank of cnt 
	Node *findNodeRank(int);				  // find the nth frequent string in the list
	void reverse();							  // reverse the linked list
	void reverse(Node *, Node *);			  // reverse the linked list
	void rotate(string);					  // rotate the list with given string node as start
	void rotate(int);						  // rotate the list with n steps
	bool palindrome();						  // check if the list is palindrome
	bool palindrome(Node *);				  // check if the list is palindrome
	Node deletelast(string);				  // delete the last node that appear
};

#endif