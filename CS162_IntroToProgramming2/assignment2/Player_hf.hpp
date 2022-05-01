#ifndef PLAYER_HF_HPP
#define PLAYER_HF_HPP

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <sstream>

#include "Hand_hff.hpp"
#include "Game_hf.hpp"
#include "Deck_hf.hpp"
#include "Card_hf.hpp"

using namespace std;

class Player
{
	private:
		Hand hand;
		string name;
	public:
		Player();
		Player(const Hand&, string);

		// destructor
	 	~Player();

		//copy constructor
		Player(const Player&);

		//accessors
		Hand& getHand();
		string getName();
		
		//mutators
		void setHand(const Hand&);
		void setName(string);
		
		//methods for adding and removing cards
		void rmC(int);
		void addC(const Card&);

		//asking for suits of 8
		void suitOfEights(int rank, int suit);
		int checkOption(const string);
		void loopOption(string &, int &);
		void optionForA(int &);
		void printSuitForEights(int);
		void optionForB(int &);
		int suitOfEights();

		// checkers
		int checkIfCardPlayable(int rank, int suit);
};

#endif