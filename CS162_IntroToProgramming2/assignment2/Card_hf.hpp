#ifndef CARD_HF_HPP
#define CARD_HF_HPP

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <sstream>


struct Position
{
    int x;
    int y;
};


class Card
{
	private:
		int rank;
		int suit;

	public:
		Card();
		Card(int, int);
		Card(Position&);
 
		// destroyer
		~Card();

		// accessors
		int get_rank() const;
		int get_suit() const;
		int notZero();
		Position* get_position();

		// mutators
		void emptyCard();
		void set_rank(int);
		void set_suit(int);
		void set_cardtozero();
		void set_ranksuit(int, int);
		void set_position(const Position&);

		// Print functions
		void printSuit();
		void printRank();
};

#endif