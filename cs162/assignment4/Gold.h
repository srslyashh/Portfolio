#include "Event.h"
#include <iostream>

#ifndef GOLD_H
#define GOLD_H

using namespace std;

class Gold : public Event
{
    public:
        Gold();
        char getCh();
        void percept();
        void encounter();
};

#endif