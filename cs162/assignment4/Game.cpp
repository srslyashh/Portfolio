#include "Game.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <exception>
#include <stdlib.h>

using namespace std;

/******************************************************
** Function : Game(int, int)
** Description: initialize Game
** Input: int
** Output: initialized members of game
******************************************************/
Game::Game(int inputMode, int inputSize)
{
    srand(time(NULL));
    size = inputSize;
    isGameOver = false;
    wumStatus = true;
    goldFound = false;
    isAdventurerAlive = true;
    mode = inputMode;
    initialRoomCol = rand() % inputSize;
    initialRoomRow = rand() % inputSize;
    arrows = 3;
    initializeBR();
}

/******************************************************
** Function : playMenuTwo()
** Description: Menu for second game
** Input: none
** Output: options for second game
******************************************************/
void Game::playMenuTwo()
{
    printWelcome();
    if(mode == 0)
    {
        while(isGameOver != true)
        {
            printDebugMode();
            printEventsNear();
            printSelection();
        }
    }
    else
    {
        while(isGameOver != true)
        {
            printNormalMode();
            printEventsNear();
            printSelection();
        }
    }
}

/******************************************************
** Function : play()
** Description: play game
** Input: none
** Output: play first Game
******************************************************/
void Game::play()
{
    printWelcome();
    setEvents();
    if(mode == 0)
    {
        while(isGameOver != true)
        {
            printDebugMode();
            printEventsNear();
            printSelection();
        }
    }
    else
    {
        while(isGameOver != true)
        {
            printNormalMode();
            printEventsNear();
            printSelection();
        }
    }
}

/******************************************************
** Function :initializingData()
** Description: initialize data for second g
** Input: none
** Output: initialized members of g
******************************************************/
void Game::initializingData()
{
    
    deleteG();
    isGameOver = false;
    wumStatus = true;
    goldFound = false;
    winGame = false;
    isAdventurerAlive = true;
    arrows = 3;
}

/******************************************************
** Function :getInitialP()
** Description: get initial position
** Input: none
** Output: initialized members of position
******************************************************/
void Game::getInitialP()
{
    position = roomholder[0];
    initialRoomRow = roomholder[0]->getRow();
    initialRoomCol = roomholder[0]->getCol();
    positionRoomRow = initialRoomRow;
    positionRoomCol = initialRoomCol;
}

/******************************************************
** Function :deleteG()
** Description: delete game
** Input: none
** Output: delete game
******************************************************/
void Game::deleteG()
{
    for(unsigned int i = 0; i < evtholder.size(); i++)
    {
        delete evtholder[i];
    }
    evtholder.clear();
}

/******************************************************
** Function :setEventsSecond(int event, int i)
** Description: set second event
** Input: none
** Output: none
******************************************************/
void Game::setEventsSecond(int event, int i)
{
    if(event == 1)
    {
        Rope *r = new Rope();
        evtholder.push_back(r);
        roomholder[i]->setEvent(r,1);
        getInitialP();
    }
    else if(event == 2) // wumpus
    {
        Wumpus *w = new Wumpus();
        evtholder.push_back(w);
        roomholder[i]->setEvent(w,2);
    }
    else if(event == 3)
    {
        Gold *g = new Gold();
        evtholder.push_back(g);
        roomholder[i]->setEvent(g,3);
    }
    else if(event == 4)
    {
        Pits *p = new Pits();
        evtholder.push_back(p);
        roomholder[i]->setEvent(p,4);
    }
    else if(event == 5)
    {
        Bats *b = new Bats();
        evtholder.push_back(b);
        roomholder[i]->setEvent(b,5);
    }

}

/******************************************************
** Function :playSecond()
** Description: play second game
** Input: none
** Output: none
******************************************************/
void Game::playSecond()
{
    initializingData();
    setEventsSecond(1,0);
    setEventsSecond(2,1);
    setEventsSecond(3,2);
    setEventsSecond(4,3);
    setEventsSecond(4,4);
    setEventsSecond(5,5);
    setEventsSecond(5,6);
}

