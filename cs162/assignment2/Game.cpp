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
** Function : Game()
** Description: initialize Game()
** Input: none
** Output: initialized Game
******************************************************/
Game::Game()
{
	cards = Deck();
	cards.cards52();
	cards.shuffling();

	topCard();

	// A here means player is user and B means that player is computer.
	players[0] = Player(Hand(), "A");
	players[1] = Player(Hand(), "B");
}

/******************************************************
** Function : ~Game()
** Description: game destroyed
** Input: none
** Output: game destroyed
******************************************************/
Game::~Game()
{
	// game gets destroyed here.
}

/******************************************************
** Function : getDeck()
** Description: get deck
** Input: none
** Output: return cards
******************************************************/
Deck& Game::getDeck()
{
	return cards;
}

/******************************************************
** Function : getPlayer()
** Description: return players
** Input: none
** Output: return players
******************************************************/
Player* Game::getPlayer()
{
	return players;
}

/******************************************************
** Function : getTopPile()
** Description: return top pile
** Input: none
** Output: return top pile
******************************************************/
Card& Game::getTopPile()
{
	return top_pile;
}

/******************************************************
** Function : setTopCard(card&)
** Description: set top card to new card
** Input: none
** Output: set top card
******************************************************/
void Game::setTopCard(Card &newC)
{
	top_pile.set_rank(newC.get_rank());
	top_pile.set_suit(newC.get_suit());
}

/******************************************************
** Function : setTopCardForEigts(int, int)
** Description: set top card to new card
** Input: int
** Output: set top card
******************************************************/
void Game::setTopCardForEights(int rank, int suit)
{
	top_pile.set_rank(rank);
	top_pile.set_suit(suit);
}

/******************************************************
** Function : topCard()
** Description: see top card at top
** Input: int
** Output: fill top card position
******************************************************/
void Game::topCard()
{
	Card* holderforc = cards.getCards();
	int loopAgain = 0;

	while(loopAgain == 0)
	{
		for(int i = 0; i < 1; i++)
		{
			if(holderforc[i].get_rank() != 0 && holderforc[i].get_suit() != 0)
			{
				top_pile = holderforc[i];
				holderforc[i].set_cardtozero();
				loopAgain = 1;
			}
		}
	}
	cards.changeNum(cards.get_size(),1);
}

