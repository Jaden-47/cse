// Filename: bst.cpp
//
// Contains the class BST that represents a binary search tree. This contains some basic operations, such as insert, delete, find, and printing in various traversal orders
//
// C. Seshadhri, Jan 2020

#include "bst.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

// Default constructor sets head and tail to null
BST ::BST()
{
    root = NULL;
}

// Insert(int val): Inserts the int val into tree, at the head of the list. Note that there may be multiple copies of val in the list. Just calls the recursive function
// Input: Int to insert into the BST
// Output: Void, just inserts new Node
void BST::insert(string val)
{
    Node *to_insert = new Node(val); // create a new Node with the value val
    if (find(val))
    {
        return;
    }
    root = insert(root, to_insert); // make call to recursive insert, starting from root
    //cout<<"root:"<<root->right->key<<endl;
    return;
}

// insert(Node* start, Node* to_insert): Inserts the Node to_insert into tree rooted at start. We will always call with start being non-null. Note that there may be multiple copies of val in the list.
// Input: Int to insert into the subtree
// Output: Void, just inserts new Node
Node *BST::insert(Node *start, Node *to_insert)
{
    if (start == NULL)
    {
        start = to_insert;
        return start;
    }

    if (to_insert->key < start->key)
    {
        start->sizes++;
        to_insert->parent = start;
        start->left = insert(start->left, to_insert);
    }
    if (to_insert->key > start->key)
    {
        start->sizes++;
        to_insert->parent = start;
        start->right = insert(start->right, to_insert);
    }
    start->height = (get_height(start->left) > get_height(start->right)) ? get_height(start->left) + 1 : get_height(start->right) + 1;

    int factor = get_balence_factor(start);
    //cout << "factor:" << factor <<" start:"<<start->key<< endl;
    if (factor > 1 && get_balence_factor(start->left) >= 0) // LL: right rotate
    {
        //cout << "LL:" << start->key << endl;
        return right_rotate(start);
    }
    else if (factor < -1 && get_balence_factor(start->right) <= 0) // RR: left rotate
    {
        //cout << "RR:" << start->key << endl;
        return left_rotate(start);
    }
    else if (factor > 1 && get_balence_factor(start->left) <= 0) // LR: first left, then right rotate
    {
        //cout << "LR:" << start->key << endl;
        start->left = left_rotate(start->left);
        return right_rotate(start);
    }
    else if (factor < -1 && get_balence_factor(start->right) >= 0) // RL: first right, then left rotate
    {
        //cout << "RL:" << start->key << endl;
        start->right = right_rotate(start->right);
        //cout<<printInOrder()<<endl;
        return left_rotate(start);
    }
    //cout<<1;
    return start;
}
// void left_rotate(Node*): left rotate the tree to keep the AVL feature
// Input: the root node of the subtree
// Output: None
Node *BST::left_rotate(Node *start)
{
    Node *right = start->right;
    Node *right_left = right->left;

    right->left = start;
    right->parent = start->parent;

    start->right = right_left;
    start->parent = right;

    if (right_left)
    {
        start->sizes += right_left->sizes;
        right->sizes--;
        right_left->parent = start;
    }

    start->sizes = start->sizes - right->sizes - 1;

    right->sizes = start->sizes + 1;
    if (right->right)
    {
        right->sizes += right->right->sizes + 1;
    }

    start->height = (get_height(start->left) > get_height(start->right)) ? get_height(start->left) + 1 : get_height(start->right) + 1;
    right->height = (get_height(right->left) > get_height(right->right)) ? get_height(right->left) + 1 : get_height(right->right) + 1;
    //cout<<"right:"<<right->sizes<<endl;
    return right;
}

// void right_rotate(Node*): right rotate the tree to keep the AVL feature
// Input: the root node of the subtree
// Output: None
Node *BST::right_rotate(Node *start)
{
    Node *left = start->left;
    Node *left_right = left->right;

    left->right = start;
    left->parent = start->parent;

    start->left = left_right;
    start->parent = left;

    if (left_right)
    {
        start->sizes += left_right->sizes;
        left->sizes--;
        left_right->parent = start;
    }
    start->sizes = start->sizes - left->sizes - 1;

    left->sizes = start->sizes + 1;
    if (left->left)
    {
        left->sizes += left->left->sizes + 1;
    }

    start->height = (get_height(start->left) > get_height(start->right)) ? get_height(start->left) + 1 : get_height(start->right) + 1;
    left->height = (get_height(left->left) > get_height(left->right)) ? get_height(left->left) + 1 : get_height(left->right) + 1;
    //cout<<"left:"<<left->sizes<<endl;
    return left;
}

