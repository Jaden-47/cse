/*
 * @Author: your name
 * @Date: 2021-01-26 20:58:15
 * @LastEditTime: 2021-01-26 21:48:22
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /asgn1/ll.cpp
 */

// Filename: ll.cpp
//
// Contains the class LinkedList that represents a linked list. This contains some basic operations, such as insert, delete, find, length
//
// Japheth Frolick, August 2019
// C. Seshadhri, Jan 2020

#include "ll.hpp"

// Default constructor sets head and tail to null
LinkedList ::LinkedList()
{
    head = NULL;
}

// Insert(int val): Inserts the int val into list, at the head of the list. Note that there may be multiple copies of val in the list.
// Input: Int to insert into the linked list
// Output: Void, just inserts new Node
// Simply calls recursive function
void LinkedList ::insert(string val)
{
    Node *to_add = new Node; // creates new Node
    to_add->cnt = 1;
    to_add->data = val;  // sets the data to hold input val
    to_add->next = head; // make to_add point to existing head
    head = to_add;       // set head to to_add
}

// find(int val): Finds a Node with data "val"
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Just a wrapper to recursive function
Node *LinkedList ::find(string val)
{
    return find(val, head); // just call recursive function
}

// find(int val, Node* curr): Finds a Node with data "val", at list starting from curr
// Input: string to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Technically, it finds the first Node in the list containing val
Node *LinkedList ::find(string val, Node *curr)
{
    // curr will look over list. At every iteration, we will check if curr->data is val. If so, we are done. Otherwise, we proceed through the list.
    while (curr != NULL) //looping over list
    {
        if (curr->data == val) // found val, so return curr
            return curr;
        curr = curr->next; // otherwise, proceed through list
    }
    // if loop terminates, val not found
    return NULL;
}

// deleteNode(int val): Delete a Node with data val, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. If there are multiple Nodes with val, only the first Node in the list is deleted.
Node *LinkedList ::deleteNode(string val)
{
    return deleteNode(val, NULL, head); // recursive call. We set prev to NULL, and curr to head
}

// deleteNode(int val, Node* prev, Node* curr): Delete a Node with data val  from the list starting *with* curr. prev stores pointer of previous node, to aid deletion
// Note that we cannot delete curr, so we only look at the list after that. If no node is found, return NULL.
// Input: string to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. If there are multiple Nodes with val, only the first Node in the list is deleted.
Node *LinkedList ::deleteNode(string val, Node *prev, Node *curr)
{
    if (curr == NULL) // base case, val not found, no more list left
        return NULL;
    if (curr->data == val) // val is found! Now for the case analysis
    {
        if (prev == NULL)
        { // prev was supposed to be pointer of previous node. Since prev is NULL, curr is the head
            delete (head);
            head = head->next; // delete head
        }
        else
        {
            delete (curr);
            prev->next = curr->next; // delete curr from the list, by "skipping" over curr
        }
        return curr; // returning node with val
    }
    return deleteNode(val, curr, curr->next); // proceed one step in the list
}

// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list
void LinkedList ::deleteList()
{
    deleteList(head);
}

// deleteList(curr): Deletes every Node of list starting from curr to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list starting from curr
void LinkedList ::deleteList(Node *curr)
{
    if (curr == NULL) // base case, empty list
        return;
    Node *nextNode = curr->next; // store next node
    delete (curr);               // delete current node
    deleteList(nextNode);        // recursive call
}

// Prints list in order
// Input: None
// Output: string that has all elements of the list in order
string LinkedList ::print()
{
    string to_return = print(head);
    if (to_return.length() > 0) // non-empty string, has extra space at end
        to_return.pop_back();   // delete last character
    return to_return;
}

// print(Node *curr): Prints list in order, starting from curr
// Input: None
// Output: string that has all elements of the list in order
string LinkedList ::print(Node *curr)
{
    if (curr == NULL) // base case, empty list
        return "";    // return empty string
    return "data: " + curr->data + " cnt: " + to_string(curr->cnt) + "\n" + print(curr->next);
}

// Computes the length of the linked list
// Input: None
// Output: Int, length of list
int LinkedList ::length()
{
    return length(head); // recursive call
}

