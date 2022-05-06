#include "Animal.h"
#include "Bear.h"
#include <iostream>

using namespace std;

/******************************************************
** Function : Bear()
** Description: initialize Bear() - default constructor
** Input: none
** Output: initialized Bear variables to its own traits
******************************************************/
Bear::Bear()
{
    setAge(0);
    setCost(6000);
    setFoodCost(80);
    setRevenue(1200); // revenue as a baby :)
}

/******************************************************
** Function : Bear()
** Description: initialize Bear() - parameterized constructor
** Input: ints
** Output: initialized Bear variables to its own traits
******************************************************/
Bear::Bear(int a, int c, float fc,int r) : Animal(a, c, fc, r)
{
    // passing info to animal.
}

/******************************************************
** Function : ~Bear()
** Description: destructor for bear()
** Input: none
** Output: destroyed bear()
******************************************************/
Bear::~Bear()
{
    // cout << "BEAR OBJECT DESTROYED" << endl;
}

/******************************************************
** Function : printB()
** Description: print B properties
** Input: none
** Output: print
******************************************************/
void Bear::printB()
{
    cout << "Bear's property: " << endl;
    cout << "age: " << getAge() << endl;
    cout << "cost: " << getCost() << endl;
    cout << "food cost: " << getFoodCost() << endl;
    cout << "revenue: " << getRevenue() << endl;
}

/******************************************************
** Function : newFoodB()
** Description: setting new food cost for bear
** Input: float
** Output: new food cost for bear
******************************************************/
void Bear::newFoodB(float nfc)
{
    float a = newFoodC(nfc);
    setFoodCost(a);
}

/******************************************************
** Function : checkerSum(float nfc)
** Description: check total sum for food
** Input: float
** Output: return float
******************************************************/
float Bear::checkerSum(float nfc)
{
    return newFoodC(nfc);
}