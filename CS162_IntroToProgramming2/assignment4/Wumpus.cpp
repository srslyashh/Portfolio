#include "Wumpus.h"
#include <iostream>

using namespace std;

/******************************************************
** Function : Wumpus()
** Description: initialize Wumpus() - default constructor
** Input: none
** Output: initialized members of wumpus
******************************************************/
Wumpus::Wumpus()
{
    // such emptiness
}

/******************************************************
** Function : getCh()
** Description: getCh
** Input: none
** Output: get Char
******************************************************/
char Wumpus::getCh()
{
    return 'W';
}

/******************************************************
** Function : getpercept()
** Description: get percept
** Input: none
** Output: get percept
******************************************************/
void Wumpus::percept()
{
    cout << "You smell a terrible stench" << endl;
}

/******************************************************
** Function : getencounter()
** Description: get encounter
** Input: none
** Output: get encounter
******************************************************/
void Wumpus::encounter()
{
    cout << endl << "Womp womp. The wumpus ate you :( You died." << endl << endl;
}