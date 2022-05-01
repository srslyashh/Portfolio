#include "Event.h"
#include <iostream>

#ifndef BATS_H
#define BATS_H

using namespace std;

class Bats : public Event
{
    public:
        Bats();
        char getCh();
        void percept();
        void encounter();
};

#endif