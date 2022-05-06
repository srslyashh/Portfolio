#include "Pits.h"
#include <iostream>

using namespace std;

/******************************************************
** Function : Pits()
** Description: initialize Pits() - default constructor
** Input: none
** Output: initialized members of Pits()
******************************************************/
Pits::Pits()
{
    // such emptiness
}

/******************************************************
** Function : getCh()
** Description: getCh
** Input: none
** Output: get Char
******************************************************/
char Pits::getCh()
{
    return 'P';
}

/******************************************************
** Function : getpercept()
** Description: get percept
** Input: none
** Output: get percept
******************************************************/
void Pits::percept()
{
    cout << "You feel a breeze" << endl;
}

/******************************************************
** Function : getencounter()
** Description: get encounter
** Input: none
** Output: get encounter
******************************************************/
void Pits::encounter()
{
    cout << "Oh no! You fell into a bottomless pit :( You died." << endl;
}