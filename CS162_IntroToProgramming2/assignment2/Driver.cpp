/******************************************************
** Program: crazyeights.cpp
** Author: Kathleen Ashley
** Date: 10/27/2020
** Description: Play Crazy eights with computer
** Input: options
** Output: the winner!
******************************************************/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <sstream>

#include "Game_hf.hpp"
#include "Deck_hf.hpp"
#include "Hand_hff.hpp"
#include "Player_hf.hpp"
#include "Card_hf.hpp"

using namespace std;

int main()
{	
	int loopAgain = 0, gameNYO = 0, player = 0;
	while(loopAgain == 0)
	{
		Game play = Game();
		play.printInitialWelcome();
		play.distributeUserCards();
		int player = 0;

		while(play.isGameOver() == 1)
		{
			if(player == 0)
			{
				play.printStuff();
				player = 1;
			}
			if(player == 1)
			{
				play.computerTurn();
				player = 0;
			}
		}
		if(player == 0)
		{
			play.printWinner();
		}
		play.playAgain(loopAgain);
	}
}