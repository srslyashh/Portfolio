# Crazy Eights
###### CS 162 - Fall 2020

## Description

A C++ program that shuffles a deck of cards and give 7 cards to each the user and the robot. The remaining card would be compiled in a stack called “stock” while facing down (Rank and suit remain hidden). The top card would be in a separated pile. The game starts with the card from the user, having to have the same rank or suit as the card in the separated pile. The card then is placed on top of that pile. Then the robot gets to play a card, with the same rank/suit from the card on top of the pile. In the case where either user or robot doesn’t have any cards with required rank or suit, they need to draw from stock (they will stop drawing until they find a card they could play, or until the deck runs out of cards). The game continues until one player gets rid of all the cards, or until all the cards are drawn and no one could play. One becomes a winner in this game by having no cards at the end, or by becoming the player with the least amount of cards. 

## Command 

Run the program with: 

      make

Then, run: 

      ./ass2

## Game's Flow

1. Shuffle the cards and give 7 cards to each player.
2. Separate the remaining cards in a stack called “stock” and make sure they’re faced down.
3. The top of the remaining cards should be in a different pile, and have it turned over.
4. User plays a card
5. Has to play a card that has the same rank/suit as the one on top of the remaining cards.
6.	Could play eights of any suit, then ask the user to specify which suit they want the next player to match. 
    -	If the user doesn’t have such card, make them draw a card until they find one, they could play with or until the deck runs out of cards.
    -	If the user does have such card, put the card on top of the pile.
 7.	Print the state of the game after each turn.
8. Get the robot/ Player B to play
  - Has to play a card that has the same rank/suit as the one on top of the remaining cards.
  -	Could play eights of any suit, then ask the user to specify which suit they want the next player to match. 
  9.	If the user doesn’t have such card, make them draw a card until they find one, they could play with or until the deck runs out of cards.
10.	If the user does have such card, put the card on top of the pile.
11.	Game continues
  -	The game continues and ends only if the deck runs out of cards and no one can play a card or if one player has gotten rid of all of their cards. 
  -	If neither player has 0 cards at the end of the game, the player with the least amount of cards wins.

## Requirements

The program should do the following:
- Set up a deck of 52 cards as described above.
- Shuffle the deck (i.e. randomize the order of cards).
- Deal the cards to the two players.
- Play a game of Crazy Eights as described above, with the following gameplay features:
- Print the current state of the game (e.g. the cards held by the human player and the card of on the top of the pile) after each turn (keeping the computer player's cards hidden).
- On the human player's turn, prompt the user for a card to play. When they enter a card, either put the card on top of the pile or have them draw a card from the deck if they can't play. If the card is an 8, prompt the user to declare a suit for the next player. 
- Once the game is over, you should announce the winner and ask the user if they want to play again.
- You should not have any memory leaks in your program.


 
