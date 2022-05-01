#ifndef TIGER_H
#define TIGER_H

#include "Animal.h"
#include <iostream>
using namespace std;

class Tiger : public Animal
{
    public:
        // constructors
        Tiger();
        Tiger(int, int, float, int);
        // destructor
        ~Tiger();
        // print function
        void printT();
        // setting new food cost for tiger.
        void newFoodT(float);
        float checkerSum(float nfc);
};

#endif