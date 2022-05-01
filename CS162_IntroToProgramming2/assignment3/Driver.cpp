/******************************************************
** Program: ZOO TYCOON!
** Author: Kathleen Ashley
** Date: 11/09/2020
** Description: Play as a zoo keeper
** Input: options
** Output: a well-kept zoo :)
******************************************************/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <sstream>

#include "Animal.h"
#include "Bear.h"
#include "Tiger.h"
#include "Sealion.h"
#include "Zoo.h"

using namespace std;

int main()
{
    Zoo game;
    game.printInitial();
    while(game.getQuitG() == 0)
    {
        game.printStatus();
        if(game.getQuitG() == 0)
        {
            game.randomEvent();
        }
        else if(game.getQuitG() == 1)
        {
            game.GameOver(game.isGameOver());
        }
    }
    return 0;
}