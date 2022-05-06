/*****************************************************
 ** Program: Assignment 2 - Text Game Adventure
 ** Author: Kathleen Ashley
 ** Date: January 25 2020
 ** Description: Taking the user choices for the game.
 ** Input: Positive integer. (1,2,3).
 ** Output: The output depends on the user's choice, and the output will
 ** come with the accumulated points at the end of the game.
 *****************************************************/

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
	srand(time(NULL));

 	/* I assume the number of firstchoice would be either 1 or 2.
	 * So an unsigned short is perfect. (min 0, max 65,535).
	 */
	unsigned short firstchoice;

	/* I assume secondchoice is either 1,2 or 1,2,3. Hence,
	 * an unsigned short would be sensible since i wouldn't need
	 * store a large number. (min 0, max 65,535).
	 */
	unsigned short secondchoice;

	/* I assume thirdchoice is either 1,2,3 or 1,2. So,
	 * an unsigned short would be sufficient. Because it would
	 * never be less than 0. (min 0, max 65,535).
	 */
	unsigned short thirdchoice;

	/* I assume points would be between 0 to 70. Hence,
	 * unsigned short is perfect because it would never store
	 * values below 0. (min 0, max 65,535).
	 */
	unsigned short points = 0;

	/* I assume replaygame would only be either 0 or 1.Thus, unsigned short
	 * is sufficient. (min 0, max 65,535).
	 */
	unsigned short replaygame = 0;

	while(replaygame == 0)
	{
		/* this is to make sure that even when the game is repeated, points will
		 * always start from 0.
		 */
		points = 0;
		cout << "You've been in your cabin in the woods for a few days, when " << endl
	 			 << "the news of people turning into zombies due to a virus," << endl
				 << "broke. You.." << endl;
		cout << "(1) Pack up and try to go to a place that is safer." << endl;
		cout << "(2) Try to arm up and guard your cabin." << endl;
		cin >> firstchoice;
		points+= 10;

		if (firstchoice == 1)
		{
			cout << "\nYou gain 10 points for a score of " << points << " points." << endl;
			cout << endl;
			cout << "You finish packing up essentials, you leave your cabin and you.."
					 << endl;
			cout << "(1) Head to the nearest stop with the car to stock up food."
					 << endl;
			cout << "(2) Go deeper inside the woods for a safer place with" << endl
					 << "    limited food left." << endl;
			cin >> secondchoice;
			points+= 10;

				if (secondchoice == 1)
				{
					cout << "\nYou gain 10 points for a score of " << points << " points." << endl;
					cout << endl;
					cout << "You finally arrive to the nearest stop.. However, " << endl
							 << "it's eerily quiet. You.." << endl;
					cout << "(1) Go to the store right away and take whatever you" << endl
							 << "    need and leave." << endl;
					cout << "(2) You try to venture around the place a little bit." << endl
							 << "    See what's going on." << endl;
					cin >> thirdchoice;

					if (thirdchoice == 1)
					{
						cout << endl;
						points+= 50;
						cout << "Game over. You're a good survivor! Here's 50 points" << endl
								 << "for your cleverness." << endl;
						cout << "Your points accumulated is.." << points << "!" << endl;
					}
					else if (thirdchoice == 2)
					{
						cout << endl;
						if(rand() % 2 == 0)
						{
							points-= 10;
							cout << "A zombie jumped on you out of nowhere and started" << endl
									 << "eating your brains.. Ouch.." << endl;
							cout << "You lose 10 points for a score of " << points << " points."
									 << endl;
							cout << "Game over. Your points accumulated is.." << points << "."
								 	 << endl;
						}
						// if rand() % 2 != 0, then fall to this case.
						else
						{
							points+= 50;
							cout << "You noticed a zombie coming out of nowhere, and " << endl
									 << "you shot him right away in the head. You survived.." << endl;
							cout << "Congratulations for surviving. Here's 50 points " << endl
									 << "as a reward." << endl;
							cout << "Your points accumulated is.." << points << "!" << endl;
						}
					}
					// if thirdchoice is other than 1 or 2, the program quits.
					else
					{
						cout << endl;
						cout << "That is not a valid choice." << endl;
						return 1;
					}
				}
				else if (secondchoice == 2)
				{
					cout << "\nYou gain 10 points for a score of " << points << " points." << endl;
					cout << endl;
					points-= 10;
					cout << "You died due to dehydration and starvation. There was" << endl
							 << "no source of water around.." << endl;
					cout << "You lose 10 points for a score of " << points << " points."
							 << endl;
					cout << "Game over. Your points accumulated is.." << points << "."
							 << endl;
				}
				// if secondchoice is other than 1 or 2, the program quits.
				else
				{
					cout << "That is not a valid choice." << endl;
					return 1;
				}
		}
		else if (firstchoice == 2)
		{
			cout << "\nYou gain 10 points for a score of " << points << " points." << endl;
			cout << endl;
			cout << "After a few days of guarding your cabin, you woke up to " << endl
					 << "someone knocking your door, while screaming,\"PLEASE!!" << endl
					 << "HELP MY WIFE!! SHE'S DYING!!\" You.." << endl;
			cout << "(1) Say sorry you can't help and tell them to go to " << endl
					 << "    another cabin nearby.. Wherever that is.." << endl;
			cout << "(2) Open the door and help them as much as you can." << endl;
			cout << "(3) Threaten them to leave or else you would shoot them." << endl;
			cin >> secondchoice;

			if(secondchoice == 1)
			{
				cout << endl;
				cout << "\nYou gain 10 points for a score of " << points << " points." << endl;
				points+= 10;
				if(rand() % 2 == 0)
				{
					points-= 10;
					cout << "You died when the stranger tried to break in and shot" << endl
							 << "you with the gun he was carrying.." << endl;
					cout << "You lose 10 points for a score of " << points << " points."
							 << endl;
					cout << "Game over. Your points accumulated is.." << points << "."
							 << endl;
				}
				// if rand() % 2 != 0, then fall to this case.
				else
				{
					cout << endl;
					points+= 50;
					cout << "Wow. what a good luck! The stranger tried to break" << endl
							 << "in and to shoot you. But he missed. So you shot him" << endl
							 << "and his wife.." << endl;
					cout << "Congratulations for surviving. Here's 50 points " << endl
							 << "as a reward." << endl;
					cout << "Your points accumulated is.." << points << "!" << endl;
				}
			}
			else if(secondchoice == 2)
			{
				cout << "\nYou gain 10 points for a score of " << points << " points." << endl;
				cout << endl;
				points+= 10;
				cout << "The man came inside the cabin, with a woman he " << endl
						 << "was carrying in his arms. You saw a bite mark on her" << endl
						 << "wrist.. Her skin was turning gray-ish pale. You.." << endl;
				cout << "(1) Buy her more time with her husband by giving her " << endl
						 << "    some pain killers." << endl;
				cout << "(2) Tell them to get out." << endl;
				cout << "(3) Insist that amputating her forearm would be the " << endl
						 << "    best shot for her to live." << endl;
				cin >> thirdchoice;
				cout << "\nYou gain 10 points for a score of " << points << " points." << endl;
				points+= 10;

				if(thirdchoice == 1)
				{
					cout << endl;
					points+= 50;
					cout << "You and the husband survived. As the wife turned," << endl
							 << "you shot her in the head.." << endl;
					cout << "Congratulations for surviving. Here's 50 points " << endl
							 << "as a reward." << endl;
					cout << "Your points accumulated is.." << points << "!" << endl;
				}
				else if(thirdchoice == 2)
				{
					if(rand() % 2 == 0)
					{
						cout << endl;
						points+= 50;
						cout << "The husband shot you of out frustration,but missed." << endl
								 << "You hold your gun right away and tell them you're" << endl
								 << "giving a chance for them to live. They left.." << endl
								 << "And you survived." << endl;
			 			cout << "Congratulations for surviving. Here's 50 points " << endl
			 					 << "as a reward." << endl;
						cout << "Your points accumulated is.." << points << "!" << endl;
					}
					// if rand() % 2 != 0, then fall to this case.
					else
					{
						cout << endl;
						points-= 10;
						cout << "The husband of the woman shot you out of frustration."<< endl
						 		 << "You died..." << endl;
						cout << "You lose 10 points for a score of " << points << " points."
		 						 << endl;
						cout << "Game over. Your points accumulated is.." << points << "."
								 << endl;
					}
				}
				else if(thirdchoice == 3)
				{
					cout << endl;
					if(rand() % 2 == 0)
					{
						points-=10;
						cout << "You were too late..While amputating her forearm, the" << endl
								 << "virus had already spread in her body. She woke up and" << endl
								 << "bit you in the neck.. You shot yourself in the head" << endl
						 	 	 << "before you turned.." << endl;
						cout << "You lose 10 points for a score of " << points << " points."
		 						 << endl;
						cout << "Game over. Your points accumulated is.." << points << "."
								 << endl;
					}
					// if rand() % 2 != 0, then fall to this case.
					else
					{
						points+= 50;
						cout << "You are the hero! The wife of the man survived, and" << endl
						 		 << "everyone gets to live." << endl;
						cout << "Congratulations for surviving. Here's 50 points " << endl
			 			 		 << "as a reward." << endl;
						cout << "Your points accumulated is.." << points << "!" << endl;
					}
				}
				// if thirdchoice is other than 1,2, or 3, it will quit the program.
				else
				{
					cout << endl;
					cout << "That is not a valid choice." << endl;
					return 1;
				}
			}
			else if(secondchoice == 3)
			{
				cout << endl;
				cout << "\nYou gain 10 points for a score of " << points << " points." << endl;
				points+= 10;
				if (rand() % 2 == 0)
				{
					cout << endl;
					points-= 10;
					cout << "You died as the man shot you from behind the door" << endl
					 		 << "multiple times, just so they can come in.." << endl;
					cout << "You lose 10 points for a score of " << points << " points."
							 << endl;
					cout << "Game over. Your points accumulated is.." << points << "."
							 << endl;
				}
				// else : rand() % 2 != 0, it will fall under this case.
				else
				{
					cout << endl;
					points+= 50;
					cout << "You threatened them as you stared out from the window." << endl
					 		 << "You saw the man pointing a gun to the door. You shot" << endl
							 << "him and his wife right away.. You survived. " << endl;
					cout << "Congratulations for surviving. Here's 50 points " << endl;
				 	cout << "as a reward." << endl;
					cout << "Your points accumulated is.." << points << "!" << endl;
				}
			}
			// if secondchoice is not 1,2, or 3, it will quit the program.
			else
			{
				cout << endl;
				cout << "That is not a valid choice." << endl;
				return 1;
			}
		}
		// if first choice is anything other than 1 or 2, it quits the program.
		else
		{
			cout << endl;
			cout << "That is not a valid choice." << endl;
			return 1;
		}

		cout << "\nDo you want to play the game again? (0 = Yes / 1 = No)" << endl;
		cin >> replaygame;

		if(replaygame == 1)
		{
			return 0;
		}
	}
}
