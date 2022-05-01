#include "Bats.h"
#include <iostream>

using namespace std;

/******************************************************
** Function : Bats()
** Description: initialize Bats() - default constructor
** Input: none
** Output: initialized members of bats
******************************************************/
Bats::Bats()
{
    // such emptiness..
}

/******************************************************
** Function : getCh()
** Description: getCh
** Input: none
** Output: get Char
******************************************************/
char Bats::getCh()
{
    return 'B';
}

/******************************************************
** Function : getpercept()
** Description: get percept
** Input: none
** Output: get percept
******************************************************/
void Bats::percept()
{
    cout << "You hear wings flapping" << endl;
}

/******************************************************
** Function : getencounter()
** Description: get encounter
** Input: none
** Output: get encounter
******************************************************/
void Bats::encounter()
{
    cout << endl << "Oh no! An angry bat grabbed you and took you to a random room!" 
        << endl << endl;
}