#include "Event.h"

#ifndef ROPE_H
#define ROPE_H

using namespace std;

class Rope : public Event
{
    public:
        Rope();
        char getCh();
        void percept();
        void encounter();
};


#endif