/******************************************************
** Function :eventHeader()
** Description: print event header
** Input: none
** Output: print
******************************************************/
void Game::eventHeader()
{
   cout << endl << "==============================" << endl;
   cout << "|   message(s) from percept   | " << endl;
   cout << "==============================" << endl << endl;
    
}

/******************************************************
** Function : printWelcome()
** Description: print welcome
** Input: none
** Output: print
******************************************************/
void Game::printWelcome()
{
    cout << endl;
    cout << "=====================================" << endl;
    cout << "|            WELCOME TO             |" << endl;
    cout << "|     ~~~~  HUNT THE WUMPUS ~~~~~   |" << endl;
    cout << "=====================================" << endl;
    cout << endl << endl;
}

/******************************************************
** Function : checkIfRope(int mop, int rowOrCol, int &rope)
** Description: check if event is rope
** Input: ints
** Output: none
******************************************************/
void Game::checkIfRope(int mop, int rowOrCol, int &rope)
{
    if(rowOrCol == 0)
    {
        char ch = cave[positionRoomRow + mop][positionRoomCol].getEventP()->getCh();
        if(ch == 'R')
        {
            rope++;
        }
    }
    else if(rowOrCol == 1)
    {
        char ch = cave[positionRoomRow][positionRoomCol+mop].getEventP()->getCh();
        if(ch == 'R')
        {
            rope++;
        }
    }
}

/******************************************************
** Function : printEventsNearTwo(int &totalE, int &rope)
** Description: print events nearby
** Input: ints
** Output: print percepts()
******************************************************/
void Game::printEventsNearTwo(int &totalE, int &rope)
{
    if(positionRoomCol + 1 < size)
    {
        if(cave[positionRoomRow][positionRoomCol + 1].getIsFilled() == true)
        {
            cave[positionRoomRow][positionRoomCol + 1].getEventP()->percept();
            checkIfRope(1,1,rope);
            totalE++;
        }
    }
    if(positionRoomCol - 1 >= 0)
    {
        if(cave[positionRoomRow][positionRoomCol - 1].getIsFilled() == true)
        {
            cave[positionRoomRow][positionRoomCol - 1].getEventP()->percept();
            checkIfRope(-1,1,rope);
            totalE++;
        }
    }
    if(totalE - rope <= 0)
    {
        cout << "No messages" << endl;
    }
    cout << endl;
}

/******************************************************
** Function : printEventsNearTwo(int &totalE, int &rope)
** Description: print events nearby
** Input: ints
** Output: print percepts()
******************************************************/
void Game::printEventsNear()
{
    int totalE = 0, rope = 0;
    eventHeader();
    if(positionRoomRow - 1 >= 0)
    {
        if(cave[positionRoomRow -1][positionRoomCol].getIsFilled() == true)
        {
            cave[positionRoomRow - 1][positionRoomCol].getEventP()->percept();
            checkIfRope(-1,0,rope);
            totalE++;
        }
    }
    if(positionRoomRow + 1 < size)
    {
        if(cave[positionRoomRow + 1][positionRoomCol].getIsFilled() == true)
        {
            cave[positionRoomRow + 1][positionRoomCol].getEventP()->percept();
            checkIfRope(1,0,rope);
            totalE++;
        }
    }
    printEventsNearTwo(totalE, rope);
}

/******************************************************
** Function : initializeBR()
** Description: initialize room
** Input: -
** Output: initialized rooms
******************************************************/
void Game::initializeBR()
{
    for(int i = 0; i < size; i++)
    {
        vector<Room> holder;
        for(int j = 0; j < size; j++)
        {
            holder.push_back(Room(i,j));
        }
        cave.push_back(holder);
    }
}

