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
** Function : Player()
** Description: set player 
** Input: none
** Output: set player
******************************************************/
Player::Player()
{
	this->hand = Hand();
	name = "empty";
}

/******************************************************
** Function : Player(const Hand& hand2, string n)
** Description: set player to given values
** Input: Hand& and string
** Output: set
******************************************************/
Player::Player(const Hand& hand2, string n)
{
	this->hand = hand2;
	this->name = n;
}

/******************************************************
** Function : ~Player()
** Description: destructor
** Input: none
** Output: player gets destroyed
******************************************************/
Player::~Player()
{
	// PLAYER GOT DESTROYED HERE.
}

/******************************************************
** Function : Player(const Player&)
** Description: copy player
** Input: Player&
** Output: player gets copied
******************************************************/
Player::Player(const Player& oplayer)
{
	string str1 = oplayer.name;
	if(!(str1.compare("empty")))
	{
		this->hand = oplayer.hand;
		this->name = oplayer.name;
	}
}

/******************************************************
** Function : getHand()
** Description: return hand
** Input: none
** Output: return hand
******************************************************/
Hand& Player::getHand()
{
	return this->hand;
}

/******************************************************
** Function : getName()
** Description: get name
** Input: none
** Output: return name
******************************************************/
string Player::getName()
{
	return this->name;
}

/******************************************************
** Function : setHand()
** Description: sethand
** Input: none
** Output: set hand to new hand
******************************************************/
void Player::setHand(const Hand& ohand)
{
	this->hand = ohand;
}

/******************************************************
** Function : setName()
** Description: set name
** Input: none
** Output: set name to other name
******************************************************/
void Player::setName(string oname)
{
	this->name = oname;
}

/******************************************************
** Function : rmC(int)
** Description: removecard()
** Input: none
** Output: remove card
******************************************************/
void Player::rmC(int index)
{
	hand.removeCard(index);
}

/******************************************************
** Function : addC(card&)
** Description: addcard
** Input: none
** Output: card added
******************************************************/
void Player::addC(const Card &member)
{
	hand.addCard(member);
}

/******************************************************
** Function : checkOption(string)
** Description: check if option valid
** Input: string
** Output: return 0 if true
******************************************************/
int Player::checkOption(const string option)
{
	for(int i = 0; i < option.length(); i++)
	{
		if(option.length() == 1)
		{
			if(option[i] == '1' || option[i] == '2')
			{
				return 0;
			}
			if(option[i] == '3' || option[i] == '4')
			{
				return 0;
			}
		}
	}
	return 1;
}

/******************************************************
** Function : loopOption(string, int&)
** Description: loop option until option given is valid
** Input: string, int&
** Output: print
******************************************************/
void Player::loopOption(string &option, int &destination)
{
	int loopA = 0;
	while(loopA == 0)
	{
		if(checkOption(option) == 0)
		{
			loopA = 1;
			stringstream changeToInt(option);
			changeToInt >> destination;
		}
		else
		{
			cout << "The number you chose wasn't an option. Choose from 1-4:" << endl;
			cin >> option;
		}
	}
}

/******************************************************
** Function : optionForA(int&)
** Description: option for eights
** Input: int&
** Output: print
******************************************************/
void Player::optionForA(int &returnNum)
{
	string optionValid;
	cout << "Magic eight! Which suit would you like your opponent to match?" << endl;
	cout << "Choose one of these suits:" << endl;
	cout << "(1) Diamonds." << endl;
	cout << "(2) Clubs." << endl;
	cout << "(3) Hearts." << endl;
	cout << "(4) Spades." << endl;
	cin >> optionValid;
	loopOption(optionValid, returnNum);
}


/******************************************************
** Function : printSuitForEights(int)
** Description: print suit
** Input: int
** Output: print
******************************************************/
void Player::printSuitForEights(int returnNum)
{
	if(returnNum == 1)
	{
		cout << "Diamonds";
	}
	else if(returnNum == 2)
	{
		cout << "Clubs";
	}
	else if(returnNum == 3)
	{
		cout << "Hearts";
	}
	else if(returnNum == 4)
	{
		cout << "Spades";
	}
}

/******************************************************
** Function : optionForB(int&)
** Description: print option for b
** Input: int
** Output: print
******************************************************/
void Player::optionForB(int &returnNum)
{
	srand(time(0));
	returnNum = rand()%4 + 1;

	cout << endl << endl <<  "=====================================" << endl;
	cout << endl << "   Player B has played 8";
	cout << " of ";
	printSuitForEights(returnNum);
	cout << endl << endl<< "=====================================" << endl << endl;
}

/******************************************************
** Function : suitofeights()
** Description: print suit
** Input: none
** Output: direct each to their own options
******************************************************/
int Player::suitOfEights()
{
	int returnNum = 0;
	// if player is user.
	if(this->name == "A")
	{
		optionForA(returnNum);
	}
	else if(this->name == "B")
	{
		optionForB(returnNum);
	}

	return returnNum;
}