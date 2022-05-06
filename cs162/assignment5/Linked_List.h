#ifndef LINKED_LIST_H
#define LINKED_LIST_H

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

using namespace std;

class Linked_List 
{
    private:
        unsigned int length; 
        Node *head; 
        int mode;
        unsigned int primeNum;
    public:
        int get_length();
        void print(); 
        void clear(); 
        unsigned int push_front(int); 
        unsigned int push_back(int); 
        unsigned int insert(int val, unsigned int index); 
        void sort_ascending(); 
        void sort_descending(); 

        // extra functions:
        Linked_List();
        int addMore();
        void moreMembers();
        void sortQ();
        void loopChar(string&, int&, int);
        int checkChar(string&, int&, int);
        void firstQ();
        void loopInput(string&, int&, int, int);
        int checkInput(string, int, int);
        int checkInputTwo(int, int, int);
        int checkCharTwo(string&, int&, int);
        void initialQ();
        void recursiveMS(Node **);
        Node* recursiveSS(Node *);
        void divide(Node *, Node **, Node **);
        Node* mergeLL(Node *, Node *);
        void swapPlaces(Node **, Node *, Node *, Node *);
        void swappy(Node* , Node*);
        unsigned int push_middle(int, int);
        void printPrime();
        int checkIfPrime(int);
        void playAgain(int&);
        void memberOption();
        void insertionOpt();
};

#endif