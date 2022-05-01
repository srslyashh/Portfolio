#ifndef GAME_HF_HPP
#define GAME_HF_HPP

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <sstream>

#include "Deck_hf.hpp"
#include "Hand_hff.hpp"
#include "Player_hf.hpp"
#include "Card_hf.hpp"

using namespace std;

class Game
{
	private:
		Deck cards;
		Player players[2];
		Card top_pile;
	public:
		Game();
		~Game();

		// accessors
		Deck& getDeck();
		Player* getPlayer();
		Card& getTopPile();

        // mutators
        void setTopCard(Card &);

		//functions 
		void distributeUserCards();
		void topCard();
		void topPile();
		void printStuff();
		void distributeCards();
		void printInitialWelcome();
		void loopOptG(string &, int &, int);
		int checkOptG(const string, int);
		void whichOption(Hand &, Card*&);
		void cardSelected(Hand &, Card*&);
		int isSelectedValid(int, Card*&, int);
		void isSelectedValidT(int &, Card*&, int);
		void isCardSelectedEights(int &, Card*& , int &);
		void setTopCardForEights(int, int);
		void printASelection(Card *&, int, Card&);

		// to check whether game is over or not
		int isGameOver();
		int checkIfHandEmpty();
		int checkIfStockEmpty();
		int cardsUnplayable();

		// functions for computer
		void computerTurn();
		void EightsComp(int, Card *&);
		int matchCard(Card*&, Card&, int, int&, int&);
		void printTopCard(Card&);
		void setTopCardForB(Card*& , int);

		// print winner
		void printMessage(int);
		void printWinner();
		int theLeastCards();
		int whoseEmpty();

		// play Again?
		void playAgain(int &);
};


#endif