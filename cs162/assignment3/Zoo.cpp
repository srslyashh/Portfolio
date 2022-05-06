#include "Animal.h"
#include "Bear.h"
#include "Tiger.h"
#include "Sealion.h"
#include "Zoo.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

/******************************************************
** Function : Zoo()
** Description: initialize Zoo() - default constructor
** Input: none
** Output: initialized members of zoo
******************************************************/
Zoo::Zoo()
{
    sealion = NULL;
    tiger = NULL;
    bear = NULL;
    balance = 100000;
    numSL = 0;
    numTiger = 0;
    numBear = 0;
    totalFeed = 0;
    bonus = 0;
    quitGame = 0;
}

/******************************************************
** Function : setUpSL()
** Description: setting up sealion
** Input: none
** Output: sl will be set up to sealion arr.
******************************************************/
void Zoo::setUpSL(SeaLion* const& sl, int msl)
{
    if(msl > 0)
    {
        this->sealion = new SeaLion[msl];

        for(int i = 0; i < msl; i++)
		{
			this->sealion[i].setAge(sl[i].getAge());
			this->sealion[i].setCost(sl[i].getCost());
            this->sealion[i].setFoodCost(sl[i].getFoodCost());
            this->sealion[i].setRevenue(sl[i].getRevenue());
            this->sealion[i].setBonus(sl[i].getBonus());
		}
		numSL = msl;
    }
}

/******************************************************
** Function : setUpT()
** Description: setting up tiger
** Input: none
** Output: t will be set up to tiger arr.
******************************************************/
void Zoo::setUpT(Tiger* const& t, int mt)
{
    if(mt > 0)
    {
        tiger = new Tiger[mt];

        for(int i = 0; i < mt; i++)
		{
			this->tiger[i].setAge(t[i].getAge());
			this->tiger[i].setCost(t[i].getCost());
            this->tiger[i].setFoodCost(t[i].getFoodCost());
            this->tiger[i].setRevenue(t[i].getRevenue());
		}
		numTiger = mt;
    }
}

/******************************************************
** Function : setUpB()
** Description: setting up bear arr with *&
** Input: none
** Output: b will be set up to bear arr.
******************************************************/
void Zoo::setUpB(Bear* const& b, int mb)
{
    if(mb > 0)
    {
        bear = new Bear[mb];

        for(int i = 0; i < mb; i++)
		{
			this->bear[i].setAge(b[i].getAge());
			this->bear[i].setCost(b[i].getCost());
            this->bear[i].setFoodCost(b[i].getFoodCost());
            this->bear[i].setRevenue(b[i].getRevenue());
		}
		numBear = mb;
    }
}

/******************************************************
** Function : getQuitG()
** Description: return quit G.
** Input: none
** Output: quitGame.
******************************************************/
int Zoo::getQuitG()
{
    return quitGame;
}

/******************************************************
** Function : Zoo()
** Description: parameterized constructor
** Input: none
** Output: set up all the animal arrays.
******************************************************/
Zoo::Zoo(SeaLion* const &sl, Tiger* const &t, Bear* const &b,
        int msl, int mt,int mb)
{
    setUpSL(sl, msl);
    setUpT(t,mt);
    setUpB(b, mb);
}

/******************************************************
** Function : ~Zoo()
** Description: destroying Zoo()
** Input: none
** Output: zoo destroyed
******************************************************/
Zoo::~Zoo()
{
    if(numSL > 0)
    {
        delete[] sealion;
    }
    this->sealion = NULL;
    if(numTiger > 0)
    {
        delete[] tiger;
    }
    this->tiger = NULL;
    if(numBear > 0)
    {
        delete[] bear;
    }
    this->bear = NULL;
}

/******************************************************
** Function : getAdult()
** Description: see how many animals are adult.
** Input: int
** Output: return int of animals
******************************************************/
int Zoo::getAdult(int animal)
{
    int amount = 0;
    if(animal == 1)
    {
        for(int i = 0; i < numSL; i++)
        {
            if(sealion[i].getAge() >= 48)
            {
                amount++;
            }
        }
    }
    else if(animal == 2)
    {
        for(int i = 0; i < numTiger; i++)
        {
            if(tiger[i].getAge() >= 48)
            {
                amount++;
            }
        }
    }
    else if(animal == 3)
    {
        for(int i = 0; i < numBear; i++)
        {
            if(bear[i].getAge() >= 48)
            {
                amount++;
            }
        }
    }
    return amount;
}

