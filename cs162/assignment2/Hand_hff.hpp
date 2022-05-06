#ifndef HAND_HFF_HPP
#define HAND_HFF_HPP

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <sstream>

#include "Card_hf.hpp"

using namespace std;

class Hand
{
	private:
		Card* cards;
		int n_cards;

	public:
		Hand();
		Hand(Card* const &, int);
		// destructor
		~Hand();

		// copy constructor
		Hand(const Hand&);

		// operation overloading
		Hand& operator=(const Hand&);	

		// accessors
		int getNumCards();
		Card*& getCards();
		int getSuit(int);
		int getRank(int);

		// print
		void printCardsAtHand();

		//mutators

		//functions
		void addCard(const Card&);
		void removeCard(int);
		int isCardChosenValid(int, int);
};


#endif