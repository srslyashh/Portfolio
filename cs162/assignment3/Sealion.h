#ifndef SEALION_H
#define SEALION_H

#include "Animal.h"
#include <iostream>
using namespace std;

class SeaLion : public Animal
{
    private: 
        int bonus;
    public:
        // constructors
        SeaLion();
        SeaLion(int, int, int, float, int);

        // destructor
        ~SeaLion();

        // setting new food cost for sea lion.
        void newFoodSL(float);

        // bonus functions
        void randBonus();
        // getters & setters for bonus.
        int getBonus();
        void setBonus(int);
        
        // print function
        void printSL();
        // empty sealion
        void emptySL();
        float checkerSum(float nfc);
};

#endif