/******************************************************
** Function : getBaby()
** Description: see how many animals are babies.
** Input: int
** Output: return int of animals
******************************************************/
int Zoo::getBaby(int animal)
{
   int amount = 0;
    if(animal == 1)
    {
        for(int i = 0; i < numSL; i++)
        {
            if(sealion[i].getAge() < 6)
            {
                amount++;
            }
        }
    }
    else if(animal == 2)
    {
        for(int i = 0; i < numTiger; i++)
        {
            if(tiger[i].getAge() < 6)
            {
                amount++;
            }
        }
    }
    else if(animal == 3)
    {
        for(int i = 0; i < numBear; i++)
        {
            if(bear[i].getAge() < 6)
            {
                amount++;
            }
        }
    }
    return amount;
}

/******************************************************
** Function : getAdolescent()
** Description: see how many animals are adolescent.
** Input: int
** Output: return int of animals
******************************************************/
int Zoo::getAdolescent(int animal)
{
    int amount = 0;
    if(animal == 1)
    {
        for(int i = 0; i < numSL; i++)
        {
            if(sealion[i].getAge() >= 6 && sealion[i].getAge() < 48)
            {
                amount++;
            }
        }
    }
    else if(animal == 2)
    {
        for(int i = 0; i < numTiger; i++)
        {
            if(tiger[i].getAge() >= 6 && tiger[i].getAge() < 48)
            {
                amount++;
            }
        }
    }
    else if(animal == 3)
    {
        for(int i = 0; i < numBear; i++)
        {
            if(bear[i].getAge() >= 6 && bear[i].getAge() < 48)
            {
                amount++;
            }
        }
    }
    return amount;
}

/******************************************************
** Function : priceFunction()
** Description: return price for animal * quantity.
** Input: int
** Output: return total
******************************************************/
int Zoo::priceFunction(int species, int quantity)
{
    if(species == 1)
    {
        return 800 * quantity;
    }
    else if(species == 2)
    {
        return 15000 * quantity;
    }
    else if(species == 3)
    {
        return 6000 * quantity;
    }
    return 0;
}

/******************************************************
** Function : printInitial()
** Description: initial print
** Input: int
** Output: print
******************************************************/
void Zoo::printInitial()
{
    cout << endl;
    cout << "=======================================" << endl;
    cout << "+             WELCOME TO              +" << endl;
    cout << "+         ~  ZOO TYCOON  ~            +" << endl;
    cout << "=======================================" << endl;
    cout << endl;
}

/******************************************************
** Function : printStatus()
** Description: print Status in every turn.
** Input: none
** Output: print
******************************************************/
void Zoo::printStatus()
{
    if(isBalance0() == true)
    {
        quitGame = 1;
    }
    else
    {
        cout << "On this month you have: " << endl;
        cout << "- Money: $" << balance << endl;
        cout << "- Animals: " << endl;
        cout << "      * Sea lions: " << getBaby(1) << " babies, " << getAdolescent(1) << 
                " adolescents and " << getAdult(1) << " adults." << endl;
        cout << "      * Tigers: " << getBaby(2) << " babies, " << getAdolescent(2) << 
                " adolescents and " << getAdult(2) << " adults." << endl;
        cout << "      * Bears: " << getBaby(3) << " babies, " << getAdolescent(3) << 
                " adolescents and " << getAdult(3) << " adults." << endl;
        printOptions();
    }
}

/******************************************************
** Function : checkOption()
** Description: check if option is valid.
** Input: string, int
** Output: int
******************************************************/
int Zoo::checkOption(const string option, int range)
{
    int holder = 0;
    stringstream changeToInt(option);
    changeToInt >> holder;
    if( 0 < holder && holder <= range)
    {
        return 0;
    }
    return 1;
}

/******************************************************
** Function : loopOption()
** Description: loop until option is valid.
** Input: string, int
** Output: right value
******************************************************/
void Zoo::loopOption(string &option, int &destination, int range)
{
    int loopAgain = 0;
    while(loopAgain == 0)
    {
        if(checkOption(option,range) == 0)
        {
            loopAgain = 1;
            stringstream changeToInt(option);
            changeToInt >> destination;
        }
        else
        {
            cout << "The value you entered wasn't valid. Enter another option:" << endl;
            cin >> option;
        }
    }
}

