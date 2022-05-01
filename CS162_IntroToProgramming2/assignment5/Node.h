#ifndef NODE_H
#define NODE_H

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

using namespace std;

class Node
{
    public:
        int val;
        Node *next;
        Node();
        Node(int);
        void setNext(Node *);
        Node* getNext();
};


#endif