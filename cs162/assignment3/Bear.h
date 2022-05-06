#ifndef BEAR_H
#define BEAR_H

#include "Animal.h"
#include <iostream>
using namespace std;

class Bear : public Animal
{
    public:
        // constructors
        Bear();
        Bear(int, int, float, int);

        // destructor
        ~Bear();

        // print function
        void printB();

        // setting new food cost for tiger.
        void newFoodB(float);
        float checkerSum(float nfc);
};

#endif