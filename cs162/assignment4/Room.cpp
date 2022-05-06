#include "Room.h"
#include <iostream>

using namespace std;

/******************************************************
** Function : Room()
** Description: initialize Room() - default constructor
** Input: none
** Output: initialized members of Room
******************************************************/
Room::Room()
{
    eventsP = NULL;
    eventNum = 0; // 0 is empty
    isFilled = false;
    adventurerE = false;
}

/******************************************************
** Function : setEvent(Event *e, int num)
** Description: setevent
** Input: none
** Output: event is set
******************************************************/
void Room::setEvent(Event *e, int num)
{
    // 2 = wumpus, 3 = gold
    // 4 = bats, 5 = pits
    eventsP = e;
    eventNum = num;
    isFilled = true;
}

/******************************************************
** Function : emptyRoom()
** Description: empty room
** Input: none
** Output: room empty
******************************************************/
void Room::emptyRoom()
{
    eventsP = NULL;
    eventNum = 0;
    isFilled = false;
    adventurerE = false;
}

/******************************************************
** Function : getEventP()
** Description: get event P
** Input: none
** Output: return event p
******************************************************/
Event* Room::getEventP()
{
    return eventsP;
}

/******************************************************
** Function : ~Room()
** Description: delete room
** Input: none
** Output: delete room
******************************************************/
Room::~Room()
{
    // such emptiness
}

/******************************************************
** Function : Room(int newRow, int newCol)
** Description: parameterized parameter for room
** Input: none
** Output: delete room
******************************************************/
Room::Room(int newRow, int newCol)
{
    row = newRow;
    col = newCol;
    eventsP = NULL;
    eventNum = 0; // 0 is empty
    isFilled = false;
    adventurerE = false;
}

/******************************************************
** Function : getIsFilled()
** Description: return isFilled
** Input: none
** Output: return val
******************************************************/
bool Room::getIsFilled()
{
    return isFilled;
}

/******************************************************
** Function : getAdventurer()
** Description: return Adventurer()
** Input: none
** Output: return val
******************************************************/
bool Room::getAdventurer()
{
    return adventurerE;
}

/******************************************************
** Function : getEventNum()
** Description: return EventNum()
** Input: none
** Output: return val
******************************************************/
int Room::getEventNum()
{
    return eventNum;
}

/******************************************************
** Function : setIsFilled()
** Description: set isFilled
** Input: none
** Output: set val
******************************************************/
void Room::setIsFilled(bool newVal)
{
    isFilled = newVal;
}

/******************************************************
** Function : setAdventurer(bool newVal)
** Description: set Adventurer
** Input: none
** Output: set val
******************************************************/
void Room::setAdventurer(bool newVal)
{
    adventurerE = newVal;
}   

/******************************************************
** Function : setEventNum(int newNum)
** Description: set setEventNum
** Input: none
** Output: set val
******************************************************/
void Room::setEventNum(int newNum)
{
    eventNum = newNum;
}

/******************************************************
** Function : getRow()
** Description: get Row
** Input: none
** Output: return val
******************************************************/
int Room::getRow()
{
    return row;
}

/******************************************************
** Function : setRow()
** Description: set Row
** Input: none
** Output: set val
******************************************************/
void Room::setRow(int newR)
{
    row = newR;
}

/******************************************************
** Function : getCol()
** Description: get Col
** Input: none
** Output: return val
******************************************************/
int Room::getCol()
{
    return col;
}

/******************************************************
** Function : setCol()
** Description: set Col
** Input: none
** Output: set val
******************************************************/
void Room::setCol(int newC)
{
    col = newC;
}