/******************************************************
** Function : loopCheck(string input, int &destination)
** Description: check loop
** Input: -
** Output: return int
******************************************************/
int Game::loopCheck(string input, int &destination)
{
    int hold = 0;
    stringstream changeToInt(input);
    changeToInt >> hold;

    if(hold == 1 || hold == 2)
    {
        return 0;
    }
    return 1;
}

/******************************************************
** Function : playCheck(string &input, int &destination)
** Description: check option
** Input: -
** Output: loop until value is right
******************************************************/
void Game::playCheck(string &input, int &destination)
{
    int loopAgain = 0;
    while(loopAgain == 0)
    {
        if(loopCheck(input,destination) == 0)
        {
            loopAgain = 1;
            stringstream changeToInt(input);
            changeToInt >> destination;
        }
        else
        {
            cout << "The value you entered wasn't valid." << endl;
            getline(cin,input);
        }
    }
}

/******************************************************
** Function : playAgain(int &again, int &configI)
** Description: playAgain options
** Input: -
** Output: print
******************************************************/
void Game::playAgain(int &again, int &configI)
{
    string input, configS;
    cout << "Do you want to play the game again? (N : 1 / Y = 2)" << endl;
    getline(cin, input);
    playCheck(input, again);

    if(again == 2)
    {
        cout << "Choose one option from below:" << endl;
        cout << "(1) Same cave configuration" << endl;
        cout << "(2) Random cave configuration" << endl;
        getline(cin,configS);
        playCheck(configS,configI);
    }
    else if(again == 1)
    {
        cout << endl << "Goodbye!" << endl;
    }
}

/******************************************************
** Function : roomEmpty(int &randR, int &randC)
** Description: is room empty
** Input: -
** Output: return int
******************************************************/
int Game::roomEmpty(int &randR, int &randC)
{
    srand(time(NULL));
    int loopAgain = 0, rholder = randR, cholder = randC;
    while(loopAgain == 0)
    {
        if(cave[rholder][cholder].getIsFilled() == false)
        {
            randR = rholder;
            randC = cholder;
            loopAgain = 1;
        }
        else
        {
            rholder = rand() % size;
            cholder = rand()% size;
        }
    }
    return 0;
}

/******************************************************
** Function : printNormalChar(int i, int j)
** Description: print char for normal mode
** Input: -
** Output: print
******************************************************/
void Game::printNormalChar(int i, int j)
{
    int positionFilled = 1;
    if(position->getRow() == i && position->getCol() == j)
    {
        cout << "*";
        positionFilled = 0;
    }
    if(positionFilled == 1)
    {
        cout << " ";
    }
}

/******************************************************
** Function : printNormallMode()
** Description: print normal mode
** Input: -
** Output: print
******************************************************/
void Game::printNormalMode()
{
    for(int i = 0; i < size; i++)
    {
        printTopLowBar();
        printInBetween();
        for(int j = 0; j < size; j++)
        {
            if(j == 0)
            {
                cout << "| ";
            }
            printNormalChar(i, j);
            cout << " | ";
        }
        cout << endl;
        printInBetween();
    }
    printTopLowBar();
}

/******************************************************
** Function : setEventsThree(int event, int randR, int randC)
** Description: set Events
** Input: -
** Output: events are set
******************************************************/
void Game::setEventsThree(int event, int randR, int randC)
{
    if(event == 3)
    {
        Gold *g = new Gold();
        evtholder.push_back(g);
        if(roomEmpty(randR,randC) == 0)
        {
            cave[randR][randC].setEvent(g,3);
            roomholder.push_back(&(cave[randR][randC]));
        }
    }
    else if(event == 4)
    {
        Pits *p = new Pits();
        evtholder.push_back(p);
        if(roomEmpty(randR,randC) == 0)
        {
            cave[randR][randC].setEvent(p,4);
            roomholder.push_back(&(cave[randR][randC]));
        }
    }
    else if(event == 5)
    {
        Bats *b = new Bats();
        evtholder.push_back(b);
        if(roomEmpty(randR,randC) == 0)
        {
            cave[randR][randC].setEvent(b,5);
            roomholder.push_back(&(cave[randR][randC]));
        }
    }
}

