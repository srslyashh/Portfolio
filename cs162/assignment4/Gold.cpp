#include "Gold.h"
#include <iostream>

using namespace std;

/******************************************************
** Function : Gold()
** Description: initialize Gold() - default constructor
** Input: none
** Output: initialized members of gold
******************************************************/
Gold::Gold()
{
    // such emptiness
}

/******************************************************
** Function : getCh()
** Description: getCh
** Input: none
** Output: get Char
******************************************************/
char Gold::getCh()
{
    return 'G';
}

/******************************************************
** Function : getpercept()
** Description: get percept
** Input: none
** Output: get percept
******************************************************/
void Gold::percept()
{
    cout << "You see a glimmer nearby." << endl;
}

/******************************************************
** Function : getencounter()
** Description: get encounter
** Input: none
** Output: get encounter
******************************************************/
void Gold::encounter()
{
    cout << endl << "You've found the gold and you've picked it up. Time to leave!" 
    << endl << endl;
}