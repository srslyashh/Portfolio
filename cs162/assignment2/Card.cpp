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

/******************************************************
** Function : Card()
** Description: set rank and suit to 0
** Input: nothing
** Output: rank and suit set to 0
******************************************************/
Card::Card()
{
	rank = 0;
	suit = 0;
}

/******************************************************
** Function : ~Card()
** Description: destructor
** Input: nothing
** Output: card destructed
******************************************************/
Card::~Card()
{
	// CARD GOT DESTROYED HERE
}

/******************************************************
** Function : emptyCard()
** Description: set rank and suit to 0
** Input: nothing
** Output: rank and suit set to 0
******************************************************/
void Card::emptyCard()
{
	// zero here means that the card is empty.
	rank = 0;
	suit = 0;
}

/******************************************************
** Function : Card()
** Description: set rank and suit to ints
** Input:  ints
** Output: rank and suit set to ints
******************************************************/
Card::Card(int a, int b)
{
	rank = a;
	suit = b;
}

/******************************************************
** Function : Card(Position& position)
** Description: get position
** Input: Position&
** Output: rank and suit set to position
******************************************************/
Card::Card(Position& position)
{
	rank = position.x;
	suit = position.y;
}

/******************************************************
** Function : get_rank()
** Description: get rank
** Input: nothing
** Output: return rank
******************************************************/
int Card::get_rank() const
{
	return rank;
}

/******************************************************
** Function : get_suit()
** Description: get suit
** Input: nothing
** Output: return suit
******************************************************/
int Card::get_suit() const
{
	return suit;
}

/******************************************************
** Function : notZero()
** Description: check if rank and suit are zero.
** Input: nothing
** Output: return true or false
******************************************************/
int Card::notZero()
{
	if(rank != 0 && suit != 0)
	{
		return 0;
	}
	return 1;
}

/******************************************************
** Function : get_position()
** Description: get position
** Input: nothing
** Output: return position
******************************************************/
Position* Card::get_position()
{
	Position* hold = new Position;
	hold->x = rank;
	hold->y = suit;
	return hold;
}

/******************************************************
** Function : set_rank(int)
** Description: set rank to int
** Input: nothing
** Output: nothing
******************************************************/
void Card::set_rank(int a)
{
	rank = a;
}

/******************************************************
** Function : sset_suit(int b)
** Description: set suit to int
** Input: nothing
** Output: nothing
******************************************************/
void Card::set_suit(int b)
{
	suit = b;
}

/******************************************************
** Function : set_ranksuit(int)
** Description: set ranksuit to int
** Input: nothing
** Output: nothing
******************************************************/
void Card::set_ranksuit(int a, int b)
{
	suit = a;
	rank = b;
}

/******************************************************
** Function : set_position()
** Description: set position
** Input: nothing
** Output: nothing
******************************************************/
void Card::set_position(const Position& position)
{
	rank = position.x;
	suit = position.y;
}

/******************************************************
** Function : set_cardtozero()
** Description: set card rank and suit to 0
** Input: nothing
** Output: nothing
******************************************************/
void Card::set_cardtozero()
{
	this->rank = 0;
	this->suit = 0;
}

/******************************************************
** Function : printRank()
** Description: print Rank
** Input: nothing
** Output: print rank
******************************************************/
void Card::printRank()
{
	if(this->rank == 1)
	{
		cout << "A";
	}
	else if(this->rank == 11)
	{
		cout << "J";
	}
	else if(this->rank == 12)
	{
		cout << "Q";
	}
	else if(this->rank == 13)
	{
		cout << "K";
	}
	else
	{
		cout << this->rank;
	}
}

/******************************************************
** Function : printSuit()
** Description: printSuit
** Input: nothing
** Output: print suit
******************************************************/
void Card::printSuit()
{
	if(this->suit == 1)
	{
		cout << "Diamonds";
	}
	else if(this->suit == 2)
	{
		cout << "Clubs";
	}
	else if(this->suit == 3)
	{
		cout << "Hearts";
	}
	else if(this->suit == 4)
	{
		cout << "Spades";
	}
}