/******************************************************
** Function : setEventsTwo(int event)
** Description: set Events
** Input: -
** Output: events are set
******************************************************/
void Game::setEventsTwo(int event)
{
    srand(time(NULL));
    int randR = rand() % size;
    int randC = rand() % size;

    if(event == 1) // also rope.
    {
        Rope* r = new Rope();
        evtholder.push_back(r);
        if(roomEmpty(randR,randC) == 0)
        {
            cave[randR][randC].setEvent(r,1);
            roomholder.push_back(&(cave[randR][randC]));
        }
        initialR = (&(cave[randR][randC]));
        position = (&(cave[randR][randC]));
        positionRoomRow = randR;
        positionRoomCol = randC;
        initialRoomRow = randR;
        initialRoomCol = randC;
    }
    else if(event == 2)
    {
        Wumpus* w = new Wumpus();
        evtholder.push_back(w);
        if(roomEmpty(randR,randC) == 0)
        {
            cave[randR][randC].setEvent(w,2);
            roomholder.push_back(&(cave[randR][randC]));
        }
    }
    else if(event == 3 || event == 4 || event == 5)
    {
        setEventsThree(event, randR, randC);
    }
}

/******************************************************
** Function : setEvents()
** Description: set Events
** Input: -
** Output: events are set
******************************************************/
void Game::setEvents()
{
    setEventsTwo(1); // 1 is adventurer
    setEventsTwo(2); // 2 is wumpus
    setEventsTwo(3); // 3 is gold
    setEventsTwo(4); // 4 is pits
    setEventsTwo(4); 
    setEventsTwo(5); // 5 is bats
    setEventsTwo(5); 
}

/******************************************************
** Function : printChar(int i,int j)
** Description: print char for debug mode
** Input: int
** Output: print
******************************************************/
void Game::printChar(int i,int j)
{
    int positionFilled = 1;
    if(position->getRow() == i && position->getCol() == j)
    {
        cout << "*";
        positionFilled = 0;
    }

    if(cave[i][j].getEventNum() != 0 && positionFilled == 1)
    {
        cout << cave[i][j].getEventP()->getCh();
    }
    else if(cave[i][j].getEventNum() == 0 && positionFilled == 1)
    {
        cout << " ";
    }
}

/******************************************************
** Function : printTopLowBar()
** Description: print top and low bars
** Input: -
** Output: print
******************************************************/
void Game::printTopLowBar()
{
    for(int j = 0; j < size; j++)
    {
        if(j == 0)
        {
            cout << "+";
        }
        cout << "---+";
    }
    cout << endl;
}

/******************************************************
** Function : printInBetween()
** Description: print in between
** Input: -
** Output: print
******************************************************/
void Game::printInBetween()
{
    for(int i = 0; i < size; i++)
    {
        if(i == 0)
        {
            cout << "|";
        }
        cout << "   |";
    }
    cout << endl;
}

/******************************************************
** Function : printDebugMode()
** Description: print debug mode
** Input: -
** Output: print
******************************************************/
void Game::printDebugMode()
{
    for(int i = 0; i < size; i++)
    {
        printTopLowBar();
        printInBetween();
        for(int j = 0; j < size; j++)
        {
            if(j == 0)
            {
                cout << "| ";
            }
            printChar(i, j);
            cout << " | ";
        }
        cout << endl;
        printInBetween();
    }
    printTopLowBar();
}

/******************************************************
** Function : setPosition()
** Description: set new position
** Input: -
** Output: print
******************************************************/
void Game::setPosition(Room *newPosition)
{
    position = newPosition;
}

/******************************************************
** Function : getPosition()
** Description: get new position
** Input: -
** Output: address
******************************************************/
Room* Game::getPosition()
{
    return position;
}   