// find(int val): Finds a Node with key "val"
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Technically, it finds the first Node with val, at it traverses down the tree
Node *BST ::find(string val)
{
    return find(root, val); // call the recursive function starting at root
}

// find(Node* start, int val): Recursively tries to find a Node with key "val", in subtree rooted at val
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Technically, it finds the first Node with val, at it traverses down the tree
Node *BST ::find(Node *start, string val)
{
    if (start == NULL || start->key == val) // tree is empty or we found val
        return start;
    if (val < start->key) // val is smaller, so go left
        return find(start->left, val);
    else // val is larger, so go right
        return find(start->right, val);
}

// minNode(Node* start): gets the minimum Node in subtree rooted at start
// Input: Pointer to subtree root
// Output: pointer to the minimum node in the subtree
Node *BST ::minNode(Node *start)
{
    if (start == NULL) // typically, this should not happen. But let's return the safe thing
        return NULL;
    if (start->left == NULL) // Base case: we have found the minimum
        return start;
    else
        return minNode(start->left); // recursive call in left subtree
}

// maxNode(Node* start): gets the maximum Node in subtree rooted at start
// Input: Pointer to subtree root
// Output: pointer to the maximum node in the subtree
Node *BST ::maxNode(Node *start)
{
    if (start == NULL) // typically, this should not happen. But let's return the safe thing
        return NULL;
    if (start->right == NULL) // Base case: we have found the maximum
        return start;
    else
        return maxNode(start->right); // recursive call in left subtree
}

// deleteNode(int val): Delete a Node with key val, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. If there are multiple Nodes with val, only the first Node in the list is deleted.
Node *BST ::deleteKey(string val)
{
    return deleteNode(find(val)); // get a node with the value and delete that node
}

// deleteNode(Node* to_delete): Delete the input node, and return pointer to the deleted node. The node will be isolated from the tree, to prevent memory leaks
// Input: Node to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL.
Node *BST ::deleteNode(Node *to_delete)
{
    if (to_delete == NULL) // val not present in tree, so return NULL
        return NULL;

    bool isRoot = (to_delete == root) ? true : false; // determine if node to delete is root
    bool isLeftChild = false;
    if (!isRoot)                                                             // if this is not the root
        isLeftChild = (to_delete->parent->left == to_delete) ? true : false; // determine if node is left child of parent. Note that line throws error iff to_delete is root

    bool isDeleted = false; // convenient flag for writing code

    // if to_delete's left child is NULL, then we can splice this node off. We set the appropriate
    // pointer of the parent to the right child of to_delete
    if (to_delete->left == NULL)
    {
        //         cout << "left is null, isLeftChild is "+to_string(isLeftChild) << endl;
        //         cout << "parent is "+to_string(to_delete->parent->key) << endl;
        if (isRoot) // if deleting root, then we reset root
        {
            root = to_delete->right;
            if (root != NULL)
                root->parent = NULL; // set parent to be NULL
        }
        else
        {
            if (isLeftChild)                                  // node is left child of parent
                to_delete->parent->left = to_delete->right;   // setting left child of parent to be right child of node
            else                                              // node is right child of parent
                to_delete->parent->right = to_delete->right;  // setting right child of parent to be right child of node
            if (to_delete->right != NULL)                     // to_delete is not a leaf
                to_delete->right->parent = to_delete->parent; // update parent of the child of the deleted node, to be parent of deleted node
        }
        isDeleted = true; // delete is done
    }
    // suppose node is not deleted yet, and it's right child is NULL. We splice off as before, by setting parent's child pointer to to_delete->left
    if (!isDeleted && to_delete->right == NULL)
    {
        if (isRoot) // if deleting root, then we reset root
        {
            root = to_delete->left;
            if (root != NULL)
                root->parent = NULL; // set parent to be NULL
        }
        else
        {
            if (isLeftChild)                                 // node is left child of parent
                to_delete->parent->left = to_delete->left;   // setting left child of parent to be left child of node
            else                                             // node is right child of parent
                to_delete->parent->right = to_delete->left;  // setting right child of parent to be left child of node
            if (to_delete->left != NULL)                     // to delete is not a leaf
                to_delete->left->parent = to_delete->parent; // update parent of the child of deleted node, to be parent of deleted node
        }
        isDeleted = true; // delete is done
    }
    if (isDeleted) // so node has been deleted
    {
        to_delete->left = to_delete->right = NULL;
        return to_delete;
    }

    // phew. The splicing case is done, so now for the recursive case. Both children of to_delete are not null, so we replace the data in to_delete by the successor. Then we delete the successor node
    // first, get the minimum node of right subtree
    Node *succ = minNode(to_delete->right);
    to_delete->key = succ->key;
    //     cout << "Replacing with "+to_string(succ->key) << endl;
    return deleteNode(succ); // make recursive call on succ. Note that succ has one null child, so this recursive call will terminate without any other recursive calls
}

// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list
void BST ::deleteBST()
{
    deleteBST(root);
}

// Deletes every Node in subtree rooted at startto prevent memory leaks.
// Input: Node* start
// Output: Void, just deletes every Node of the list
void BST ::deleteBST(Node *start)
{
    if (start == NULL) // tree is already empty
        return;
    deleteBST(start->left);  // delete left subtree
    deleteBST(start->right); // delete right subtree
    delete (start);          // delete node itself
}

// Prints tree in order. Calls the recursive function from the root
// Input: None
// Output: string that has all elements of the tree in order
string BST ::printInOrder()
{
    return printInOrder(root);
}

// Prints tree Preorder. Calls the recursive function from the root
// Input: None
// Output: string that has all elements of the tree pre order
string BST ::printPreOrder()
{
    return printPreOrder(root);
}

// Prints tree Postorder. Calls the recursive function from the root
// Input: None
// Output: string that has all elements of the tree post order
string BST ::printPostOrder()
{
    return printPostOrder(root);
}

// Prints rooted subtree tree in order, by making recursive calls
// Input: None
// Output: string that has all elements of the rooted tree in order
string BST ::printInOrder(Node *start)
{
    if (start == NULL) // base case
        return "";     // return empty string
    string leftpart = printInOrder(start->left);
    string rightpart = printInOrder(start->right);
    string output = start->key + "size:" + to_string(start->sizes);
    /*
    if(start->parent){
        output+=" parent:"+start->parent->key;
    }
    */
    if (leftpart.length() != 0)            // left part is empty
        output = leftpart + " " + output;  // append left part
    if (rightpart.length() != 0)           // right part in empty
        output = output + " " + rightpart; // append right part
    return output;
}

// Prints rooted subtree tree preorder, by making recursive calls
// Input: None
// Output: string that has all elements of the rooted tree preorder
string BST ::printPreOrder(Node *start)
{
    if (start == NULL) // base case
        return "";     // return empty string
    string leftpart = printPreOrder(start->left);
    string rightpart = printPreOrder(start->right);
    string output = start->key;
    if (leftpart.length() != 0)            // left part is empty
        output = output + " " + leftpart;  // append left part
    if (rightpart.length() != 0)           // right part in empty
        output = output + " " + rightpart; // append right part
    return output;
}

// Prints rooted subtree tree postorder, by making recursive calls
// Input: None
// Output: string that has all elements of the rooted tree in post order
string BST ::printPostOrder(Node *start)
{
    if (start == NULL) // base case
        return "";     // return empty string
    string leftpart = printPostOrder(start->left);
    string rightpart = printPostOrder(start->right);
    string output = start->key;
    if (rightpart.length() != 0)           // right part is empty
        output = rightpart + " " + output; // append left part
    if (leftpart.length() != 0)            // left part in empty
        output = leftpart + " " + output;  // append right part
    return output;
}

string BST ::printInOrder(string begin, string last)
{
    return printInOrder(root, begin, last);
}

