/******************************************************
** Program: C++ LINKED LIST IMPLEMENTATION
** Author: Kathleen Ashley
** Date: 12/07/2020
** Description: Keep data in linked list
** Input: options
** Output: A sorted linked list, and total numbers of prime!
******************************************************/

#include "Node.h"
#include "Linked_List.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <exception>

using namespace std;

int main()
{
    int loopAgain = 0;
    
    while(loopAgain == 0)
    {
        Linked_List game;
        game.initialQ();
        while(game.addMore() == 0)
        {
            game.memberOption();
        }
        game.sortQ();
        game.print();
        game.printPrime();
        game.playAgain(loopAgain);
        game.clear();
    }
    cout << endl << "BYE-BYE! :)" << endl;
    return 0;
}