/******************************************************
** Function : printOptions()
** Description: print options for users
** Input: none
** Output: print
******************************************************/
void Zoo::printOptions()
{
    string option;
    int intOpt;
    cout << endl;
    cout << "Options: " << endl;
    cout << "(1) Buy a species." << endl;
    cout << "(2) Proceed to the next month." << endl;
    cout << "(3) Quit game." << endl;
    cin >> option;
    loopOption(option, intOpt,3);
    if(intOpt == 1)
    {
        buySpeciesOpt();
    }
    else if(intOpt == 2)
    {
        monthEnd();
    }
    else
    {
        cout << "You have chosen to exit the game :(" << endl;
        quitGame = 1;
    }
}

/******************************************************
** Function : checkMoney()
** Description: check if money is enough
** Input: ints
** Output: print
******************************************************/
int Zoo::checkMoney(int feedOrSpe = 0,int option = 0, int quantity = 0)
{
    float price, total = 0;
    // feed is 1 and species is 2.
    // option for species, 1 for sea lion, 2 tiger, 3 black bears
    // option for feed, 1 for cheap, 2 for regular, 3 for premium.
    if(feedOrSpe == 1)
    {
        total = checkingSum(option);
        if(balance > total)
        {
            total = sumFeed(option);
            totalFeed = total;
            return 0;
        }
    }
    else if(feedOrSpe == 2)
    {
        price = priceFunction(option, quantity);
        if(price < balance)
        {
            return 0;
        }
    }
    return 1;
}

/******************************************************
** Function : incrementAge()
** Description: incrementAge()
** Input: none
** Output: age gets incremented
******************************************************/
void Zoo::incrementAge()
{
    for(int i = 0; i < numSL; i++)
    {
        sealion[i].setAge(sealion[i].getAge()+1);
    }
    for(int i = 0; i < numTiger; i++)
    {
        tiger[i].setAge(tiger[i].getAge()+1);
    }
    for(int i = 0; i < numBear; i++)
    {
        bear[i].setAge(bear[i].getAge()+1);
    }
}   

/******************************************************
** Function : subtractFeed()
** Description: subtractFeed()
** Input: none
** Output: balance minus feed costs
******************************************************/
void Zoo::subtractFeed()
{
    balance-= totalFeed;
    cout << endl << "Cost of feed for this month is: $" << totalFeed << endl;
}

/******************************************************
** Function : revenueNotUpdated()
** Description: update revenues + total them together.
** Input: none
** Output: none
******************************************************/
float Zoo::revenueNotUpdated()
{
    float total = 0;
    for(int i = 0; i < numSL; i++)
    {
        if(sealion[i].getAge() == 6 && sealion[i].getRevenue() == 240)
        {
            sealion[i].setRevenue(120);
        }
        total += sealion[i].getRevenue();
    }
    for(int i = 0; i < numTiger; i++)
    {
        if(tiger[i].getAge() == 6 && tiger[i].getRevenue() == 3000)
        {
            tiger[i].setRevenue(1500);
        }
        total += tiger[i].getRevenue();
    }
    for(int i = 0; i < numBear; i++)
    {
        if(bear[i].getAge() == 6 && bear[i].getRevenue() == 1200)
        {
            bear[i].setRevenue(600);
        }
        total += bear[i].getRevenue();
    }
    return total;
}

/******************************************************
** Function : isGameOver()
** Description: check if game is over
** Input: none
** Output: int
******************************************************/
int Zoo::isGameOver()
{
    if(isBalance0() == true)
    {
        return 0;
        quitGame = 1;
    }
    else if(checkEnoughBalance() == 1)
    {
        return 2;
        quitGame = 1;
    }
    return 1;
}

/******************************************************
** Function : GameOver()
** Description: game over print
** Input: int
** Output: print
******************************************************/
void Zoo::GameOver(int exit)
{
    if(exit == 0)
    {
        cout << endl << "=============================================" << endl;
        cout << "+   Game is over. Your zoo went bankrupt :(  +" << endl;
        cout << endl << "=============================================" << endl;
    }
    else if(exit == 2)
    {
        cout << endl << "=====================================================" << endl;
        cout << "+ GAME OVER FOR NOT HAVING ENOUGH MONEY TO PAY FEED +" << endl;
        cout << endl << "=====================================================" << endl;
    }
    else
    {
        cout << endl << "=============================================" << endl;
        cout << "+            SEE YOU NEXT TIME!             +" << endl;
        cout << endl << "=============================================" << endl;
    }
}