/******************************************************
** Function : checkDirection(const string& input, int &shootArr)
** Description: check if dir is valid
** Input: -
** Output: int
******************************************************/
int Game::checkDirection(const string& input, int &shootArr)
{
    if(input == "s" || input == "w" || input == "a" || input == "d")
    {
        return 0;
    }
    else if(input == " s" || input == " w" || input == " a" || input == " d")
    {
        shootArr = 0;
        return 0;
    }
    else
    {
        return 1;
    }

}

/******************************************************
** Function : loopDirection()
** Description: loop if dir opt is right
** Input: -
** Output: loop
******************************************************/
void Game::loopDirection(string &input, string &destination, int &shootArr)
{
    int loopAgain = 0;
    while(loopAgain == 0)
    {
        if(checkDirection(input, shootArr) == 0)
        {
            loopAgain = 1;
            destination = input;
        }
        else
        {
            cout << "The direction entered wasn't valid. Enter another input: " << endl;
            getline(cin, input);
        }
    }
}

/******************************************************
** Function : settingCurrCol()
** Description: setting new col
** Input: -
** Output: new col
******************************************************/
void Game::settingCurrCol(int minorplus, int row, int col)
{
    setPosition(&(cave[row][col + minorplus]));
    positionRoomRow = row;
    positionRoomCol = col + minorplus;
}

/******************************************************
** Function : settingCurrRow()
** Description: setting new row
** Input: -
** Output: new row
******************************************************/
void Game::settingCurrRow(int minorplus, int row, int col)
{
    setPosition(&(cave[row + minorplus][col]));
    positionRoomRow = row + minorplus;
    positionRoomCol = col;
}

/******************************************************
** Function : outOfBoundsPrint()
** Description: print
** Input: -
** Output:print
******************************************************/
void Game::outOfBoundsPrint()
{
    cout << "The direction you selected was not reachable. :(" << endl << endl;
}

/******************************************************
** Function : isRoomAdjacent()
** Description: direction and move
** Input: st
** Output:print and move
******************************************************/
void Game::isRoomAdjacent(string input)
{
    int currentRow = position->getRow();
    int currentCol = position->getCol();
    if(input == "s") // south
    {
        if(currentRow + 1 < size)
        {
            settingCurrRow(1, currentRow, currentCol);
        }
        else
        {
            outOfBoundsPrint();
        }
    }
    else if(input == "w") // north
    {
        if(currentRow - 1 >= 0)
        {
            settingCurrRow(-1, currentRow, currentCol);
        }
        else
        {
            outOfBoundsPrint();
        }
    }
    isRoomAdjacentTwo(input, currentRow, currentCol);
}

/******************************************************
** Function : isRoomAdjacent()
** Description: direction and move
** Input: st
** Output:print and move
******************************************************/
void Game::isRoomAdjacentTwo(string input, int currentRow, int currentCol)
{
    if(input == "a") // west
    {
        if(currentCol- 1 >= 0)
        {
            settingCurrCol(-1, currentRow, currentCol);
        }
        else
        {
            outOfBoundsPrint();
        }
    }
    else if(input == "d") // east
    {
        if(currentCol + 1 < size)
        {
            settingCurrCol(1, currentRow, currentCol);
        }
        else
        {
            outOfBoundsPrint();
        }
    }
    encounter();
}

/******************************************************
** Function : wumpusMove()
** Description: wumpus move
** Input: st
** Output:print and move
******************************************************/
void Game::wumpusMove()
{
    srand(time(NULL));
    int randNum = rand() % 4;
    int randR = rand() % size;
    int randC = rand() % size;
    Event *w;
    if(randNum != 4) // 75% chance for wumpus to move
    {
        cout << "Oh no! The wumpus woke up after he heard your shot."
             << " He moved to a different room." << endl << endl;
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                if(cave[i][j].getEventNum() == 2)
                {
                    w = cave[i][j].getEventP();
                    cave[i][j].emptyRoom();
                }
            }
        }
        if(roomEmpty(randR, randC) == 0)
        {   
            cave[randR][randC].setEvent(w,2);
        }
    }
    else
    {
        cout << "Whew! Thank goodness the Wumpus didn't wake up!" << endl << endl;
    }
}

