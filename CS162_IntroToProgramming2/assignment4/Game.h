#include "Event.h"
#include "Wumpus.h"
#include "Gold.h"
#include "Pits.h"
#include "Rope.h"
#include "Bats.h"
#include "Room.h"

#include <iostream>
#include <vector>

#ifndef GAME_H
#define GAME_H

using namespace std;

class Game
{
    private:
        vector <vector<Room>> cave;
        vector <Event *> evtholder;
        vector <Room *> roomholder;
        Room *position;
        Room *initialR;
        int initialRoomRow;
        int initialRoomCol;
        int positionRoomRow;
        int positionRoomCol;
        int arrows;
        int size;
        bool winGame;
        int mode; // 0 = debug, 1 = normal
        bool isGameOver; // 0 = true, 1 = false
        bool wumStatus; // true = alive, false = dead
        bool goldFound; // 0 = found, 1 = no
        bool isAdventurerAlive; // 0 = true, 1 false
    public:
        Game(int,int);
        void setPosition(Room *);
        Room* getPosition();
        void printWelcome();
        void printSelection();
        void printEventsNear();
        void printTopLowBar();
        void printData();
        void printGrid();
        void printDebugMode();
        void printInBetween();
        void printNormalMode();
        void printEncounter();
        void printWumpStatus(int);
        void printChar(int,int);
        void initializeEvent(int);
        void setEvents();
        void wumpusMove();
        void shootArrow(string);
        void shootArrowTwo(string, int&);
        void isRoomAdjacent(string);
        void moveEventBat();
        void emptyRoom();
        void gameOverCheck();
        void initializeBR();
        void loopDirection(string &, string &, int&);
        int checkDirection(const string& input, int&);
        void settingCurrCol(int , int , int );
        void outOfBoundsPrint();
        void settingCurrRow(int, int, int);
        void isRoomAdjacentTwo(string, int, int);
        void play();
        void setEventsTwo(int);
        int roomEmpty(int&,int&);
        void setEventsThree(int, int, int);
        void eventHeader();
        void encounter();
        void encounterTwo();
        void printNormalChar(int, int);
        void printEnding();
        void printEventsNearTwo(int&, int&);
        void checkIfRope(int,int, int&);
        void playAgain(int &,int &);
        void playCheck(string &,int&);
        int loopCheck(string,int&);
        void playConfig(int);
        void playSecond();
        void deleteG();
        void initializingData();
        void setEventsSecond(int, int);
        void playMenuTwo();
        void getInitialP();
        void checkWumpus(int,int, int&);
};


#endif