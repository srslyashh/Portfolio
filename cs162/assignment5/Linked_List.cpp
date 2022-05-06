#include "Node.h"
#include "Linked_List.h"

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

/******************************************************
** Function : Linked_List()
** Description: initialize Linked_List() - default constructor
** Input: none
** Output: initialized members of Linked_List
******************************************************/
Linked_List::Linked_List()
{
    length = 0;
    head = NULL;
    mode = 0;
    primeNum = 0;
}

/******************************************************
** Function : checkInputTwo(int,int,int)
** Description: check if input is within range/not.
** Input: int
** Output: return 0 if true, return 1 if false.
******************************************************/
int Linked_List::checkInputTwo(int hold, int range = 0, int hrange = 0)
{
    if(range == 0)
    {
        if(hold >= 0 && hold < hrange)
        {
            return 0;
        }
    }
    return 1;
}

/******************************************************
** Function : checkInput(string,int,int)
** Description: check if input is within range/not.
** Input: string,int
** Output: return 0 if true, return 1 if false.
******************************************************/
int Linked_List::checkInput(string str, int range = 0, int hrange = 0)
{
    int hold = 0;
    stringstream changeToInt(str);
    changeToInt >> hold;

    if(range == 1 && hrange == 2)
    {
        if(hold == range || hold == hrange)
        {
            return 0;
        }
    }
    else if(range == -2147483647 && hrange == 2147483647)
    {
        if(-2147483648 <= hold && hold <= 2147483647)
        {
            return 0;
        }
    }
    else
    {
        return checkInputTwo(hold, range,hrange);
    }
    return 1;
}


/******************************************************
** Function : loopInput(string& ,int& ,int, int)
** Description: keep on looping until input is valid.
** Input: string,int
** Output: change value of dest.
******************************************************/
void Linked_List::loopInput(string &str, int& dest, int range, int hrange)
{
    int loopAgain = 0;

    while(loopAgain == 0)
    {
        if(checkInput(str,range, hrange) == 0)
        {
            loopAgain = 1;
            stringstream changeToInt(str);
            changeToInt >> dest;
        }
        else
        {
            cout << "The value you entered wasn't valid. Enter another value:" << endl;
            cin >> str;
        }
    }
}

/******************************************************
** Function : push_front(int value)
** Description: push at the front of the linked list
** Input: int value
** Output: head will point at new Node.
******************************************************/
unsigned int Linked_List::push_front(int value)
{
    Node *firstn = new Node(value);
    firstn->next = head;
    head = firstn;
    length++;
    return length;
}

/******************************************************
** Function : push_middle(int value, int index)
** Description: push in the middle of the linked list.
** Input: int value
** Output: new node will be located at index.
******************************************************/
unsigned int Linked_List::push_middle(int value, int index)
{
    int counter = 0;
    Node *holder = new Node(value);
    Node *headH = head;

    while(headH->next != NULL && counter < index)
    {
        headH = headH->next;
        counter++;
    }

    holder->next = headH->next;
    headH->next = holder;
    length++;
    return length;
}

/******************************************************
** Function : insert(int val, unsigned int index)
** Description: insert a new node at the index chosen.
** Input: int value, int index
** Output: new node will be located at index. return length
******************************************************/
unsigned int Linked_List::insert(int val, unsigned int index)
{
    if(index == 0)
    {
        push_front(val);
    }
    else if(0 < index && index < length)
    {
        push_middle(val, index);
    }
    else
    {
        push_back(val);
    }
    return length;
}

/******************************************************
** Function : initialQ()
** Description: print question to screen
** Input: none
** Output: new node will be put at the head.
******************************************************/
void Linked_List::initialQ()
{
    string hold;
    int holderI = 0;
    cout << endl << "Please enter a number: " << endl;
    cin >> hold;
    loopInput(hold, holderI,-2147483647, 2147483647);
    push_front(holderI);
}

/******************************************************
** Function : checkCharTwo(string &hold, int& dest, int mode)
** Description: check if the char inputted by user is valid
** Input: string&, int&,int
** Output: return 0 if valid, 1 if invalid
******************************************************/
int Linked_List::checkCharTwo(string &hold, int& dest, int mode)
{
    if(hold == "A" || hold == "a")
    {
        dest = 1;
        return 0;
    }
    else if(hold == "D" || hold == "d")
    {
        dest = 2;
        return 0;
    }
    return 1;
}

/******************************************************
** Function : checkChar(string &hold, int& dest, int mode)
** Description: check if the char inputted by user is valid
** Input: string&, int&,int
** Output: return 0 if valid, 1 if invalid
******************************************************/
int Linked_List::checkChar(string &hold, int& dest, int mode)
{
    if(mode == 1)
    {
        if(hold == "Y" || hold == "y")
        {
            dest = 0; // 0 means they want another num.
            return 0;
        }
        else if(hold == "N" || hold == "n")
        {
            dest = 1;
            return 0;
        }
    }
    else if(mode == 2)
    {
        return checkCharTwo(hold, dest, mode);
    }
    return 1;
}

