#include "Animal.h"
#include "Sealion.h"
#include <iostream>

using namespace std;

/******************************************************
** Function : SeaLion()
** Description: initialize SeaLion() - default constructor
** Input: none
** Output: initialized SeaLion variables to its own traits
******************************************************/
SeaLion::SeaLion()
{
    bonus = 0;
    setAge(0);
    setCost(800);
    setFoodCost(80);
    setRevenue(240); // revenue as a baby sea lion.
}

/******************************************************
** Function : SeaLion()
** Description: initialize SeaLion() - parameterized constructor
** Input: ints
** Output: initialized SeaLion variables to its own traits
******************************************************/
SeaLion::SeaLion(int bo, int a, int c, float fc,int r) : Animal(a, c, fc, r)
{
    bonus = bo;
    // sending ints to animal.
}

/******************************************************
** Function : ~SeaLion()
** Description: destructor
** Input: none
** Output: destroyed seaLion
******************************************************/
SeaLion::~SeaLion()
{
    // cout << "Sea lion gets destroyed here." << endl;
}

/******************************************************
** Function : printSL()
** Description: print sea lion properties
** Input: none
** Output: print to screen
******************************************************/
void SeaLion::printSL()
{
    cout << "Sea lion's property: " << endl;
    cout << "age: " << getAge() << endl;
    cout << "cost: " << getCost() << endl;
    cout << "food cost: " << getFoodCost() << endl;
    cout << "revenue: " << getRevenue() << endl;
}

/******************************************************
** Function : newFoodSL()
** Description: set new food cost
** Input: none
** Output: food cost for sea lion
******************************************************/
void SeaLion::newFoodSL(float nfc)
{
    setFoodCost(newFoodC(nfc));
    // food for sea lion equals to the base food cost.
}

/******************************************************
** Function : checkerSum(float nfc)
** Description: check total sum for food
** Input: float
** Output: return float
******************************************************/
float SeaLion::checkerSum(float nfc)
{
    return newFoodC(nfc);
}

/******************************************************
** Function : setBonus()
** Description: set bonus!
** Input: int
** Output: set bonus to new bonus.
******************************************************/
void SeaLion::setBonus(int bonus2)
{
    bonus = bonus2;
}

/******************************************************
** Function : getBonus()
** Description: get bonus!
** Input: none
** Output: return bonus
******************************************************/
int SeaLion::getBonus()
{
    return bonus;
}

/******************************************************
** Function : randBonus()
** Description: randomize bonus
** Input: none
** Output: randomized number between 150 and 400.
******************************************************/
void SeaLion::randBonus()
{
    srand(time(0));
    // randomizing bonus between 150 to 400.
    int bonus = rand() % 251 + 150;
    setBonus(bonus);
}

/******************************************************
** Function : emptySL()
** Description: resetting sealion.
** Input: none
** Output: empty sea lion
******************************************************/
void SeaLion::emptySL()
{
    setAge(0);
    setCost(0);
    setFoodCost(0);
    setRevenue(0);
    bonus = 0;
}
