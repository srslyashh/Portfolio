#include "Node.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <exception>

/******************************************************
** Function : Node()
** Description: initialize Node() - default constructor
** Input: none
** Output: initialized members of node
******************************************************/
Node::Node()
{
    val = 0;
    next = NULL;
}

/******************************************************
** Function : Node(int)
** Description: initialize Node(int) - parameterized constructor
** Input: int
** Output: initialized members of node
******************************************************/
Node::Node(int value)
{
    val = value;
    next = NULL;
}

/******************************************************
** Function : setNext(Node *nextptr)
** Description: set next 
** Input: Node *nextptr
** Output: next is changed to nextptr.
******************************************************/
void Node::setNext(Node *nextptr)
{
    next = nextptr;
}

/******************************************************
** Function : Node* getNext()
** Description: get next 
** Input: none
** Output: return next
******************************************************/
Node* Node::getNext()
{
    return next;
}