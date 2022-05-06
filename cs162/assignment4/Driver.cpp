/******************************************************
** Program: HUNT THE WUMPUS!!!
** Author: Kathleen Ashley
** Date: 11/22/2020
** Description: Try to escape out of the cave w gold
** Input: options
** Output: Fun game!
******************************************************/

#include "Event.h"
#include "Wumpus.h"
#include "Gold.h"
#include "Pits.h"
#include "Rope.h"
#include "Bats.h"
#include "Room.h"
#include "Game.h"

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <exception>

using namespace std;

int main(int argc, char** argv)
{
    int mode = 2, size = 0, again = 0, config = 0;
    size = stoi(argv[1]);
    if(argc != 3)
    {
        cout << "Error: Too few arguments." << endl;
        exit(1);
    }
    else if(size < 4)
    {
        cout << "Error: grid size is smaller than four." << endl;
        exit(1);
    }
    string modeS = string(argv[2]);
    if(modeS == "true")
    {
        mode = 0;
    }
    else if(modeS == "false")
    {
        mode = 1;
    }
    
    Game game(mode,size);
    game.play();
    game.printEnding();
    game.playAgain(again, config);

    while(again == 2)
    {
        if(config == 2)
        {
            Game game2(mode,size);
            game2.play();
            game2.printEnding();
            game2.deleteG();
            game.playAgain(again,config);
        }
        else if(config == 1)
        {
            game.playSecond();
            game.playMenuTwo();
            game.printEnding();
            game.playAgain(again,config);
        }
    }
    game.deleteG();
    
    return 0;
}