/******************************************************
** Function : monthlyRevenue()
** Description: monthly revenue for owner
** Input: none
** Output: balance gets added
******************************************************/
void Zoo::monthlyRevenue()
{
    float totalrev = 0;
    totalrev = revenueNotUpdated();
    cout << "Revenue for this month is: $" << totalrev << endl << endl;
    balance += totalrev;
}

/******************************************************
** Function : printSummary
** Description: print
** Input: none
** Output: - updated -
******************************************************/
void Zoo::printSummary()
{
    cout << endl;
    cout << "=========================================" << endl;
    cout << "+         SUMMARY FOR THIS MONTH        +" << endl;
    cout << "=========================================" << endl;
    cout << endl;
}

/******************************************************
** Function : monthEnd()
** Description: what happens when the month ends
** Input: none
** Output: - updated -
******************************************************/
void Zoo::monthEnd()
{
    if(numSL != 0 || numBear != 0 || numTiger != 0)
    {
        printFeed();
        printSummary();
        subtractFeed();
        incrementAge();
        monthlyRevenue();
    }
}

/******************************************************
** Function : addSeaLion()
** Description: add Sea Lion member
** Input: none
** Output: sea lion gets updated
******************************************************/
void Zoo::addSeaLion()
{
    SeaLion *newarr = new SeaLion[numSL+1];

    if(numSL > 0)
    {
        for(int i = 0; i < numSL; i++)
        {
            newarr[i].setAge(sealion[i].getAge());
			newarr[i].setCost(sealion[i].getCost());
            newarr[i].setFoodCost(sealion[i].getFoodCost());
            newarr[i].setRevenue(sealion[i].getRevenue());
            newarr[i].setBonus(sealion[i].getBonus());
        }
    }
    delete[] sealion;
    sealion = NULL;

    newarr[numSL].setAge(48);
    newarr[numSL].setCost(800);
    newarr[numSL].setFoodCost(80);
    newarr[numSL].setRevenue(120);
    newarr[numSL].setBonus(0);

    sealion = newarr;
    numSL++;
}

/******************************************************
** Function : addTiger()
** Description: add Tiger member
** Input: none
** Output: Tiger gets updated
******************************************************/
void Zoo::addTiger()
{
    Tiger *newarr = new Tiger[numTiger+1];

    if(numTiger > 0)
    {
        for(int i = 0; i < numTiger; i++)
        {
            newarr[i].setAge(tiger[i].getAge());
			newarr[i].setCost(tiger[i].getCost());
            newarr[i].setFoodCost(tiger[i].getFoodCost());
            newarr[i].setRevenue(tiger[i].getRevenue());
        }
    }
    delete[] tiger;
    tiger = NULL;

    newarr[numTiger].setAge(48);
    newarr[numTiger].setCost(15000);
    newarr[numTiger].setFoodCost(80);
    newarr[numTiger].setRevenue(1500);

    tiger = newarr;
    numTiger++;
}

/******************************************************
** Function : addBear()
** Description: add Bear member
** Input: none
** Output: Bear gets updated
******************************************************/
void Zoo::addBear()
{
    Bear *newarr = new Bear[numBear+1];
    if(numBear > 0)
    {
        for(int i = 0; i < numBear; i++)
        {
            newarr[i].setAge(bear[i].getAge());
			newarr[i].setCost(bear[i].getCost());
            newarr[i].setFoodCost(bear[i].getFoodCost());
            newarr[i].setRevenue(bear[i].getRevenue());
        }
    }
    delete[] bear;
    bear = NULL;

    newarr[numBear].setAge(48);
    newarr[numBear].setCost(6000);
    newarr[numBear].setFoodCost(80);
    newarr[numBear].setRevenue(600);

    bear = newarr;
    numBear++;
}