// length(Node *curr): Computes the length of the linked list, starting from curr
// Input: None
// Output: Int, length of list
int LinkedList ::length(Node *curr)
{
    if (curr == NULL) // base case
        return 0;
    return 1 + length(curr->next); // recursive call
}

// sortList(): Sort the list as the value of "cnt" in decending rank
// Input: None
// Output: None
void LinkedList ::sortList()
{
    return sortList(head, NULL, NULL, NULL);
}

// sortList(Node*): Sort the list as the value of "cnt" in decending rank
// Input: None
// Output: None
void LinkedList ::sortList(Node *curr, Node *prev, Node *next, Node *tail)
{
    if (head == NULL || head->next == NULL)
    {
        return;
    }
    if (head->cnt < head->next->cnt)
    {
        Node *temp = new Node;
        temp->cnt = head->cnt;
        temp->data = head->data;
        temp->next = head->next->next;
        delete (head);
        head = head->next;
        head->next = temp;
    }
    if (head->next->next == NULL)
    {
        return;
    }
    else
    {
        while (head->next != tail)
        {
            curr = head;
            for (prev = curr, curr = prev->next, next = curr->next; next != tail; prev = prev->next, curr = curr->next, next = next->next)
            {

                if (curr->cnt <= next->cnt)
                {
                    if (curr->cnt == next->cnt && curr->data < next->data)
                    {
                        goto out1;
                    }
                    prev->next = next;
                    curr->next = next->next;
                    next->next = curr;
                    Node *temperary = curr;
                    curr = next;
                    next = temperary;
                }
            out1:;
            }
            tail = curr;
            if (head->cnt <= head->next->cnt)
            {
                if (head->cnt == head->next->cnt && head->data < head->next->data)
                {
                    goto out2;
                }
                Node *temp1 = new Node;
                temp1->cnt = head->cnt;
                temp1->data = head->data;
                temp1->next = head->next->next;
                delete (head);
                head = head->next;
                head->next = temp1;
            }
        out2:;
        }
    }
}

// findNodeRank(Node *curr): Computes the length of the linked list, starting from curr
// Input: string: the start charcter, int:the nth rank
// Output: the node we find, if not find, return NULL
Node *LinkedList ::findNodeRank(int rank)
{
    Node *tempNode = head;
    for (int temp = 0; temp < rank; temp++)
    {
        if (tempNode == NULL)
        {
            return NULL;
        }
        tempNode = tempNode->next;
    }
    return tempNode;
}

// reverse(Node *curr): reverse the linked list
// Input: None
// Output: the reverrsed list head node
void LinkedList ::reverse()
{
    return reverse(NULL, head);
}

// reverse(Node *curr): reverse the linked list
// Input: prev node and current node
// Output: the reverrsed list head node
void LinkedList::reverse(Node *prev, Node *curr)
{
    Node *temp;
    while (curr)
    {
        temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    head = prev;
    return;
}

// rotate(Node *curr): rotate the list with given node as start
// Input: the string node need to be the new beginning node
// Output: None
void LinkedList::rotate(string data)
{
    Node *curr = head, *prev = NULL;
    while (curr != NULL)
    {
        if(curr->data == data){
            head=curr;
            while(curr->next){
                curr = curr->next;
            }
            curr->next = prev;
            if(prev!=NULL){
            prev->next = NULL;
            }
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    return;
}

// rotate(int n): rotate the list with nth node as start
// Input: the string node need to be the new beginning node
// Output: None
void LinkedList::rotate(int n)
{
    if(!n){
        return;
    }
    Node *curr = head,*prev=NULL;
    for (int k=0;k<n;k++){
        if(curr==NULL){
            return;
        }
        prev=curr;
        curr=curr->next;
    }
    prev->next=NULL;
    prev=head;
    head=curr;
    while(curr->next){
        curr = curr->next;
    }
    curr->next = prev;
}

// palindrome(): return the whether the list is palindrome
// Input: None
// Output: True or false whether list is palindrome
bool LinkedList ::palindrome(){
    return palindrome(head);
}


// palindrome(Node *curr): return the whether the list is palindrome
// Input: The first node of the list
// Output: True or false whether list is palindrome
bool LinkedList ::palindrome(Node *){
    return true;
}

// deletelast(Node *curr): return the appearance of the node
// Input: The first node of the list
// Output: True or false whether list is palindrome
Node deletelast(Node *curr); // delete the last node that appear