string BST::printInOrder(Node *start, string begin, string last)
{
    if (start == NULL) // base case
        return "";     // return empty string
    string leftpart, rightpart, output;
    if (begin < start->key)
    {
        //cout<<"start:"<<start->key<<" begin:"<<begin<<endl;
        leftpart = printInOrder(start->left, begin, last);
        //cout<<"start:"<<start->key<<" leftpart:"<<leftpart<<endl;
    }
    if (last > start->key)
    {
        //cout<<"start:"<<start->key<<" last:"<<last<<endl;
        rightpart = printInOrder(start->right, begin, last);
        //cout<<"start:"<<start->key<<" rightpart:"<<rightpart<<endl;
    }

    if (begin <= start->key && last >= start->key)
    {
        output = start->key;
        //cout<<output<<endl;
        if (leftpart.length() != 0)            // left part is empty
            output = leftpart + " " + output;  // append left part
        if (rightpart.length() != 0)           // right part in empty
            output = output + " " + rightpart; // append right part
        //cout<<"final output:"<<output<<endl;
        return output;
    }
    output = leftpart + rightpart;
    //cout<<"final output:"<<output<<endl;
    return output;
}

int BST::range(string begin, string last)
{
    return range(root, begin, last);
}

int BST::range(Node *start, string begin, string last)
{
    if (!start)
    {
        return 0;
    }

    if (begin > start->key)
    {
        return range(start->right, begin, last);
    }

    if (last < start->key)
    {
        return range(start->left, begin, last);
    }

    //cout << "start:" << start->key << " begin:" << begin << endl;
    int output = 0;
    int a = 0;
    if (start->parent)
    {
        if (start->parent->key <= last && start->parent->key >= begin && start->parent->left == start)
        {
            if (start->right)
            {
                //cout << "start:" << start->key << " right:" << start->right->key << " sizes:" << start->right->sizes << endl;
                output = start->right->sizes + 1;
                goto left1;
            }
        }
    }
    
    if (start->parent)
    {
        if (start->parent->key <= last && start->parent->key >= begin && start->parent->right == start)
        {
            if (start->left)
            {
                //cout << "start:" << start->key << " right:" << start->right->key << " sizes:" << start->right->sizes << endl;
                output = start->left->sizes + 1;
                a = 1;
            }
        }
    }
    output += range(start->right, begin, last);
left1:
    if (a == 0)
    {
        output += range(start->left, begin, last);
    }

    return ++output;
}

int BST::get_height(Node *n)
{
    if (!n)
    {
        return 0;
    }
    return n->height;
}

int BST::get_balence_factor(Node *start) // get the balence factor of the tree start with the node
{
    if (!start)
    {
        return 0;
    }
    return get_height(start->left) - get_height(start->right);
}

bool BST::is_balenced() // tell whether the tree is balenced
{
    return is_balenced(root);
}

bool BST::is_balenced(Node *start) // tell whether the tree start with the node is balenced
{
    if (!start)
    {
        return true;
    }
    if (get_balence_factor(start) > 1 || get_balence_factor(start) < 1)
    {
        return false;
    }
    return is_balenced(start->left) && is_balenced(start->right);
}

Node *BST ::lca(string a, string b) // getting the lca of two ints. Just a wrapper for real recursion function
{
    if (find(a) && find(b))
    {
        return lca(root, a, b);
    }
    else
    {
        return NULL;
    }
}

Node *BST ::lca(Node *start, string a, string b) // the lca of two ints, in subtree rooted at Node*. Works by recursion
{
    if (a < start->key && b < start->key)
    {
        return lca(start->left, a, b);
    }
    else if (a > start->key && b > start->key)
    {
        return lca(start->right, a, b);
    }
    else
    {
        return start;
    }
}

int BST ::width() // return the largest non-null node amount in the same level.
{
    // 求height可用max和min的parent次数最大值
    /*
getMaxWidth(tree)
maxWdth = 0
for i = 1 to height(tree)
  width =   getWidth(tree, i);
  if(width > maxWdth) 
      maxWdth  = width
return maxWidth
*/
    return 0;
}

int BST ::width(Node *start, string level) // return the largest non-null node amount in the same level.
{
    /*
if tree is NULL then return 0;
if level is 1, then return 1;  
else if level greater than 1, then
    return getWidth(tree->left, level-1) + 
    getWidth(tree->right, level-1);
    */
    return 0;
}