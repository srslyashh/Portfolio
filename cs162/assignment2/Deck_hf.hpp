#ifndef DECK_HF_HPP
#define DECK_HF_HPP


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <sstream>

#include "Hand_hff.hpp"
#include "Card_hf.hpp"

using namespace std;

class Deck
{
	private:
		Card cards[52];
		int n_cards;

	public:
		Deck();
		Deck(Card* const &, int);

		// destructor
		~Deck();

		// get the size
		int get_size();
		Card* getCards();
		// copy constructor
		Deck(const Deck&);

		// operation overloading
		void operator=(const Deck& other);

		// add card or cards
		void changeNum(int, int);
		void printCards();
		void dealCardToPlayer(Hand &, Deck&, int);
		void cards52();
		void add_card(const Card&);
		void add_cards(Card* const &, int n);
		void shuffling();
};

#endif