#include "Animal.h"
#include "Tiger.h"
#include <iostream>

using namespace std;

/******************************************************
** Function : Tiger()
** Description: initialize Tiger() - default constructor
** Input: none
** Output: initialized Tiger variables to its own traits
******************************************************/
Tiger::Tiger()
{
    setAge(0);
    setCost(15000);
    setFoodCost(80);
    setRevenue(3000); // revenue as a baby tiger.
}

/******************************************************
** Function : Tiger()
** Description: initialize Tiger() - parameterized constructor
** Input: ints
** Output: initialized Tiger variables to its own traits
******************************************************/
Tiger::Tiger(int a, int c, float fc, int r) : Animal(a, c, fc, r)
{
    // sending info to animal.
}

/******************************************************
** Function : checkerSum(float nfc)
** Description: check total sum for food
** Input: float
** Output: return float
******************************************************/
float Tiger::checkerSum(float nfc)
{
    return newFoodC(nfc);
}

/******************************************************
** Function : ~Tiger()
** Description: destructor
** Input: none
** Output: destroyed tiger
******************************************************/
Tiger::~Tiger()
{
    // cout << "TIGER IS DESTROYED!" << endl;
}

/******************************************************
** Function : printT()
** Description: printing Tiger properties
** Input: none
** Output: print
******************************************************/
void Tiger::printT()
{
    cout << "Tiger's property: " << endl;
    cout << "age: " << getAge() << endl;
    cout << "cost: " << getCost() << endl;
    cout << "food cost: " << getFoodCost() << endl;
    cout << "revenue: " << getRevenue() << endl;
}

/******************************************************
** Function : newFoodT()
** Description: setting new food cost for tiger
** Input: float
** Output: new value for tiger food cost
******************************************************/
void Tiger::newFoodT(float nfc)
{
    setFoodCost(newFoodC(nfc));
}