/******************************************************
** Function : checkOptG(const string, int)
** Description: check option 
** Input: string, int
** Output: return 0 if true
******************************************************/
int Game::checkOptG(const string option, int numCards)
{
	int holder = 0;
	stringstream changeToInt(option);
	changeToInt >> holder;

	if(0 < holder && holder <= numCards)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

/******************************************************
** Function : loopOptG(string &, int&, int)
** Description: check option 
** Input: string, int, int
** Output: ask for another value if isnt true
******************************************************/
void Game::loopOptG(string &option, int &destination, int numCards)
{
	int loopA = 0;
	while(loopA == 0)
	{
		if(checkOptG(option, numCards) == 0)
		{
			loopA = 1;
			stringstream changeToInt(option);
			changeToInt >> destination;
		}
		else
		{
			cout << "The number you chose wasn't an option." << endl;
			cin >> option;
		}
	}
}

/******************************************************
** Function : distributeUserCards()
** Description: distribute 7 cards to each users
** Input: none
** Output: 7 cards in hand
******************************************************/
void Game::distributeUserCards()
{
	Hand& handPlayer0 = players[0].getHand();
	Deck& getDeckV = getDeck();

	cards.dealCardToPlayer(handPlayer0, getDeckV, 7);
	Hand& handPlayer1 = players[1].getHand();
	cards.dealCardToPlayer(handPlayer1, getDeckV, 7);

	cout << endl << "Seven initial cards have been distributed to each player." << endl << endl;
}

/******************************************************
** Function : printInitialWelcome()
** Description: printInitialWelcome
** Input: none
** Output: print
******************************************************/
void Game::printInitialWelcome()
{
	cout << endl;
	cout << "======================" << endl;
	cout << "| CRAZY EIGHT'S GAME |" << endl;
	cout << "======================" << endl;
	cout << endl;
}

/******************************************************
** Function : printStuff()
** Description: print for player A
** Input: none
** Output: print
******************************************************/
void Game::printStuff()
{
	string option;
	Hand &holder = players[0].getHand();
	Card*& holderforhandc = holder.getCards();
	Card &chold = getTopPile();

	cout << "Player B has " << (players[1].getHand()).getNumCards() << " cards to play." << endl;
	printTopCard(chold);

	holder.printCardsAtHand();
	whichOption(holder,holderforhandc);
}

/******************************************************
** Function : whichOption(hand&, card*&)
** Description: which option
** Input: none
** Output: print
******************************************************/
void Game::whichOption(Hand &holder, Card*& holderforhandc)
{
	Deck& deckC = getDeck();
	string option;
	int optInt = 0, loopAgain = 0, gameover = 1, stockisEmpty = 1;
	while(loopAgain == 0)
	{
		gameover = isGameOver();
		if(gameover == 0)
		{
			printWinner();
			loopAgain = 1;
		}
		else if(gameover == 1)
		{
            stockisEmpty = checkIfStockEmpty();
			cout << endl << "Which operation would you like to do?" << endl;
			cout << "(1) Use card at hand." << endl;
			cout << "(2) Draw from stock." << endl;
			cin >> option;
			loopOptG(option,optInt,2);
			if(optInt == 1)
			{
				cardSelected(holder,holderforhandc);
				loopAgain = 1;
			}
			else if(optInt == 2 && stockisEmpty == 1)
			{
				cards.dealCardToPlayer(holder,deckC,1);
				printTopCard(getTopPile());
				holder.printCardsAtHand();
			}
		}
	}
	
}

/******************************************************
** Function : isSelectedValid
** Description: which option
** Input: int, card, int
** Output: preturn 0 if true
******************************************************/
int Game::isSelectedValid(int index, Card*& holderforhandc, int player = 0)
{
	Card& topCard = getTopPile();

	// if the card chosen matches with either suit/rank, return 0.
	if(holderforhandc[index-1].get_rank() == topCard.get_rank())
	{
		return 0;
	}
	else if(holderforhandc[index-1].get_suit() == topCard.get_suit())
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/******************************************************
** Function : isSelectedValidT
** Description: keep on asking for data until true
** Input: int, card, int
** Output: print
******************************************************/
void Game::isSelectedValidT(int &index, Card*& holderforhandc, int player = 0)
{
	int loopAgain = 0;
	while(loopAgain == 0)
	{
		if(isSelectedValid(index, holderforhandc, player) == 0)
		{
			loopAgain = 1;
		}
		else 
		{
			cout << "The card didn't match with the top card's suit or rank. Enter another option: ";
			cin >> index;
		}
	}
}

/******************************************************
** Function : isCardSelectedEights
** Description: is card selected eights
** Input: int, card, int
** Output: print
******************************************************/
void Game::isCardSelectedEights(int &index, Card*& holderforhandc, int &storesuit)
{
	if(holderforhandc[index-1].get_rank() == 8)
	{
		players[0].optionForA(storesuit);
	}
}

/******************************************************
** Function : printASelection
** Description: print what A has selected
** Input: int, card, int
** Output: print
******************************************************/
void Game::printASelection(Card *&handA, int option, Card& hold)
{
	cout << endl << endl <<  "=====================================" << endl;
	cout << endl << "   Player A has played ";
	handA[option].printRank();
	cout << " of ";
	handA[option].printSuit();
	cout << endl << endl << "=====================================" << endl << endl;
	printTopCard(hold);
}

/******************************************************
** Function : cardSelected()
** Description: what does the user select, loop until 
** a card can be used
** Input: hand&holder
** Output: print
******************************************************/
void Game::cardSelected(Hand &holder, Card*& holderforhandc)
{
	string option;
	int optInt, storesuit = 0;
	Card& hold = getTopPile();
	cout << endl << "Which card would you like to select? Option: ";
	cin >> option;
	loopOptG(option,optInt, holder.getNumCards());
	isCardSelectedEights(optInt, holderforhandc, storesuit);

	if(storesuit == 0)
	{
		isSelectedValidT(optInt, holderforhandc);
		setTopCard(holderforhandc[optInt-1]);
	}
	else
	{
		setTopCardForEights(8, storesuit);
	}
	printASelection(holderforhandc,optInt-1, hold);
	holder.removeCard(optInt-1);
}

/******************************************************
** Function : checkIfStockEmpty()
** Description: check If Stock Empty
** Input: hand&holder
** Output: return 0 if true
******************************************************/
int Game::checkIfStockEmpty()
{
	int empty = 0;
	Deck& holdDeck = getDeck();
	Card* deckcards = holdDeck.getCards();

	for(int i = 0; i < 52; i++)
	{
		if(deckcards[i].get_rank() != 0 || deckcards[i].get_suit() != 0)
		{
			empty++;
		}
	}
	if(empty == 0)
	{
		return 0;
	}
	return 1;
}

/******************************************************
** Function : checkIfHandEmpty()
** Description: check If hand empty
** Input: hand&holder
** Output: return 0 if true
******************************************************/
int Game::checkIfHandEmpty()
{
	// to check if hand on either two players are empty.
	for(int i = 0; i < 2; i++)
	{
		Hand& playerhold = players[i].getHand();
		if(playerhold.getNumCards() == 0)
		{
			return 0;
		}
	}
	return 1;
}

/******************************************************
** Function : ardsUnplayable()
** Description: check If card unplayable
** Input: none
** Output: return 1 if true
******************************************************/
int Game::cardsUnplayable()
{
	Card& topPile = getTopPile();
	for(int i = 0; i < 2; i++)
	{
		Hand& hand = players[i].getHand();
		Card*& cardsAH = hand.getCards();
		for(int j = 0; j < hand.getNumCards(); j++)
		{
			if(cardsAH[j].get_rank() == topPile.get_rank() || 
			cardsAH[j].get_suit() == topPile.get_suit())
			{
				return 1;
			}
			else if(cardsAH[j].get_rank() == 8)
			{
				return 1;
			}
		}
	}
	return 0;
}

/******************************************************
** Function : isGameOver()
** Description: check if game over
** Input: none
** Output: return 0 if true
******************************************************/
int Game::isGameOver()
{
	if((checkIfStockEmpty() == 0 && cardsUnplayable() == 0 )|| checkIfHandEmpty() == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/******************************************************
** Function : matchCard(card*&, int, int, int)
** Description: see if any cards match the top pile
** Input: none
** Output: return 0 if true
******************************************************/
int Game::matchCard(Card*& computerC, Card& topPile, int playNum, int& option, int &eights)
{
	Hand& hand = players[playNum].getHand();
	
	for(int i = 0; i < hand.getNumCards(); i++)
	{
		if(computerC[i].get_rank() == topPile.get_rank() || 
		   computerC[i].get_suit() == topPile.get_suit())
		{
			option = i;
			return 0;
		}
		else if(computerC[i].get_rank() == 8)
		{
			eights = 1;
			option = i;
			return 0;
		}
	}
	return 1;

}

/******************************************************
** Function : eightsComp()
** Description: eights for computer
** Input: none
** Output: call other function for this
******************************************************/
void Game::EightsComp(int option, Card *& computerC)
{
	int suit = 0;
	if(computerC[option].get_rank() == 8)
	{
		players[1].optionForB(suit);
		setTopCardForEights(8, suit);
	}
}

/******************************************************
** Function : setTopCard()
** Description: set top card for player B
** Input: Card*&, int
** Output: call other function for this
******************************************************/
void Game::setTopCardForB(Card *& computerC, int option)
{
	setTopCard(computerC[option]);
	cout << endl << endl <<  "=====================================" << endl;
	cout << endl << "   Player B has played ";
	computerC[option].printRank();
	cout << " of ";
	computerC[option].printSuit();
	cout << endl << endl << "=====================================" << endl << endl;
	
}

/******************************************************
** Function : printTopCard()
** Description: print top card
** Input: Card*
** Output: print top card
******************************************************/
void Game::printTopCard(Card& topPile)
{
	cout << endl << "========================================" << endl;
	cout << endl << "            CARD TO MATCH: " << endl;
	cout << "      Rank: ";
	topPile.printRank();
	cout << " , Suit: ";
	topPile.printSuit();
	cout << endl << endl << "========================================" << endl;
}

/******************************************************
** Function : computerTurn()
** Description: let computer play
** Input: none
** Output: computer's turn
******************************************************/
void Game::computerTurn()
{
	int option = 0, match = 0, eights = 0, loopAgain = 0, gameover = 1, isStockE = 1;
	Hand& computerH = players[1].getHand();
	Card*& computerC = computerH.getCards();
	Deck& deckC = getDeck();
	Card& topPile = getTopPile();

	while(loopAgain == 0)
	{
		gameover = isGameOver();
		if(gameover == 0)
		{
			loopAgain = 1;
		}
		else if(gameover == 1)
		{
            isStockE = checkIfStockEmpty();
            match = matchCard(computerC, topPile, 1, option, eights);
			if(match == 0)
			{
				if(eights == 1)
				{
					EightsComp(option, computerC);
                    computerH.removeCard(option);
					loopAgain = 1;
				}
				else if(eights == 0)
				{
					setTopCardForB(computerC, option);
                    computerH.removeCard(option);
					loopAgain = 1;
				}
			}
			else if(match == 1 && isStockE == 1)
			{
				cards.dealCardToPlayer(computerH, deckC, 1);
			}
		}
	}
}

/******************************************************
** Function : printMessage(int)
** Description: winning message
** Input: none
** Output: print
******************************************************/
void Game::printMessage(int player)
{
	if(player == 0)
	{
		cout << " ========================================" << endl;
		cout << " | CONGRATULATIONS! YOU ARE THE WINNER! |" << endl;
		cout << " ========================================" << endl;
	}
	else if(player == 1)
	{
		cout << " ========================================" << endl;
		cout << " | WOMP WOMP. PLAYER B WON THIS GAME :( |" << endl;
		cout << " ========================================" << endl;	
	}
	else
	{
		cout << " ========================================" << endl;
		cout << " |       AWEEEE THIS GAME IS A TIE.      |" << endl;
		cout << " ========================================" << endl;
	}
}

/******************************************************
** Function : theLeastCards
** Description: who has the least cards
** Input: none
** Output: return by numbers
******************************************************/
int Game::theLeastCards()
{
	Hand& player0 = players[0].getHand();
	Hand& player1 = players[1].getHand();

	if(player0.getNumCards() > player1.getNumCards())
	{
		return 0;
	}
	else if(player0.getNumCards() < player1.getNumCards())
	{
		return 1;
	}
	else if(player0.getNumCards() == player1.getNumCards())
	{
		return 2;
	}
}

/******************************************************
** Function : whoseEmpty()
** Description: check who is empty
** Input: none
** Output: return by numbers
******************************************************/
int Game::whoseEmpty()
{
	Hand& player0 = players[0].getHand();
	Hand& player1 = players[1].getHand();

	if(player0.getNumCards() == 0)
	{
		return 0;
	}
	else if(player1.getNumCards() == 0)
	{
		return 1;
	}
}

/******************************************************
** Function : printwinner
** Description: print winner
** Input: none
** Output: print
******************************************************/
void Game::printWinner()
{
	int player0 = 0, player1 = 0, winner = 0;
	if(checkIfHandEmpty() == 0)
	{
		winner = whoseEmpty();
		printMessage(winner);
	}
	else if(checkIfStockEmpty()== 0 && cardsUnplayable() == 0)
	{
		winner = theLeastCards();
		printMessage(winner);
	}
}

/******************************************************
** Function : playAgain()
** Description: play again or not
** Input: int
** Output: changed value in main
******************************************************/
void Game::playAgain(int &loopAgain)
{
	string option;
	int holder = 0;
	cout << "The game is over. Would you like to play again?" << endl;
	cout << "(1) Yes" << endl;
	cout << "(2) No" << endl;
	cin >> option;
	loopOptG(option, holder, 2);
	loopAgain = holder -1;
}