/******************************************************
** Function : printwumpStatus()
** Description: print status of wump
** Input: -
** Output:print
******************************************************/
void Game::printWumpStatus(int alreadyD)
{
    if(wumStatus == false && alreadyD == 1)
    {
        cout << "Your arrow killed the Wumpus!" << endl << endl;
    }
    else if(wumStatus == true && alreadyD == 1)
    {
        cout << "Your arrow missed the Wumpus :(" << endl;
        wumpusMove();
    }
}

/******************************************************
** Function : checkWumpus(int num, int rowOrCol)
** Description: check if wumpus is already dead or no
** Input: -
** Output: see if wumpus dead
******************************************************/
void Game::checkWumpus(int num, int rowOrCol, int &alreadyD)
{
    if(rowOrCol == 0)
    {
        if(cave[positionRoomRow+num][positionRoomCol].getEventP()->getCh() == 'W')
        {
            if(wumStatus == false)
            {
                cout << "Wumpus is already dead." << endl;
                alreadyD = 0;
            }
            else if(wumStatus == true)
            {
                wumStatus = false;
            }
        }
    }
    else
    {
        if(cave[positionRoomRow][positionRoomCol+num].getEventP()->getCh() == 'W')
        {
            if(wumStatus == false)
            {
                cout << endl << "Wumpus is already dead." << endl;
                alreadyD = 0;
            }
            else if(wumStatus == true)
            {
                wumStatus = false;
            }
        }
    }
}

/******************************************************
** Function : shootArrowTwo()
** Description: shoot arrow
** Input: -
** Output: see if wumpus dead
******************************************************/
void Game::shootArrowTwo(string direction, int &alreadyD)
{
    int intr = -1;
    if(direction == "a")
    {
        cout << endl << "You fired an arrow to the West" << endl;
        int loop = positionRoomCol - 0;
        for(int i = 0; i < loop; i++)
        {
            if(cave[positionRoomRow][positionRoomCol + intr].getIsFilled() == true)
            {
                checkWumpus(intr,1,alreadyD);
            }
            intr--;
        }
    }
    else if(direction == "w")
    {
        cout << endl << "You fired an arrow to the North" << endl;
        int loop = positionRoomRow - 0;
        for(int i = 0; i < loop; i++)
        {
            if(cave[positionRoomRow + intr][positionRoomCol].getIsFilled() == true)
            {
                checkWumpus(intr,0,alreadyD);
            }
            intr--;
        }
    }
}

/******************************************************
** Function : shootArrowTwo()
** Description: shoot arrow
** Input: -
** Output: see if wumpus dead
******************************************************/
void Game::shootArrow(string direction)
{
    int intr = 1, alreadyD = 1;
    arrows--;
    if(direction == "s")
    {
        cout << endl << "You fired an arrow to the South" << endl;
        int loop = size - (positionRoomRow + 1);
        for(int i = 0; i < loop; i++)
        {
            if(cave[positionRoomRow+intr][positionRoomCol].getIsFilled() == true)
            {
                checkWumpus(intr,0,alreadyD);
            }
            intr++;
        }
    }
    else if(direction == "d")
    {
        cout << endl << "You fired an arrow to the East" << endl;
        int loop = size - (positionRoomCol + 1);
        for(int i = 0; i < loop; i++)
        {
            if(cave[positionRoomRow][positionRoomCol+intr].getIsFilled() == true)
            {
                checkWumpus(intr,1,alreadyD);
            }
            intr++;
        }
    }
    else
    {
        shootArrowTwo(direction,alreadyD);
    }
    printWumpStatus(alreadyD);
}