/******************************************************
** Function : addSpecies()
** Description: sort add by the species 
** Input: none
** Output: sort
******************************************************/
void Zoo::addSpecies(int species, int quantity)
{
    for(int i = 0; i < quantity; i++)
    {
        if(species == 1)
        {
            addSeaLion();
        }
        else if(species ==2)
        {
            addTiger();
        }
        else if(species == 3)
        {
            addBear();
        }
    }
}

/******************************************************
** Function : buying species opt
** Description: opt user to buy species
** Input: none
** Output: print
******************************************************/
void Zoo::buySpeciesOpt()
{
    string option, quantity;
    int optSpe, qInt = 0, price, loop = 0;
    cout << endl << "Which species do you want to buy?" << endl;
    cout << "(1) Sea lion - $800" << endl;
    cout << "(2) Tiger - $15000" << endl;
    cout << "(3) Black bears - $6000" << endl;
    cin >> option;
    loopOption(option, optSpe, 3);
    cout << endl << "How many species do you want? (1-2): " << endl;
    cin >> quantity;
    loopOption(quantity, qInt, 2);
    while(loop == 0)
    {
        if(checkMoney(2,optSpe,qInt)==0)
        {
            addSpecies(optSpe, qInt);
            price = priceFunction(optSpe, qInt);
            balance-= price;
            loop = 1;
        }
        else
        {
            cout << "Your money is not enough. Please enter another value." << endl;
            cin >> option;
            loopOption(option, optSpe, 3);
        }
    }
    monthEnd();
}

/******************************************************
** Function : printFeed()
** Description: prompt user to choose which feed to buy.
** Input: none
** Output: print
******************************************************/
void Zoo::printFeed()
{
    string option;
    int OptInt, loop = 0;
    cout << endl << "Before proceeding to the next month, which feed would you like "
         << "to give your animal?" << endl;
    cout << "(1) Cheap - costs half as much as regular." << endl;
    cout << "(2) Regular" << endl;
    cout << "(3) Premium - costs twice as much as regular." << endl;
    cin >> option;
    loopOption(option, OptInt, 3);
    while(loop == 0)
    {
        if(checkEnoughBalance() == 1 || isBalance0() == true)
        {
            cout << "NOT ENOUGH" << endl;
            quitGame = 1;
            loop = 1;
        }
        else if(checkEnoughBalance() == 0)
        {
            if(checkMoney(1,OptInt, 0)==0)
            {
                loop = 1;
            }
            else
            {
                cout << "Your money is not enough. Please choose another type of feed" << endl;
                cin >> option;
                loopOption(option, OptInt, 3);
            }
        }
    }
}

/******************************************************
** Function : checkEnoughBalance()
** Description: check if user got enough balance.
** Input: none
** Output: print
******************************************************/
int Zoo::checkEnoughBalance()
{
    if(balance < checkingSum(1))
    {
        return 1;
    }
    return 0;
}

/******************************************************
** Function : checkingSum(float feed)
** Description: checking if sum is enough for balance.
** Input: float
** Output: return float
******************************************************/
float Zoo::checkingSum(float feed)
{
    float price = feedOption(feed);
    float total = 0;
    int holder = 0;
    if(numSL > 0)
    {
        for(int i = 0; i < numSL; i++)
        {
            sealion[i].checkerSum(price);
            holder = sealion[i].getFoodCost() * 1;
            total += holder;
        }
    }
    if(numTiger > 0)
    {
        for(int i = 0; i < numTiger; i++)
        {
            tiger[i].checkerSum(price);
            holder = tiger[i].getFoodCost() * 5;
            total += holder;
        }
    }
    if(numBear > 0)
    {
        for(int i = 0; i < numBear; i++)
        {
            bear[i].checkerSum(price);
            holder = bear[i].getFoodCost() * 2;
            total += holder;
        }
    }
    return total;
}

/******************************************************
** Function : feedOption(float feed)
** Description: option for feed 
** Input: none
** Output: return how much option is worth
******************************************************/
float Zoo::feedOption(float feed)
{
    float price = 0;
    if(feed == 1)
    {
        price = 0.5;
    }
    else if(feed == 2)
    {
        price = 1;
    }
    else
    {
        price = 2;
    }
    return price;
}

