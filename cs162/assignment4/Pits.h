#include "Event.h"
#include <iostream>

#ifndef PITS_H
#define PITS_H

using namespace std;

class Pits : public Event
{
    public:
        Pits();
        char getCh();
        void percept();
        void encounter();
};

#endif