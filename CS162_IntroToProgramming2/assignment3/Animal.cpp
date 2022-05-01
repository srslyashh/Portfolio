#include "Animal.h"
#include <iostream>

using namespace std;

/******************************************************
** Function : Animal()
** Description: initialize Animal
** Input: none
** Output: initialized Animal variables
******************************************************/
Animal::Animal()
{
    age = 0;
    cost = 0;
    foodCost = 0;
    revenue = 0;
}

/******************************************************
** Function : Animal()
** Description: parameterized constructor
** Input: ints
** Output: initialized animal by ints
******************************************************/
Animal::Animal(int a,int c,float fc,int r)
{
    age = a;
    cost = c;
    foodCost = fc;
    revenue = r;
}

/******************************************************
** Function : ~Animal()
** Description: animal destructor
** Input: none
** Output: destroyed animal
******************************************************/
Animal::~Animal()
{
    // cout << "Animal gets destroyed here" << endl;
}

/******************************************************
** Function : getAge()
** Description: getter for animal
** Input: none
** Output: int
******************************************************/
int Animal::getAge()
{
    return age;
}

/******************************************************
** Function : getCost()
** Description: getter for animal
** Input: none
** Output: int
******************************************************/
int Animal::getCost()
{
    return cost;
}

/******************************************************
** Function : getFoodCost()
** Description: getter for animal
** Input: none
** Output: float
******************************************************/
float Animal::getFoodCost()
{
    return foodCost;
}

/******************************************************
** Function : getRevenue()
** Description: getter for animal
** Input: none
** Output: int
******************************************************/
int Animal::getRevenue()
{
    return revenue;
}

/******************************************************
** Function : setAge()
** Description: setter for animal
** Input: int
** Output: none
******************************************************/
void Animal::setAge(int a)
{
    age = a;
}

/******************************************************
** Function : setCost()
** Description: setter for animal
** Input: int
** Output: none
******************************************************/
void Animal::setCost(int c)
{
    cost = c;
}

/******************************************************
** Function : setFoodCost()
** Description: setter for animal
** Input: int
** Output: none
******************************************************/
void Animal::setFoodCost(float fc)
{
    foodCost = fc;
}

/******************************************************
** Function : setRevenue()
** Description: setter for animal
** Input: int
** Output: none
******************************************************/
void Animal::setRevenue(int r)
{
    revenue = r;
}

/******************************************************
** Function : newFoodC()
** Description: setting a new value for food cost.
** Input: float
** Output: float
******************************************************/
float Animal::newFoodC(float nfc)
{
    // if nfc = 0.5 means cheap.
    // if nfc = 1 means regular.
    // if nfc = 2 means premium.
    srand(time(0));
    int a = rand()% 41 + 80;
    float b;

    // multiplying current food cost * randomized percentage * nfc.
    // whichAnimal is the monthly food cost depending on which animal.
    b = foodCost * a * nfc / 100;
    // setting food cost to new food cost.
    return b;
}

/******************************************************
** Function : emptyAnimal()
** Description: resetting animal values
** Input: none
** Output: none
******************************************************/
void Animal::emptyAnimal()
{
    // setting animals to 0 would then raise a flag to other operator
    // to delete animal. 
    setAge(0);
    setCost(0);
    setFoodCost(0);
    setRevenue(0);
}