/******************************************************
** Function : bonusSL()
** Description: bonus for sea lion
** Input: none
** Output: rand and get bonus
******************************************************/
void Zoo::bonusSL()
{
    cout << "There's a boom in the zoo attendance! You received extra revenue!" << endl;
    float total = 0;
    for(int i = 0; i < numSL; i++)
    {
        sealion[i].randBonus();
        total += sealion[i].getBonus();
    }
    bonus = total;
    cout << endl << "You received $" << total << " as bonus!" << endl << endl;
}

/******************************************************
** Function : sumFeed(float feed)
** Description: sum all the feed together.
** Input: none
** Output: summed feed
******************************************************/
float Zoo::sumFeed(float feed)
{
    float price = feedOption(feed);
    float total = 0;
    float holder = 0;
    
    if(numSL > 0)
    {
        for(int i = 0; i < numSL; i++)
        {
            sealion[i].newFoodSL(price);
            holder = sealion[i].getFoodCost();
            holder *= 1;
            total += holder;
        }
    }
    if(numTiger > 0)
    {
        for(int i = 0; i < numTiger; i++)
        {
            tiger[i].newFoodT(price);
            holder = tiger[i].getFoodCost();
            holder *= 5;
            total += holder;
        }
    }
    if(numBear > 0)
    {
        for(int i = 0; i < numBear; i++)
        {
            bear[i].newFoodB(price);
            holder = bear[i].getFoodCost();
            holder *= 3;
            total += holder;
        }
    }
    return total;
}


