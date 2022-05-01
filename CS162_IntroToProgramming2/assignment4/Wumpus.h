#include "Event.h"
#include <iostream>

#ifndef WUMPUS_H
#define WUMPUS_H

using namespace std;

class Wumpus : public Event
{
    public:
        Wumpus();
        char getCh();
        void percept();
        void encounter();
};

#endif