// Filename: bst.h
//
// Header file for the class BST that represents a binary search tree
//
// C. Seshadhri, Jan 2020

#ifndef BST_H
#define BST_H

#include <string>

using namespace std;

// node struct to hold data
class Node
{
public:
    string key;
    Node *left, *right, *parent;
    int height;
    int sizes;

    Node() // default constructor
    {
        left = right = parent = NULL; // setting everything to NULL
        height = 0;
        sizes = 0;
    }

    Node(string val) // constructor that sets key to val
    {
        key = val;
        left = right = parent = NULL; // setting everything to NULL
        height = 1;
        sizes = 0;
    }
};

class BST
{
private:
    // Stores root of tree
public:
    Node *root;
    BST();                                                       // Default constructor sets root to null
    void insert(string);                                         // insert int into list
    Node *insert(Node *, Node *);                                // recursive version that inserts a node
    Node *left_rotate(Node *);                                   // left rotate the tree
    Node *right_rotate(Node *);                                  // right rotate the tree
    Node *find(string);                                          // find int in tree, and return pointer to node with that int. If there are multiple copies, this only finds one copy
    Node *find(Node *, string);                                  // recursive version that finds in a rooted subtree
    Node *minNode(Node *);                                       // gets minimum node in rooted subtree
    Node *maxNode(Node *);                                       // gets maximum node in rooted subtree
    Node *deleteKey(string);                                     // remove a node with int (if it exists), and return pointer to deleted node. This does not delete all nodes with the value.
    Node *deleteNode(Node *);                                    // try to delete node pointed by argument. This also returns the node, isolated from the tree.
    void deleteBST();                                            // deletes every node to prevent memory leaks, and frees memory
    void deleteBST(Node *start);                                 // deletes every Node in subtree rooted at startto prevent memory leaks.
    string printInOrder();                                       // Construct string with tree printed InOrder
    string printInOrder(Node *start);                            // Construct string with rooted subtree printed InOrder
    string printInOrder(string begin, string last);              // Construct string start within the range of start and end string printed InOrder
    string printInOrder(Node *start, string begin, string last); // Construct string start within the range of start and end string printed InOrder. Works by recursion.
    string printPreOrder();                                      // Construct string with tree printed PreOrder
    string printPreOrder(Node *start);                           // Construct string with rooted subtree printed PreOrder
    string printPostOrder();                                     // Construct string with tree printed PostOrder
    string printPostOrder(Node *start);                          // Construct string with rooted subtree printed PostOrder
    int range(string begin, string last);                        // get the number of strings in the range from begin to last
    int range(Node *start, string begin, string last);           // get the number of strings in the range from begin to last. Works by recursion.
    int get_height(Node *);                                      // get the height of the node
    int get_balence_factor(Node *);                              // get the balence factor of the tree start with the node
    bool is_balenced();                                          // tell whether the tree is balenced
    bool is_balenced(Node *);                                    // tell whether the tree start with the node is balenced
    Node *lca(string, string);                                   // getting the lca of two ints. Just a wrapper for real recursion function
    Node *lca(Node *, string, string);                           // the lca of two ints, in subtree rooted at Node*. Works by recursion
    int width();                                                 // return the largest non-null node amount in the same level.
    int width(Node *, string);                                   // return the width in this level
};

#endif
