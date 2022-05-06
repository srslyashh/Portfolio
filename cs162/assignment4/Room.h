#include "Event.h"
#include <iostream>

#ifndef ROOM_H
#define ROOM_H

using namespace std;

class Room
{
    private:
        Event *eventsP;
        int eventNum; 
        bool isFilled;
        bool adventurerE;
        int row;
        int col;
    public:
        Room();
        ~Room();
        Room(int, int);
        Event* getEventP();
        bool getIsFilled();
        bool getAdventurer();
        int getEventNum();
        void setIsFilled(bool);
        void emptyRoom();
        void setAdventurer(bool);
        void setEventNum(int);
        void setEvent(Event *e, int);
        int getRow();
        void setRow(int);
        int getCol();
        void setCol(int);
};


#endif