/******************************************************
** Function : printSelection()
** Description: print
** Input: -
** Output: print
******************************************************/
void Game::printSelection()
{
    string input, finalized, ws, dir;
    string space = " ";
    int shootArr = 1;
    cout << "You have " << arrows << " arrows left." << endl;
    cout << "What would you like to do?" << endl;
    cout << "(W) - move north" << endl;
    cout << "(S) - move south" << endl;
    cout << "(A) - move west" << endl;
    cout << "(D) - move east" << endl;
    cout << "( ) - add a space before any directions to shoot." << endl;
    getline(cin,input);
    loopDirection(input, finalized, shootArr);

    if(shootArr == 0)
    {
        istringstream str(finalized);
        str >> dir;
        if(arrows > 0)
        {
            shootArrow(dir);
        }
        else
        {
            cout << "You have ran out of arrows! Select another option." 
            << endl << endl;
        }
    }
    else if(shootArr == 1)
    {
        isRoomAdjacent(finalized);
    }
}

/******************************************************
** Function : moveEventBat()
** Description: bats move adventurer
** Input: -
** Output: moved adventurer
******************************************************/
void Game::moveEventBat()
{
    int loopAgain = 0;
    srand(time(NULL));

    while(loopAgain == 0)
    {
        int randR = rand() % size;
        int randC = rand() % size;

        if(cave[randR][randC].getEventNum() != 5 || cave[randR][randC].getEventNum() == 0)
        {
            setPosition(&(cave[randR][randC]));
            positionRoomRow = randR;
            positionRoomCol = randC;
            loopAgain = 1;
        }
    }
    encounter();
}

/******************************************************
** Function : encounterTwo()
** Description: print encounter()
** Input: -
** Output: print encounter()
******************************************************/
void Game::encounterTwo()
{
    if(cave[positionRoomRow][positionRoomCol].getEventNum() == 3)
    {
        if(goldFound == false)
        {
            cave[positionRoomRow][positionRoomCol].getEventP()->encounter();
            goldFound = true;
        }
        else if(goldFound == true)
        {
            cout << endl << "You've taken the gold! There's nothing else to take" << endl;
        }
    }
    else if(cave[positionRoomRow][positionRoomCol].getEventNum() == 4)
    {
        cave[positionRoomRow][positionRoomCol].getEventP()->encounter();
        isGameOver = true;
        isAdventurerAlive = false;
        winGame = false;
    }
    else if(cave[positionRoomRow][positionRoomCol].getEventNum() == 5)
    {
        cave[positionRoomRow][positionRoomCol].getEventP()->encounter();
        moveEventBat();
    }
}

/******************************************************
** Function : printEnding()
** Description: print encounter()
** Input: -
** Output: print encounter()
******************************************************/
void Game::printEnding()
{
    if(winGame == true)
    {
        cout << endl <<  "===========================================" << endl;
        cout << "|   CONGRATULATIONS! YOU WON THE GAME! :)  |" << endl;
        cout << "===========================================" << endl << endl;
    }
    else if(winGame == false)
    {
         cout << endl << "===========================================" << endl;
        cout << "|           WOMP WOMP :( YOU LOST         |" << endl;
        cout << "===========================================" << endl << endl;
    }
}

/******************************************************
** Function : encounter()
** Description: print encounter()
** Input: -
** Output: print encounter()
******************************************************/
void Game::encounter()
{
    if(positionRoomRow == initialRoomRow && positionRoomCol == initialRoomCol)
    {
        if(goldFound == true && isAdventurerAlive == true)
        {
            winGame = true;
            isGameOver = true;
        }
        else if(goldFound == true && isAdventurerAlive == true 
        && wumStatus == false)
        {
            winGame = true;
            isGameOver = true;
        }
    }
    else if(cave[positionRoomRow][positionRoomCol].getEventNum() == 2)
    {
        if(wumStatus == true)
        {
            cave[positionRoomRow][positionRoomCol].getEventP()->encounter();
            isGameOver = true;
            isAdventurerAlive = false;
            winGame = false;
        }
        else if(wumStatus == false)
        {
            cout << "You've killed the Wumpus! The stink came from his dead body" << endl;
        }
    }
    encounterTwo();
}