/******************************************************
** Function : eventPrint(int n)
** Description: print events
** Input: int
** Output: print
******************************************************/
void Zoo::eventPrint(int n)
{
    if(n == 1)
    {
        cout << endl;
        cout << "========================================" << endl;
        cout << "+  NO EVENT HAPPENED DURING THIS MONTH +" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
    else if(n == 0)
    {
        cout << endl;
        cout << "========================================" << endl;
        cout << "+  AN EVENT HAPPENED DURING THIS MONTH +" << endl;
        cout << "========================================" << endl;
        cout << endl;
    }
}

/******************************************************
** Function : doesAExist(int species)
** Description: check if species exist
** Input: int
** Output: return int 
******************************************************/
int Zoo::doesAExist(int species)
{
    if(species == 1)
    {
        if(numSL > 0)
        {
            return 0;
        }
    }
    else if(species == 2)
    {
        if(numTiger > 0)
        {
            return 0;
        }
    }
    else
    {
        if(numBear > 0)
        {
            return 0;
        }
    }
    return 1;
}

/******************************************************
** Function : getName(int species)
** Description: return string name.
** Input: int
** Output: return string
******************************************************/
string Zoo::getName(int species)
{
    if(species == 1)
    {
        return "sea lion";
    }
    else if(species == 2)
    {
        return "tiger";
    }
    else
    {
        return "bear";
    }
}

/******************************************************
** Function : bill for sl.
** Description: bill for sick animals.
** Input: int
** Output: return float
******************************************************/
float Zoo::billSL(int &randS)
{
    for(int i = 0; i < numSL; i++)
    {
        if(sealion[i].getAge() != 0 && sealion[i].getAge() < 6)
        {
            i = randS;
            return 800;
        }
    }
    return 400;
}

/******************************************************
** Function : billTiger()
** Description: bill for sick animals -tiger
** Input: int
** Output: return float
******************************************************/
float Zoo::billTiger(int &randS)
{
    for(int i = 0; i < numTiger; i++)
    {
        if(tiger[i].getAge() != 0 && tiger[i].getAge() < 6)
        {
            i = randS;
            return 15000;
        }
    }
    return 7500;
}

/******************************************************
** Function : billBear()
** Description: bill for sick animals -bear
** Input: int
** Output: return float
******************************************************/
float Zoo::billBear(int &randS)
{
    for(int i = 0; i < numTiger; i++)
    {
        if(bear[i].getAge() != 0 && bear[i].getAge() < 6)
        {
            i = randS;
            return 6000;
        }
    }
    return 3000;
}

/******************************************************
** Function : bill(int species, int &randS)
** Description: bill for sick animals.
** Input: int
** Output: return float
******************************************************/
float Zoo::bill(int species, int &randS)
{
    if(species == 1)
    {
        return billSL(randS);
    }
    else if(species == 2)
    {
        return billTiger(randS);
    }
    else
    {
        return billBear(randS);
    }
    return 1;
}

/******************************************************
** Function : removeSeaLion(int index)
** Description: remove sea lion.
** Input: int
** Output: removed sea lion.
******************************************************/
void Zoo::removeSeaLion(int index)
{
    if(numSL > 0)
    {
        SeaLion *newarr = new SeaLion[numSL-1];
        int counter = 0;

        sealion[index].emptySL();

        for(int i = 0; i < numSL; i++)
        {
            if(i != index)
            {
                newarr[counter].setAge(sealion[i].getAge());
                newarr[counter].setCost(sealion[i].getCost());
                newarr[counter].setFoodCost(sealion[i].getFoodCost());
                newarr[counter].setRevenue(sealion[i].getRevenue());
                newarr[counter].setBonus(sealion[i].getBonus());
                counter++;
            }
        }

        delete[] sealion;
        sealion = NULL;
        sealion = newarr;
        numSL--;
    }
}

/******************************************************
** Function : rremoveTiger(int index)
** Description: remove tiger
** Input: int
** Output: removed tiger
******************************************************/
void Zoo::removeTiger(int index)
{
    if(numTiger > 0)
    {
        Tiger *newarr = new Tiger[numTiger-1];
        int counter = 0;

        tiger[index].emptyAnimal();

        for(int i = 0; i < numTiger; i++)
        {
            if(i != index)
            {
                newarr[counter].setAge(tiger[i].getAge());
                newarr[counter].setCost(tiger[i].getCost());
                newarr[counter].setFoodCost(tiger[i].getFoodCost());
                newarr[counter].setRevenue(tiger[i].getRevenue());
                counter++;
            }
        }

        delete[] tiger;
        tiger = NULL;
        tiger = newarr;
        numTiger--;
    }
}

/******************************************************
** Function : rremoveBear(int index)
** Description: remove bear
** Input: int
** Output: removed bear
******************************************************/
void Zoo::removeBear(int index)
{
    if(numBear > 0)
    {
        Bear *newarr = new Bear[numBear-1];
        int counter = 0;

        bear[index].emptyAnimal();

        for(int i = 0; i < numBear; i++)
        {
            if(i != index)
            {
                newarr[counter].setAge(bear[i].getAge());
                newarr[counter].setCost(bear[i].getCost());
                newarr[counter].setFoodCost(bear[i].getFoodCost());
                newarr[counter].setRevenue(bear[i].getRevenue());
                counter++;
            }
        }

        delete[] bear;
        bear = NULL;
        bear = newarr;
        numBear--;
    }
}

/******************************************************
** Function : removeSpecies(int species, int index)
** Description: sort remove by species.
** Input: int
** Output: sort
******************************************************/
void Zoo::removeSpecies(int species, int index)
{
    if(species == 1)
    {
        removeSeaLion(index);
    }
    else if(species == 2)
    {
        removeTiger(index);
    }
    else if(species == 3)
    {
        removeBear(index);
    }
}

/******************************************************
** Function : animalSick(int species)
** Description: animal sick function
** Input: int
** Output: cure or kill animal
******************************************************/
void Zoo::animalSick(int species)
{
    int randS = 0, intOpt;
    float bill2;
    string option;
    cout << "Your " << getName(species) << " just got sick."
         << "Would you like to cure him?" << endl;
    cout << "(1) Yes." << endl;
    cout << "(2) No." << endl;
    cin >> option; 
    loopOption(option, intOpt, 2);
    if(intOpt == 1)
    {
        bill2 = bill(species,randS);
        if(balance < bill2)
        {
            cout << "You cannot pay for the bill. :(" << endl;
            intOpt = 2;
        }
        balance-=bill2;
        cout << endl << "You paid $" << bill2 << " to cure your animal." << endl;
        cout << endl <<  " ****** Your animal has been cured! :) ******" << endl << endl;
    }
    if(intOpt == 2)
    {
        cout << endl << "Your animal has died. It's getting buried out of the zoo." 
             << endl << endl;
        removeSpecies(species, randS);
    }
}

/******************************************************
** Function : addSLB()
** Description: add sealion baby
** Input: int
** Output: add sealion baby
******************************************************/
void Zoo::addSLB()
{
    SeaLion *newarr = new SeaLion[numSL+1];

    if(numSL > 0)
    {
        for(int i = 0; i < numSL; i++)
        {
            newarr[i].setAge(sealion[i].getAge());
			newarr[i].setCost(sealion[i].getCost());
            newarr[i].setFoodCost(sealion[i].getFoodCost());
            newarr[i].setRevenue(sealion[i].getRevenue());
            newarr[i].setBonus(sealion[i].getBonus());
        }
    }
    delete[] sealion;
    sealion = NULL;

    newarr[numSL].setAge(0);
    newarr[numSL].setCost(800);
    newarr[numSL].setFoodCost(80);
    newarr[numSL].setRevenue(240);
    newarr[numSL].setBonus(0);

    sealion = newarr;
    numSL++;
}

/******************************************************
** Function : addTB()
** Description: add TIGER baby
** Input: int
** Output: add tiger baby
******************************************************/
void Zoo::addTB()
{
    Tiger *newarr = new Tiger[numTiger+1];

    if(numTiger > 0)
    {
        for(int i = 0; i < numTiger; i++)
        {
            newarr[i].setAge(tiger[i].getAge());
			newarr[i].setCost(tiger[i].getCost());
            newarr[i].setFoodCost(tiger[i].getFoodCost());
            newarr[i].setRevenue(tiger[i].getRevenue());
        }
    }
    delete[] tiger;
    tiger = NULL;

    newarr[numTiger].setAge(0);
    newarr[numTiger].setCost(15000);
    newarr[numTiger].setFoodCost(80);
    newarr[numTiger].setRevenue(3000);

    tiger = newarr;
    numTiger++;
}

/******************************************************
** Function : addBB()
** Description: add bear baby
** Input: int
** Output: add bear baby
******************************************************/
void Zoo::addBB()
{
    Bear *newarr = new Bear[numBear+1];

    if(numBear > 0)
    {
        for(int i = 0; i < numBear; i++)
        {
            newarr[i].setAge(bear[i].getAge());
			newarr[i].setCost(bear[i].getCost());
            newarr[i].setFoodCost(bear[i].getFoodCost());
            newarr[i].setRevenue(bear[i].getRevenue());
        }
    }
    delete[] bear;
    bear = NULL;

    newarr[numBear].setAge(0);
    newarr[numBear].setCost(6000);
    newarr[numBear].setFoodCost(80);
    newarr[numBear].setRevenue(1200);

    bear = newarr;
    numBear++;
}

/******************************************************
** Function : giveBirth(int species)
** Description: GIVE BIRTH
** Input: int
** Output: add baby 
******************************************************/
void Zoo::giveBirth(int species)
{
    cout << "Congratulations! Your animal just gave birth(s)!" << endl << endl;
    if(species == 1)
    {
        addSLB();
    }
    else if(species == 2)
    {
        for(int i = 0; i < 3; i++)
        {
            addTB();
        }
    }
    else if(species == 3)
    {
        for(int i = 0; i < 2; i++)
        {
            addBB();
        }
    }
}

/******************************************************
** Function : randomEvent()
** Description: randomize event.
** Input: none
** Output: depend
******************************************************/
void Zoo::randomEvent()
{
    srand(time(0));
    int loop = 0;
    while(loop == 0)
    {
        int random = rand()% 4 + 1;
        int randS = rand() % 3 + 1;
        if(random == 1)
        {
            if(doesAExist(randS) == 0)
            {
                eventPrint(0);
                animalSick(randS);
                loop = 1;
            }
        }
        else if(random == 2)
        {
            if(getAdult(randS) == 2)
            {
                eventPrint(0);
                giveBirth(randS);
                loop = 1;
            }
        }
        else if(random == 3 || random == 4)
        {
            randomEventTwo(loop, random);
        }
    }
}

/******************************************************
** Function : randomEvent()
** Description: randomize event.
** Input: none
** Output: depend
******************************************************/
void Zoo::randomEventTwo(int &loop, int random)
{
    if(random == 3)
    {
        if(doesAExist(1) == 0)
            {
                eventPrint(0);
                bonusSL();
                balance += bonus;
                bonus = 0;
                loop = 1;
            }
    }
    else
    {
        eventPrint(1);
        loop = 1;
    }
}

/******************************************************
** Function : isBalance0()
** Description: isbalance 0 check
** Input: none
** Output: return val
******************************************************/
bool Zoo::isBalance0()
{
    if(balance == 0 || balance < 0)
    {
        return true;
    }
    return false;
}