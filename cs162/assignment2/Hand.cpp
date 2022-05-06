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
** Function : Hand()
** Description: initialization for hand()
** Input: none
** Output: initialized hand
******************************************************/
Hand::Hand()
{
	this->cards = NULL;
	this->n_cards = 0;

}

/******************************************************
** Function : Hand(Card* const &arr,int num)
** Description: initialized hand with data given
** Input: card*& and num
** Output: initialized hand
******************************************************/
Hand::Hand(Card* const &arr,int num)
{
	if(num > 0)
	{
		this->cards = new Card[num];

		for(int i = 0; i < num; i++)
		{
			this->cards[i].set_rank(arr[i].get_rank());
			this->cards[i].set_suit(arr[i].get_suit());
		}
		n_cards = num;
	}
}

/******************************************************
** Function : ~Hand()
** Description: hand destructor
** Input: none
** Output: Hand gets destroyed
******************************************************/
Hand::~Hand()
{
	if(this->n_cards >0)
	{
		delete[] cards;
	}
	this->cards = NULL;
}

/******************************************************
** Function : getNumCards()
** Description: get num cards
** Input: none
** Output: return value
******************************************************/
int Hand::getNumCards()
{
	return n_cards;
}

/******************************************************
** Function : getCards()
** Description: get cards
** Input: none
** Output: return value
******************************************************/
Card*& Hand::getCards()
{
	return cards;
}

/******************************************************
** Function : getSuit()
** Description: get suit
** Input: none
** Output: return value
******************************************************/
int Hand::getSuit(int num)
{
	return cards[num].get_suit();
}

/******************************************************
** Function : getRank()
** Description: get rank
** Input: none
** Output: return value
******************************************************/
int Hand::getRank(int num)
{
	return cards[num].get_rank();
}


/******************************************************
** Function : Hand(const Hand&)
** Description: copy constructor
** Input: Hand&
** Output: copied data
******************************************************/
Hand::Hand(const Hand &hand2)
{
	if(hand2.n_cards > 0)
	{
		this->cards = new Card[hand2.n_cards];
		this->n_cards = hand2.n_cards;
		for(int i = 0; i < n_cards; i++)
		{
			this->cards[i].set_rank(hand2.cards[i].get_rank());
			this->cards[i].set_suit(hand2.cards[i].get_suit());
		}
	}
	else
	{
		this->n_cards = 0;
	}
}

/******************************************************
** Function : operator=(const Hand &hand2)
** Description: operation overloading
** Input: Hand&
** Output: copied data
******************************************************/
Hand& Hand::operator=(const Hand &hand2)
{
	if(hand2.n_cards > 0)
	{
		delete[] this->cards;
		this->cards = new Card[hand2.n_cards];
		this->n_cards = hand2.n_cards;

		for(int i = 0; i < hand2.n_cards; i++)
		{
			this->cards[i].set_rank(hand2.cards[i].get_rank());
			this->cards[i].set_suit(hand2.cards[i].get_suit());
		}
	}
	else
	{
		this->n_cards = 0;
	}
}

/******************************************************
** Function : addCard(Card&)
** Description: add card to hand
** Input: Card&
** Output: add card
******************************************************/
void Hand::addCard(const Card& member)
{
	Card *newarr = new Card[this->n_cards+1];

	if(this->n_cards > 0)
	{
		for(int i = 0; i < this->n_cards; i++)
		{
			// copy all the old data to the new arr
			newarr[i].set_rank(this->cards[i].get_rank());
			newarr[i].set_suit(this->cards[i].get_suit());		
		}
	}
	delete[] this->cards;
	this->cards = NULL;

	// add the new member
	newarr[this->n_cards].set_rank(member.get_rank());
	newarr[this->n_cards].set_suit(member.get_suit());

	this->cards = newarr;
	this->n_cards++;
}


/******************************************************
** Function : isCardChosenValid(int, int)
** Description: see if card chosen valid
** Input: int
** Output: return 0 if true, otherwise 1.
******************************************************/
int Hand::isCardChosenValid(int rank, int suit)
{
	for(int i = 0; i < this->n_cards; i++)
	{
		if(cards[i].get_rank() == rank && cards[i].get_suit() == suit)
		{
			// call emptyCard function to set the cards to zero.
			cards[i].emptyCard();
			return 0;
		}
	}
	return 1;
}

/******************************************************
** Function : removeCard(index)
** Description: remove card at given index
** Input: int
** Output: remove card
******************************************************/
void Hand::removeCard(int index)
{
	Card *newarr = new Card[this->n_cards - 1];
	int counter = 0, innercount = 1;

	// with the index given, set card to zero.
	cards[index].set_cardtozero();
	for(int i = 0; i < this->n_cards; i++)
	{
		if(this->cards[i].get_rank() != 0 && this->cards[i].get_suit() != 0)
		{
			newarr[counter].set_rank(this->cards[i].get_rank());
			newarr[counter].set_suit(this->cards[i].get_suit());
			counter++;
		}
	}

	delete[] this->cards;
	this->cards = NULL;
	cards = newarr;
	this->n_cards--;
}

/******************************************************
** Function : printCardsAtHand()
** Description: print cards at hand
** Input: none
** Output: print to screen
******************************************************/
void Hand::printCardsAtHand()
{
	int i = 0, counter = 0, num = 1;
	cout << "Your card(s) at hand: " << endl;

	while(counter < this->n_cards)
	{
		if(cards[i].get_rank() != 0 || cards[i].get_suit() != 0)
		{
			cout << "(" << num << ")" << " Rank: ";
			this->cards[i].printRank();
			cout << ", Suit: ";
			this->cards[i].printSuit();
			cout << endl;
			num++;
			counter++;
		}
		i++;
	}
}