/******************************************************
** Function : loopChar(string &hold, int& dest, int mode)
** Description: loop until input is valid
** Input: string&, int&,int
** Output: valid input will be put in dest.
******************************************************/
void Linked_List::loopChar(string &hold, int& dest, int mode)
{
    int loopAgain = 0;

    while(loopAgain == 0)
    {
        if(checkChar(hold,dest,mode) == 0)
        {
            loopAgain = 1;
        }
        else
        {
            cout << "The value you entered wasn't valid. Enter another value:" << endl;
            cin >> hold;
        }
    }
}

/******************************************************
** Function : addMore()
** Description: check if user wants to add more members.
** Input: none
** Output: return 0 if yes, 1 if no.
******************************************************/
int Linked_List::addMore()
{
    string hold;
    int torf;
    cout << "Do you want another num (y or n): " << endl;
    cin >> hold;
    loopChar(hold, torf, 1);
    return torf;
}

/******************************************************
** Function : push_back(int value)
** Description: insert at tail
** Input: int value
** Output: node will be inserted at tail.
******************************************************/
unsigned int Linked_List::push_back(int value)
{
    Node *newNode = new Node(value);
    Node *tmp;

    // while "next" is not NULL (last element), go on to the next element.
    for(tmp = head; tmp->next != NULL; tmp = tmp->next)
    {
        // empty
    }

    tmp->next = newNode;
    length++;
    return length;
}

/******************************************************
** Function : moreMembers()
** Description: prompt user to enter value, insert node at tail.
** Input: none
** Output: node will be inserted at tail.
******************************************************/
void Linked_List::moreMembers()
{
    string holder;
    int finalI = 0;
    cout << endl << "Enter a number: " << endl;
    cin >> holder;
    loopInput(holder, finalI, -2147483647, 2147483647);
    push_back(finalI);
}

/******************************************************
** Function : insertionOpt()
** Description: give options to use the insert() function
** Input: none
** Output: node will be inserted at chosen index.
******************************************************/
void Linked_List::insertionOpt()
{
    string holder;
    int val = 0, index = 0;
    cout << endl << "Enter a number: " << endl;
    cin >> holder;
    loopInput(holder,val,-2147483647, 2147483647);
    cout << "Enter an index: " << endl;
    cin >> holder;
    loopInput(holder,index, 0, length);
    insert(val,index);
}

/******************************************************
** Function : memberOption()
** Description: give options to enter member in two ways
** Input: none
** Output: members will be added from chosen option
******************************************************/
void Linked_List::memberOption()
{
    string option;
    int optionI;
    cout << endl << "Choose the following: " << endl;
    cout << "(1) Add member without index. " << endl;
    cout << "(2) Add member with index. " << endl;
    cin >> option;
    loopInput(option,optionI,1,2);
    if(optionI == 1)
    {
        moreMembers();
    }
    else if(optionI == 2)
    {
        insertionOpt();
    }
}

/******************************************************
** Function : mergeLL(Node *low, Node *high)
** Description: recursive function to merge linked list.
** Input: Node *low, Node *high
** Output: members will be sorted and merged
******************************************************/
Node* Linked_List::mergeLL(Node *low, Node *high)
{
    Node *tmp = NULL;

    if(low == NULL || high == NULL)
    {
        return (low == NULL) ? high : low;
    }
    if(low->val <= high->val)
    {
        tmp = low;
        tmp->next = mergeLL(low->next, high);
    }
    else if(high->val <= low->val)
    {
        tmp = high;
        tmp->next = mergeLL(low, high->next);
    }
    return tmp;
}

/******************************************************
** Function : divide(Node *start, Node **low, Node **high)
** Description: split the merge sort into two.
** Input: Node **
** Output: node will be split
******************************************************/
void Linked_List::divide(Node *start, Node **low, Node **high)
{
    Node* midhold = start;
    Node* highhold;

    for(highhold = start->next; highhold != NULL; )
    {
        highhold = highhold->next;
        if(highhold != NULL)
        {
            midhold = midhold->next;
            highhold = highhold->next;
        }
    }
    *low = start;
    *high = midhold->next;
    midhold->next = NULL;
}

/******************************************************
** Function : swappy(Node*,Node*)
** Description: swap nodes' next
** Input: Node **
** Output: node will be swapped
******************************************************/
void Linked_List::swappy(Node* prevVal, Node* most)
{
    Node *holder = most->next;
    most->next = prevVal ->next;
    prevVal->next = holder;
}

/******************************************************
** Function : swapPlaces(Node **,Node*,Node*,Node*)
** Description: swap nodes' place.
** Input: Node **
** Output: node will be swapped
******************************************************/
void Linked_List::swapPlaces(Node **start, Node *prevVal, Node *most, Node *prevMinP)
{
    // position the least at the beginning.
    *start = most; 
    // change the previous node's next with prevVal.
    prevMinP->next = prevVal; 
    swappy(prevVal, most);
}

