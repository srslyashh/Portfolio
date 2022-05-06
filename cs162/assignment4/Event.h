#include <iostream>

#ifndef EVENT_H
#define EVENT_H

using namespace std;

class Event
{
    public:
        Event();
        virtual ~Event() = default;
        virtual char getCh() = 0;
        virtual void percept() = 0;
        virtual void encounter() = 0;
};

#endif