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
** Function : Deck()
** Description: set Deck
** Input: nothing
** Output: deck set
******************************************************/
Deck::Deck()
{
	for(int i = 0; i < 52; i++)
	{
		Card c = Card();
		this->cards[i] = c;
	}
	this->n_cards = 52;
}

/******************************************************
** Function : get_size()
** Description: get num Cards
** Input: nothing
** Output: num Cards
******************************************************/
int Deck::get_size()
{
	return n_cards;
}

/******************************************************
** Function : getCards()
** Description: getCards
** Input: nothing
** Output: cards
******************************************************/
Card* Deck::getCards()
{
	return cards;
}

/******************************************************
** Function : Deck(Card *&, int)
** Description: set Deck
** Input: Card* const &arr, int size
** Output: copy
******************************************************/
Deck::Deck(Card* const &arr, int size)
{
	if(size > 0)
	{
		for(int i = 0; i < size; i++)
		{
			this->cards[i].set_rank(arr[i].get_rank());
			this->cards[i].set_suit(arr[i].get_suit());
		}
		this->n_cards = size;
	}
}

/******************************************************
** Function : ~Deck()
** Description: Deck gets destroyed here
** Input: nothing
** Output: deck destroyed
******************************************************/
Deck::~Deck()
{
	// DECK GOT DESTROYED HERE.
}

/******************************************************
** Function : Deck(const Deck &other)
** Description: copy constructor
** Input: Deck&
** Output: deck copied from one to another
******************************************************/
Deck::Deck(const Deck &other)
{
	if(other.n_cards > 0)
	{
		this->n_cards = other.n_cards;
		
		for(int i = 0; i < n_cards; i++)
		{
			this->cards[i].set_rank(other.cards[i].get_rank());
			this->cards[i].set_suit(other.cards[i].get_suit());
		}
	}
	else
	{
		this->n_cards = 0;
	}
}

/******************************************************
** Function : printCards()
** Description: print cards
** Input: none
** Output: print cards with rank and suit
******************************************************/
void Deck::printCards()
{
	for(int i = 0 ; i < 52; i++)
	{
		cout << "Rank: " << cards[i].get_rank() << "Suit: " << cards[i].get_suit() << endl;
	}
}

/******************************************************
** Function : changeNum(int num_cards, int minus)
** Description: changeNum
** Input: int num_cards, int minus
** Output: changedNum
******************************************************/
void Deck::changeNum(int num_cards, int minus)
{
	this->n_cards = num_cards - minus;
}

/******************************************************
** Function : Deck::operator=(const Deck &other)
** Description: operation overloading
** Input: Deck&
** Output: operation overloading done
******************************************************/
void Deck::operator=(const Deck &other)
{
	if(n_cards > 0)
	{
		memset(this->cards,0,52);
	}

	if(other.n_cards > 0)
	{
		n_cards = other.n_cards;

		for(int i= 0; i < other.n_cards; i++)
		{
			this->cards[i].set_rank(other.cards[i].get_rank());
			this->cards[i].set_suit(other.cards[i].get_suit());
		}
	}
	else
	{
		this->n_cards = 0;
	}
}

/******************************************************
** Function : dealCardToPlayer(Hand &CAH, Deck& deckC, int numCard)
** Description:deal card to players
** Input: int, hand and deck
** Output: yeay
******************************************************/
void Deck::dealCardToPlayer(Hand &CAH, Deck& deckC, int numCard)
{
	int CardsStored = 0, counter = 0, i, loopAgain = 0;
	Card* holdC = deckC.getCards();

	while(loopAgain == 0)
	{
		for(i = 0; i < 52; i++)
		{
			if((holdC[i].get_rank() != 0) && (holdC[i].get_suit() != 0))
			{
				if(counter == numCard)
				{
					loopAgain = 1;
					break;
				}

				CAH.addCard(holdC[i]);
				holdC[i].set_cardtozero();
				i++;
				counter++;
			}
			else if(loopAgain == 0 && i == 51)
			{
				cout << "Stock is empty." << endl;
				loopAgain = 1;
				break;
			}
		}
	}
}

/******************************************************
** Function : addCard()
** Description: addCard to Card
** Input: Card*&, int
** Output: added card
******************************************************/
void Deck::add_cards(Card* const &card2, int size)
{
	for(int i = 0; i < size; i++)
	{
		this->cards[i].set_rank(card2[i].get_rank());
		this->cards[i].set_suit(card2[i].get_suit());
	}
	this->n_cards = size;
}

/******************************************************
** Function : shuffling()
** Description: shuffle deck
** Input: none
** Output: shuffled deck
******************************************************/
void Deck::shuffling()
{
	srand(time(0));

	for(int i = 0; i < 52; i++)
	{
		int randNum = rand()%52;
		swap(cards[i],cards[randNum]);
	}
}

/******************************************************
** Function : cards52()
** Description: fill deck with 52 cards
** Input: none
** Output: deck filled
******************************************************/
void Deck::cards52()
{
	int outerloop = 0;
	for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 13; j++)
			{
				cards[outerloop].set_ranksuit(i+1,j+1);
				outerloop++;
			}
		}
}
