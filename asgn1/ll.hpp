#ifndef __LL_HPP__
#define __LL_HPP__

#ifndef NIL
#define NIL (void *)0
#endif

#include <string>

using namespace std;

// the following line 13 to line 37 codes are from codio box prep:linkedlist folder

struct Node
{
	string data;
	Node *next;
};

class LinkedList
{
	private:
		Node *head; // Stores head of linked list
	public:
		LinkedList(); // Default constructor sets head to null
        void insert(string); // insert int into list 
        Node* find(string); // find int in list, and return pointer to node with that int. If there are multiple copies, this only finds one copy
        Node* find(string, Node*); // recursive find 
        Node* deleteNode(string); // remove a node with int (if it exists), and return pointer to deleted node. This does not delete all nodes with the value.
        Node* deleteNode(string, Node*, Node*); // recursive remove
		void deleteList(); // deletes every node to prevent memory leaks, and frees memory
		void deleteList(Node*); // recursive delete 
		string print(); // Construct string with data of list in order 
		string print(Node*); // recursive construct string
		int length(); // Returns the length of the linked list
		int length(Node*); // recursive length computation
};

#endif