/******************************************************
** Function : recursiveSS(Node *start)
** Description: recursive selection sort.
** Input: Node *
** Output: return sorted node.
******************************************************/
Node* Linked_List::recursiveSS(Node *start)
{
    int swapped = 1;
    Node *most = start, *hold, *prevAdd = NULL;
    if(start->next == NULL)
    {
        return start;
    }
    for(hold = start; hold->next != NULL; hold = hold->next)
    {
        if(hold->next->val > most->val)
        {
            swapped = 0;
            most = hold->next;
            prevAdd = hold;
        }
    }
    if(swapped == 0)
    {
        swapPlaces(&start, start, most, prevAdd);
    }
    start->next = recursiveSS(start->next);
    return start;
}

/******************************************************
** Function : recursiveMS(Node **headL)
** Description: recursive merge sort.
** Input: Node **
** Output: node will be sorted with merge sort algorithm
******************************************************/
void Linked_List::recursiveMS(Node **headL)
{
    Node *start = *headL;
    Node *low, *high;
    // if the firstE is empty/next is empty, return.
    if(start == NULL || start->next == NULL)
    {
        return;
    }
    // divide by half.
    divide(start, &low, &high);
    recursiveMS(&low);
    recursiveMS(&high);
    // combine linked lists and sort.
    *headL = mergeLL(low, high);
}

/******************************************************
** Function : sort_ascending()
** Description: call recursive merge sort
** Input: none
** Output: sorted linked list by merge sort algorithm
******************************************************/
void Linked_List::sort_ascending()
{   
    recursiveMS(&head);
}

/******************************************************
** Function : sort_descending()
** Description: call recursive selection sort.
** Input: none
** Output: sorted linked list by recursive selection sort algorithm
******************************************************/
void Linked_List::sort_descending()
{
    Node **headHold = &head;
    if(*headHold != NULL)
    {
        *headHold = recursiveSS(*headHold);
    }
}

/******************************************************
** Function : print()
** Description: print linked list
** Input: none
** Output: print sorted linked list to screen
******************************************************/
void Linked_List::print()
{
    Node* holder = head;
    cout << endl << "Your linked list is: ";
    while(holder != NULL)
    {
        cout << holder->val << " ";
        holder = holder->next;
    }
    cout << endl;
}

/******************************************************
** Function : sortQ()
** Description: sort question
** Input: none
** Output: call the appropriate functions
******************************************************/
void Linked_List::sortQ()
{
    string holder;
    int sortAOrD = 0; // a = 1, d = 2.
    cout << endl << "Sort ascending or descending (a or d): " << endl;
    cin >> holder;
    loopChar(holder, sortAOrD, 2);
    if(sortAOrD == 1)
    {
        sort_ascending();
    }
    else if(sortAOrD == 2)
    {
        sort_descending();
    }
}

/******************************************************
** Function : clear()
** Description: clear data
** Input: none
** Output: cleared data
******************************************************/
void Linked_List::clear()
{
    Node *headNode = head;
    while(headNode != NULL)
    {
        // set head to the next node in head.
        head = head->next;
        // delete the current head.
        delete headNode;
        headNode = head;
    }
    length = 0;
    head = NULL;
}

/******************************************************
** Function : checkIfPrime(int value)
** Description: check if value is prime.
** Input: int 
** Output: return 0 if prime, 1 if not.
******************************************************/
int Linked_List::checkIfPrime(int value)
{
    // if val is negative, make it positive then check.
    if(value < 0)
    {
        value = -value;
    }
    if((value != 2 && value % 2 == 0) || value == 0 || value == 1)
    {
        return 1;
    }
    else
    {
        // start checking from i = 3, bc the last check started at 2. increment by 2 
        // instead of 1, bc 1 would make it an even number instead of odd.
        for(int i = 3; (i * i) <= value; i += 2)
        {
            if(value % i == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

/******************************************************
** Function : printPrime()
** Description: print the total number of prime.
** Input: int 
** Output: print to screen
******************************************************/
void Linked_List::printPrime()
{
    Node *holder;
    for(holder = head; holder != NULL; holder = holder->next)
    {
        if(checkIfPrime(holder->val) == 0)
        {
            primeNum++;
        }
    }
    cout << "You have " << primeNum << " prime number(s) in your list." << endl;
}

/******************************************************
** Function : playAgain(int& loopAgain)
** Description: ask if player wants to play again.
** Input: int&
** Output: print to screen
******************************************************/
void Linked_List::playAgain(int& loopAgain)
{
    string holder;
    cout << endl << "Do you want to do this again? (y or n): " << endl;
    cin >> holder;
    loopChar(holder,loopAgain, 1);
}